SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIRS := .
DIRS := $(INCLUDE_DIRS) $(SRC_DIR) $(OBJ_DIR) #$(LIB_DIR)

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_FILES := $(OBJ_FILES:.o=.d)
MODULE_FILES := $(filter-out $(DIRS),$(patsubst %/.,%,$(wildcard */.)))
MODULE_MAKEFILES := $(MODULE_FILES:%=%/makefile)
LIB_FILES := $(foreach f,$(MODULE_FILES),$f/$f.a)

SUBMODULE_MAKEFILE := submodule.mk

INCLUDE_FLAGS := $(INCLUDE_DIRS:%=-I%)

LD_FLAGS :=
CXX_FLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -O2
CXX := g++
CPP := gcc -E
AR := ar
AR_FLAGS := rv
M4 := m4

NAME := cardgame

$(NAME): $(OBJ_FILES) $(LIB_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $(OBJ_FILES) $(LIB_FILES)

$(NAME).a: $(OBJ_FILES) $(LIB_FILES)
	$(AR) $(AR_FLAGS) $@ $(OBJ_FILES) $(LIB_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -c -o $@ $<

clean: $(MODULE_FILES:%=%.clean)
	@$(foreach f,$(NAME) $(NAME).a $(OBJ_DIR) $(MODULE_MAKEFILES),[[ -e $f ]] && rm -r $f && echo rm -r $f || true;)


$(MODULE_MAKEFILES): $(SUBMODULE_MAKEFILE)
	$(M4) -D DIR__=$(@:%/makefile=%) $(SUBMODULE_MAKEFILE) > $@

-include $(DEP_FILES)

include $(MODULE_MAKEFILES)

.PHONY: clean

