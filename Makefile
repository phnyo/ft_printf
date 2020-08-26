SRC := ft_printf.c
CC := gcc
OBJS := $(subst .c,.o,$(SRCS))
CFLAGS := -Wall -Werror -Wextra
NAME := libftprintf.a

all: $(NAME)
$(NAME): 
	ar rcs $(NAME) $(OBJS)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all