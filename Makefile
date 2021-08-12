cred="\033[0;31m"
cgreen="\033[0;32m"
cend="\033[0;0m"

CC =	clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -I. #-fsanitize=address -g3
SHELL = /bin/bash
# SRCS =	vector_iterator.cpp
SUBDIRS = vect
SUBDIRS_BIN = $(addprefix bin/, $(SUBDIRS))
VECT_SRCS =	$(addprefix src/vect/,\
	vector_iterator.cpp \
	vector_reassign.cpp \
)
SRCS = $(VECT_SRCS)
BINS = $(SRCS:src/%.cpp=bin/%)
INC = vector.hpp

all:	$(BINS)
	@for b in $(BINS); \
		do echo -e $(cred) "Testing $$b" $(cend); \
		exec $$b; \
	done

echo:
	@echo $(BINS)

bin/%:	src/%.cpp
	$(CC) -o $@ $< $(CFLAGS)

$(BINS):	$(INC) | $(SUBDIRS_BIN)

$(SUBDIRS_BIN):
	mkdir -p $(SUBDIRS_BIN)

# clean:
# 	rm -rf bin/

fclean:
	rm -rf bin/

re: fclean all

.PHONY: all fclean re
