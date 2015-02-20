
#PDP-8 Emulator for iPad

This is my PDP8 Emulator for the iPad.  It's written in Lua using the Codea platform.
All the resources it uses are standard with Codea so you shouldn't have any difficulty
running it as is.  

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
There are three buttons that control the speed of the IO devices.  There is a "FAST" button next to the Reader, another next to the Punch, and a "TTY FAST" button below the control panel.  If these are not pushed, then the speed of the corresponding devices is 10cps.  In fast mode they go much faster.  The speed should be close to 100cps for the reader, 50cps for the punch, and 100+cps for the TTY.  

Be careful.  As with the original PDP8, a fast reader can quickly outpace a slow TTY or Punch.  This won't be a problem with the regular PDP8 software, like the editor or the assembler.  However, you're own programs will have to keep it in mind.

###Auto Reader
If you enable the AUTO button next to the reader, it couples the reader to the keyboard, allowing you to enter a paper tape as though it were being typed from the keyboard.  In many cases the Reader should be slow in order to avoid overrunning the TTY.

###Listings.
There are two buttons below the control panel.  "Junk Listing" simply erases the TTY.  Careful, there's no way to get it back.

The other button is "Save Listing".  This copies the contents of TTY to `Dropbox:listing`.  Remember that Codea doesn't create this for you, so you'll have to go to `Apps/Codea` in your Dropbox account, and add an empty `listing` file.  Also remember that Codea does not automatically sync it's copy of your dropbox with the real dropbox, so you'll have to go to Codea's asset picker and push the `sync` button.   I've included a convenient function named `dummy` in the `Main` module that has a `readText("Dropbox:xxxx")` line in it.  Just click on it, and Codea's asset picker will open.


More documentation is coming...

### Note on code structure:

Yes, it's test driven.  I wrote a little unit testing utility that makes it pretty easy.   It's far from perfect, but it's workable.

The GUI stuff is not test driven, but the processor and bit manipulations are.  I test the GUI stuff in a very tight loop, in the TDD style, but there's no good way
to write unit tests against the Codea platform.  That doesn't matter too much since the edit/test loop is so fast when working with the GUI.

Refactoring in this environment (iPad screen, and bluetooth keyboard) is not ideal.  There's no refactoring browser, 
nor any really helpful tools.  Even selecting code on the screen is a pain.  Fingers are nowhere near as precise as a mouse.
Therefore, my functions are generally too large, and I have a significant backlog of cleanup to do.  But I'm doing it.  _Be patient._


