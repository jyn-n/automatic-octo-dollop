BASE = .
SRC_DIR := $(BASE)/src
OBJ_DIR := $(BASE)/obj
LIB_DIR := $(BASE)/lib
INCLUDE_DIRS := $(BASE)/.
DIRS := $(INCLUDE_DIRS) $(SRC_DIR) $(OBJ_DIR) $(LIB_DIR)

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)
MODULE_FILES := $(filter-out $(DIRS),$(patsubst %/.,%,$(wildcard $(BASE)/*/.)))
LIB_FILES := $(patsubst %,$(LIB_DIR)/%.a,$(MODULE_FILES))
LD_FLAGS :=
CC_FLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -O2 $(patsubst %,-I%,$(INCLUDE_DIRS))
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

$(LIB_DIR)/%.a: %/%.a
	@make -C $(patsubst lib/%.a,%,$@) $(patsubst lib/%,%,$@)
	@mkdir -p $(LIB_DIR)
	cp $(patsubst lib/%.a,%,$@)/$(patsubst lib/%.a,%,$@).a $@

clean: $(BASE).clean

$(BASE).clean: $(foreach f,$(MODULE_FILE),$f.clean)
	@$(foreach f,$(NAME) $(NAME).a $(OBJ_DIR) $(LIB_DIR),[[ -e $f ]] && rm -r $f && echo rm -r $f || true;)

-include $(DEP_FILES)

include $(patsubst %,%/makefile,$(MODULE_FILES))

.PHONY: clean $(BASE).clean

