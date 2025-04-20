Submitted by:
Hilay Ben Tzur : 314854290
Alona Avraham : 209849306

- Bonus features *only in Special* edition (Press 2 on main menu to toggle):	
*	colors
*	explosion effect when a barrel hits mario - weather it explodes or not
*	Animation for hammer hit - '+' is displayed for a brief moment


- Additional bonus (?):
*	Score increse after mario reaches the princess is dependent on the distance between them 
*	If filename is too long to display in one line. It will be cut off at the end of the screen and 3 dots will be added.
*	Notifies what is wrong in the screen if invalid. (Tells at least one problem at a time)
*	Ghosts that climb ladders have an algorithm to hunt mario (choose wisely to go up or down - 
	horizontaly we prefer them wandering on the platform for a better game exprience)


- Clarifications about the game:
*	When Mario falls he can control his direction by pressing the left or right arrow keys [3]. https://mama.mta.ac.il/mod/forum/discuss.php?d=2206
*	When Mario jumps while moving it takes him 4 chars away from the jump point. https://mama.mta.ac.il/mod/forum/discuss.php?d=2113#p2733
*	Screen graphics are from text to ascii art generator and may look distorted due to printing '\'
*	Hammer hit is 2 chars away from mario's point. https://mama.mta.ac.il/mod/forum/discuss.php?d=3638
*	On silent mode, the results will be shown for RESULTS_SCREEN_TIME for each screen (can be changed in GameConfig.h)


- Valid game board is:
*	Not shorter in width
*	Not shorter in height
*	Must include mario princess and donkey
- all other "error" may disturb the gameplay (legend less than 20 from the end of file, mario not on floor and dies...) but not crash the program.


Enjoy :)