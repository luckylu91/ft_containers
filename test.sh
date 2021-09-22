#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m' # No Color
ERASE='\033[2K'

TEST_NAME=$(echo $1 | cut -d/ -f2-)
TEST_STDOUT_MINE="$1/out_mine"
TEST_STDERR_MINE="$1/err_mine"
TEST_STDOUT_STD="$1/out_std"
TEST_STDERR_STD="$1/err_std"
TEST_LEAKS_MINE="$1/leaks_mine"
TEST_LEAKS_STD="$1/leaks_std"

mkdir -p $1
echo -n "Test $TEST_NAME..."

$2 > $TEST_STDOUT_MINE 2> $TEST_STDERR_MINE
$3 > $TEST_STDOUT_STD 2> $TEST_STDERR_STD

DIFF=$(diff $TEST_STDOUT_MINE $TEST_STDOUT_STD)
if [ -z "$DIFF" ]; then
  echo -e "[$GREEN""OK""$NC""]"
else
  echo -e "[$RED""KO""$NC""]"
fi

# leaks -atExit -- $2 > $TEST_LEAKS_MINE
# if [[ $? -ne 0 ]]; then
#   echo -e "    -> ""$RED""LEAKS""$NC"
# fi

# leaks -atExit -- $3 > $TEST_LEAKS_STD
# if [[ $? -ne 0 ]]; then
#   echo -e "    -> ""$RED""LEAKS_STD""$NC"
# fi
