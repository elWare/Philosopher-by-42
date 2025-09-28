NAME = philo

DEL_LINE 		= \033[2K
ITALIC 			= \033[3m
BOLD 			= \033[1m
DEF_COLOR 		= \033[0;39m
GRAY 			= \033[0;90m
RED 			= \033[0;91m
GREEN 			= \033[0;92m
YELLOW 			= \033[0;93m
BLUE 			= \033[0;94m
MAGENTA 		= \033[0;95m
CYAN 			= \033[0;96m
WHITE 			= \033[0;97m
BLACK 			= \033[0;99m
ORANGE 			= \033[38;5;209m
BROWN 			= \033[38;2;184;143;29m
DARK_GRAY 		= \033[38;5;234m
MID_GRAY 		= \033[38;5;245m
DARK_GREEN 		= \033[38;2;75;179;82m
DARK_YELLOW 	= \033[38;5;143m

CC				= cc
CFLAGS			= -Wall -Werror -Wextra -g #-fsanitize=thread
RM				= rm -f

SRCS			= srcs/ft_check.c \
					srcs/ft_controller.c \
					srcs/ft_eat_n_think.c \
					srcs/ft_forks.c \
					srcs/ft_free_tools.c \
					srcs/ft_gettool_a.c \
					srcs/ft_gettool_b.c \
					srcs/ft_gettool_c.c \
					srcs/ft_init.c \
					srcs/ft_philo.c \
					srcs/ft_printing.c \
					srcs/ft_sleep.c \
					srcs/ft_tools_1.c \
					srcs/ft_tools_2.c 

OBJS_DIR		= ./OBJS
INCLUDES		= ./includes

OBJS 			= $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o)


all: $(NAME)

$(NAME): $(OBJS)

	@echo "${DARK_YELLOW}${BOLD}Compiling my ${NAME}... ${DEF_COLOR}"
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "    ____  __    _ __                       __                     "
	@echo "   / __ \/ /_  (_) /___  _________  ____  / /_  ___  __________   "
	@echo "  / /_/ / __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/   "
	@echo " / ____/ / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  )    "
	@echo "/_/   /_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/     "
	@echo "                                /_/                               "
	@echo " "
	@echo "${DARK_GREEN}${BOLD}Compilation of ${NAME} is done! 👌${DEF_COLOR}"
	@echo " "
	@echo "${YELLOW}${BOLD}	Remember, 😡 you must enter...${DEF_COLOR}"
	@echo " "
	@echo " "
	@echo "./philo +";
	@echo "number of philosophers (must be a number between 1 and 200) +"
	@echo "time to die (must be a number greater than 60 ms.) +"
	@echo "time to eat (must be a number greater than 60 ms.) +"
	@echo "time to sleep (must be a number greater than 60 ms.) ..."
	@echo " "
	@echo "${DARK_GREEN}😳 Optionally ${DEF_COLOR}: the number of times each phyllo must eat."
	@echo " "
	@echo "${DARK_GREEN}Now let's see an example:	${DEF_COLOR}./philo 4 800 200 200 5"
	@echo " "
	@echo "This will create 4 philosophers," 
	@echo "each with a time to die 😭 of 800 ms,"
	@echo "a time to eat 🤤 of 200 ms, a time to sleep 🥱 of 200 ms,"
	@echo "and each philosopher must eat 5 times."
	@echo " "
	@echo "${YELLOW}${BOLD}	😵‍💫 Don't be confused ${DEF_COLOR}... and enjoy the experience. 🤪"
	@echo " "
	@echo " "

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
	@echo "${BLUE}${BOLD}Compiling $<...${DEF_COLOR}"

clean:
	@${RM} ${OBJS}
	@echo "${RED}${BOLD}Cleaning objects...${DEF_COLOR}"
	@ if [ -d "${OBJS_DIR}" ]; then ${RM} -r ${OBJS_DIR}; fi
	@echo "${GREEN}${BOLD}Clening objects of ${NAME} is done! 💥${DEF_COLOR}"

fclean: clean
	@${RM} ${NAME}
	@echo "${RED}${BOLD}Cleaning ${NAME}...${DEF_COLOR}"	
	@ if [ -d "$(OBJS_DIR)" ]; then ${RM} -r $(OBJS_DIR); fi
	@echo "${GREEN}${BOLD}Cleaning all of ${NAME} is done! 💥💥${DEF_COLOR}"

re: fclean all
	@echo "${DARK_GREEN}${BOLD}Recompilation is done! 👌${DEF_COLOR}"

.PHONY: all clean fclean re