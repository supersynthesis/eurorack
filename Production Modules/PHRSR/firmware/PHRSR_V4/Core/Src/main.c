#include "stm32f30x.h"

#include <expo_lut.h>
#include <stm32F334_config.h>

//defaults

#define NUM_STEPS			16
#define RATE_MULTIPLIER		1
#define RATE_OFFSET			16000
#define CLOCK_SHIFT			5
#define EXPONENT			1.9

/*

 // phraser can be smooth and continuous vs 16 steps if you set it up thusly
 // triggers will get all wrong though!

 #define NUM_STEPS			1024
 #define RATE_MULTIPLIER		50
 #define RATE_OFFSET			55000
 #define CLOCK_SHIFT			2
 #define EXPONENT			1.8
 */

volatile uint16_t seq_a[NUM_STEPS];
volatile uint16_t seq_b[NUM_STEPS];
volatile uint16_t new_seq_b_order = 0;
volatile uint16_t new_seq_a_order = 0;
volatile uint16_t rate_pot_val, DC_pot_val;
volatile uint32_t seq_phase_accumulator;
volatile uint32_t seq_phase_increment;
volatile uint16_t seq_index, seq_a_index, seq_b_index;
volatile uint16_t seq_a_start, seq_b_start;
volatile uint16_t seq_a_count, seq_b_count;
volatile uint16_t seq_a_length = NUM_STEPS;
volatile uint16_t new_seq_a_length = NUM_STEPS;
volatile uint16_t seq_b_length = NUM_STEPS;
volatile uint16_t new_seq_b_length = NUM_STEPS;
volatile uint16_t period_width, width_count, clk_width_count;
volatile float period_max;

#define CLOCK_WIDTH

volatile uint8_t left_button_state, right_button_state, steps_button_state,
		clk_in_state, last_clk_in_state, last_steps_button_state,
		last_left_button_state, last_right_button_state;

volatile uint8_t steps_a_flag = 0;
volatile uint8_t steps_b_flag = 0;

volatile uint16_t this_time, last_time;

volatile uint8_t clk_out, last_clk_out;
volatile int8_t delayed_clk;

void SysTick_Handler() {
	//system tick
}

void loop() {
}

const int16_t tanh_table[256];

void setup() {
	GPIO_Config();
	DAC_Config();
	TIM_Config();
	ADC_Config();
	NVIC_Config();
	SysTick_Config(SystemCoreClock / 100000);
}

int main(void) {
	setup();
	while (1) {
		loop();
	}
}

void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

		//grab our buttons
		left_button_state = GPIO_ReadInputDataBit(GPIOB, LEFT_BUTTON);
		right_button_state = GPIO_ReadInputDataBit(GPIOA, RIGHT_BUTTON);
		steps_button_state = GPIO_ReadInputDataBit(GPIOA, STEPS_BUTTON);
		clk_in_state = GPIO_ReadInputDataBit(GPIOB, CLOCK_IN);

		//grab our pots
		rate_pot_val += (ADC[1] - rate_pot_val) * 0.02f;
		DC_pot_val += (ADC[0] - DC_pot_val) * 0.02f;

		// if we get a low to high transition on clock input
		// note: unorthodox clock output here. in order to delay the actual clock output by one sample,
		// we set a high clock to 2, and a low clock to -2. at the end of this handler, we decrement or
		// increment, and compare against +/-1 for the actual dac output of the clock. this is to fix
		// the accidentally slow filter on the main dac outputs, causing them to always be a touch
		// behind the clock output. woopsies!
		if (clk_in_state == 0) {
			if (last_clk_in_state == 1) {
				//set phase of dds to 0
				seq_phase_accumulator = 0;
				//increment step
				step_increment();
				//set clock output high
				delayed_clk = 2;
			}
		} else {
			//if we get a high to low transition on clock input
			if (last_clk_in_state == 0) {
				//set clock output low
				delayed_clk = -2;
			}
		}

		//in fast loop:
		//if steps is pressed
		if (steps_button_state == 0) {

			//if left button is pressed
			if (left_button_state == 0) {
				//	and last left button was not pressed
				if (last_left_button_state == 1) {
					steps_a_flag = 1;
					seq_a_length = 1;
					seq_a_start = seq_a_index;
					seq_a_count = 0;
				} else {
					//else if steps was pressed but now isn't
					if (last_steps_button_state == 0) {

					}
				}
			} else {
				//if left button is not pressed
				if (left_button_state == 1) {
					//and left button was pressed
					if (last_left_button_state == 0) {
						steps_a_flag = 0;
						//seq_a_length++;
					}
				}
			}

			//if right button is pressed
			if (right_button_state == 0) {
				//	and right button was not pressed
				if (last_right_button_state == 1) {
					steps_b_flag = 1;
					seq_b_length = 1;
					seq_b_start = seq_b_index;
					seq_b_count = 0;
				} else {
					//else if steps was pressed
					if (last_steps_button_state == 0) {
					}
				}
			} else {
				//if right button is not pressed
				if (right_button_state == 1) {
					//if right button was pressed
					if (last_right_button_state == 0) {
						//lower steps pressed flag
						steps_b_flag = 0;
						//seq_b_length++;
					}
				}
			}
		} else {
			if (last_steps_button_state == 0) {
				if (left_button_state == 0) {
					//lower steps pressed flag
					steps_a_flag = 0;
					//seq_a_length++;
				}
				if (right_button_state == 0) {
					//lower steps pressed flag
					steps_b_flag = 0;
					//seq_b_length++;
				}
			}
		}

		//update dds stuff
		clk_out = (seq_phase_accumulator >> (32 - CLOCK_SHIFT)) & 1;
		//seq_phase_increment = (rate_pot_val * 235) + 21000;
		seq_phase_increment = pow(rate_pot_val, EXPONENT) + RATE_OFFSET;
		seq_phase_accumulator += seq_phase_increment * RATE_MULTIPLIER;

		//clock out

		//if clk_out is 0
		if (clk_out == 0) {
			//and last was 1
			if (last_clk_out == 1) {
				//increment our step
				step_increment();
				//and set clock output high
				delayed_clk = 2;
			}
		} else {
			//else clk_out is 1, if it last was 0
			if (last_clk_out == 0) {
				//set clock output low
				delayed_clk = -2;
			}
		}

		last_clk_in_state = clk_in_state;
		last_clk_out = clk_out;
		last_steps_button_state = steps_button_state;
		last_left_button_state = left_button_state;
		last_right_button_state = right_button_state;

		if (delayed_clk > 0) {
			if (delayed_clk == 1) {
				DAC_SetChannel1Data(DAC2, DAC_Align_12b_R, 4095);
			}
			delayed_clk--;
		}

		if (delayed_clk < 0) {
			if (delayed_clk == -1) {
				DAC_SetChannel1Data(DAC2, DAC_Align_12b_R, 0);
			}
			delayed_clk++;
		}
	}

}

void DMA1_Channel1_IRQHandler(void) {
	/* Test on DMA1 Channel1 Transfer Complete interrupt */
	if (DMA_GetITStatus(DMA1_IT_TC1)) {
		/* Clear DMA1 Channel1 Transfer Complete pending bit */
		DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
}

void step_increment() {
	//DAC_SetChannel1Data(DAC2, DAC_Align_12b_R, 4095);

	//increment all the steps
	seq_index++;
	seq_a_index++;
	seq_b_index++;
	seq_a_count++;
	seq_b_count++;

	seq_a_index &= NUM_STEPS - 1;
	seq_b_index &= NUM_STEPS - 1;

	if (seq_a_length >= NUM_STEPS) {
		seq_a_length = NUM_STEPS;
	}
	if (seq_b_length >= NUM_STEPS) {
		seq_b_length = NUM_STEPS;
	}

	//	if steps pressed flag is raised
	if (steps_a_flag == 1) {
		//increment sequence length
		seq_a_length++;
		if (seq_a_length >= NUM_STEPS) {
			seq_a_length = NUM_STEPS;
		}
	} else if (seq_a_count >= seq_a_length) {
		if (seq_a_length != NUM_STEPS) {
			seq_a_index = seq_a_start;
			seq_a_count = 0;
		}
	}

	//	if steps pressed flag is raised
	if (steps_b_flag == 1) {
		//increment sequence length
		seq_b_length++;
		if (seq_b_length >= NUM_STEPS) {
			seq_b_length = NUM_STEPS;
		}
	} else if (seq_b_count >= seq_b_length) {
		if (seq_b_length != NUM_STEPS) {
			seq_b_index = seq_b_start;
			seq_b_count = 0;
		}
	}

	if (steps_a_flag == 0) {
		if (left_button_state == 0) {
			seq_a[seq_a_index] = DC_pot_val;
		}
	}

	if (steps_b_flag == 0) {
		if (right_button_state == 0) {
			seq_b[seq_b_index] = DC_pot_val;
			//seq_c[seq_index] = DC_pot_val;
		}
	}

	DAC_SetChannel1Data(DAC1, DAC_Align_12b_R, seq_b[seq_b_index]);
	DAC_SetChannel2Data(DAC1, DAC_Align_12b_R, seq_a[seq_a_index]);
}
