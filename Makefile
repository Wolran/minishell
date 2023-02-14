#*************************************************************************** #
#                                                                              #
#            :::      ::::::::                                                 #
#          :+:      :+:    :+:                                                 #
#        +:+ +:+         +:+         Makefile v2.1                             #
#      +#+  +:+       +#+                                                      #
#    +#+#+#+#+#+   +#+               By: troberts <troberts@student.42.fr>     #
#         #+#    #+#                                                           #
#        ###   ########.fr                                                     #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              VARIABLE REFERENCE                              #
# **************************************************************************** #

NAME= minishell

CC= clang
CFLAGS= -Wall -Werror -Wextra -g3 $(INCLUDE)
LDFLAGS=
DEPFLAGS= -MT $@ -MMD -MP -MF $(DEP_DIR)$*.d

INCLUDE = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(LIBFT_INC)

LIBFT_DIR= libs/libft
LIBFT_LIB= $(LIBFT_DIR)/libft.a
LIBFT_INC= $(LIBFT_DIR)/include

INCLUDE_DIR= includes
OBJ_DIR= obj/
SRC_DIR= sources/
DEP_DIR= dep/

# **************************************************************************** #
#                                .C & .H FILES                                 #
# **************************************************************************** #

SRC_FILE=	\
			core/clean_token.c \
			exec/assign_fd.c \
			exec/execute_cmd.c \
			exec/get_path_cmd.c \
			exec/pre_process.c \
			fake_parser.c \
			main.c

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ=		$(addprefix obj/, ${SRC_FILE:.c=.o})
DEP_FILE=	$(SRC_FILE:.c=.o)
DEP=		$(addprefix dep/, ${SRC_FILE:.c=.o})
#OBJ=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# **************************************************************************** #
#                                HEADER CONFIG                                 #
# **************************************************************************** #

#                 # <-- start here         | <-- middle             # <-- stop here
HEADER_NAME 	= +                    Minishell                    #

COLOR_RED		= \033[0;31m
COLOR_GREEN		= \033[0;32m
COLOR_YELLOW	= \033[0;33m
COLOR_BLUE		= \033[0;34m
COLOR_PURPLE	= \033[0;35m
COLOR_CYAN		= \033[0;36m
COLOR_WHITE		= \033[0;37m
COLOR_END		= \033[m

HEADER =		@echo "${COLOR_CYAN}\
				\n/* ************************************************************************** */\
				\n/*                                                                            */\
				\n/*            :::      ::::::::                                               */\
				\n/*          :+:      :+:    :+:                                               */\
				\n/*        +:+ +:+         +:${HEADER_NAME}*/\
				\n/*      +\#+  +:+       +\#+                                                    */\
				\n/*    +\#+\#+\#+\#+\#+   +\#+                    <vmuller@student.42.fr>            */\
				\n/*         \#+\#    \#+\#                     <troberts@student.42.fr>            */\
				\n/*        \#\#\#   \#\#\#\#\#\#\#\#.fr                                                   */\
				\n/*                                                                            */\
				\n/* ************************************************************************** */\
				\n \
				\n${COLOR_END}"

HEADER_VAR =	@echo "${COLOR_CYAN}\
				\n \
				BINARY NAME: $(NAME) \
				\n CC: $(CC) \
				\n CFLAGS: $(CFLAGS) \
				\n LDFLAGS: $(LDFLAGS) \
				\n${COLOR_END}"

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): FORCE header
	$(HEADER_VAR)
	@echo -n "${COLOR_PURPLE}Creatings libs : \n[${COLOR_END}"
	@$(MAKE) --no-print-directory --silent $(LIBFT_LIB)
	@echo -n "${COLOR_PURPLE}]\n\n${COLOR_END}"
	@echo -n "${COLOR_YELLOW}Compiling : \n[${COLOR_END}"
	@$(MAKE) --no-print-directory --silent $(OBJ)
	@echo -n "${COLOR_YELLOW}]\n\n${COLOR_END}"
	@echo -n "${COLOR_GREEN}Linking : "
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LIBFT_LIB)
	@echo "${COLOR_GREEN}Done. ${COLOR_END}"

FORCE: ;

malloc_test: $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -fsanitize=undefined -rdynamic -o $@ $(OBJ) $(LIBFT_LIB) -L. -lmallocator

bonus: $(NAME)

$(LIBFT_LIB): makelibf ;

makelibf :
	make -C $(LIBFT_DIR)

# $(OBJ): | $(OBJ_DIR)

# $(OBJ_DIR):
# 	@mkdir -p $(@D)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo -n "${COLOR_YELLOW}#${COLOR_END}"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

reobj: FORCE header cleanobj
	$(HEADER_VAR)
	@echo -n "${COLOR_YELLOW}Compiling : \n[${COLOR_END}"
	@$(MAKE) --no-print-directory --silent $(OBJ)
	@echo -n "${COLOR_YELLOW}]\n\n${COLOR_END}"
	@echo -n "${COLOR_GREEN}Linking : "
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LIBFT_LIB)
	@echo "${COLOR_GREEN}Done. ${COLOR_END}"

# $(DEP): | $(DEP_DIR)

# $(DEP_DIR):
# 	mkdir -p $@

$(DEP): $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(DEPFLAGS) $(CFLAGS) -o $@

header:
	$(HEADER)

cleanobj:
	@rm -f $(OBJ)

cleanobjdir: cleanobj
	@rm -rf $(OBJ_DIR)

cleanlibft:
	@make -C $(LIBFT_DIR) clean

fcleanlibft:
	@make -C $(LIBFT_DIR) fclean

clean: header
	@echo "${COLOR_RED}Removing libs objects.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent cleanlibft
	@echo "${COLOR_RED}Removing objects.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent cleanobj
	@echo "${COLOR_RED}Removing object directory.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent cleanobjdir

fclean: clean
	@echo "${COLOR_RED}Removing libs binary files.${COLOR_END}"
	@$(MAKE) --no-print-directory --silent fcleanlibft
	@echo "${COLOR_RED}Removing binary file.${COLOR_END}"
	@rm -f $(NAME) $(NAME_BONUS)

re: header fclean all

# reobj: cleanobj
# 	make -C .

norm: header
	@echo -n "$(COLOR_GREEN)"
	-python3 -m norminette $(SRC_DIR)
	@echo "$(COLOR_PURPLE)"
	-python3 -m norminette $(INCLUDE_DIR)
	@echo -n "$(COLOR_END)"

.PHONY: all clean fclean re reobj norm header cleanobj bonus obj_rule

# include $(DEP)

# DEP_CFLAGS=-MM -MD
# ALL_CFLAGS=-I ./inc -Wall -Wextra -Werror
# src=$(wildcard *.c)
# dep=$(src:.c=.d)
# 
# ... (other flags, other rules like all etc.)
# 
# %.o:%.c
#     $(CC) -c $< $(ALL_CFLAGS) -o $@
# %.d:%.c
#     $(CC) $< $(DEP_FLAGS) $(ALL_CFLAGS) -o $@
# 
# ... (other rules etc.)
# 
# #This below has to be at the end of the Makefile, else it does not work
-include $(DEP)