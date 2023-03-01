#=============================
#flags
#=============================
NAME		:= philo
CC			:= cc 
RM			:= rm -f
CFLAGS		:= -O 
# CFLAGS		:= -Wall -Wextra -Werror -O 
DFLAGS		:= -MMD -MP
#=============================
#src
#=============================
# VPATH = srcs:srcs/UTIL
SRCDIR    = src
SRCS	:= 	philo.c


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
$(NAME): $(OBJECTS)
	@echo $(BLUE)"----- $(NAME) $(CC) start-----"$(RESET)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(INCLUDE) $(MFLAGS) $(LFLAGS)
	@echo $(GREEN)"----- $(NAME) $(CC) done-----"$(RESET)
	@echo $(SKYBLUE) "make .o" $(RESET)
#-----
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	 -mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

# $(OBJDIR)/%.o: $(PARSE_DIR)/%.c
# 	 -mkdir -p $(OBJDIR) 
# 	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

# $(OBJDIR)/%.o: $(EXE_DIR)/%.c
# 	 -mkdir -p $(OBJDIR) 
# 	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

# $(OBJDIR)/%.o: $(UTIL_DIR)/%.c
# 	 -mkdir -p $(OBJDIR) 
# 	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@
#-----

FORCE:

all: $(NAME) 

clean:
	$(RM) $(OBJECTS) $(DEPENDS)
	@echo $(YELLOW)"----- $(NAME) clean done-----"$(RESET)

fclean:	clean
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
	./$(NAME)
	
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
	
