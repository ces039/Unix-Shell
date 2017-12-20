Melanie Cheng
Corrine Smith
Charles Beers
Anne Marie Brook
Matthew Harmon


cd: 	When the user just inputs "cd" it'll take you back to the home directory. However they can also
	input "cd (directory path)" that'll take them to the specified directory.If a directory outside 
	of the current directory is used as the argument, it will not work. It will require a call to cd 
	with no parameter first to return to the home directory.


[tab][enter]:	when the user pressed [tab][enter] the  "pwd" command will be executed and prints full path to 
		the current directory.

calendar:	When the user inputs "calendar [year] [month]" , with year and month being integers, the gshell
		will print out a calendar of that month in the specified year. If improper parameters are given
		the calendar function will throw an error and inform the user of the proper format.

history:	When the user types "history" a list of the previous commands without arguments will be printed,
		without a limit on the number of commands. Also, works when multiple commands on one line separated
		by semicolons.

multiple commands: User can call multiple commands separated by a semicolon. 



#######################
       EXAMPLES
#######################

gshell> ls;cd;ls;pwd;calendar 2017 3


Labs  README.md
Command ls added to history
gshell: program terminated successfully


directory change complete
Command cd added to history
gshell: program terminated successfully


!		      csci315	     Lab5 Table.xlsx   src
csci204		      Desktop	     Music	       tempGitRepo
csci205		      Documents      mytrace.out       Templates
csci205_finalproject  Ecosystem1.py  NetBeansProjects  test
csci205_hw	      ecosystem.py   perl5	       Videos
csci205_hw03	      Game.py	     Pictures
csci206		      lab01.txt      Public
csci311		      lab01.txt~     __pycache__
Command ls added to history
gshell: program terminated successfully


/nfs/unixspace/linux/accounts/student/c/ces039
Command pwd added to history
gshell: program terminated successfully



     March 2017
Su Mo Tu We Th Fr Sa
          1  2  3  4 
 5  6  7  8  9 10 11 
12 13 14 15 16 17 18 
19 20 21 22 23 24 25 
26 27 28 29 30 31 
ishell: program terminated properly
Command calendar added to history
gshell: program terminated successfully

#######################
       HISTORY
#######################
gshell> history

COMMAND HISTORY
ls
cd
cd
ls
cd
ls
pwd
calendar


	

