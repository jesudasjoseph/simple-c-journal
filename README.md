CS133c Final Project

Only runs on the Linux Subsystem of Windows if not on a Computer running linux.
I use the system("clear") function to clear the console a few times.

BUGS!
-Selecting menu option 1 before selecting entry 0 on the first run will throw a memory error. (File isn't created until you add a journal entry (menu item 0))

(Assignment #6) There are several dynamic arrays in this assignment one example is on line:169 which is handled in the function on line:60
(Assignment #4) I think assignment 4 dealt with handling char arrays or strings. This assignment does plenty of that, so I hope assignment #4 is covered too. :) (fingers crossed)

###Final Project Plan (Assignment #7)###

Journal Project
-I want to make a journal like program that saves user journal entrees and then allows the user to read them.
-I want to have multiple entrees in a single dated file
-I will use the file as a structured database and will add a struct array that contains all entrees in the one file.


File Writing-
I think I will either have to write every char individually or find a write string function
I'll use a delimiter to separate journal entrees

File Structure-
#Time
#Entree content line #1
#Entree content line #2
#Entree content line #3
#Entree content line ETC..
#Delimiter
#Time
#Entree content line #1
#Entree content line #2
#ETC...

Reading-
I'll read every character individually and control lines/delimiter stuff in it's own function.
