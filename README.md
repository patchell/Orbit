E................Edit Bodies
P................Pause/Run Toggle
Q................Quit
R................Rest to Beginning
S............... Start
Z + <SHIFT> .... Zoom IN
Z................Zoom Out
Mouse wheel ... Zoom in and out
Mouse wheel + <SHIFT>.... Speed Up/ Slow Down

March 4, 2025
I fixed the bug where the program bug where
it would exit with code "3".  Turns out that
was a KillTimer problem, and it seems you cannot
put that in the window destructor.  Or, if you
can (and I see no reason you could not do this)
then there is some other problem.  Sort of brute
force,  I killed the timer if it was running and
then called PostQuitMessage(0);

March 1, 2025 Ver 1.1
Made major improvements in the GUI (I hope), 
fixed a couple of bugs, added short cut keys,
context menu, Follow the body mode, etc.

The program still exits with a CODE 3 ???

Some of this stuff is still not finished, for instance, the context menus don't actually 
do anything.


//-------------------------------
Well, I would say most of the basic
functionality is working as of
Feb 13, 2022.  One big issue I am having
is that the program exits with a code 3.
Obviously, something is wrong, but so far,
my searches have not revealed anything that
helps me find out what it is.  So for now,
well, there are more important things to
do.

Eventually I want to dispolay the Energy of
the objects, as well as things like Potential
Engergy, which, it seems, is difficult to
do if you have 2 or more moving bodies.
Also, things like angulare momentum, stuff
like that.  Sort of like being back in
Physics 21.
