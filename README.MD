# Open Source firmware replacement for Cricut(tm) Personal cutter machines. #

----------

**IMPORTANT: REPROGRAMMING THE CPU WILL PERMANENTLY ERASE YOUR ORIGINAL FIRMWARE
THERE IS NO WAY TO GET THE ORIGINAL FIRMWARE BACK OTHER THAN BUYING ANOTHER MACHINE.** 

**About the Cricut** 

Cricut cutting machines can be had for about $50 or less on Craigslist.  They contain two stepper motors, a moving solenoid powered knife holder that generates 12 volts to the solenoid using PWM.  They typically contain wheels that control speed, pressure, and other settings (one of them is usually an optical encoder, the others are potentiometers), a display of sorts, and a keyboard that has a ton of fairly useless buttons with green LED backlights.  Additionally, an onboard USB port and the Atmel ATMega1281 chip running at 16mhz provides all the horsepower you would need.  The stepper motors are controlled by eight mosfets.  So in reality, you get a fairly decent XY controller board with a PWM output for solenoid or laser control for cheap!  One of my future plans are to put a laser diode in place of the knife holder and see what I can do with it.

*******************************************************************************
1/29/2023 - Ported Firmware back to Cricut Personal from https://github.com/thetazzbot/FreeExpression, got the original Cricut LCD and keypad working with nice feedback, including pressure and speed settings as well as media states etc. This port will not support the Expression, or cake models at this time, with modification it could probably be made to support those options again as well.  My work was just very targeted. Some of the features in this port are untested, primarily the portions regarding Flash and the gcode stuff.  If you use HPGL, it works great.  Updated Readme to include some basic info from my own experiences, added Keypad Overlay image for reference, and will include the compiled hex(in the release directory) for those only wishing to flash the firmware.  I hope this helps others wishing to utilise the Cricut personal more easily.  Please see my notes below regarding board modifications necissary for programming, Which I have personally not seen documented elsewhere, and had to figure out on my own.  -AL 

4/17/2019 - The edge connector at the front of the machine appears to be a very close match to a TE CONN SEC II 10 POS 100C/L found here.. https://www.te.com/usa-en/product-5-5530843-0.html

3/25/2019 - Updated the project settings and files to include contributions from Gary Stofer, for his Cricut Cake Mini machine that uses a different display and button layout, as well as GCode parser.  Compiled with Atmel Studio 7, all compile errors resolved and verified it uploads to the machine and runs.  Still have to perform testing because my machine is currently not responding to button or dial changes, so either the code is flawed somewhere or my machine is (which is not impossible, as I have had it opened and mistreated it with a soldering iron several times).

1/13/2019
Updated project to Atmel Studio 7

6/11/2017 
Merged pull request from Gary Stofer to improve HGPL reliability

Previous notes:

Original firmware cannot be copied from another machine (it has been
locked and cannot be read from the CPU)

Original firmware cannot be restored through any PC application used for normal firmware upgrades.

This firmware has only been tested on the machine that I have. It may not work on your machine.  It may cause permanent damage, and it
will certainly void your warranty.

This firmware cannot read your original cartridges ever.

Cricut is a trademark of PROVO CRAFT and this firmware is **not** a PROVO CRAFT product. This firmware  was developed completely independently, without any documentation of PROVO CRAFT products, and without any and all original firmware. If you have problems with this firmware, do not consult PROVO CRAFT. 

Originally was forked from https://github.com/Arlet/Freecut  

The recent updates include the option of using a Standard 4x20 LCD with a SPI interface (Cricut CAKE)  or the original Oled graphics LCD that comes on the Expression machine. 

If you still want to proceed:

You will need a ATMEL programmer device and an Atmel Studio 6.2 or newer installation. An ATMEL JTAG ICE MKII pod and the JTAG interface of the AVR is a good way to start. See picture and detailing connection and file Connector pinout.txt for details. you can also use an ISP programmer just to program the machine, no soldering necessary, just remove the bottom of the unit, uplug the cable from the from cartridge slot and route it out the front of the bottom of the case. Then plug this 10 pin connector into the 6 pin ISP connector, ensuring the red wire of the cable (pin 1) mates up with the pin 1 on your ISP header.  

*****Cricut Personal Board Modifications*****
A note from AL- I never seen it documented elsewhere, and kind of had to figure this out on my own, on my cricut personal, in particular, I found 
there were 2 resistors and a diode pulling pins of the ISP header High, I had to remove the following before I was able to program: R80,R81, and D1.  For flashing, I used Arduino ISP with AVRDUDE, as a matter of convenience because I had an arduino laying around.  

Use Inkscape to draw and send a file to the cutter.  Inkscape 0.91 has an export to Plot feature (under Extensions) which sends a HPGL langauge file to the COM port where the cutter is connected to. Use 9600 baud and  make sure XON/XOFF is selected for flow control. Inkscape works good on WIndows and Linux machines. 

----------


## Keypad key functions: ##

- On/Off : Powers the machine and executes carriage homing sequence. On sucessful boot, display will show FreecutAL
- Move buttons : Moves the carriage and the media freely.
- Home (ResetAll) : Re-homes the carriage, media is assumed to be unloaded.
- Load Paper		 : Pulls in media or cutting mat about 1/2".
- Unload Paper	 : Moves the mat/media back to the loading point. 
- X,Y Offset (BackSpace): Sets the current X and Y position as location 0,0 for following cuts
- Cutter Down (Numeral 1) : Drops the cutter down. This only works when the media is loaded. Useful  for measuring actual cutting force with a scale.
- Cutter Up (Numeral 2)  : Moves the cutter away from the media.
- Adjustments to speed and pressue have a scale of 1-9 and can be adjustred in two ways:
	First is via the Dials, which select the middle range of the scale for each. IE settings 3-7, not 1-5 as indicated on the dials.   
	The second way is via the keypad, which can push the settings to either end of the scale, beyond the dials ability.  
		To use the keypad, just press F1, to select pressure or F2, for speed, then use plus and minus to adjust which ever one is selected.  
		Regardless of the method used, the adjustment made will hold until the machine is power cycled, at which time the settings will revert to the dial setting.  
- F5, and F6 : Cutter Down, and Cutter Up, respectively
- F3, and F4 : Are both attached to debugging functions, F3 operates a Flash test, F4 will output "Hello World" to the USB serial Com your device is connected to.  
- Letter H : HPGL language selection, (default)
- Letter G: G-code language selection, see file g-code.c for supported g-code tokens

- Stop: Aborts the currently cached cutting operations, but new data arriving from the PC will still trigger subsequent motion.

## Dials ##

- Dial Speed: 	Also adjusts the cutting speed and is used to read the cutting speed after power up. Only the mid range of the speed choices can be selected, use the +/keys to get all the way to the end.

- Dial Pressure: Also adjusts the cutting pressure and is used to read the initial pressure on power-up. Only the mid range of the pressure choices can be selected, use the +/keys for the full range.

- Dial Size:  Not used. The machine can cut up to 80"x12"wide.

## Multi-cut and media lock ##

After the machine moves the media/carriage there is a time of about 1 minute (depending on speed setting) where the motors stay engaged and you can not move the media/carriage by hand. After this timeout the motors go into standby and you can move carriage and media by hand. This timeout is useful so that one can cut the same shape multiple times and not loose registration - for thick material multi-cut.

# Command language #


Currently supports HPGL -- HP Graphic Language. Cutting speed and pressure is NOT taken from the language input, only from keyboard and associated dials.

After the machine moves the media/carriage there is a time of about 1 minute at speed 5 where the motors stay engaged and you can not move the media/carriage by hand. After this timeout the motors go into standby and you can move carriage and media by hand. This timeout is useful so that one can cut the same shape multiple times and not loose registration - for thick material multi-cut.

Hope to add an option for GPGL (Graphtec)  in the future. 

# CAD and Cutting #
From the CAD system export via DXF format, then open that file in Inkscape. On the input dialog choose manual scale factor of 25.4 if the original CAD file was done in inch scale, otherwise set to 1.0. 
To cut, select all objects then use PATH/Object to Path, the Extensions/Export/Plot.  Plotter resolution set to 400 dpi.  Suggest Rotate the X Access so things print/cut as they appear on the screen.  
Note: The position on the screen is irrelevant, as the machine always cuts at origin 0,0 which is upper right as opposed to Inkscape's origin of lower left. Future plans include the ability to cut/print in place.
Pen number, force and speed are ignored. Rotation and Mirror as desired. Connection Settings are 9600/XON/XOFF and HPGL for language. Com port number as per device manger.   To execute press Apply. 


 

