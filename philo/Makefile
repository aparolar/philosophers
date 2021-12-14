# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 11:45:45 by aparolar          #+#    #+#              #
#    Updated: 2021/12/14 10:48:36 by aparolar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
SRCS		=	philo.c\
				philoso.c\
				forks.c\
				utils.c\
				time.c\
				ft_isdigit.c\
				ft_atoi.c\
				ft_putnbr_fd.c\
				ft_putstr_fd.c\
				ft_intlen.c\
				
OBJS		=	$(SRCS:.c=.o)
DBGFLAGS	=	-g3 -fsanitize=address#thread
FLAGS		=	#-Wall -Werror -Wextra
CC			=	@gcc

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(DBGFLAGS) $(SRCS) -o $(NAME)

all:		$(NAME)

re:			fclean all

clean:		
			rm -f *.o

fclean:		clean
			rm -f $(NAME)

git_push:	fclean
			git add .
			git status
			git commit -m "Update $(shell date)"
			git push

.PHONY:		all re clean fclean
