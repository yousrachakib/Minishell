CC = cc 
FLAGS = -Wall -Wextra -Werror -lreadline -g #-fsanitize=address
NAME = minishell
SRC = parsing/main.c \
	parsing/utils_minishell.c \
	parsing/syntaxerror/check_errors.c \
	parsing/syntaxerror/print_errorfunctions.c \
	parsing/syntaxerror/syntaxerror.c \
	parsing/token/creat_commandlist.c \
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
	parsing/redirection/redirection.c \
	execution/ft_execution.c \
	execution/builtins/ft_env.c \
	execution/builtins/ft_exit.c \
	execution/builtins/ft_isalpha.c \
	execution/builtins/ft_isdigit.c \
	execution/builtins/ft_printf.c \
	execution/builtins/ft_pwd.c \
	execution/builtins/ft_split.c \
	execution/builtins/ft_strjoin.c\
	execution/builtins/ft_strncmp.c\
	execution/builtins/ft_atoi.c\
	execution/builtins/ft_echo.c\
	execution/ft_check_path.c\
	execution/builtins/ft_cd.c\
	execution/builtins/change_pwd.c

	
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