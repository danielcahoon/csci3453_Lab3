Lab 3
Danny Cahoon
CSCI3453 001

To compile the program, run make while in this directory to use my Makefile.
To run the program, use the following format for the command:
  ./ucd-csci3453-lab3 frameSize inputFile outputFile

Included is a testing.sh bash script that will run my program with a frame size
of 128, 256, 512,and 1024 including a progress bar at the bottom to show what
percentage of the test runs have been done. To run that test it uses "pg-reference.txt"
as the input file and creates an output file called "output". In order to run the script
just do the following:
  ./testing.sh
