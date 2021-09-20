cred="\\033[0;31m"
cgreen="\\033[0;32m"
cend="\\033[0;0m"
cup="\\033[1A"
erase="\\033[1A\\033[2K"

CC =clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -I. -Iinclude
SHELL = /bin/bash
# SUBDIRS = vect map
SUBDIRS = $(shell find src -mindepth 1 -type d | grep -v ".dSYM" | cut -d/ -f2-)
TEST_SRCS = $(shell find src -mindepth 2 -type f | grep -v ".dSYM")
SUBDIRS_OBJ = $(addprefix obj/, $(SUBDIRS))
SUBDIRS_BIN = $(addprefix bin/, $(SUBDIRS))
SUBDIRS_TEST = $(addprefix test/, $(SUBDIRS))
# VECT_SRCS =	$(addprefix src/vect/,\
# 	vector_iterator.cpp \
# 	vector_reassign.cpp \
# )
# SRCS = $(VECT_SRCS)
OBJS =	$(TEST_SRCS:src/%.cpp=obj/%_mine.o) \
				$(TEST_SRCS:src/%.cpp=obj/%_std.o) \
				obj/main.o
TESTS =	$(TEST_SRCS:src/%.cpp=test/%)
INC =	pair.hpp \
			vector.hpp \
			map.hpp

all:	fclean $(TESTS)
map:	fclean $(filter test/map/%, $(TESTS))
vect:	fclean $(filter test/vect/%, $(TESTS))

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

# clean:
# 	rm -rf bin/

fclean:
	rm -rf bin/
	rm -rf obj/
	rm -rf test/

re: fclean all

.PHONY: all fclean re
