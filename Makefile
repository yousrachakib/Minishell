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
	execution/ft_execution.c \
	execution/ft_pipe.c \
	execution/builtins/ft_env.c \
	execution/builtins/ft_exit.c \
	execution/utils/ft_isalpha.c \
	execution/utils/ft_isdigit.c \
	execution/utils/ft_printf.c \
	execution/builtins/ft_pwd.c \
	execution/utils/ft_strncmp.c\
	execution/utils/ft_atoi.c\
	execution/utils/fonction_utils.c\
	execution/builtins/ft_echo.c\
	execution/ft_check_path.c\
	execution/builtins/ft_cd.c\
	execution/builtins/change_pwd.c\
	execution/builtins/ft_unset.c\
	execution/builtins/ft_export.c \
	execution/builtins/blt_export.c \
	parsing/redirection/utils.c \
	parsing/redirection/here_doc.c \
	parsing/redirection/here_doc_expand.c \

OBJ = $(SRC:.c=.o)
HEADER = minishell.h 

all : $(NAME)

$(NAME) : $(OBJ)  $(HEADER)
		$(CC) $(FLAGS) $(OBJ)  -lreadline  -o $(NAME) 

%.o : %.c $(HEADER)
		@$(CC) $(FLAGS) -c $< -o $@

clean : 
		rm -rf $(OBJ)
fclean : clean
		rm -rf $(NAME)

re : clean fclean all
