# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ple-lez <ple-lez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 09:20:47 by ple-lez           #+#    #+#              #
#    Updated: 2022/12/06 14:48:58 by ple-lez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

LIBFT_PATH=./libft
LIBFT=${LIBFT_PATH}/libft.a
MAKE_LIBFT=make -C ${LIBFT_PATH}
LIB_FLAGS=-L${LIBFT_PATH} -lft -lreadline

INC_DIR=./include
INC_FLAGS=-I${INC_DIR} -I${LIBFT_PATH}

SRC_DIR=./src/

MAIN_FILES=main.c init.c path.c signal.c env_variables.c free.c minishell.c
MAIN_DIR=./
MAIN=$(addprefix ${MAIN_DIR}, ${MAIN_FILES})

PARSER_FILES=lexer.c astree.c parser.c parser_utils.c lexer_utils.c \
			 wildcard.c lexer_check.c
PARSER_DIR=./parser/
PARSER=$(addprefix ${PARSER_DIR}, ${PARSER_FILES})

CMDS_FILES=execute.c execute_command.c execute_pipe.c execute_redirection.c \
		   execute_logic.c error.c execute_utils.c split_args.c
CMDS_DIR=./commands/
CMDS=$(addprefix ${CMDS_DIR}, ${CMDS_FILES})

BUILTINS_FILES=echo.c builtins.c export.c env.c unset.c exit.c cd.c pwd.c
BUILTINS_DIR=./builtins/
BUILTINS=$(addprefix ${BUILTINS_DIR}, ${BUILTINS_FILES})

SRC_FILES= $(MAIN) $(PARSER) $(CMDS) $(BUILTINS)


OBJ_DIR=./obj/
OBJ_FILES=${SRC_FILES:%.c=${OBJ_DIR}%.o}

TEST_EXE=run_test
UNITY_CONFIG_DEFINES=-D UNITY_OUTPUT_COLOR -D UNITY_FIXTURE_NO_EXTRAS
UNITY_INC=-I./unity/src -I./unity/extras/fixture/src

TEST_FILES=unity/src/unity.c unity/extras/fixture/src/unity_fixture.c \
		   test/main/all_tests.c test/main/all_tests_runner.c test/test_lexer.c \
		   test/test_parser.c test/test_path.c test/test_env.c test/test_export.c \
		   test/test_unset.c test/test_args.c test/test_wildcards.c \
		   src/init.c src/path.c src/env_variables.c src/free.c \
		   $(addprefix $(SRC_DIR), $(PARSER)) \
		   $(addprefix $(SRC_DIR), $(BUILTINS)) \
		   $(addprefix $(SRC_DIR), $(CMDS))

TEST_OBJ_DIR=./test_obj/
TEST_OBJ_FILES=${TEST_FILES:%.c=${TEST_OBJ_DIR}%.o}

RM=rm -f
CC=cc
CFLAGS=-Wall -Werror -Wextra -g3

all: ${NAME}

${NAME}: ${LIBFT} ${OBJ_FILES}
	${CC} ${CFLAGS} ${INC_FLAGS} -o ${NAME} ${OBJ_FILES} ${LIB_FLAGS}

${OBJ_FILES}: ${OBJ_DIR}%.o : $(SRC_DIR)%.c
#	mkdir -p ${OBJ_DIR}
	mkdir -p $(@D)
	${CC} ${CFLAGS} ${INC_FLAGS} -c $< -o $@

${LIBFT}:
	${MAKE_LIBFT}

clean:
	${RM} -r ${OBJ_DIR}
	${RM} -r ${TEST_OBJ_DIR}
	${MAKE_LIBFT} clean

fclean: clean
	${RM} ${NAME}
	${RM} ${TEST_EXE}
	${MAKE_LIBFT} fclean

re: fclean
	make all
	${MAKE_LIBFT} re

test: ${TEST_OBJ_DIR} ${TEST_EXE}

${TEST_OBJ_DIR}:
	mkdir -p $@

${TEST_EXE}: ${LIBFT} ${TEST_OBJ_FILES}
	${CC} ${CFLAGS} $^ -o $@ ${LIB_FLAGS}

${TEST_OBJ_FILES}: ${TEST_OBJ_DIR}%.o :%.c
	mkdir -p $(@D)
	${CC} ${CFLAGS} ${UNITY_CONFIG_DEFINES} ${UNITY_INC} ${INC_FLAGS} -c $< -o $@

.PHONY: all clean fclean re test
