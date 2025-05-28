NAME        = server
MANDA_CLIENT = client
BONUS_NAME	= server_bonus
BONUS_CLIENT = client_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

SRV_SRCS    = server.c style_server.c utils_list.c utils_libft.c
CLI_SRCS    = client.c style_client.c utils_libft.c
SRV_BONUS_SRCS    = server_bonus.c style_server.c utils_list.c utils_libft.c
CLI_BONUS_SRCS    = client_bonus.c style_client.c utils_libft.c

SRV_OBJS    = $(SRV_SRCS:.c=.o)
CLI_OBJS    = $(CLI_SRCS:.c=.o)
SRV_BONUS_OBJS    = $(SRV_BONUS_SRCS:.c=.o)
CLI_BONUS_OBJS    = $(CLI_BONUS_SRCS:.c=.o)

INCLUDES    = -I.

# LES COULEURS
COLOR_BLK   = \033[0m
COLOR_GRIS = \033[38;5;146m
COLOR_MATRIX = \033[38;5;46m

MATRIX_CODE = "\n\
$(COLOR_MATRIX)\
01001101 01001001 01001110 01001001 01010100 01000001 01001100 01001011\n\n\
>>> Booting into the Matrix...\n\
>>> Connection: Server [OK] | Client [OK]\n\
>>> Executables linked to the Source.\n\
>>> Signals scrambled. Reality overwritten.\n\
>>> Welcome, Operator.\n\
$(COLOR_BLK)"

MATRIX_CLEAN = "\n\
$(COLOR_GRIS)\
[▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓] 100%\n\
ALL FILES NEUTRALIZED.\n\
WELCOME BACK TO THE VOID.\n\
$(COLOR_BLK)"

all: $(NAME) $(MANDA_CLIENT)
	@clear
	@echo $(MATRIX_CODE)

$(NAME):	$(SRV_OBJS)
	@$(CC) $(CFLAGS) $(SRV_OBJS) $(INCLUDES) -o $(NAME)

$(MANDA_CLIENT):	$(CLI_OBJS)
	@$(CC) $(CFLAGS) $(CLI_OBJS) $(INCLUDES) -o $(MANDA_CLIENT)

bonus:	$(BONUS_NAME) $(BONUS_CLIENT)
	@clear
	@echo $(MATRIX_CODE)

$(BONUS_NAME):	$(SRV_BONUS_OBJS)
	@$(CC) $(CFLAGS) $(SRV_BONUS_OBJS) $(INCLUDES) -o $(BONUS_NAME)

$(BONUS_CLIENT):	$(CLI_BONUS_OBJS)
	@$(CC) $(CFLAGS) $(CLI_BONUS_OBJS) $(INCLUDES) -o $(BONUS_CLIENT)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(SRV_OBJS) $(CLI_OBJS) $(SRV_BONUS_OBJS) $(CLI_BONUS_OBJS)
	@clear
	@echo $(MATRIX_CLEAN)

fclean: clean
	@$(RM) $(NAME) $(MANDA_CLIENT) $(BONUS_NAME) $(BONUS_CLIENT)

re: fclean all

.PHONY: all clean fclean re bonus