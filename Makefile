# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 11:23:36 by pajimene          #+#    #+#              #
#    Updated: 2024/06/19 16:50:00 by pajimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= pipex

CFLAGS	= -Wall -Wextra -Werror -g3

CC		= cc

RM		= rm -rf

SRCS	= pipex.c \
		  pipex_utils.c \
		  ft_split.c \
		  string_utils.c \

B_SRCS	= pipex_bonus.c \
		  pipex_utils_bonus.c \
		  ft_split.c \
		  string_utils.c \
			
OBJS 	= $(SRCS:.c=.o)

B_OBJS 	= $(B_SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -c $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

bonus: $(B_OBJS)
	$(CC) $(CFLAGS) -c $(B_SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(B_OBJS)

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re	bonus