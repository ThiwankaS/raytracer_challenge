PROG = ray

CMD = cc

CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address,undefined

SRCS = \
	ray.c\
	transform.c\
	tuple.c\
	matrix.c\
	main.c\


OBJS = $(SRCS:.c=.o)

all : $(PROG)

$(PROG) : $(OBJS)
	$(CMD) $(CFLAGS) -o $@ $^ -lm

%.o : %.c
	$(CMD) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(PROG)

re : fclean all

.PHONY : all clean fclean re
