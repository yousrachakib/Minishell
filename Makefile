CC = cc 
FLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address
NAME = minishell
SRC = parsing/main.c \
	parsing/utils_minishell.c \
	parsing/split.c \
	parsing/creat_commandlist.c \
	parsing/syntaxerror.c

OBJ = $(SRC:.c=.o)
HEADER = minishell.h 


all : $(NAME)

$(NAME) : $(OBJ)  $(HEADER)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
		@$(CC) $(CFLAGS) -c $< -o $@

clean : 
		rm -rf $(OBJ)
fclean : clean
		rm -rf $(NAME)

re : clean fclean all