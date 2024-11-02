
#ifndef PRESET_TABLE_H
#define PRESET_TABLE_H

#define NUM_PRESETS 6


static const float amp_attack_val_table[6] = { 0.015f, 0.001f, 0.001f, 0.001f, 0.015f, 0.0f,  };


static const float amp_decay_val_table[6] = { 0.779f, 0.779f, 3.0f, 1.0f, 0.4f, 2.89f,  };


static const float base_pitch_val_table[6] = { 45.0f, 45.0f, 52.0f, 37.0f, 30.0f, 40.0f,  };


static const float drive_val_table[6] = { 0.0f, 0.0f, 0.05f, 0.05f, 0.1f, 0.0f,  };


static const float mod_decay_val_table[6] = { 0.7f, 0.7f, 0.7f, 0.6f, 2.0f, 0.2f,  };


static const float mod_pitch_val_table[6] = { 0.0f, 0.0f, 773.0f, 200.0f, 1700.0f, 76.0f,  };


static const float mod_pitch_amt_table[6] = { 0.0f, 0.0f, 0.0f, 0.0005f, 0.005f, 0.005f,  };


static const float pmod_amt_val_table[6] = { 20.0f, 0.0f, 300.0f, 300.0f, 1500.0f, 100.0f,  };


static const float pitch_decay_val_table[6] = { 0.01f, 0.01f, 0.01f, 0.004f, 0.01f, 0.01f,  };


static const float pitch_sustain_val_table[6] = { 20.0f, 20.0f, 10.0f, 20.0f, 80.0f, 35.0f,  };


static const float pitch_release_val_table[6] = { 0.6f, 0.6f, 2.0f, 2.0f, 0.8f, 0.89f,  };


static const float svf1_val_table[6] = { 0.01f, 0.01f, 0.01f, 0.0176f, 0.01f, 0.01f,  };


static const float svf2_val_table[6] = { 0.2f, 0.2f, 0.25f, 0.108f, 0.06f, 0.148f,  };



#endif /* PRESET_TABLE_H */
