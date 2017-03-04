DIR__-HERE := DIR__
DIR__-SRC_DIR := $(DIR__-HERE)/src
DIR__-OBJ_DIR := $(DIR__-HERE)/obj
DIR__-INCLUDE_DIRS := $(DIR__-HERE)/
DIR__-DIRS := $(DIR__-INCLUDE_DIRS) $(DIR__-SRC_DIR) $(DIR__-OBJ_DIR)

DIR__-CPP_FILES := $(wildcard $(DIR__-SRC_DIR)/*.cpp)
DIR__-OBJ_FILES := $(DIR__-CPP_FILES:$(DIR__-SRC_DIR)/%.cpp=$(DIR__-OBJ_DIR)/%.o)
DIR__-DEP_FILES := $(DIR__-OBJ_FILES:.o=.d)
DIR__-MODULE_FILES := $(filter-out $(DIR__-DIRS),$(patsubst %/.,%,$(wildcard $(DIR__-HERE)/*/.)))
DIR__-MODULE_MAKEFILES := $(DIR__-MODULE_FILES:%=%/makefile)
DIR__-LIB_FILES := $(foreach f,$(DIR__-MODULE_FILES),$f/$(notdir $f).a)

DIR__-INCLUDE_FLAGS := $(DIR__-INCLUDE_DIRS:%=-I%)

DIR__-NAME := DIR__/$(notdir DIR__)

$(DIR__-NAME): $(DIR__-OBJ_FILES) $(DIR__-LIB_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $(DIR__-OBJ_FILES) $(DIR__-LIB_FILES)

$(DIR__-NAME).a: $(DIR__-OBJ_FILES) $(DIR__-LIB_FILES)
	@$(AR) $(AR_FLAGS) $@ $(DIR__-OBJ_FILES) $(DIR__-LIB_FILES)

$(DIR__-OBJ_DIR)/%.o: $(DIR__-SRC_DIR)/%.cpp
	@mkdir -p $(DIR__-OBJ_DIR)
	$(CXX) $(CXX_FLAGS) $(DIR__-INCLUDE_FLAGS) -c -o $@ $<

DIR__.clean: $(DIR__-MODULE_FILES:%=%.clean)
	@$(foreach f,$(DIR__-NAME) $(DIR__-NAME).a $(DIR__-OBJ_DIR) $(DIR__-MODULE_MAKEFILES),[[ -e $f ]] && rm -r $f && echo rm -r $f || true;)

$(DIR__-MODULE_MAKEFILES): $(SUBMODULE_MAKEFILE)
	$(M4) -D $(SUBMODULE_MACRO_NAME)=$(@:%/makefile=%) $(SUBMODULE_MAKEFILE) > $@

-include $(DIR__-DEP_FILES)

include $(DIR__-MODULE_MAKEFILES)

.PHONY: DIR__.clean

