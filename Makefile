# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 15:52:54 by lejulien          #+#    #+#              #
#    Updated: 2020/03/03 07:00:49 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m

SRCS	= $(wildcard ./srcs/cub*.c) $(wildcard ./libft-42/*.c)

OBJS	= $(SRCS:.c=.o)

NAME	= cub3d.out

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDEH = -framework OpenGL -framework AppKit

all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

cubheader:
	@echo ""
	@echo "${_PURPLE}'######::'##::::'##:'########:::'#######::'########::"
	@echo "##... ##: ##:::: ##: ##.... ##:'##.... ##: ##.... ##:"
	@echo "##:::..:: ##:::: ##: ##:::: ##:..::::: ##: ##:::: ##:"
	@echo "##::::::: ##:::: ##: ########:::'#######:: ##:::: ##:"
	@echo "##::::::: ##:::: ##: ##.... ##::...... ##: ##:::: ##:"
	@echo "##::: ##: ##:::: ##: ##:::: ##:'##:::: ##: ##:::: ##:"
	@echo ":######::. #######:: ########::. #######:: ########::"
	@echo ":......::::.......:::........::::.......:::........::"
	@echo ""
	@echo "${_RED}Start compiling ..."
	@echo ""

$(NAME): cubheader $(OBJS)
	gcc $(INCLUDEH) -o $(NAME) $(OBJS) ./minilibx/libmlx.a

bonus: $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

%.o: %.c
	@echo "${_CYAN}Passing from $< to .o ..."
	@$(GCC) -w -D BUFFER_SIZE=1024 $(INCLUDEH) -c $<  -o $(<:.c=.o)

run: fclean $(NAME) clean
	@echo "${_GREEN}Starting Cub3D :"
	@rm -f $(OBJS)
	@./cub3d.out ./maps/conf.cub

runsave: fclean $(NAME) clean
	@echo "${_GREEN}Starting Cub3D :"
	@rm -f $(OBJS)
	@./cub3d.out ./maps/conf.cub --save

