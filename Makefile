NAME = micro_paint
ALT = mini_paint
OBJECTS = micro_paint.o
ALT_OBJECTS = mini_paint.o
HEADERS = 
CFLAGS = -Wall -Werror -Wextra

all: $(NAME) $(ALT)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(ALT): $(ALT_OBJECTS)
	$(CC) $(CFLAGS) $(ALT_OBJECTS) -o $(ALT)

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(ALT_OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -f $(ALT)

re: fclean all

runrectangle: all
	@./$(NAME) operationfile.rectangle

runcircle: all
	@./$(ALT) operationfile.circle

run: runrectangle runcircle

.PHONE: all clean fclean re runrectangle runcircle run
