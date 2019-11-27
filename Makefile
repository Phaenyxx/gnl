# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: trifflet <trifflet@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/07 12:41:36 by trifflet     #+#   ##    ##    #+#        #
#    Updated: 2019/11/26 14:12:28 by trifflet    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME		=	get_next_line

HEADER		=	get_next_line.h

SRC			=	get_next_line.c			\
				get_next_line_utils.c	\
				test.c

OBJ			=	${SRC:.c=.o}

FLAGS		=	-Wall -Wextra -Werror -g
DFLAGS		=	-D BUFFER_SIZE=$(SIZE)
SIZE		=	64
%.o: %.c $(HEADER)
			gcc -g $(FLAGS) $(DFLAGS) -c $< -o ${<:.c=.o}

all:    	$(NAME)

$(NAME):	$(OBJ)
			gcc -g $(FLAGS) $(DFLAGS) -o $(NAME) $(OBJ)

clean:
			rm -rf $(OBJ) $(OBJ_BONUS)

fclean: 	clean
			rm -rf $(NAME) *.dSYM

re:			fclean all
