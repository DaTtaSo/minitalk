CLIENT_NAME 				= 			client

SERVER_NAME					=			server

LIBFT				=			includes/libft/libft.a

HEAD 				=			minitalk.h

OBJ_DIR				=			obj/

CC					=			cc

CFLAGS				=		-Wall -Werror -MMD -MP -g3

SRCS_DIR			=			srcs/

FILE_CL				=			client \
								minitalk_utils

FILE_SV				=			server \
								minitalk_utils

SRC_CL				+=			$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILE_CL)))

SRC_SV				+=			$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILE_SV)))

OBJ_CL			=			$(patsubst $(SRCS_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_CL))
DEP_CL			=			$(patsubst $(SRCS_DIR)%.c,$(OBJ_DIR)%.d,$(SRC_CL))

OBJ_SV			=			$(patsubst $(SRCS_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_SV))
DEP_SV			=			$(patsubst $(SRCS_DIR)%.c,$(OBJ_DIR)%.d,$(SRC_SV))


all:					$(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME):				$(OBJ_CL) $(LIBFT)
							$(CC) $(CFLAGS) $(OBJ_CL) $(LIBFT) -o $@

$(SERVER_NAME):				$(OBJ_SV) $(LIBFT)
							$(CC) $(CFLAGS) $(OBJ_SV) $(LIBFT) -o $@

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
						@mkdir -p $(dir $@)
						$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
	$(MAKE) -C includes/libft

clean:
						make clean -C includes/libft
						@rm -rf $(OBJ_DIR)
						@echo "Deleting $(OBJ_DIR)"


fclean:					clean
							make fclean -C includes/libft
							@rm -rf $(CLIENT_NAME) $(SERVER_NAME)
							@echo "Deleting $(CLIENT_NAME) & $(SERVER_NAME)"


re: 					fclean
						$(MAKE) all

FORCE:

.PHONY: 				re all clean fclean FORCE

-include $(DEP)
