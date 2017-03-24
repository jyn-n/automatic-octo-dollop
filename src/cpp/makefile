
NAME := cardgame

BUILD_DIR := build
BUILD_INCLUDE_DIR := $(BUILD_DIR)/include
BUILD_LIB_DIR := $(BUILD_DIR)/obj
BUILD_OBJ_DIR := $(BUILD_LIB_DIR)

BUILD_REQUIREMENTS := build_requirements__

SRC_DIR := src
HDR_DIR := hdr
INL_DIR := inl
INCLUDE_DIRS := $(HDR_DIR) $(INL_DIR)
DIRS := $(INCLUDE_DIRS) $(SRC_DIR) $(BUILD_DIR) $(HDR_DIR) $(INL_DIR)

MODULE_FILES := $(filter-out $(DIRS),$(patsubst %/.,%,$(wildcard */.)))
MODULE_MAKEFILES := $(MODULE_FILES:%=%/makefile)

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BUILD_OBJ_DIR)/%.o)
DEP_FILES := $(OBJ_FILES:.o=.d)

HPP_FILES := $(wildcard $(HDR_DIR)/*.hpp)
INL_FILES := $(wildcard $(INL_DIR)/*.inl)

LIB_NAME := $(BUILD_LIB_DIR)/$(NAME).a

BUILD_HPP_FILES := $(HPP_FILES:$(HDR_DIR)/%=$(BUILD_INCLUDE_DIR)/%)
BUILD_INL_FILES := $(INL_FILES:$(INL_DIR)/%=$(BUILD_INCLUDE_DIR)/%)
BUILD_LIB_FILES := $(foreach f,$(MODULE_FILES),$(BUILD_LIB_DIR)/$f/$(notdir $f).a)

SUBMODULE_MAKEFILE := submodule.mk
SUBMODULE_MACRO_NAME := DIR__

INCLUDE_FLAGS := $(INCLUDE_DIRS:%=-I%) $(BUILD_INCLUDE_DIR:%=-I%)

LD_FLAGS :=
CXX_FLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -O2
CXX := g++
AR := ar
AR_FLAGS := rvT
M4 := m4

$(NAME): $(BUILD_INL_FILES) $(BUILD_HPP_FILES) $(BUILD_LIB_FILES) $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $(OBJ_FILES) $(BUILD_LIB_FILES)

$(LIB_NAME): $(BUILD_INL_FILES) $(BUILD_HPP_FILES) $(BUILD_LIB_FILES) $(OBJ_FILES)
	@mkdir -p $(BUILD_LIB_DIR)
	$(AR) $(AR_FLAGS) $@ $(filter $?,$(OBJ_FILES)) $(LIB_FILES)

$(BUILD_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_OBJ_DIR)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -c -o $@ $<

$(BUILD_INCLUDE_DIR)/%.hpp: $(HDR_DIR)/%.hpp
	@mkdir -p $(BUILD_INCLUDE_DIR)
	cp $< $@

$(BUILD_INCLUDE_DIR)/%.inl: $(INL_DIR)/%.inl
	@mkdir -p $(BUILD_INCLUDE_DIR)
	cp $< $@

clean: $(MODULE_FILES:%=%.clean)
	@#if using separate BUILD_LIB_DIR and BUILD_OBJ_DIR remember to remove both here
	@$(foreach f,$(NAME) $(LIB_NAME) $(OBJ_FILES) $(DEP_FILES) $(MODULE_MAKEFILES) $(BUILD_HPP_FILES) $(BUILD_INL_FILES),$(if $(wildcard $f),echo rm $f && rm $f,true);)
	@$(foreach f,$(BUILD_OBJ_DIR) $(BUILD_INCLUDE_DIR) $(BUILD_DIR),$(if $(wildcard $f),echo rm -d $f && rm -d $f,true);)


$(MODULE_MAKEFILES): $(SUBMODULE_MAKEFILE)
	$(M4) -D $(SUBMODULE_MACRO_NAME)=$(@:%/makefile=%) $(SUBMODULE_MAKEFILE) > $@

-include $(DEP_FILES)

include $(MODULE_MAKEFILES)

.PHONY: clean

