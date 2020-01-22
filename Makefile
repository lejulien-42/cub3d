# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 15:52:54 by lejulien          #+#    #+#              #
#    Updated: 2020/01/22 03:40:29 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	= $(wildcard cub*.c) $(wildcard ./libft-42/*.c)
SRCSTEST= ./cub_draw_utils.c ./cub_get_next_line.c ./cub_get_next_line_utils.c ./test.c $(wildcard ./libft-42/*.c)
OTEST= $(wildcard ./*.o)

OBJS	= $(SRCS:.c=.o)

NAME	= cub3d.out

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDEH	= -I /usr/X11/include -g -l mlx -framework OpenGL -framework AppKit



all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME):	$(OBJS)
	gcc $(INCLUDEH) -o $(NAME) $(OBJS)

test:
	gcc -D BUFFER_SIZE=1024 $(INCLUDEH) -c $(SRCSTEST)
	gcc $(INCLUDEH) -o $(NAME) $(OTEST)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(GCC) -D BUFFER_SIZE=1 $(INCLUDEH) -c $<  -o $(<:.c=.o)

run: fclean $(NAME)
	./cub3d.out conf.cub
