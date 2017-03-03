SRC_DIR := src
OBJ_DIR := obj
HDR_DIR := include
INL_DIR := inl
INCLUDE_DIRS := $(HDR_DIR) $(INL_DIR)
DIRS := $(INCLUDE_DIRS) $(SRC_DIR) $(OBJ_DIR)

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)
MODULE_FILES := $(filter-out $(DIRS),$(patsubst %/.,%,$(wildcard */.)))
LIB_FILES := $(patsubst %,%/%.a,$(MODULE_FILES))
LD_FLAGS :=
CC_FLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -O2 $(patsubst %,-I%,$(INCLUDE_DIRS))
CC := g++
AR := ar
AR_FLAGS := rv

NAME := core

$(NAME).a: $(OBJ_FILES) submodules
	$(AR) $(AR_FLAGS) $@ $(OBJ_FILES) $(LIB_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CC_FLAGS) -c -o $@ $<

submodules:
	@$(foreach f,$(MODULE_FILES),make -C $f)

clean:
	@$(foreach f,$(wildcard $(NAME) $(OBJ_FILES) $(DEP_FILES)),[[ -f $f ]] && rm $f && echo "rm $f" || true;)

-include $(DEP_FILES)

foo:
	@echo $(MODULE_FILES)
	@echo $(LIB_FILES)

.PHONY: clean submodules foo
