cred="\\033[0;31m"
cgreen="\\033[0;32m"
cend="\\033[0;0m"
cup="\\033[1A"
erase="\\033[1A\\033[2K"

CC =clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinclude #-g3 -fsanitize=address
SHELL = /bin/bash

SUBDIRS = $(shell find src -mindepth 1 -type d | grep -v ".dSYM" | cut -d/ -f2-)
SUBDIRS_SPEED = $(shell find src_speed -mindepth 1 -type d | grep -v ".dSYM" | cut -d/ -f2-)

TEST_SRCS = $(shell find src -mindepth 2 -type f | grep -v ".dSYM")
TEST_SPEED_SRCS = $(shell find src_speed -mindepth 2 -type f | grep -v ".dSYM")

SUBDIRS_OBJ = $(addprefix obj/, $(SUBDIRS))
SUBDIRS_BIN = $(addprefix bin/, $(SUBDIRS))
SUBDIRS_TEST = $(addprefix test/, $(SUBDIRS))
SUBDIRS_TEST_SPEED = $(addprefix test_speed/, $(SUBDIRS_SPEED))

OBJS =	$(TEST_SRCS:src/%.cpp=obj/%_mine.o) \
				$(TEST_SRCS:src/%.cpp=obj/%_std.o) \
				obj/main.o
TESTS =				$(TEST_SRCS:src/%.cpp=test/%)
TESTS_RULES =	$(TEST_SRCS:src/%.cpp=test_rule/%)
TESTS_SPEED =	$(TEST_SPEED_SRCS:src_speed/%.cpp=test_speed/%)

INC =		$(wildcard include/*)

.PRECIOUS: bin/%

all:	$(TESTS_RULES)
map:	$(filter test/map/%, $(TESTS))
vect: $(filter test/vect/%, $(TESTS))
stack: $(filter test/stack/%, $(TESTS))
reverse: $(filter test/reverse_iterator/%, $(TESTS))

speed:
	@echo $(TEST_SPEED_SRCS)
	@echo $(TESTS_SPEED)

echo:
	@echo $(TESTS)

$(SUBDIRS_OBJ):
	@mkdir -p $(SUBDIRS_OBJ)

$(SUBDIRS_BIN):
	@mkdir -p $(SUBDIRS_BIN)

$(SUBDIRS_TEST):
	@mkdir -p $(SUBDIRS_TEST)

$(SUBDIRS_TEST_SPEED):
	@mkdir -p $(SUBDIRS_TEST_SPEED)

$(OBJS): $(INC) | $(SUBDIRS_OBJ)
$(BINS):        | $(SUBDIRS_BIN)

obj/%_mine.o: src/%.cpp
	$(CC) -c -D MINE -o $@ $< $(CFLAGS)
	@echo -en "$(erase)"

obj/%_std.o: src/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	@echo -en "$(erase)"

obj/main.o: src/main.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	@echo -en "$(erase)"

bin/%:	obj/%.o obj/main.o | $(SUBDIRS_BIN)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo -en "$(erase)"

test/%: bin/%_mine bin/%_std | $(SUBDIRS_TEST)
	@bash test.sh $@ $^

test_rule/%: bin/%_mine bin/%_std | $(SUBDIRS_TEST)
	@bash test.sh $@ $^

test_speed/%: src_speed/main.cpp src_speed/%.cpp | $(SUBDIRS_TEST_SPEED)
	@clang++ $^ -o $@_mine -Wall -Wextra -Werror -std=c++98 -Iinclude -D MINE
	@clang++ $^ -o $@_std -Wall -Wextra -Werror -std=c++98 -Iinclude
	@bash test_speed.sh $@

clean:
	rm -rf obj/

fclean:
	rm -rf bin/
	rm -rf obj/
	rm -rf test/

re: fclean all

.PHONY: all fclean re test_rule
