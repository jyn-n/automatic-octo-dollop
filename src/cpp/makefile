
NAME := cardgame

LD_FLAGS ?=
CXX_FLAGS ?= -std=c++17 -Wall -Wextra -pedantic -MMD -O2
CXX ?= g++
AR ?= ar
AR_FLAGS ?= rvT
M4 ?= m4
SED ?= sed
MKDIR ?= mkdir
RM ?= rm
CP ?= cp

all: $(NAME)

TEMPLATE_MAKEFILE := template.mk
TEMPLATE_MACRO_NAME := DIR__

BUILD_DIR := build
BUILD_INCLUDE_DIR := $(BUILD_DIR)/include
BUILD_OBJ_DIR := $(BUILD_DIR)/obj

BASE_MAKEFILE := $(BUILD_DIR)/makefile

DIR_GUARD=@$(MKDIR) -p $(@D)

$(BASE_MAKEFILE): $(TEMPLATE_MAKEFILE)
	$(DIR_GUARD)
	$(M4) -D $(TEMPLATE_MACRO_NAME)= $(TEMPLATE_MAKEFILE) > $@
	$(SED) -i -e 's/$$(-HERE)\///g' -e 's/\/$$(-HERE)//g' $@

#$(BUILD_DIR):
#	$(MKDIR) $@

-NAME := $(NAME)

clean: clean_base_makefile .clean

clean_base_makefile:
	$(RM) $(BASE_MAKEFILE)

.PHONY: all clean clean_base_makefile

include $(BASE_MAKEFILE)

