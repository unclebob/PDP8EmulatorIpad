
#PDP-8 Emulator for iPad

This is my PDP8 Emulator for the iPad.  It's written in Lua using the Codea platform.
All the resources it uses are standard with Codea so you shouldn't have any difficulty
running it as is.  

### Shelves and Racks

To the left are the shelves of the current rack.  You can switch to other racks by pushing the "Next" and "Prev" buttons
at the bottom.  The shelves can hold paper tapes and core images.  Tap on a paper tape to select it, and then tap the reader to load it.
Tap a core image to select it, and tap Load Core to load it.

If you tap "Save Core" it will put the current core image on a new shelf, and name it "Core_" followed by a time stamp.  You can tap the
Shelf and type a new name if you like.  By the same token if there is a puched tape in the punch, and you tap it, it will put it on an empty
shelf named "Tape_" followed by a time stamp.  Again, you can rename it if you like by taping on it, and editing the name.  

Opt-Y should erase the name of the selected shelf.  You can type a new name if you like.  Or, if you unselect a shelf with no name,
then the object on that shelf will be deleted.  So be careful.

More documentation is coming...

### Note on code structure:

Yes, it's test driven.  I wrote a little unit testing utility that makes it pretty easy.   It's far from perfect, but it's workable.

The GUI stuff is not test driven, but the processor and bit manipulations are.  I test the GUI stuff in a very tight loop, in the TDD style, but there's no good way
to write unit tests against the Codea platform.  That doesn't matter too much since the edit/test loop is so fast when working with the GUI.

Refactoring in this environment (iPad screen, and bluetooth keyboard) is not ideal.  There's no refactoring browser, 
nor any really helpful tools.  Even selecting code on the screen is a pain.  Fingers are nowhere near as precise as a mouse.
Therefore, my functions are generally too large, and I have a significant backlog of cleanup to do.  But I'm doing it.  _Be patient._


