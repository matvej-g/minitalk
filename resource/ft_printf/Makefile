NAME	= libftprintf.a

SRCS	= \
	ft_printf.c ft_write_format.c

OBJS	= $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS)	: %.o : %.c
	cc -Wall -Werror -Wextra -c $<

all	: $(NAME)

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re	: fclean
	$(MAKE) all


.PHONY	: all clean fclean re