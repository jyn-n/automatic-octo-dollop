SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIRS := .
DIRS := $(INCLUDE_DIRS) $(SRC_DIR) $(OBJ_DIR) #$(LIB_DIR)

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_FILES := $(OBJ_FILES:.o=.d)
MODULE_FILES := $(filter-out $(DIRS),$(patsubst %/.,%,$(wildcard */.)))
LIB_FILES := $(foreach f,$(MODULE_FILES),$f/$f.a)
LD_FLAGS :=
CC_FLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -O2 $(INCLUDE_DIRS:%=-I%)
CC := g++
AR := ar
AR_FLAGS := rv

NAME := cardgame

$(NAME): $(OBJ_FILES) $(LIB_FILES)
	$(CC) $(LD_FLAGS) -o $@ $(OBJ_FILES) $(LIB_FILES)

$(NAME).a: $(OBJ_FILES) $(LIB_FILES)
	$(AR) $(AR_FLAGS) $@ $(OBJ_FILES) $(LIB_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(LIB_FILES): sub
	@make -C $(shell echo $@ | sed 's/\/.*//') $(shell echo $@ | sed 's/.*\///') 

clean:
	@$(foreach f,$(NAME) $(NAME).a $(OBJ_DIR),[[ -e $f ]] && rm -r $f && echo rm -r $f || true;)
	@$(foreach f,$(MODULE_FILES),make -C $f clean)

-include $(DEP_FILES)

foo:
	@echo $(OBJ_FILES)
	@echo $(LIB_FILES)

.PHONY: clean sub

