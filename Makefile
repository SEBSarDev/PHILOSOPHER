NAME = philo
CC = clang
FLAG = -Wall -Werror -Wextra
INC = -lpthread 
#-D_REENTRANT?
SRCS = srcs/main.c \
       srcs/initialize.c \
       srcs/action.c \
       srcs/ft_atoi.c \
       srcs/ft_itoa.c \
       srcs/check_death.c \
       srcs/utils.c \
       srcs/util_forks.c \
       srcs/exit.c
OBJS = $(SRCS:.c=.o)
$(NAME) : $(OBJS)
	$(CC) $(FLAG) $(OBJS) -I./includes -I./usr/include $(INC) -o $(NAME)
%.o : %.c
	$(CC) $(FLAG) -o $@ -c $<
all : $(NAME)
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all
.PHONY : all clean fclean re
