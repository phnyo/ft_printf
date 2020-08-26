# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/26 16:52:53 by fsugimot          #+#    #+#              #
#    Updated: 2020/08/26 16:57:51 by fsugimot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS := converters.c converter_utils.c flg_parse.c flg_parse_utils.c flg_proc.c flg_proc_utils.c ft_printf.c num_utils.c str_utils.c
CC := gcc
OBJS := $(subst .c,.o,$(SRCS))
CFLAGS := -Wall -Werror -Wextra
NAME := libftprintf.a

all: $(NAME)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -o $^
$(NAME): $(OBJS) 
	ar rcs $(NAME) $< 
clean: $(OBJS)
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all