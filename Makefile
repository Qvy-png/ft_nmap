NAME = ft_nmap

CC = cc

SRCS = srcs

CFLAGS = -Wall -Werror -Wextra -g3

RM = rm

OBJ = $(SRC:.c=.o)

SRC =	$(SRCS)/main.c		\
		$(SRCS)/utils.c		\
		$(SRCS)/ports.c		\
		$(SRCS)/flags.c		\
		$(SRCS)/luggage.c	\
		$(SRCS)/threads.c
		
INCL =	includes/ft_nmap.h

all: $(NAME)

bonus: $(NAME)_bonus

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@
		
$(NAME): $(OBJ)
	@echo " \033[0;31mCompiling $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo " \033[0;32mSuccess\033[0m"

clean:
	@$(RM) -f $(OBJ)
	@echo " \033[0;32mCleaning done!\033[0m"
	
fclean: clean
	@$(RM) -f $(NAME) 
	@$(RM) -f $(NAME)_bonus

re: fclean all

	
.PHONY: clean fclean
