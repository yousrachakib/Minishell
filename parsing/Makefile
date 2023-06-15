CC = cc 
FLAGS = -Wall -Wextra -Werror -lreadline
NAME = minishell
SRC = main.c 

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