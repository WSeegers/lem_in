# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/03 20:54:46 by wseegers          #+#    #+#              #
#    Updated: 2018/06/15 02:25:23 by wseegers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
CC = clang
CFLAGS = -Werror -Wall -Wextra 
INC = -I toolkit-wtc/include -I src
LIB = toolkit-wtc/toolkit-wtc.a

SRC_PATH = src
SRC = parse_env.c parse_graph.c get_paths.c issue_orders.c
BIN_PATH = bin
BIN := $(SRC:%.c=$(BIN_PATH)/%.o)
DEP := $(BIN:%.o=%.d)

all : Make_LIB $(NAME) 

Make_LIB :
	make -C toolkit-wtc

$(NAME) : % : $(SRC_PATH)/%.c $(BIN) $(LIB)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

$(BIN_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(BIN_PATH)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

-include $(DEP)

clean :
	rm -rf $(BIN_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C toolkit-wtc

re : fclean all

.PHONEY : usage all make_all  clean  fclean  re
