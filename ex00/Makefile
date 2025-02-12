NAME	=	convert
CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++20 -g
SRCS	=	main.cpp \
			ScalarConverter.cpp
OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re