#=============================
#flags
#=============================
NAME		:= philo
CC			:= cc 
RM			:= rm -f
CFLAGS		:= -O
# CFLAGS 			:= -g  -fsanitize=address -fsanitize=undefined 
# CFLAGS		:= -O -Weverything
# CFLAGS		:= -fsanitize=thread -Wall -Wextra -O
# CFLAGS		:= -fsanitize=address -Wall -Wextra -O 
# CFLAGS		:= -Wall -Wextra -Werror -O 
DFLAGS		:= -MMD -MP
#=============================
#src
#=============================
# VPATH = srcs:srcs/UTIL
SRCDIR    = src
MONITORDIR    = $(SRCDIR)/monitor
PHILOSOPHESRDIR    = $(SRCDIR)/philosophers
WRITERRDIR    = $(SRCDIR)/writer

SRCS	:= 	main.c\
		 	th_monitor_main.c\
		 	th_monitor_fork.c\
			th_monitor_death.c\
			th_monitor_utils.c\
			th_monitor_make_log.c\
			th_philo.c\
			th_philo_fork.c\
			th_philo_wish.c\
			th_writer.c\
			init_struct_philo.c\
			init_struct_share1.c\
			init_struct_share2.c\
			thread_create.c\
			parse.c\
			ft_strjoin.c\
			ft_control_queue.c\
			ft_itoa.c\
			ft_memmove.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_memset.c\
			ft_calloc.c\
			ft_positive_mod.c\
			ft_ltoa.c\
			ft_isdigit_str.c\
			ft_get_time_in_millisec.c\
			ft_pthread_mutex_trylock.c\
			ft_strtol.c\
			ft_is_utils.c\
			ft_lstadd_back.c\

#=============================
#directory
#=============================
INCDIR		= include/
# INCLUDE		= -I $(INCDIR) -lpthread
INCLUDE		= -I $(INCDIR)
OBJDIR		= obj
ifeq "$(strip $(OBJDIR))" ""
OBJDIR	= .
endif
OBJECTS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))
DEPENDS		= $(OBJECTS:.o=.d)
LIBDIR		= $(SRCDIR)/libft
# LIBFT		= $(LIBDIR)/libft.a

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

$(OBJDIR)/%.o: $(LIBDIR)/%.c
	-mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: $(MONITORDIR)/%.c
	-mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: $(PHILOSOPHESRDIR)/%.c
	-mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: $(WRITERRDIR)/%.c
	-mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@

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

# debug:	CFLAGS+= -g
# debug:	re

NAME_DEBUG = dbg
debug: CFLAGS += -g
debug: fclean $(NAME_DEBUG)

$(NAME_DEBUG): $(OBJECTS)
	@echo $(BLUE)"----- $(NAME) $(CC) start-----"$(RESET)
	$(CC) -o $@ $^ $(CFLAGS) -g $(DFLAGS) $(INCLUDE) $(MFLAGS) $(LFLAGS)
	@echo $(GREEN)"----- $(NAME) $(CC) done-----"$(RESET)
	@echo $(SKYBLUE) "make .o" $(RESET)

# @printf "$(ORANGE_DIM)"
# $(CC) $(CFLAGS_DEBUG) $(OBJS) $(LIBS) -o $@
# @printf "$(RESET)"

-include $(DEPENDS)

#=============================
#make option
#=============================
s:	CFLAGS +=  -g  -fsanitize=address -fsanitize=undefined 
s:	re

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

