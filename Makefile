CLIENT	= client
SERVER	= server

LIBFTPRINTF		= resource/ft_printf/libftprintf.a
LIBFTPRINTF_DIR	= resource/ft_printf

LIBFT		= resource/libft/libft.a
LIBFT_DIR	= resource/libft

SRC_S	= server.c
SRC_C	= client.c

OBJ_S	= server.o
OBJ_C	= client.o

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all : $(LIBFT) $(LIBFTPRINTF) $(SERVER) $(CLIENT)

$(SERVER) : $(OBJ_S) minitalk.h
	@ $(CC) $(CFLAGS) $(LIBFT) $(LIBFTPRINTF) -o $@ $(OBJ_S)
	@printf "server ready. \n"

$(CLIENT) : $(OBJ_C) minitalk.h
	@ $(CC) $(CFLAGS) $(LIBFT) $(LIBFTPRINTF) -o $@ $(OBJ_C)
	@printf "client ready. \n"

$(LIBFTPRINTF) :
	@ $(MAKE) -C $(LIBFTPRINTF_DIR)

$(LIBFT) :
	@ $(MAKE) -C $(LIBFT_DIR)

%.o : %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

clean :
	@ $(MAKE) clean -C $(LIBFTPRINTF_DIR)
	@ $(MAKE) clean -C $(LIBFT_DIR)
	@ rm -rf $(OBJ_S) $(OBJ_C)
	@ printf "object files removed.\n"

fclean :
	@ $(MAKE) fclean -C $(LIBFTPRINTF_DIR)
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ rm -rf $(SERVER) $(CLIENT)
	@printf "client removed.\n"
	@printf "server removed.\n"

re	: fclean
	$(MAKE) all

.PHONY: all clean fclean re