cred="\033[0;31m"
cgreen="\033[0;32m"
cend="\033[0;0m"

CC =clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -I. -Iinclude -fsanitize=address -g3
SHELL = /bin/bash
# SUBDIRS = vect map
SUBDIRS = $(shell find src -mindepth 1 -type d | grep -v ".dSYM" | cut -d/ -f2-)
TEST_SRCS = $(shell find src -mindepth 2 -type f | grep -v ".dSYM")
SUBDIRS_OBJ = $(addprefix obj/, $(SUBDIRS))
SUBDIRS_BIN = $(addprefix bin/, $(SUBDIRS))
# VECT_SRCS =	$(addprefix src/vect/,\
# 	vector_iterator.cpp \
# 	vector_reassign.cpp \
# )
# SRCS = $(VECT_SRCS)
SRCS = $(TEST_SRCS) src/main.c
OBJS = $(SRCS:src/%.cpp=obj/%.o)
BINS = $(SRCS:src/%.cpp=bin/%)
INC = vector.hpp

all:	$(BINS)
	@for b in $(BINS); \
		do echo -e $(cred) "Testing $$b" $(cend); \
		exec $$b; \
	done

echo:
	@echo $(BINS)

$(SUBDIRS_OBJ):
	mkdir -p $(SUBDIRS_OBJ)

$(SUBDIRS_BIN):
	mkdir -p $(SUBDIRS_BIN)

$(OBJS): $(INC) | $(SUBDIRS_OBJ)
$(BINS):        | $(SUBDIRS_BIN)


obj/%_mine.o: src/%.cpp
	$(CC) -c -D MINE -o $@ $< $(CFLAGS)

obj/%_std.o: src/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/main.o: src/main.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

bin/%:	obj/%.o obj/main.o | $(SUBDIRS_BIN)
	$(CC) -o $@ $^ $(CFLAGS)

%: bin/%_mine bin/%_std
	echo $(word 1,$^)
	echo $(word 2,$^)

# clean:
# 	rm -rf bin/

fclean:
	rm -rf bin/
	rm -rf obj/

re: fclean all

.PHONY: all fclean re
