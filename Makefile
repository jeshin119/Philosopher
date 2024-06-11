NAME = philo

CC = cc
# CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g -fsanitize=address
RM = rm
RMFLAGS = -rf

INCLUDE = include
SRCS = $(wildcard srcs/*.c)
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

