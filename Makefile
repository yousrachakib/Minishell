CC = cc 
FLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address
NAME = minishell
SRC = parsing/main.c \
	parsing/utils_minishell.c \
	parsing/syntaxerror/check_errors.c \
	parsing/syntaxerror/print_errorfunctions.c \
	parsing/syntaxerror/syntaxerror.c \
	parsing/token/creat_commandlist.c \
	parsing/token/tokenizer.c \
	parsing/token/creat_finallist.c \
	parsing/token/handling_file.c \
	parsing/environment/env_list.c \
	parsing/environment/creat_fill.c \
	parsing/environment/expand_envvariables.c \
	parsing/libftfunctions/ft_strchr.c \
	parsing/libftfunctions/strncpy.c \
	parsing/libftfunctions/ft_isalphanumeric.c \
	parsing/libftfunctions/ft_strcmp.c \
	parsing/libftfunctions/ft_itoa.c \
	parsing/libftfunctions/ft_strjoin.c \
	parsing/libftfunctions/ft_split.c \
	parsing/redirection/redirection.c \


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