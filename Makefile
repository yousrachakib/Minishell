CC = cc 
FLAGS = -Wall -Wextra -Werror -lreadline
NAME = minishell
SRC = main.c \
	ft_split.c \
	utils_minishell.c \
	parsing.c \
	excecution/parse_env.c  \
	excecution/excecution_utils.c excecution/pwd.c excecution/nrml_command.c \
	excecution/cd.c excecution/export.c excecution/unset.c \
	excecution/echo.c excecution/utils.c 

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