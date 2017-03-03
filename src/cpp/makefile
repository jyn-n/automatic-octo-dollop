SRC_DIR := src
OBJ_DIR := obj
HDR_DIR := include
INL_DIR := inl
LIB_DIR := lib
INCLUDE_DIRS := $(HDR_DIR) $(INL_DIR)
DIRS := $(INCLUDE_DIRS) $(SRC_DIR) $(OBJ_DIR) $(LIB_DIR)

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)
MODULE_FILES := $(filter-out $(DIRS),$(patsubst %/.,%,$(wildcard */.)))
LIB_FILES := $(patsubst %,$(LIB_DIR)/%.a,$(MODULE_FILES))
LD_FLAGS :=
CC_FLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -O2 $(patsubst %,-I%,$(INCLUDE_DIRS))
CC := g++

NAME := cardgame

$(NAME): $(OBJ_FILES) $(LIB_FILES)
	$(CC) $(LD_FLAGS) -o $@ $(OBJ_FILES) $(LIB_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(LIB_DIR)/%.a: sub
	@make -C $(patsubst lib/%.a,%,$@)
	@mkdir -p $(LIB_DIR)
	mv $(patsubst lib/%.a,%,$@)/$(patsubst lib/%.a,%,$@).a $@

clean:
	@$(foreach f,$(wildcard $(NAME) $(OBJ_FILES) $(DEP_FILES)),[[ -f $f ]] && rm $f && echo "rm $f" || true;)

-include $(DEP_FILES)

.PHONY: clean sub
