
NAME := cardgame

LD_FLAGS +=
CXX_FLAGS += -std=c++1z -Wall -Wextra -pedantic -MMD -O2
CXX ?= g++
AR ?= ar
AR_FLAGS += crvsT
M4 ?= m4
SED ?= sed
MKDIR ?= mkdir
RM ?= rm
CP ?= cp


TEMPLATE_MAKEFILE := template.mk
TEMPLATE_MACRO_NAME := DIR__

BUILD_DIR := build/
BUILD_INCLUDE_DIR := $(BUILD_DIR)include/
BUILD_OBJ_DIR := $(BUILD_DIR)obj/

BASE_MAKEFILE := $(BUILD_DIR)makefile

DIR_GUARD=$(if $(wildcard $(@D)),,$(MKDIR) -p $(@D))
BUILD_MESSAGE=@echo -e '\x1b[1;34m::\x1b[0m Making \x1b[1;39m$@\x1b[0m'

all: start_message .headers $(NAME)
	@echo -e '\x1b[1;34m::\x1b[0m \x1b[1;39mMaking all completed\x1b[0m'

$(BASE_MAKEFILE): $(TEMPLATE_MAKEFILE)
	$(BUILD_MESSAGE)
	$(DIR_GUARD)
	$(M4) -D $(TEMPLATE_MACRO_NAME)= $(TEMPLATE_MAKEFILE) > $@
	$(SED) -i -e 's/$$(-HERE)\///g' -e 's/\/$$(-HERE)//g' -e 's/-HERE := \//-HERE :=/' $@

-ARCHIVE_NAME := $(BUILD_DIR)main.a

$(NAME): $(-ARCHIVE_NAME)
	$(BUILD_MESSAGE)
	$(CXX) $(LD_FLAGS) -o $@ $^

start_message:
	@echo -e '\x1b[1;34m::\x1b[0m \x1b[1;39mMaking all\x1b[0m'

clean: clean_base_makefile .clean

clean_base_makefile:
	$(RM) $(BASE_MAKEFILE)

.PHONY: all clean clean_base_makefile start_message

include $(BASE_MAKEFILE)

