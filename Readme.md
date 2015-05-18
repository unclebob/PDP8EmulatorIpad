
#PDP-8 Emulator for iPad

This is my PDP8 Emulator for the iPad.  It's written in Lua using the Codea platform.
All the resources it uses are standard with Codea so you shouldn't have any difficulty
running it as is.  

### Getting Started
Get Codea running on your iPad.  Tap the little arrow in the upper left, and a little panel will slide open on the left.  Tap the "assets" icon, and select the "Dropbox" item from the menu.  Link dropbox to Codea using your dropbox password.

Get all the files from github and copy them into your dropbox account.  It's probably best to use a regular computer for this.  I haven't tried using the iPad to move these files to Dropbox, though it may be possible.  

Using the Dropbox app on the iPad, find the src/PDP8.lua file.  Open it in dropbox's text editor, and copy the entire contents to the clipboard.
Also, using the Dropbox app, move all the files in the `tapes` directory to the `Apps/Codea` directory in Dropbox.

Return to the Codea main screen, and once again tap the arrow at the upper left.  Again tap the "Assets" icon, and select the Dropbox menu.  You'll see a little `sync` button at the upper right of the Dropbox pop-up.  Tap it.  This will synchronize the contents of the `Apps/Codea` dropbox folder with Codea's internal memory.  You'll have to do this every time you move something in and out of Codea's dropbox memory.

Return again to the Codea main screen.  Push and hold the `Add New Project` button (the one with the big plus sign). Select the menu item that says "Paste into Project".  The PDP8 emulator code that was on the clipboard should be imported into this project.  Give it a name like PDP8 `<grin>`. 
	
Now run the emulator.  It should pop right up and the basic paper tapes should be in the selves at the left.

#### Configuring the emulator for your iPad

After starting the emulator tap the `RUN` button on the front panel.  You should see the lights blinking furiously.  The PDP8 is rapidly executing the zeros in memory.  (`0000` is an `AND` instruction).  Look at the lower right and you'll see a little statistics panel with three numbers in it.  

 * `fps`: Frames per second.  This is the number of times the screen is being redrawn per second.  Codea tries to redraw the screen 60 times per second.  If that number is much less than 60 it means that the emulator is taking longer than one sixtieth of a second to execute a batch of instruction.
 * `ips`: Instructions per second.  This number, on an iPad air (circa 2015) should be about 23,000.  On slower iPads it could be 5,000 or less.
 * `ipf`: Instructions per frame.  This is the batch size.  It is the number of instructions that are executed between drawing frames.  You can change this number by tapping the `Speed` button just to the left of the numbers.  It defaults to 401.  The bigger the batch, the faster the emulator runs, but the slower the screen updates.

If `ips` is less than 23,000 you may have to configure some of the timing parameters in the source code.  Stop the emulator by tapping the `QuitX2` button twice in rapid succession.  You should be returned to the Codea editor.

Tap the `Main` tab at the top of the screen.  You should see the code for the Main Module which begins with six constants:

 * `VERSION`: This is the version number of the code.  It prints at the lower left of the screen when the emulator is running.
 * `ION_DELAY`: This is the number of instructions to wait after an ION instruction before turning the interrupts on.  In a real PDP8 this number is 1.  But for slow iPads it's better to make this number to 30 or more in order to sidestep bugs in old DEC software; particularly FOCAL.  (See "FOCAL" below).
 * `AUTO_CR_DELAY`: This is the number of seconds (usually a fraction) that the tape reader will pause after reading a `CR` (Carriage Return, Octal 215).  This delay is only imposed when the reader is in `Auto` mode, and the `FAST` toggle is not set.  For slow iPads it's best to set this number to `0.5` or larger, to allow old DEC programs, particularly FOCAL, to have time to process the end of a line.
 * `FAST_TTY_DELAY`: This is the number of seconds (usually a small fraction) that the TTY will delay between characters when the `TTY FAST` toggle is set.  This number defaults to zero so that the TTY will print as fast as possible in fast mode.  
 * `FAST_READER_DELAY`: This is the number of seconds (usually a very small fraction) that the tape reader delays between characters when the `FAST` toggle is set.  For realism it defaults to `1/300` to get close to 300 characters per second; the actual speed of the DEC high speed reader.  Remember that the reader can only read as fast as the PDP8 requests characters, so on slow iPads, the reader may not get up to 300cps.  On fast iPads you can set this number to zero, and watch the tape reader really scream!
 * `FAST_PUNCH_DELAY`: This is the number of seconds (usually a small fraction) that the punch delays between characters when the `FAST` toggle is set.  This number defaults to `1/50` for realism, since the DEC high speed punch operated at 50cps.  Set this number to zero to punch as fast as possible.  

### Key Maps.
I use the Kensington KeyFolio Pro 2 bluetooth keyboard with my emulator.  The key mapping works
tolerably well, but there are a few exceptions.

 * Type Delete for CR
 * Type enter for LF
 * Type Option-underscore for rubout
 * Type Option-C for Ctrl-C
 * Type Option-L for Ctrl-L
 * Type Option-G for Ctrl-G
 
### Loading Standard Programs.
When you start the emulator, the 4K of "core" is set to all zeroes.  To load any of the standard paper tapes in the shelf at the left you'll have to toggle in the Rim loader (see below).  Then you can load in the Bin loader, and then load the editor or the assembler.  Or use the RIM loader to load in Focal. 

It would be a good idea to save a core image of the rim loader, the bin loader, the assembler, the editor, and FOCAL.  You can do this by tapping the `Save` button below the tape shelves.  See the instructions below.  An, in general, read the whole document (RTFM!).  And, of course, Have fun! 

### The Front Panel
The lights on the front panel are also buttons.  You can tap them to change their state.  You can also slide your finger along the lights to change them as a group.

 * `PC` - The Program Counter.  This is the address of the next instruction to be executed.
 * `MA` - Memory Address.  Whenever memory is read or written, this is the address.  It's also the effective address for the `EXAM` and `DEP` buttons.
 * `MB` - Memory Buffer.  Whenever the data stored into, or read from, memory, including with the `EXAM` and `DEP` buttons.
 * `AC` - Accumulator.  This is the register that most math and comparison operations use.
 * `SR` - Switch Register.  Use this to set program options.
 * `LINK` - A one bit register that catches any carry-out when adding to the `AC`. 
 * `ION` - Indicates if the interrupts have been turned on.
 * `KBD` - The "Keyboard Ready" flag.  Is set if a character is waiting to be read from the keyboard input bufffer
 * `TTY` - The "TTY" Ready flag.  Is set if the TTY is finished typing the last character and is ready to type a new character.

To store a word in memory from the front panel, enter the address in the `MA` register.  Enter the data in the `MB` register.  Tap `DEP`.  The word will be stored, and the `MA` register will be incremented.

To display the contents of a memory location on the front panel, enter the address into the `MA` register and tap `EXAM`.  The contents will appear in the `MB` register.

To run a program, enter the starting address in the `PC` register and then tap `RUN`.  

To single step through a program enter the starting address in the `PC` register and then tap `STEP`.  One instruction will be executed and the results will be displayed on the front panel.

To stop a running program, simply tap the illuminated `RUN` button to turn it off and stop the computer.

### Toggling in programs
If you want to enter a program, like the RIM loader, into the computer through the front panel, follow the following procedure:
1. Enter the starting address in the `MA` register
2. Enter into the `MB` register the data you want stored at the address in the `MA` register
3. Tap `DEP`.  Note that the `MA` register has been incremented by one.
4. Go to step 2.

This is slightly different from the procedure used on a real PDP8 front panel, because in this emulator all the lights are also buttons.  On a real PDP8, it was necessary to use the switch register to enter data into the PC and MA, and there were special buttons for that purpose.  

### Shelves and Racks
To the left are the shelves of the current rack.  You can switch to other racks by pushing the "Next" and "Prev" buttons
at the bottom.  The shelves can hold paper tapes and core images.  

The names of items on shelves can be changed by taping on the shelf and then editing the text of the name.  If you type Opt-Y the name will be erased, and you can type a new name.  

To delete the contents of a shelf, simply delete the name of that shelf, and then tap another shelf, or anywhere outside of the rack.  The contents of the unnamed shelf will be deleted.  So be careful.

###Paper Tapes
Tap on a shelf that holds a paper tape to select it, and then tap the reader to load it.  The selected paper tape will show up in the reader, ready to be read by the PDP8.  The image of the paper tape is faithful, in that the holes in the paper tape correspond to the contents of the tape, and the bits that the PDP8 is reading.

To save a tape that has been punched tap it, it will be removed from the punch and placed in an empty
shelf named `Tape_<time>`.  You can rename it if you like by taping on it, and editing the name.  

###Dropbox
The first rack automatically loads paper tapes that it finds in Codea's Dropbox repository.  Codea allows you to bind that repository to your own Dropbox account.  It will use the files that you place in `Apps/Codea`.  I've included some paper tape files in this git repo that you should move into that Dropbox directory.  With those tapes you'll be able to boostrap the PDP8 with the most relevant ancient software, and actually write real PDP8 assembler programs.

### Core Images
Below the racks, between the "Next" and "Prev" buttons you'll see the "Load" and "Save" buttons.  If you push "Save" then the current contents of Core will be saved on an empty shelf.  You'll see it appear there with the name: `Core_<Time>`.  You can change the name by clicking on the shelf, and editing the text.

To load a core image into core, simply tap on the shelf to select it, and then press the "Load" button.  The core image will be immediately loaded into the PDP8 core memory.

###Teleprinter
The teleprinter has an endless roll of yellow paper.  Only the most recent 30 lines are shown, but you can scroll backwards to see previous contents by simply running your finger up and down over the paper -- similar to scrolling on a iPhone.

###Processor Statistics and Speed.
At the bottom right you'll see three numbers in a white rectangle.  This is the statistics frame.

 * `fps` stands for "Frames per Second".  This is the number of times that the screen is redrawn every second.  The lights in the registers can change no faster than this.
 * `ips` stands for instructions per second.  It is the raw speed of the processor.  
 * `ipf` stands for instructions per frame.  This is the number of instructions that are executed between redraws of the screen.  
 * `Speed Button` You can control the value of `ipf` by tapping on the `Speed` button to the left of the statistics frame.  Each tap causes the `ipf` to cycle through a few useful values which are [1,11,101,401].  The more instructions per frame, the higher the speed of the processor, but the fewer redraws per second.  The values 101,and 401 provide reasonable performance for Focal, the Editor, and the Assembler.

###IO Speed.
There are three buttons that control the speed of the IO devices.  There is a `FAST` toggle next to the Reader, another next to the Punch, and a `TTY FAST` toggle below the control panel.  If these are not set, then the speed of the corresponding devices is 10cps.  In fast mode they go much faster.  (See the "Configuring" section above).  

Be careful.  As with the original PDP8, a fast reader can quickly outpace a slow TTY or Punch.  This won't be a problem with the regular PDP8 software, like the editor or the assembler.  However, you're own programs will have to keep it in mind.

###Auto Reader
If you enable the AUTO button next to the reader, it couples the reader to the keyboard, allowing you to enter a paper tape as though it were being typed from the keyboard.  Make sure the `FAST` toggle is not set!  In `AUTO` mode the reader does not wait for the CPU to read characters, so the reader should be slow in order to avoid overrunning the TTY.

###Listings.
There are two buttons below the control panel.  "Junk Listing" simply erases the TTY.  Careful, there's no way to get it back.

The other button is "Save Listing".  This copies the contents of TTY to `Dropbox:listing`.  Remember that Codea doesn't create this for you, so you'll have to go to `Apps/Codea` in your Dropbox account, and add an empty `listing` file.  Also remember that Codea does not automatically sync it's copy of your dropbox with the real dropbox, so you'll have to go to Codea's asset picker and push the `sync` button.   I've included a convenient function named `dummy` in the `Main` module that has a `readText("Dropbox:xxxx")` line in it.  Just click on it, and Codea's asset picker will open.


More documentation is coming...

### Note on code structure:

Yes, it's test driven.  I wrote a little unit testing utility that makes it pretty easy.   It's far from perfect, but it's workable.

The GUI stuff is not test driven, but the processor and bit manipulations are.  I test the GUI stuff in a very tight loop, in the TDD style, but there's no good way to write unit tests against the Codea platform.  That doesn't matter too much since the edit/test loop is so fast when working with the GUI.

Refactoring in this environment (iPad screen, and bluetooth keyboard) is not ideal.  There's no refactoring browser, 
nor any really helpful tools.  Even selecting code on the screen is a pain.  Fingers are nowhere near as precise as a mouse.
Therefore, my functions are generally too large, and I have a significant backlog of cleanup to do.  But I'm doing it.  _Be patient._

I've managed to refactor the main program a bit, getting rid of most of the global variables, and putting them into the PDP8 class.  In order to verify each refactoring step I need to run the emulator, push the test button, quit the emulator, run it again, and then do some specific testing.  The cycle time is about 60 seconds; which isn't too bad.  However, it's long enough that I've begun to consider some kind of integration testing functions that I can run automatically.  


