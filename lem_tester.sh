#!/bin/sh

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
CLR=$(tput sgr 0)

if [ -e "lem-in.path" ]; then
	EXEC=$(cat lem-in.path)
else
	read -e -p "Enter the path to your lem-in executable: " FILEPATH
	eval EXEC=${FILEPATH/\~/$home}
	echo $EXEC > lem-in.path
fi

echo "********************************************"
echo "|     __     __     ______   ______        |"
echo "|    /\ \  _ \ \   /\__  _\ /\  ___\       |"
echo "|    \ \ \/ \".\ \  \/_/\ \/ \ \ \____      |"
echo "|     \ \__/\".~\_\    \ \_\  \ \_____\     |"
echo "|      \/_/   \/_/     \/_/   \/_____/     |"
echo "|                                          |"
echo "|   Lem-in tester                          |"
echo "|                         by: WSeegers     |"
echo "********************************************"
echo ""                                  
echo "Error testing:"
EMAPS=./error_maps

rm -f RESULT.log

for map in $EMAPS/*; do
	MNAME=$(basename $map) 
	MNAME=`echo $MNAME | cut -f 1 -d '.'`

	$EXEC/lem-in < $map 2>&1 > /dev/null
	RET=`echo $?`
	if [ $RET -eq 139 ]; then
		printf "%-30s "${RED}"[SEGFAULT]\n"${CLR} $MNAME
	elif [ $RET -gt 128 ]; then
		printf "%-30s "${RED}"[ERROR]\n"${CLR} $MNAME
	else
		printf "%-30s "${GREEN}"[PASS]\n"${CLR} $MNAME
	fi
done

echo "" 
echo "Testing valid maps" 

GMAPS=./maps

for map in $GMAPS/*; do
	MNAME=$(basename $map) 
	MNAME=`echo $MNAME | cut -f 1 -d '.'`

	echo $MNAME >> RESULT.log
	$EXEC/lem-in < $map | ./solution_check.py 2>&1 >> RESULT.log
	RET=`echo $?`
	if [ $RET -eq 139 ]; then
		printf "%-30s "${RED}"[SEGFAULT]\n"${CLR} $MNAME
	elif [ $RET -gt 128 ]; then
		printf "%-30s "${RED}"[ERROR]\n"${CLR} $MNAME
	elif [ $RET -eq 1 ]; then
		printf "%-30s "${RED}"[FAIL]\n"${CLR} $MNAME
	else
		printf "%-30s "${GREEN}"[PASS]\n"${CLR} $MNAME
	fi
done

echo ""
echo "   SEE RESULT.log"
