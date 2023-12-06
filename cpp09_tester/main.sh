#!/bin/bash

# ---------------------------------------------------------------------------- #
#                                    Colors                                    #
# ---------------------------------------------------------------------------- #

DEF_COLOR='\033[0;39m'
BLACK='\033[0;30m'
RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[0;93m'
BLUE='\033[0;94m'
MAGENTA='\033[0;95m'
CYAN='\033[0;96m'
GRAY='\033[0;90m'
WHITE='\033[0;97m'

# ---------------------------------------------------------------------------- #
#                                    Tester                                    #
# ---------------------------------------------------------------------------- #

printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};
printf ${YELLOW}"\n\t\tTEST CREATED BY: "${DEF_COLOR};
printf ${CYAN}"numartin\t\n"${DEF_COLOR};
printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};


directories=("../ex00" "../ex01" "../ex02")

printf "Check Directories: ";
for dir in "${directories[@]}"; do
    if [ -d "$dir" ]; then
        printf "${GREEN}[OK]${DEF_COLOR}"
    else
        printf "${RED}[KO]${DEF_COLOR} $dir missing";
    fi
done
printf "\n\n";

printf "\n------ EX00 TESTS ------\n";
cd ../ex00 &> /dev/null

cp ../cpp09_tester/ex00/data.csv .
cp ../cpp09_tester/ex00/subject.txt .
cp ../cpp09_tester/ex00/hard.txt .

out_files=("out_noargs" "out_subject" "out_hard")

printf "Compiling: ";
make re > /dev/null
if [ $? -eq 0 ]; then
    printf "${GREEN}[OK]${DEF_COLOR}"
else
    printf "${RED}[KO]${DEF_COLOR}";
fi
printf "\n";


printf "No args: ";
./btc &> out_noargs
DIFF=$(diff out_noargs ../cpp09_tester/ex00/exp_noargs) 
if [ "$DIFF" == "" ]; then
    printf "${GREEN}[OK]${DEF_COLOR}"
else
    printf "${RED}[KO]${DEF_COLOR}";
fi
printf "\n";


printf "Subject test: ";
./btc subject.txt &> out_subject
DIFF=$(diff out_subject ../cpp09_tester/ex00/exp_subject) 
if [ "$DIFF" == "" ]; then
    printf "${GREEN}[OK]${DEF_COLOR}"
else
    printf "${RED}[KO]${DEF_COLOR}";
fi
printf "\n";

printf "Hard test: ";
./btc hard.txt &> out_hard
DIFF=$(diff out_hard ../cpp09_tester/ex00/exp_hard) 
if [ "$DIFF" == "" ]; then
    printf "${GREEN}[OK]${DEF_COLOR}"
else
    printf "${RED}[KO]${DEF_COLOR}";
fi
printf "\n";

for file in "${out_files[@]}"; do
    rm $file &> /dev/null;
done

rm data.csv
rm hard.txt
rm subject.txt

make fclean &> /dev/null;