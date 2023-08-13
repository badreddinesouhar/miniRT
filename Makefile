CC = cc
CFLAGS =  -I/MLX/include
LDFLAGS = -L"/goinfre/bsouhar/homebrew/Cellar/glfw/3.3.8/lib" -L MLX42/
LDLIBS = -lglfw MLX42/build/libmlx42.a

CFILES = main.c get_next_line.c get_next_line_utils.c utils_rt.c atoif.c libft.c arg_init.c create_win.c light.c
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/,$(CFILES:.c=.o))
NAME = miniRT

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
