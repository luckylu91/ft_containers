#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m' # No Color
ERASE='\033[2K'

TEST_NAME=$(echo $1 | cut -d/ -f3-)
TEST_PATH=$(echo $1 | cut -d/ -f-2)
TEST_STDOUT_MINE="$TEST_PATH/time_mine"
TEST_STDERR_MINE="$TEST_PATH/err_mine"
TEST_STDOUT_STD="$TEST_PATH/time_std"
TEST_STDERR_STD="$TEST_PATH/err_std"
EXEC_MINE="$1""_mine"
EXEC_STD="$1""_std"

# mkdir -p $TEST_PATH

echo -n "Speed test $TEST_NAME (mine)... "
$EXEC_MINE 0 1> $TEST_STDOUT_MINE 2> $TEST_STDERR_MINE
cat $TEST_STDOUT_MINE
echo

echo -n "Speed test $TEST_NAME (std)... "
$EXEC_STD 0 1> $TEST_STDOUT_STD  2> $TEST_STDERR_STD
cat $TEST_STDOUT_STD
echo

echo -n "The ratio is (mine) / (std) is : "
echo "scale=3; $(cat $TEST_STDOUT_MINE) / $(cat $TEST_STDOUT_STD)" | bc
