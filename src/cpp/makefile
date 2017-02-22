CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)
LD_FLAGS :=
CC_FLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -O2
CC := g++

NAME := cardgame

$(NAME): $(OBJ_FILES)
	$(CC) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

clean:
	@$(foreach f,$(wildcard $(NAME) $(OBJ_FILES) $(DEP_FILES)),[[ -f $f ]] && rm $f && echo "rm $f" || true;)

-include $(DEP_FILES)

.PHONY: clean
