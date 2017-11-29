echo Danny Cahoon Page Replacment Simulator
echo -ne '[                    ] (0%)\r'
./ucd-csci3453-lab3 128 pg-reference.txt output
echo -ne '[#####               ] (25%)\r'
./ucd-csci3453-lab3 256 pg-reference.txt output
echo -ne '[##########          ] (50%)\r'
./ucd-csci3453-lab3 512 pg-reference.txt output
echo -ne '[###############     ] (75%)\r'
./ucd-csci3453-lab3 1024 pg-reference.txt output
echo -ne '[####################] (100%)\r'
echo -ne '\n'
