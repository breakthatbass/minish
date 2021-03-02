#!/bin/bash

# colors for printing
RED='\033[1;31m'
GREEN='\033[1;32m'
BLUE='\033[1;36m'
NC='\033[0m' # No Color

# dependency files
test_files='../src/parse.c ../src/minish.c ../src/builtins.c'
 ../src/minish. ../src/minish.cc
# make this script have permission to run src files
#chmod -R 777 ../src/*.c

counter=0  # total files
pass=0	   # files that compile and run

# start timer
start=$SECONDS
# the emojis and colors are cool but they slow the whole process down
# if there are multiple large files to run, they would have to be removed

for i in *_tests.c
do
	echo "${BLUE}building${NC} ${i}"
	counter=$((counter + 1))
	if gcc "$i" $test_files -o "${i%.c}.out"; then
		echo "\n📦 build ${GREEN}succeeded${NC}\n"
		echo "  ${BLUE}->  running${NC} ${i%.c} file"
		if ./"${i%.c}.out"; then
			pass=$((pass + 1))
		fi
	else
		echo "\n🚨 build ${RED}failed${NC}\n"
	fi
done

# clean up
rm *.out

# stop timer
duration=$(( SECONDS - start )) #unfortunately bash can't do floats

if [ $counter -eq $pass ]
then
	echo "$GREEN$pass / $counter$NC test files compiled, ran, and cleaned up in ${duration} seconds"
else
	echo "$RED$pass / $counter$NC test files compiled, ran, and cleaned up in ${duration} seconds"
fi
