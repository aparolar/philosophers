# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aparolar <aparolar@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 11:45:45 by aparolar          #+#    #+#              #
#    Updated: 2021/12/21 12:52:52 by aparolar         ###   ########.fr        #
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
				ft_is_valid_aint.c\
				start_end.c
				
OBJS		=	$(SRCS:.c=.o)
DBGF		=	-g3
DBGFA		=	$(DBGF) -fsanitize=address
DBGFP		=	$(DBGF) -fsanitize=pthread
FLAGS		=	-Wall -Werror -Wextra $(DBGFA)
CC			=	@gcc
GIT_MSG		=	"Update"

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(SRCS) -o $(NAME)

all:		$(NAME)

re:			fclean all

clean:		
			rm -f *.o

fclean:		clean
			rm -f $(NAME)

git_push:	fclean
			git add .
			git status
			git commit -m "$(GIT_MSG) $(shell date)"
			git push

.PHONY:		all re clean fclean
