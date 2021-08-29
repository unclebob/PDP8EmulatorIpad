
# PDP-8 Emulator for iPad

This is my PDP8 Emulator for the iPad.  It's written in Lua using the Codea platform.
All the resources it uses are standard with Codea, or easily accessible, so you shouldn't have any difficulty running it as is.  

### The Model
The emulator is a faithful representation of a PDP-8 with 4096 12 bit words of core memory, and an ASR-33 Teletype.  The Teletype is the only I/O device.  The Teletype has an infinite roll of paper, an infinite amount of ink, and an infinite supply of paper tape.  It has a built in paper tape reader, and a built in paper tape punch.  By default they all operate at approximately 10 characters per second, though there are cheats to make them go significantly faster.  

On my iPad, purchased in 2018, the emulator runs at just about the same speed as a real PDP-8.  That speed is adjustable should you want it to execute slower than that.  

Programming can be accomplished using the buttons on the front panel.  I have taken the liberty of turning all the front panel lights into buttons so that the registers can be set by tapping the lights rather than using the switch register at the bottom.  For that reason I have not implemented some of the front panel switches that the PDP-8 used to move data between the switch register and the registers.  

Programming is better accomplished by using the text editor and the Pal III assembler.  These are included as "paper tapes" that you can load by inserting them into the tape reader on the teletype and running the Bin Loader program.  More on that later.  

The output of the text editor is punched to paper tape.  Then the Pal III assembler is loaded using the Bin Loader, and the source code tape is fed to the assembler to produce a binary paper tape containing your executable program.  That binary paper tape can then be loaded using the Bin loader.  

If that sounds confusing, don't worry.  I'll be describing that process more in detail later.  In the mean time, let's get this program loaded onto your iPad.

## Getting Started

### Step 1: Get Dropbox Connected to Codea's "assets".
The emulator runs as a Lua program within an iPad app named Codea.  The paper tape images that are included with the emulator need to be moved into Codea's resources.  This is best done through Dropbox.  

Get the Dropbox app for your iPad.  If you don't already have a dropbox account, you should create one now.  

The GitHub distribution contains a directory named `tapes` that contains all the paper tape images that you'll be using.  Move these files into /Dropbox/Apps/Codea on your computer, and then verify that you can see them using the Dropbox app on your iPad.

Get the Codea app for your iPad.  Find the `assets` window and select dropbox.  You'll be prompted to link Dropbox with Codea.  You'll also see a `sync` button.  Once synced you should see the paper tape images as Codea assets under the Dropbox heading.

### Step 2: Load the emulator source code into Codea

On your computer find the `src/PDP8.lua` file in the GitHub distribution.  Load it into a text editor and copy it all onto your clipboard.  (Command-A Command-C should do it)

Go to the main Codea window on your iPad and create a new project.  (Hit the big + button).  Give the new project a name like PDP-8.  You should see some minimal source code show up in the programming window.  You should select and delete it all.  Then return to the main Codea window again.  

Now select Codea's `Air Code` function.  It will display a URL.  On your computer, browse to that URL.  You will see something like Codea's main window.  Click on the PDP-8 project that you just created.  The empty source code window will appear.  Paste the emulator source code, that is still in your clipboard, into this window.  Close the window.  

Now return to your iPad and go to Codea's main window.  Tap the PDP-8 project, and you should see the emulator source code show up.  The first few lines should look like this:

	--# Main
	-- PDP8

	-- To Do:
	...

	VERSION="..some version..."
	
Execute the emulator by tapping the arrow button at the upper right.  (At least that's where it is on my version of Codea).  You should see the emulator appear on your screen.  If the keyboard window obscures part of the screen dismiss it.  We'll deal with that later.  The PDP-8 Control Panel will be at your lower right.  The Teletype (TTY) paper will be above that.  The paper tape reader and punch will be to the left of the TTY and Control Panel.  And on the far left you should see a rack of paper tapes.  We'll talk about them later.  

Tap some of the lights on the control panel.  You should be able to turn them on and off; but you won't hear any sounds.  Let's fix that.  Exit the emulator by taping the `QuitX2` button twice.

### Step 3: Load the sound library.
All the sounds we need are already assets known to Codea, but they need to be downloaded.  Once again, go to Codea's asset window, and tap the download button next to `Game Sounds One`.  The sound files will download quickly if you have a good network connection.

Now restart the emulator and tap the lights again.  You should hear a pleasant little 'boink'.  

#### Configuring the emulator for your iPad

After starting the emulator tap the `RUN` button on the front panel.  You should see the lights blinking furiously.  The PDP8 is rapidly executing the zeros in memory.  (`0000` is an `AND` instruction).  Look at the lower right and you'll see a little statistics panel with three numbers in it.  

 * `fps`: Frames per second.  This is the number of times the screen is being redrawn per second.  Codea tries to redraw the screen 60 times per second.  If that number is much less than 60 it means that the emulator is taking longer than one sixtieth of a second to execute a batch of instruction.
 * `ips`: Instructions per second.  This number, on an iPad pro (circa 2019) should be something above 100,000.  On slower iPads it could be significantly less.
 * `ipf`: Instructions per frame.  This is the batch size.  It is the number of instructions that are executed between drawing frames.  You can change this number by tapping the `Speed` button just to the left of the numbers.  It defaults to 9999.  The bigger the batch, the faster the emulator runs, but the slower the screen updates.  If 'fps' is a lot lower than 30 you probably had a very slow iPad, and you might want to use the 'speed' button to reduce the batch size and slow the PDP-8 processor down. 
 
### Note on processor speed and old DEC programs.
I have found that some of the old DEC programs, particularly the PALIII assembler, misbehave when using the slow paper tape reader in combination with processor speeds greater than about 150,000 ips.  I presume this is because the programs counted on the slow speed of the processor and the synchronization of the TTY and the tape reader on the ASR33.  The emulator does not enforce that synchronization.  

The symptom I have seen is that the paper tape reader reads one or two characters and then stops.  I generally fix this either by slowing the processor using the processor `speed` button, or by switching the paper tape reader to `FAST` mode.

FOCAL works much better with faster processor speeds when reading programs from the slow reader.  This is because FOCAL does not know it is reading from paper tape.  The reader must be placed in AUTO mode, and FOCAL simply thinks someone is typing the program at the TTY keyboard.  FOCAL is not fast enough to keep up with a very fast typist.  ;-)

### Keyboard
I use a bluetooth keyboard with my emulator.  The mapping of keys to the old TTY works
tolerably well, but there are a few strange exceptions.

 * Type Delete or Backspace for CR (Carriage Return)
 * Type Enter for LF (Line Feed)
 * Type Option-backslash for rubout (used by PDP-8 software as backspace or delete.)
 * Type Option-C for Ctrl-C
 * Type Option-L for Ctrl-L (Form Feed)
 * Type Option-G for Ctrl-G (Bell)
 
 Some bluetooth keyboard like to go to sleep.  When this happens the iPad keyboard window may pop up.  If you wake up the bluetooth keyboard, the iPad keyboard window should go away.  If you dismiss the iPad keyboard window, you may find that your bluetooth keyboard will no longer work until you reboot the emulator.  (Ugh.  Trying to simulate 1960s equipment with all this fancy tech is challenging ;-)
 
### iPad sleep.
If the iPad goes to sleep while the emulator is running, then when it wakes up the screen will not refresh properly.  This is because, in order to give as much processing power to the PDP-8 as possible, I avoid redrawing the screen unless something changes.  I'll be thinking about how to resolve this in future releases.
 
### Manuals
The `manuals` directory of the GitHub distribution has several PDF files that you will find invaluable.  Above all is the _IntroToProgramming1969 (1).pdf_ manual; affectionately known as _Introduction to Programming_.  This manual will tell you everything (and I mean everything) you need to know to program the PDP-8, including how to use the text editor, the assembler, and FOCAL (A basic like interpreter).  This manual will be your bible.  It starts with binary math, and takes you all the way through the wonderful world of the PDP-8.

The other manuals in that directory are supplementary.  They contain separate, and somewhat more detailed, descriptions of the text editor, the assembler, the FORTRAN compiler, and FOCAL.  Have fun with all of them.

### The Front Panel
The lights on the front panel are also buttons.  You can tap them to change their state.  You can also slide your finger along the lights to change them as a group.  Try it!

Chapter 4 of _Introduction to Programming_ describes the PDP-8 control panel.  You might want to read that and compare it to the control panel of the emulator.  There are many similarities, but some differences.  Most of the differences are due to the fact that the emulators lights are also buttons, and therefore buttons like `lOAD ADDR` are not needed.  (Let the studious reader understand.)

 * `PC` - The Program Counter.  This is the address of the next instruction to be executed.
 * `MA` - Memory Address.  Whenever memory is read or written, this is the address.  It's also the effective address for the `EXAM` and `DEP` buttons.
 * `MB` - Memory Buffer.  Contains the data stored into, or read from, memory, including with the `EXAM` and `DEP` buttons.
 * `AC` - Accumulator.  This is the register that most math and comparison operations use.
 * `SR` - Switch Register.  Use this to set program options.
 * `LINK` - A one bit register that catches any carry-out when adding to the `AC`. 
 * `ION` - Indicates if the interrupts have been turned on.
 * `KBD` - The "Keyboard Ready" flag.  Is set if a character is waiting to be read from the keyboard input buffer.
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

This is slightly different from the procedure used on a real PDP8 front panel, again because in this emulator all the lights are also buttons.  On a real PDP8, it was necessary to use the switch register to enter data into the PC and MA, and there were special buttons, such as `LOAD ADDR` for that purpose.  

### Shelves and Racks
To the left are the shelves of the current rack.  You can switch to other racks by pushing the "Next" and "Prev" buttons at the bottom.  The shelves can hold paper tapes and core images.  

The names of items on shelves can be changed by taping on the shelf and then editing the text of the name.  If you type Opt-Y the name will be erased, and you can type a new name.  

To delete the contents of a shelf, simply delete the name of that shelf, and then tap another shelf, or anywhere outside of the rack.  The contents of the unnamed shelf will be deleted.  So be careful.

###Paper Tapes
Tap on a shelf that holds a paper tape to select it, and then tap the reader to load it.  The selected paper tape will show up in the reader, ready to be read by the PDP8.  The image of the paper tape is faithful, in that the holes in the paper tape correspond to the contents of the tape, and the bits that the PDP8 is reading.

To save a tape that has been punched, tap it.  It will be removed from the punch and placed in an empty
shelf named `Tape_<time>`.  You can rename it if you like by tapping on it, and editing the name.  It will be saved as a Codea asset, and be available for subsequent runs of the emulator.  These tapes do not, however, get put into the dropbox assets.

### Core Images
Below the racks, between the "Next" and "Prev" buttons you'll see the "Load" and "Save" buttons.  If you push "Save" then the current contents of Core will be saved on an empty shelf.  You'll see it appear there with the name: `Core_<Time>`.  You can change the name by clicking on the shelf, and editing the text.  Again, these images are saved for future emulator runs.

To load a core image into core, simply tap on the shelf to select it, and then press the "Load" button.  The core image will be immediately loaded into the PDP8 core memory.

### Teleprinter
The teleprinter has an endless roll of yellow paper.  Only the most recent lines are shown, but you can scroll backwards to see previous contents by simply running your finger up and down over the paper -- similar to scrolling on a iPhone.

### Listings.
There are two buttons below the control panel.  "Junk Listing" simply erases the TTY.  Careful, there's no way to get it back.

The other button is "Save Listing".  This copies the contents of the TTY to `Dropbox:listing_[timestamp].txt`.  Remember that Codea does not automatically sync it's dropbox assets with the real dropbox, so you'll have to go to Codea's asset window and push the `sync` button.   I've included a convenient function named `dummy` in the `Main` module that has a `readText("Dropbox:xxxx")` line in it.  Just click on it, and Codea's asset picker will open.

Be aware that the dropbox directory where listings are kept is the same directory where the initial paper tapes are kept.  The Emulator will not load an initial paper tape that begins with `"listing_"`

### IO Speed.
There are three buttons that control the speed of the IO devices.  There is a `FAST` toggle next to the Reader, another next to the Punch, and a `TTY FAST` toggle below the control panel.  If these are not set, then the speed of the corresponding devices is 10cps.  In fast mode they go much faster.  (See the "Configuring" section below).  

Be careful.  As with the original PDP8, a fast reader can quickly outpace a slow TTY or Punch.  This may not be a problem with some of the PDP8 software, like the editor or the assembler.  However, FOCAL can't handle a fast reader, and you're own programs will have to deal with it.

### Auto Reader
If you enable the AUTO button next to the reader, it couples the reader to the TTY keyboard, allowing you to enter a paper tape as though it were being typed from the keyboard.  Make sure the `FAST` toggle is not set!  In `AUTO` mode the reader does not wait for the CPU to read characters, so the reader should be slow in order to avoid overrunning the TTY, and the program.

### Loading Standard Programs.
When you start the emulator, the 4K of "core" is set to all zeroes.  To load any of the standard paper tapes in the shelf at the left you'll have to toggle in the Rim loader (see below).  Then you can load in the Bin loader, and then load the editor or the assembler.  

It would be a good idea to save a core image of the rim loader, the bin loader, the assembler, the editor, and FOCAL.  

### The Included Paper Tapes

 * `binloaderRim` This is the Bin Loader that can be read in by the RIM loader.  
 * `editBin` This is the text editor, in Bin loader format.	
 * `PALIIIV2Bin` This is the PAL III assembler (Written by Ed Yourdon so long ago) in Bin format.		
 * `focal-AJAE-PB` This is FOCAL in Bin format.
 * `lander-focal` This is the Lunar Lander FOCAL program that can be read in using AUTO mode on the reader.
 * `OdtHighBin` This is the Octal debugger in Bin format. 
 * `focalRim` This is FOCAL in RIM loader format.  It takes a while to load.	
 * `FortranCompiler` This is the 4K Fortran compiler circa 1969.
 * `FortranOS` This is the Fortran OS that loads and executes Fortran programs.
 
 If you find a binary paper tape image on the net and want to include it, you can convert it to emulator format using the `topt.c` program.  Take the output and put it in your `Dropbox/Apps/Codea` directory, and then sync with Codea.  
 
### Videos

In the videos directory of the GitHub distribution you will find some helpful videos showing how to operate the emulator.

 * [toggleInRimLoadBin.mp4](https://www.dropbox.com/s/617u6n63ucwbtj7/toggleInRimLoadBin.mp4?dl=0) shows the bootstrap procedure for the PDP-8.  Toggling in the RIM loader, and then using it to read in the Bin loader from paper tape.  The RIM loader is relatively easy to toggle in.  You can see it there right next to the front panel.  However, the RIM format is very inefficient so we don't want to use it to read in programs at 10cps.  The Bin loader is more complex, and would be very hard to toggle in; but the Bin format is twice as efficient as the RIM loader.  So, again, when we've got a 10cps device, the advantages ought to be clear.  
 
 * [editAndCompile.mp4](https://www.dropbox.com/s/3shvmqsb52r48oq/editAndCompile.mp4?dl=0) shows the process of editing, compiling, and running a small PDP-8 program written in PAL-III assembler.  This one is fun!

### Note on code structure:

Yes, it's test driven.  I wrote a little unit testing utility that makes it pretty easy.   It's far from perfect, but it's workable.

The GUI stuff is not test driven, but the processor and bit manipulations are.  I test the GUI stuff in a very tight loop, in the TDD style, but there's no good way to write unit tests against the Codea platform.  That doesn't matter too much since the edit/test loop is so fast when working with the GUI.

Refactoring in this environment (iPad screen, and bluetooth keyboard) is not ideal.  There's no refactoring browser, 
nor any really helpful tools.  Even selecting code on the screen is a pain.  Fingers are nowhere near as precise as a mouse.
Therefore, my functions are generally too large, and I have a significant backlog of cleanup to do.  But I'm doing it.  _Be patient._

I've managed to refactor the main program a bit, getting rid of most of the global variables, and putting them into the PDP8 class.  In order to verify each refactoring step I need to run the emulator, push the test button, quit the emulator, run it again, and then do some specific testing.  The cycle time is about 60 seconds; which isn't too bad.  However, it's long enough that I've begun to consider some kind of integration testing functions that I can run automatically.  

### Configuration Constants
 * `VERSION`: This is the version number of the code.  It prints at the lower left of the screen when the emulator is running.
 * `ION_DELAY`: This is the number of instructions to wait after an ION instruction before turning the interrupts on.  In a real PDP8 this number is 1.  But for slow iPads it's better to make this number to 30 or more in order to sidestep bugs in old DEC software; particularly FOCAL.  (See "FOCAL" below).
 * `AUTO_CR_DELAY`: This is the number of seconds (usually a fraction) that the tape reader will pause after reading a `CR` (Carriage Return, Octal 215).  This delay is only imposed when the reader is in `Auto` mode, and the `FAST` toggle is not set.  For slow iPads it's best to set this number to `0.5` or larger, to allow old DEC programs, particularly FOCAL, to have time to process the end of a line.
 * `FAST_TTY_DELAY`: This is the number of seconds (usually a small fraction) that the TTY will delay between characters when the `TTY FAST` toggle is set.  This number defaults to zero so that the TTY will print as fast as possible in fast mode.  
 * `FAST_READER_DELAY`: This is the number of seconds (usually a very small fraction) that the tape reader delays between characters when the `FAST` toggle is set.  For realism it defaults to `1/300` to get close to 300 characters per second; the actual speed of the DEC high speed reader.  Remember that the reader can only read as fast as the PDP8 requests characters, so on slow iPads, the reader may not get up to 300cps.  On fast iPads you can set this number to zero, and watch the tape reader really scream!
 * `FAST_PUNCH_DELAY`: This is the number of seconds (usually a small fraction) that the punch delays between characters when the `FAST` toggle is set.  This number defaults to `1/50` for realism, since the DEC high speed punch operated at 50cps.  Set this number to zero to punch as fast as possible. 
 * TTYDELAY the default delay between characters output to the TTY.  Roughly 10cps.
 * PUNCHDELAY the default delay between characters output to the punch.  Roughly 10cps.
 * READERDELAY the default delay between characters read by the reader.  This should be kept a bit slower than the TTYDELAY and PUNCHDELAY so that the reader cannot overrun the printer or the punch.
 
 


