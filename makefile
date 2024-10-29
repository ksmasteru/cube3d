NAME = curva

srcs = main.c events.c

objs = $(srcs:.c=.o)

all : $(NAME)

%.o : %.c
	gcc -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME) : $(objs)
	gcc $(objs) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -rf  $(objs)

fclean : clean
	rm -rf $(NAME)

re : fclean all

