
DIR__-HERE := DIR__
DIR__-NAME ?= $(DIR__-HERE)/$(notdir DIR__)

DIR__-BUILD_DIR := $(BUILD_DIR)/$(DIR__-HERE)
DIR__-BUILD_INCLUDE_DIR := $(BUILD_INCLUDE_DIR)/$(DIR__-HERE)
DIR__-BUILD_OBJ_DIR := $(BUILD_OBJ_DIR)/$(DIR__-HERE)

DIR__-BUILD_SUBDIRS := $(DIR__-BUILD_INCLUDE_DIR) $(DIR__-BUILD_OBJ_DIR)
DIR__-BUILD_DIRS := $(DIR__-BUILD_DIR) $(DIR__-BUILD_SUBDIRS)

DIR__-SRC_DIR := $(DIR__-HERE)/src
DIR__-HDR_DIR := $(DIR__-HERE)/hdr
DIR__-INL_DIR := $(DIR__-HERE)/inl
DIR__-INCLUDE_DIRS := $(DIR__-HDR_DIR) $(DIR__-INL_DIR)
DIR__-DIRS := $(BUILD_DIR) $(DIR__-INCLUDE_DIRS) $(DIR__-SRC_DIR) $(DIR__-BUILD_DIRS)

DIR__-BASE_DIRS := $(foreach f,$(DIR__-INCLUDE_DIRS),$(notdir $f))

DIR__-MODULE_FILES := $(filter-out $(DIR__-DIRS),$(patsubst %/.,%,$(wildcard $(DIR__-HERE)/*/.)))
DIR__-MODULE_MAKEFILES := $(DIR__-MODULE_FILES:%=$(DIR__-BUILD_DIR)/%.mk)

DIR__-MODULE_BUILD_DIRS := $(foreach f,$(DIR__-MODULE_FILES),$(DIR__-BUILD_DIR)/$f)

DIR__-CPP_FILES := $(wildcard $(DIR__-SRC_DIR)/*.cpp)
DIR__-OBJ_FILES := $(DIR__-CPP_FILES:$(DIR__-SRC_DIR)/%.cpp=$(DIR__-BUILD_OBJ_DIR)/%.o)
DIR__-DEP_FILES := $(DIR__-OBJ_FILES:.o=.d)

DIR__-HPP_FILES := $(wildcard $(DIR__-HDR_DIR)/*.hpp)
DIR__-INL_FILES := $(wildcard $(DIR__-INL_DIR)/*.inl)

DIR__-ARCHIVE_NAME := $(BUILD_OBJ_DIR)/$(DIR__-NAME).a

DIR__-BUILD_HPP_FILES := $(DIR__-HPP_FILES:$(DIR__-HDR_DIR)/%=$(DIR__-BUILD_INCLUDE_DIR)/%)
DIR__-BUILD_INL_FILES := $(DIR__-INL_FILES:$(DIR__-INL_DIR)/%=$(DIR__-BUILD_INCLUDE_DIR)/%)
DIR__-BUILD_ARCHIVE_FILES := $(foreach f,$(DIR__-MODULE_FILES),$(BUILD_OBJ_DIR)/$f/$(notdir $f).a)

DIR__-INCLUDE_FLAGS := $(DIR__-INCLUDE_DIRS:%=-I%) $(BUILD_INCLUDE_DIR:%=-I%)

$(DIR__-NAME): $(DIR__-BUILD_INL_FILES) $(DIR__-BUILD_HPP_FILES) $(DIR__-BUILD_ARCHIVE_FILES) $(DIR__-OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $(DIR__-OBJ_FILES) $(DIR__-BUILD_ARCHIVE_FILES)

$(DIR__-ARCHIVE_NAME): $(DIR__-BUILD_INL_FILES) $(DIR__-BUILD_HPP_FILES) $(DIR__-BUILD_ARCHIVE_FILES) $(DIR__-OBJ_FILES)
	$(DIR_GUARD)
	$(AR) $(AR_FLAGS) $@ $(filter $?,$(DIR__-OBJ_FILES)) $(DIR__-BUILD_ARCHIVE_FILES)

$(DIR__-BUILD_OBJ_DIR)/%.o: $(DIR__-SRC_DIR)/%.cpp
	$(DIR_GUARD)
	$(CXX) $(CXX_FLAGS) $(DIR__-INCLUDE_FLAGS) -c -o $@ $<

$(DIR__-BUILD_INCLUDE_DIR)/%.hpp: $(DIR__-HDR_DIR)/%.hpp
	$(DIR_GUARD)
	$(CP) $< $@

$(DIR__-BUILD_INCLUDE_DIR)/%.inl: $(DIR__-INL_DIR)/%.inl
	$(DIR_GUARD)
	$(CP) $< $@

DIR__.clean: $(DIR__-MODULE_FILES:%=%.clean)
	@$(foreach f,$(DIR__-NAME) $(DIR__-ARCHIVE_NAME) $(DIR__-OBJ_FILES) $(DIR__-DEP_FILES) $(DIR__-MODULE_MAKEFILES) $(DIR__-BUILD_HPP_FILES) $(DIR__-BUILD_INL_FILES),$(if $(wildcard $f),echo $(RM) $f && $(RM) $f,true);)
	@$(foreach f,$(DIR__-BUILD_OBJ_DIR) $(DIR__-BUILD_INCLUDE_DIR) $(DIR__-BUILD_DIR),$(if $(wildcard $f),echo $(RM) -d $f && $(RM) -d $f,true);)


$(DIR__-MODULE_MAKEFILES): $(TEMPLATE_MAKEFILE)
	$(M4) -D $(TEMPLATE_MACRO_NAME)=$(notdir $(@:%.mk=%)) $(TEMPLATE_MAKEFILE) > $@

-include $(DIR__-DEP_FILES)

include $(DIR__-MODULE_MAKEFILES)

.PHONY: DIR__.clean

