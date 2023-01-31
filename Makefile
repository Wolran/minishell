# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 04:19:36 by vmuller           #+#    #+#              #
#    Updated: 2023/01/28 19:27:45 by vmuller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

SRC			= 	parsing/quote.c parsing/quote*2.c \

OBJECT		= ${SRC:.c=.o}
INC			= includes

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INC}

${NAME} : ${OBJECT}
	${CC} ${OBJECT} -o ${NAME} 

all : ${NAME}

clean :
	rm -f ${OBJECT}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re

