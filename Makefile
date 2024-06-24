# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 11:23:36 by pajimene          #+#    #+#              #
#    Updated: 2024/06/24 13:30:51 by pajimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= pipex

B_NAME	= pipex_bonus

CFLAGS	= -Wall -Wextra -Werror

CC		= cc

RM		= rm -rf

SRCS	= pipex.c \
		  pipex_utils.c \
		  ft_split.c \
		  string_utils.c

B_SRCS	= pipex_bonus.c \
		  pipex_utils_bonus.c \
		  ft_split.c \
		  string_utils.c \
		  string_utils_2.c \
		  gnl.c
			
OBJS 	= $(SRCS:.c=.o)

B_OBJS 	= $(B_SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -c $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(B_NAME): $(B_OBJS)
	$(CC) $(CFLAGS) -c $(B_SRCS)
	$(CC) $(CFLAGS) -o $(B_NAME) $(B_OBJS)

all: $(NAME)

bonus: $(B_NAME)

clean:
	$(RM) $(OBJS) 
	$(RM) $(B_OBJS)

fclean: 
	make clean
	$(RM) $(NAME)
	$(RM) $(B_NAME)

re: 
	make fclean
	make all

.PHONY: all clean fclean re	bonus