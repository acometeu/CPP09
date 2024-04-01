# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acomet <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 16:30:18 by acomet            #+#    #+#              #
#    Updated: 2024/03/28 20:02:11 by acomet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	RPN

CC			=	c++

CFLAGS		=	-Wall -Wextra -Werror -std=c++98

BUILD		=	build

SRCS		= 	main.cpp \
				RPN.cpp \

OBJS 		= 	$(SRCS:%.cpp=$(BUILD)/%.o)

all: $(NAME)
.PHONY: all

$(BUILD)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(BUILD) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
.PHONY: clean

fclean: clean
	rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
