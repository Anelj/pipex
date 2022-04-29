NAME = pipex
DIR_OBJ = obj
LIST_TMP = ft_execute.c ft_split.c ft_splitpath.c ft_strjoin.c ft_strncmp.c\
           ft_pipe_helper.c ft_standard_pipe.c main.c ft_cmd.c ft_heredoc.c\
           ft_heredoc_helper.c ft_split_helper.c
LIST = $(addprefix src/, $(LIST_TMP))
LISTB_TMP = ft_execute_bonus.c ft_split_bonus.c ft_splitpath_bonus.c ft_strjoin_bonus.c ft_strncmp_bonus.c\
            ft_pipe_helper_bonus.c ft_standard_pipe_bonus.c main_bonus.c ft_cmd_bonus.c ft_heredoc_bonus.c\
            ft_heredoc_helper_bonus.c ft_split_helper_bonus.c
LISTB = $(addprefix bonus/, $(LISTB_TMP))
OBJ = $(addprefix $(DIR_OBJ)/, $(LIST_TMP:.c=.o))
OBJB = $(addprefix $(DIR_OBJ)/, $(LISTB_TMP:.c=.o))

all : $(NAME)

$(NAME): delprogr $(OBJ)
	gcc -Wall -Werror -Wextra -g $(OBJ) -o $(NAME)

bonus: delprogr $(OBJB)
	gcc -Wall -Werror -Wextra -g $(OBJB) -o $(NAME)

$(DIR_OBJ)/%.o : ./src/%.c ./src/ft_pipex.h
	mkdir -p $(DIR_OBJ)
	gcc -Wall -Werror -Wextra -g -c $< -o $@

$(DIR_OBJ)/%.o : ./bonus/%.c ./bonus/ft_pipex_bonus.h
	mkdir -p $(DIR_OBJ)
	gcc -Wall -Werror -Wextra -g -c $< -o $@

delprogr :
	rm -rf $(NAME)

clean :
	rm -rf $(DIR_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re delprogr bonus
