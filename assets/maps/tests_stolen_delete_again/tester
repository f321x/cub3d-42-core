#!/bin/bash

G="\033[0;32m";
Y="\033[0;33m";
R="\033[0;31m";
NC="\033[0m";

# Valid maps tester
MAPS_FOLDER=./tests/valid/;
MAPS=$(ls "$MAPS_FOLDER");
echo -e "\n[ VALID MAPS ]";
for MAP in $MAPS; do
	echo -n "[$MAP]"
	./cub3d "$MAPS_FOLDER$MAP" 2>/dev/null;
	if [[ $? == 0 ]]; then
		echo -e "${G}[OK]${NC}";
	else
		echo -e "${R}[FAIL]${NC}"
	fi;
done;

# Invalid maps tester
MAPS_FOLDER=./tests/invalid/;
MAPS=$(ls "$MAPS_FOLDER");
echo "[ INVALID MAPS ]";
for MAP in $MAPS; do
	echo "[$MAP]"
	./cub3d "$MAPS_FOLDER$MAP";
	if [[ $? == 0 ]]; then
		echo -e "${R}[FAIL]${NC}\n"
	else
		echo -e "${G}[OK]${NC}\n";
	fi;
done;
