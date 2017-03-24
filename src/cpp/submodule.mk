
DIR__-HERE := DIR__
DIR__-NAME := $(DIR__-HERE)/$(notdir DIR__)

DIR__-BUILD_DIR := $(BUILD_DIR)/$(DIR__-HERE)
DIR__-BUILD_INCLUDE_DIR := $(BUILD_INCLUDE_DIR)/$(DIR__-HERE)
DIR__-BUILD_LIB_DIR := $(BUILD_LIB_DIR)/$(DIR__-HERE)
DIR__-BUILD_OBJ_DIR := $(DIR__-BUILD_LIB_DIR)

DIR__-SRC_DIR := $(DIR__-HERE)/src
DIR__-HDR_DIR := $(DIR__-HERE)/hdr
DIR__-INL_DIR := $(DIR__-HERE)/inl
DIR__-INCLUDE_DIRS := $(DIR__-HDR_DIR) $(DIR__-INL_DIR)
DIR__-DIRS := $(DIR__-INCLUDE_DIRS) $(DIR__-SRC_DIR) $(DIR__-BUILD_OBJ_DIR) $(DIR__-HDR_DIR) $(DIR__-INL_DIR)

DIR__-MODULE_FILES := $(filter-out $(DIR__-DIRS),$(patsubst %/.,%,$(wildcard $(DIR__-HERE)/*/.)))
DIR__-MODULE_MAKEFILES := $(DIR__-MODULE_FILES:%=%/makefile)

DIR__-CPP_FILES := $(wildcard $(DIR__-SRC_DIR)/*.cpp)
DIR__-OBJ_FILES := $(DIR__-CPP_FILES:$(DIR__-SRC_DIR)/%.cpp=$(DIR__-BUILD_OBJ_DIR)/%.o)
DIR__-DEP_FILES := $(DIR__-OBJ_FILES:.o=.d)

DIR__-HPP_FILES := $(wildcard $(DIR__-HDR_DIR)/*.hpp)
DIR__-INL_FILES := $(wildcard $(DIR__-INL_DIR)/*.inl)

DIR__-LIB_NAME := $(BUILD_LIB_DIR)/$(DIR__-NAME).a

DIR__-BUILD_HPP_FILES := $(DIR__-HPP_FILES:$(DIR__-HDR_DIR)/%=$(DIR__-BUILD_INCLUDE_DIR)/%)
DIR__-BUILD_INL_FILES := $(DIR__-INL_FILES:$(DIR__-INL_DIR)/%=$(DIR__-BUILD_INCLUDE_DIR)/%)
DIR__-BUILD_LIB_FILES := $(foreach f,$(DIR__-MODULE_FILES),$(BUILD_LIB_DIR)/$f/$(notdir $f).a)

DIR__-INCLUDE_FLAGS := $(DIR__-INCLUDE_DIRS:%=-I%) $(BUILD_INCLUDE_DIR:%=-I%)

$(DIR__-NAME): $(DIR__-BUILD_INL_FILES) $(DIR__-BUILD_HPP_FILES) $(DIR__-BUILD_LIB_FILES) $(DIR__-OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $(DIR__-OBJ_FILES) $(DIR__-BUILD_LIB_FILES)

$(DIR__-LIB_NAME): $(DIR__-BUILD_INL_FILES) $(DIR__-BUILD_HPP_FILES) $(DIR__-BUILD_LIB_FILES) $(DIR__-OBJ_FILES)
	@mkdir -p $(DIR__-BUILD_LIB_DIR)
	@$(AR) $(AR_FLAGS) $@ $(filter $?,$(DIR__-OBJ_FILES)) $(DIR__-BUILD_LIB_FILES)

$(DIR__-BUILD_OBJ_DIR)/%.o: $(DIR__-SRC_DIR)/%.cpp
	@mkdir -p $(DIR__-BUILD_OBJ_DIR)
	$(CXX) $(CXX_FLAGS) $(DIR__-INCLUDE_FLAGS) -c -o $@ $<

$(DIR__-BUILD_INCLUDE_DIR)/%.hpp: $(DIR__-HDR_DIR)/%.hpp
	@mkdir -p $(DIR__-BUILD_INCLUDE_DIR)
	cp $< $@

$(DIR__-BUILD_INCLUDE_DIR)/%.inl: $(DIR__-INL_DIR)/%.inl
	@mkdir -p $(DIR__-BUILD_INCLUDE_DIR)
	cp $< $@

DIR__.clean: $(DIR__-MODULE_FILES:%=%.clean)
	@$(foreach f,$(DIR__-NAME) $(DIR__-LIB_NAME) $(DIR__-BUILD_OBJ_DIR) $(DIR__-MODULE_MAKEFILES),[[ -e $f ]] && rm -r $f && echo rm -r $f || true;)


$(DIR__-MODULE_MAKEFILES): $(SUBMODULE_MAKEFILE)
	$(M4) -D $(SUBMODULE_MACRO_NAME)=$(@:%/makefile=%) $(SUBMODULE_MAKEFILE) > $@

-include $(DIR__-DEP_FILES)

include $(DIR__-MODULE_MAKEFILES)

.PHONY: clean

