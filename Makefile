CC = cc 
READLINE = $(shell brew --prefix readline)
FLAGS = -Wall -Wextra -Werror  -I$(READLINE)/include -g -fsanitize=address
NAME = minishell
SRC = parsing/main.c \
	parsing/utils_minishell.c \
	parsing/syntaxerror/check_errors.c \
	parsing/syntaxerror/print_errorfunctions.c \
	parsing/syntaxerror/syntaxerror.c \
	parsing/token/creat_commandlist.c \
	parsing/token/creat_finallist.c \
	parsing/token/tokenizer.c \
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
	parsing/libftfunctions/ft_calloc.c \
	parsing/libftfunctions/ft_split.c \
	parsing/redirection/redirection.c \
	parsing/redirection/utils.c \



OBJ = $(SRC:.c=.o)
HEADER = minishell.h 

all : $(NAME)

$(NAME) : $(OBJ)  $(HEADER)
		$(CC) $(FLAGS) $(OBJ)  -lreadline  -o $(NAME) -L$(READLINE)/lib

%.o : %.c $(HEADER)
		@$(CC) $(FLAGS) -c $< -o $@

clean : 
		rm -rf $(OBJ)
fclean : clean
		rm -rf $(NAME)

re : clean fclean all