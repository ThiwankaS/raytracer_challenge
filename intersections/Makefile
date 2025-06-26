PROG = ray

LIBFT_DIR = ft_libft

LIBFT_REPO = https://github.com/ThiwankaS/ft_libft

LIBFT_A = $(LIBFT_DIR)/libft.a

CMD = cc

CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address,undefined

SRCS = \
	canvas.c\
	transform.c\
	tuple.c\
	matrix.c\
	main.c\
	ray.c\


OBJS = $(SRCS:.c=.o)

all : $(LIBFT_A) $(PROG)

# linking libft.a
$(PROG) : $(OBJS)
	$(CMD) $(CFLAGS) -o $@ $^ $(LIBFT_A) -lm

# downloading ft-libft if not already present inside the project root directory
$(LIBFT_A) :
	@if [ ! -d $(LIBFT_DIR) ]; then\
		echo "Cloning ft_libft...";\
		git clone $(LIBFT_REPO);\
	fi
	@$(MAKE) -C $(LIBFT_DIR)

%.o : %.c
	$(CMD) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(PROG)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re

.PHONY : all clean fclean re
