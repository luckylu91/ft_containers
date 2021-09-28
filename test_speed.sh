#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m' # No Color
ERASE='\033[2K'

TEST_NAME=$(echo $1 | cut -d/ -f2-)
TEST_PATH="$1"
TEST_STDOUT_MINE="$TEST_PATH/out_mine"
TEST_STDERR_MINE="$TEST_PATH/err_mine"
TEST_STDOUT_STD="$TEST_PATH/out_std"
TEST_STDERR_STD="$TEST_PATH/err_std"
EXEC_MINE="$1""_mine"
EXEC_STD="$1""_std"

mkdir -p $TEST_PATH

echo -n "Speed test $TEST_NAME (mine)... "
$EXEC_MINE 1> $TEST_STDOUT_MINE 2> $TEST_STDERR_MINE
cat $TEST_STDOUT_MINE

echo -n "Speed test $TEST_NAME (std)... "
$EXEC_STD  1> $TEST_STDOUT_STD  2> $TEST_STDERR_STD
cat $TEST_STDOUT_STD
