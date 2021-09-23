cred="\\033[0;31m"
cgreen="\\033[0;32m"
cend="\\033[0;0m"
cup="\\033[1A"
erase="\\033[1A\\033[2K"

CC =clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinclude -g3 -fsanitize=address
SHELL = /bin/bash

SUBDIRS = $(shell find src -mindepth 1 -type d | grep -v ".dSYM" | cut -d/ -f2-)
TEST_SRCS = $(shell find src -mindepth 2 -type f | grep -v ".dSYM")

SUBDIRS_OBJ = $(addprefix obj/, $(SUBDIRS))
SUBDIRS_BIN = $(addprefix bin/, $(SUBDIRS))
SUBDIRS_TEST = $(addprefix test/, $(SUBDIRS))

OBJS =	$(TEST_SRCS:src/%.cpp=obj/%_mine.o) \
				$(TEST_SRCS:src/%.cpp=obj/%_std.o) \
				obj/main.o
TESTS =				$(TEST_SRCS:src/%.cpp=test/%)
TESTS_RULES =	$(TEST_SRCS:src/%.cpp=test_rule/%)
INC =		$(wildcard include/*)

.PRECIOUS: bin/%

all:	$(TESTS_RULES)
map:	$(filter test/map/%, $(TESTS))
vect: $(filter test/vect/%, $(TESTS))

echo:
	@echo $(TESTS)

$(SUBDIRS_OBJ):
	@mkdir -p $(SUBDIRS_OBJ)

$(SUBDIRS_BIN):
	@mkdir -p $(SUBDIRS_BIN)

$(SUBDIRS_TEST):
	@mkdir -p $(SUBDIRS_TEST)

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

clean:
	rm -rf obj/

fclean:
	rm -rf bin/
	rm -rf obj/
	rm -rf test/

re: fclean all

.PHONY: all fclean re test_rule
