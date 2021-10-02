NAME = micro_paint
OBJECTS = micro_paint.o
HEADERS = 
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	@./$(NAME) operationfile

.PHONE: all clean fclean re run
