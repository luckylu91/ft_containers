#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m' # No Color
ERASE='\033[2K'

TEST_NAME=$(echo $1 | cut -d/ -f2-)
TEST_PATH="test/$TEST_NAME"
TEST_STDOUT_MINE="$TEST_PATH/out_mine"
TEST_STDERR_MINE="$TEST_PATH/err_mine"
TEST_STDOUT_STD="$TEST_PATH/out_std"
TEST_STDERR_STD="$TEST_PATH/err_std"
TEST_LEAKS_MINE="$TEST_PATH/leaks_mine"
TEST_LEAKS_STD="$TEST_PATH/leaks_std"
TEST_DIFF="$TEST_PATH/diff"

mkdir -p $TEST_PATH
echo -n "Test $TEST_NAME..."

$2 1> $TEST_STDOUT_MINE 2> $TEST_STDERR_MINE
$3 1> $TEST_STDOUT_STD 2> $TEST_STDERR_STD

diff $TEST_STDOUT_MINE $TEST_STDOUT_STD > $TEST_DIFF
if [ -s "$TEST_DIFF" ]; then
  echo -e "[$RED""KO""$NC""]"
else
  echo -e "[$GREEN""OK""$NC""]"
fi

leaks -atExit -- $2 > $TEST_LEAKS_MINE
if [[ $? -ne 0 ]]; then
  echo -e "    -> ""$RED""LEAKS""$NC"
fi

leaks -atExit -- $3 > $TEST_LEAKS_STD
if [[ $? -ne 0 ]]; then
  echo -e "    -> ""$RED""LEAKS_STD""$NC"
fi
