# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 15:57:13 by hbenazza          #+#    #+#              #
#    Updated: 2023/12/23 14:41:16 by hbenazza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	server	client

BONUS =	server_bonus	client_bonus

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

${NAME}: server.c client.c
	@cc ${FLAGS} server.c -o server
	@cc ${FLAGS} client.c -o client
	@echo "DONE!"

all: ${NAME} bonus

clean:
	@echo "Cleaning..."
	@${RM} server client

fclean:
	@echo "Cleaning..."
	@${RM} ${NAME} ${BONUS}

re: clean ${NAME}

${BONUS}: server_bonus.c client_bonus.c
	@cc ${FLAGS} server_bonus.c -o server_bonus
	@cc ${FLAGS} client_bonus.c -o client_bonus
	@echo "BONUS DONE!"

bonus:	${BONUS}
