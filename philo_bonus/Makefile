NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g -fsanitize=address
RM = rm
RMFLAGS = -rf

INCLUDE = include
SRCS = srcs/bdo.c\
		srcs/bft_atoi.c\
		srcs/binit.c\
		srcs/bmain.c\
		srcs/bmonitor.c\
		srcs/bphilo.c\
		srcs/butils.c\
		srcs/bwait.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "made $(NAME)"
d : $(SRCS)
	@$(CC) $(DFLAGS) $(SRCS) -o $(NAME)
clean : 
	@$(RM) $(RMFLAGS) $(OBJS)
	@echo cleaned
fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)
	@echo fcleaned
re : fclean all

