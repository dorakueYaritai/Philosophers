#!/bin/bash

make_makefile() {
	touch $MFILE
	echo > $MFILE '#=============================
#flags
#=============================
NAME		:= 
CC			:= cc 
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror -O 
DFLAGS		:= -MMD -MP
LFLAGS		:= -lreadline
#=============================
#src
#=============================
# VPATH = srcs:srcs/UTIL
SRCDIR    = srcs
SRCS	:= 	\

#=============================
#directory
#=============================
INCDIR		= include/
INCLUDE		= -I$(INCDIR)
OBJDIR		= obj
ifeq "$(strip $(OBJDIR))" ""
  OBJDIR	= .
endif
OBJECTS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))
DEPENDS		= $(OBJECTS:.o=.d)
LIBDIR		= libft
LIBFT		= $(LIBDIR)/libft.a
#=============================
#rule
#=============================
$(NAME): $(OBJECTS) $(LIBFT)
	@echo $(BLUE)"----- $(NAME) $(CC) start-----"$(RESET)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(INCLUDE) $(MFLAGS) $(LFLAGS)
	@echo $(GREEN)"----- $(NAME) $(CC) done-----"$(RESET)
	@echo $(SKYBLUE) "make .o" $(RESET)
#-----
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	 -mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: $(PARSE_DIR)/%.c
	 -mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: $(EXE_DIR)/%.c
	 -mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: $(UTIL_DIR)/%.c
	 -mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@
#-----

$(LIBFT): FORCE
	$(MAKE) -C $(LIBDIR)
	@echo $(GREEN)"----- $(LIBFT) $(CC) done-----"$(RESET)
FORCE:

all: $(NAME) 

clean:
	$(MAKE) clean -C $(LIBDIR)
	@echo $(YELLOW)"----- $(LIBFT) clean done-----"$(RESET)
	$(RM) $(OBJECTS) $(DEPENDS)
	@echo $(YELLOW)"----- $(NAME) clean done-----"$(RESET)

fclean:	clean
	# $(MAKE) fclean -C $(LIBDIR)
	@echo $(RED)"----- $(LIBFT) fclean done-----"$(RESET)
	$(RM) $(NAME)
	@echo $(RED)"----- $(NAME) fclean done-----"$(RESET)

re: fclean all

-include $(DEPENDS)

#=============================
#make option
#=============================
s:	CFLAGS +=  -g  -fsanitize=address -fsanitize=undefined 
s:	re
	bash test_parse.sh

run: 
	make re
	./minishell
	
p: 
	make
	bash test_parse.sh

e: 
	make
	bash test_echo.sh

.PHONY: all clean fclean re bonus sani run sani2

#=============================
#color
#=============================
RED			=	"\033[31m"
GREEN		=	"\033[32m"
YELLOW		=	"\033[33m"
BLUE		=	"\033[34m"
PURPLE		=	"\033[35m"
SKYBLUE		=	"\033[36m"
RESET		=	"\033[0m"
	'
}

make_gitignore() {
	touch .gitignore
	echo > .gitignore '*.a
*.o
*.d

test
clone/

out*
old*

.vscode
.DS_Store
.gitignore
.history
.here*
err*
.DS_Store
philo
tty
play/hioikawa/minishell

bash
diff
mini
mini_tmp
minishell
play/hioikawa/minishell
play/hioikawa/def
play/hioikawa/関数の動き/BNF_bash
play/hioikawa/srcs/BNF_minishell
old
play/hioikawa/old/miniminishell.c
play/hioikawa/srcs/parser.c
.DS_Store
BNF_bash*
play/hioikawa/old/miniminishell.c

infile*
env*
debug*
test*'
}

SRCDIR="./src"
OBJDIR="./obj"
INCDIR="./include"
DIR=($SRCDIR $OBJDIR $INCDIR)

MFILE=Makefile

mkdir -p ${DIR[@]}
make_makefile
make_gitignore