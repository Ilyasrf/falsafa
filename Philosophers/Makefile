NAME = philosopher

src = main.c parsing.c utils.c

obj = $(src:.c=.o)

hd = philo.h

flags = -Wall -Wextra -Werror

cc = cc

all: $(NAME)

$(NAME): $(src) $(obj) $(hd)
	$(cc) $(flags) $(src) -o $(NAME)

%.o : %.c
	$(cc) $(flags) -c $< -o $@

clean:
	rm -rf $(obj)

fclean: clean
	rm -rf $(NAME)

re: fclean all