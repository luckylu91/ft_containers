CC =	clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98
NAME =	tester
SRCS =	vector_iterator.cpp
OBJS = $(SRCS:%.cpp=%.o)
INC = vector.hpp

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

%.o:	%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
$(OBJS):	$(INC)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean re
