
MAIN		=	main signal
PARSE		=	parse parse_2 parse_3 parse_4 get_arg token token_2 check
ENV			=	env get_env
UTILS		=	free type

SRCS		=	$(addsuffix .c, $(addprefix main/, $(MAIN)))	\
				$(addsuffix .c, $(addprefix parsing/, $(PARSE)))	\
				$(addsuffix .c, $(addprefix env/, $(ENV)))	\
				$(addsuffix .c, $(addprefix utils/, $(UTILS)))	\

OBJS	=	$(addprefix srcs/, $(SRCS:.c=.o))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I includes -g3
NAME	=	minishell

%.o: %.c
		@${CC} ${CFLAGS} -c $< -o $@

all:	 libft $(NAME)

libft:
		@make -C libft/

$(NAME):	$(OBJS)
		@$(CC) -fsanitize=address -o $@ $^ -Llibft -lft -lreadline

clean: 
		@rm -f $(OBJS)
		@make -C libft clean

fclean:	clean
		@rm -f $(NAME)
		@make -C libft fclean

re:		fclean all

.PHONY: libft

