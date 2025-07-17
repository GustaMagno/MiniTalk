NAME_SERVER = server
NAME_CLIENT = client

NAME = minitalk.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

COMMON_SRCS = ft_printf.c
COMMON_OBJS = $(COMMON_SRCS:.c=.o)

SERVER_SRCS = server.c $(COMMON_SRCS)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CLIENT_SRCS = client.c $(COMMON_SRCS)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS)

$(NAME_CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re