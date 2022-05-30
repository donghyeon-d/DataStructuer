NAME = bst.a
AR = ar
ARFLAGS = -rcs
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS =  bst.c \
		bst_test.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS)
	$(AR) $(ARFLAGS) $@ $^
	./a.out
	make fclean

clean :
	$(RM) $(OBJS)
	$(RM) a.out
	$(RM) bst

fclean : clean
	$(RM) $(NAME)

debug : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -g -o bst_test

.PHONY : all clean fclean re bonus
.SILENT : all name clean fclean