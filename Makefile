# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/02/12 17:11:13 by mcanal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME ?= 42sh
CFLAGS += -Werror -Wextra -Wall
RCFLAGS = -O2 -fomit-frame-pointer
DCFLAGS = -g3 -DDEBUG
SCFLAGS = $(DCFLAGS) -fsanitize=address,undefined -ferror-limit=5
CC ?= gcc
MAKE += -j4

INC_PATH = include
SRC_PATH = src
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
3TH_PATH = vendor

LIBS = ps rl ft
ifneq (,$(findstring dev,$(NAME)))
LIB_NAME = $(addsuffix .dev, $(LIBS))
else ifneq (,$(findstring san,$(NAME)))
LIB_NAME = $(addsuffix .san, $(LIBS))
else
LIB_NAME = $(LIBS)
endif
3TH_NAME = libft librl libps
SRC_NAME = \
	bi.c bi/cd.c bi/echo.c bi/env.c bi/exit.c bi/export.c bi/setenv.c \
	bi/unset.c bi/unsetenv.c bi/history.c bi/read.c\
	comp.c \
	env.c \
	err.c \
	eval.c eval/ampr.c eval/andor.c eval/argv.c eval/assign.c eval/cmd.c \
	eval/cmp.c eval/compound.c eval/heredoc.c eval/lamp.c eval/list.c \
	eval/pipeline.c eval/ramp.c eval/raout.c eval/redir.c eval/rin.c \
	eval/rout.c eval/sep.c eval/simple.c eval/subshell.c \
	exp.c exp/arith.c exp/backslash.c exp/backtick.c exp/brace.c exp/dollars.c \
	exp/glob.c exp/quote.c exp/tidle.c \
	exp/comm.c exp/comm/read.c \
	exp/param.c exp/param/env.c exp/param/subst.c exp/param/val.c \
	lex.c lex/heredoc.c lex/op.c lex/utils.c lex/dollar.c lex/word.c \
	main.c \
	prompt.c \
	shell.c \
	tok.c \
	var.c

3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

ifneq (,$(findstring dev,$(NAME)))
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.dev.a|g")
else ifneq (,$(findstring san,$(NAME)))
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.san.a|g")
else
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.a|g")
endif

all:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) &&) true
endif
	+$(MAKE) $(NAME) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

dev:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev &&) true
endif
	+$(MAKE) $(NAME).dev "NAME = $(NAME).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"

san:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san &&) true
endif
	+$(MAKE) $(NAME).san "NAME = $(NAME).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "CC = clang"

$(NAME): $(3DE) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(LNK) $(OBJ) $(LIB) -o $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): exe"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(shell dirname $@)
	@printf "\r%-20s$<\n" "$(NAME):"
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

clean:
	rm -f $(OBJ) $(DEP)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

fclean: clean
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean &&) true
endif
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d | sort -r | xargs rmdir || true
	rm -f $(NAME){,.san,.dev}
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

re: clean all

test: all
	./test.sh . $(NAME)

testdev: dev
	./test.sh . $(NAME).dev

testsan: san
	./test.sh . $(NAME).san

valgrind: dev
	./valgrind.sh . $(NAME).dev

-include $(DEP)

ifndef VERBOSE
.SILENT:
endif

.PHONY: all, dev, san, $(NAME), clean, fclean, re, test, testdev, testsan, \
  valgrind
