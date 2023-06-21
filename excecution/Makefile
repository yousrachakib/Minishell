CC = cc

RM = rm -rf

FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRC =  parse_env.c  excecution/excecution_main.c \
		excecution/excecution_utils.c excecution/pwd.c excecution/nrml_command.c \
		excecution/cd.c excecution/export.c excecution/unset.c \
		excecution/echo.c
OBJS = $(SRC:.c=.o)

all: minishell

minishell : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LDFLAGS) -o minishell

%.o : %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) minishell

re: fclean minishell
