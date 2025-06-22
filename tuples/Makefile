PROG = project

CMD = cc

INCLUDES = tuple.h projectile.h

CFLAGS = -Werror -Wall -Wextra -IINCLUDES

SRCS = \
	projectile.c\
	tuple.c\

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
