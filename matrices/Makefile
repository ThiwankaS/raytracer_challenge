PROG = matrix

CMD = cc

INCLUDES = matrix.h

CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address,undefined

SRCS = \
	tuple.c\
	matrix.c\
	main.c\

OBJS = $(SRCS:.c=.o)

all : $(PROG)

$(PROG) : $(OBJS)
	$(CMD) $(CFLAGS) -o $@ $^ -lm

%.o : %.c $(INCLUDES)
	$(CMD) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(PROG)

re : fclean all

.PHONY : all clean fclean re
