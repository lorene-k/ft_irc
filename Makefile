# ------------  COLORS  ----------------------------------------------------- #
RED				=	\\033[0;31m
GREEN			=	\\033[0;32m
YELLOW			=	\\033[0;33m
DEFAULT			=	\\033[0m
ORANGE			=	\033[0;38;5;208m
BLUE  			=	\033[0;34m
CYAN  			=	\033[0;36m
PURPLE			=	\033[0;35m
MAUVE 			=	\033[38;5;177m

# ------------  PROJECT  ---------------------------------------------------- #
NAME			=	ircserv
BOT				=	ircbot

# ------------  DIRECTORIES  ------------------------------------------------ #
SRC_DIR			=	srcs/
INC_DIR			= 	includes/
OBJ_DIR			=	objs/

# ------------  SOURCES  ---------------------------------------------------- #
SRC_FLS			=	main.cpp \
					Channel.cpp \
					Channel_utils.cpp \
					Client.cpp \
					Client_data.cpp \
					Client_responses.cpp \
					Client_utils.cpp \
					Client/Commands/Client_CAP.cpp Client/Commands/Client_INVITE.cpp Client/Commands/Client_JOIN.cpp \
					Client/Commands/Client_KICK.cpp Client/Commands/Client_MODE.cpp Client/Commands/Client_NAMES.cpp \
					Client/Commands/Client_NICK.cpp Client/Commands/Client_PART.cpp Client/Commands/Client_PASS.cpp \
					Client/Commands/Client_PING.cpp Client/Commands/Client_PRIVMSG.cpp Client/Commands/Client_QUIT.cpp \
					Client/Commands/Client_TOPIC.cpp Client/Commands/Client_USER.cpp Client/Commands/Client_WHO.cpp \
					Server.cpp \
					Server_init.cpp \
					Server_run.cpp \
					Server_utils.cpp \
					Server/Commands/Server_INVITE.cpp Server/Commands/Server_JOIN.cpp \
					Server/Commands/Server_MODE.cpp Server/Commands/Server_TOPIC.cpp

BOT_SRC_FLS		=	Bot_main.cpp Bot.cpp Bot_run.cpp Bot_actions.cpp

# ------------  FILEPATHS  -------------------------------------------------- #
SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FLS))
OBJS			=	$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o, $(SRCS))

BOT_SRCS		=	$(addprefix $(SRC_DIR), $(BOT_SRC_FLS))
BOT_OBJS		=	$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o, $(BOT_SRCS))

# ------------  FLAGS  ------------------------------------------------------ #
RM_FLAGS		=	-rf
CPP_FLAGS		=	-Wall -Wextra -Werror -std=c++98 -g
INCLUDES		=	-I$(INC_DIR)

# ------------  COMMANDS  --------------------------------------------------- #
CC				=	c++
RM				=	rm $(RM_FLAGS)

# ------------  RULES  ------------------------------------------------------ #
all:				serv bot

serv:				${NAME}

bot:				$(BOT_OBJS)
					@$(CC) $(CPP_FLAGS) -o $(BOT) $(BOT_OBJS)
					@echo "$(GREEN)Compiled $(BOT)$(DEFAULT)"

$(OBJ_DIR)%.o:		$(SRC_DIR)Bot/%.cpp
					@mkdir -p $(OBJ_DIR)Bot
					@$(CC) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

$(NAME):			$(OBJS)
					@$(CC) $(CPP_FLAGS) -o $(NAME) $(OBJS)
					@echo "$(GREEN)Compiled $(NAME)$(DEFAULT)"

$(OBJ_DIR)Client/Commands/%.o: $(SRC_DIR)Client/Commands/%.cpp
					@mkdir -p $(dir $@)
					@$(CC) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o:		$(SRC_DIR)Channel/%.cpp
					@mkdir -p $(OBJ_DIR)Channel
					@$(CC) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o:		$(SRC_DIR)Client/%.cpp
					@mkdir -p $(OBJ_DIR)Client/Commands
					@$(CC) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o:		$(SRC_DIR)Server/%.cpp
					@mkdir -p $(OBJ_DIR)Server/Commands
					@$(CC) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o:		$(SRC_DIR)%.cpp
					@mkdir -p $(OBJ_DIR)
					@$(CC) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

clean:
					@$(RM) $(OBJ_DIR)
					@echo "$(ORANGE)Cleaned $(OBJ_DIR)$(DEFAULT)"

fclean:				clean
					@$(RM) $(NAME) $(BOT)
					@echo "$(RED)Cleaned $(NAME) and $(BOT)$(DEFAULT)"

re:					fclean all

.PHONY: 			all clean fclean re