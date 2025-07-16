SRC_DIR         = src/
OBJ_DIR         = objs/
INC_DIR         = header/

EXEC_DIR        = $(SRC_DIR)exec/
EXEC_OBJDIR     = $(OBJ_DIR)exec/

LIB             = libft/libft.a

BUILTINS_DIR    = $(SRC_DIR)builtins/
BUILTINS_OBJDIR = $(OBJ_DIR)builtins/

EXEC_FILES      =	servo.c				\
					execve.c			\
					exec_error.c		\
					cmd.c				\

SRC_FILES       =	main.c \
                    					word_count.c \
                    					tokenization.c \
                    					token_definition.c \
                    					is_something.c \
                    					lst_create.c \
                    					set_heredoc.c \
                    					set_redir_infile.c \
                    					set_redir_outfile.c \
                    					handle_cmd_type.c \
                    					lst_utils.c \
                    					find_env_var.c \
                    					error_check.c \
                    					free_utils.c \
                    					last_split.c \
                    					utils.c \
                    					new_token_utils.c \
                    					remove_quotes.c \
                    					get_env_var.c \
                    					token_utils.c \
                    					create_and_fill_cmd_tab.c \
                    					pars_env.c \
                    					lst_to_tab.c \
                    					print_utils.c

BUILTINS_FILES  = 	echo.c				\
					cd.c				\
					pwd.c				\
					env.c				\
					export.c			\
					unset.c				\
					exit.c				\
					hub.c				\

SOURCES         = $(addprefix $(SRC_DIR), $(SRC_FILES)) \
                  $(addprefix $(EXEC_DIR), $(EXEC_FILES)) \
                  $(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))

OBJS            = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
                  $(addprefix $(EXEC_OBJDIR), $(EXEC_FILES:.c=.o)) \
                  $(addprefix $(BUILTINS_OBJDIR), $(BUILTINS_FILES:.c=.o))

HEADER          = $(INC_DIR)minishell.h
NAME            = minishell

CC              = gcc
FLAGS           = -Wall -Wextra -Werror -g3 -I$(INC_DIR)

all: $(OBJ_DIR) $(EXEC_OBJDIR) $(BUILTINS_OBJDIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXEC_OBJDIR):
	mkdir -p $(EXEC_OBJDIR)

$(BUILTINS_OBJDIR):
	mkdir -p $(BUILTINS_OBJDIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(EXEC_OBJDIR)%.o: $(EXEC_DIR)%.c $(HEADER)
	mkdir -p $(EXEC_OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(BUILTINS_OBJDIR)%.o: $(BUILTINS_DIR)%.c $(HEADER)
	mkdir -p $(BUILTINS_OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIB) $(HEADER) Makefile
	$(CC) $(FLAGS) -o $@ $(OBJS) -lreadline $(LIB)

$(LIB):
	make -C libft

clean:
	make clean -C libft/
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
