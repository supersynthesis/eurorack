If you're not making any modifications, use STM32CubeProgrammer to flash the .elf file and you'll be good to go. This is the recommended approach! This is the recommended approach! Make sure to match the REV (either REV4 or REV5) to your hardware. REV5 is harder to solder by hand, but includes a V/OCT jumper and is the recommended version. 


The .elfs are named according to hardware version, but the folders of source code are named consistent with their STM32CubeIDE projects. 2OPFM_G431 is the latest, 2OPFM_2020 is older. I will eventually put detailed import and build instructions up, but for now: 

1: Import the project to STM32CubeIDE

2: Make sure optimization is set to "For Speed" 

3: Build and run it! 

These obviously assume familiarity with the process. 
If you are not and have questions about how to get it rolling, please don't hesitate to reach out (but google first!) 

You may notice that this code is organized poorly, and I may agree. Instead of doing a song and dance to provide
something especially clean, I wanted to share what the 2OPFM module really is and how it does its thang. 
