# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 16:41:36 by lbenedar          #+#    #+#              #
#    Updated: 2022/02/09 16:35:19 by lbenedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_containers
NAME_FT		=	ft_test
NAME_STD	=	std_test
NAME_DIFF	=	result.diff
DIFF_DIR	=	diff
LOGS_DIR	=	logs
INC_DIR		=	includes
FT			=	ft
STD			=	std
CC			=	clang++
SRCS		=	main.cpp
OBJS		=	$(SRCS:.cpp=.o)
INC			=	-I$(INC_DIR) \
				-I$(INC_DIR)/vector \
				-I$(INC_DIR)/stack \
				-I$(INC_DIR)/map \
				-I$(INC_DIR)/set
HEAD		=	$(INC_DIR)/pair.hpp \
				$(INC_DIR)/utils.hpp \
				$(INC_DIR)/reverse_iterator.hpp \
				$(INC_DIR)/vector/vector.hpp \
				$(INC_DIR)/stack/stack.hpp \
				$(INC_DIR)/map/map.hpp \
				$(INC_DIR)/map/rbtree.hpp \
				$(INC_DIR)/set/set.hpp \
				$(INC_DIR)/set/rbtree_set.hpp
CFLAGS		=	-Wextra -Werror -Wall -std=c++98 $(INC)
OPTFLAGS	=	-O0
MAKE		=	make
RM			=	rm -rf

all:
	@$(MAKE) $(NAME) -j 4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) -o $(NAME)

bonus: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DIFF_DIR)/$(NAME_DIFF)
	$(RM) $(NAME_FT)
	$(RM) $(NAME_STD)
	$(RM) $(LOGS_DIR)/$(FT)
	$(RM) $(LOGS_DIR)/$(STD)

re: fclean all

test: $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) -o $(NAME_FT)
	@$(MAKE) clean
	$(CC) $(CFLAGS) -DSTD1 $(OPTFLAGS) -c main.cpp -o main.o
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) -o $(NAME_STD)
	./$(NAME_FT) > $(LOGS_DIR)/$(FT)
	./$(NAME_STD) > $(LOGS_DIR)/$(STD)
	diff -u $(LOGS_DIR)/$(FT) $(LOGS_DIR)/$(STD) > $(DIFF_DIR)/$(NAME_DIFF) || true
	$(RM) $(NAME_FT)
	$(RM) $(NAME_STD)

%.o:%.cpp $(HEAD)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

.PHONY: all bonus clean fclean re