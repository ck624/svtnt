

PWD := $(shell pwd)
SVTNT_TESTS_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
SVTNT_DIR := $(abspath $(SVTNT_TESTS_DIR)/..)
SVTNT_SCRIPTS_DIR := $(SVTNT_DIR)/scripts

BUILD_DIR := $(SVTNT_TESTS_DIR)/build

GOOGLETEST_VERSION=1.8.0
GOOGLETEST_DIR=googletest-release-$(GOOGLETEST_VERSION)
GOOGLETEST_ZIP=$(GOOGLETEST_DIR).tar.gz
GOOGLETEST_URL=https://github.com/google/googletest/archive/release-$(GOOGLETEST_VERSION).tar.gz
UNPACK_TARGETS += $(BUILD_DIR)/googletest.unpack

include $(SVTNT_SCRIPTS_DIR)/common.mk

MK_INCLUDES += $(SVTNT_DIR)/compiler/compiler.mk
MK_INCLUDES += $(SVTNT_DIR)/model/model.mk
MK_INCLUDES += $(SVTNT_DIR)/svtnt/svtnt.mk

SVTNT_TESTS_SRC = $(notdir $(wildcard $(SVTNT_TESTS_DIR)/src/*.cpp))
SRC_DIRS += $(SVTNT_TESTS_DIR)/src
SRC_DIRS += $(BUILD_DIR)/$(GOOGLETEST_DIR)/googletest
SRC_DIRS += $(BUILD_DIR)/$(GOOGLETEST_DIR)/googletest/src
SRC_DIRS += $(BUILD_DIR)/$(GOOGLETEST_DIR)/googletest/include

ifeq (true,$(BUILD))

include $(MK_INCLUDES)

else # not build
ifeq (,$(J))
NUM_CORES := $(shell cat /proc/cpuinfo | grep 'processor.*:' | wc -l)
else
NUM_CORES := $(J)
endif
endif # end not build

GCC_BINDIR := $(dir $(shell which g++))
LD_LIBRARY_PATH := $(PLATFORM_LIB_DIR):$(GCC_BINDIR)/../lib64:$(LD_LIBRARY_PATH)
export LD_LIBRARY_PATH


RULES := 1

vpath %.cpp $(SRC_DIRS)
vpath %.cc $(SRC_DIRS)

ifeq (true,$(BUILD))
include $(MK_INCLUDES)
endif


all :
	$(Q)echo "PWD=$(PWD) SCRIPTS_DIR=$(SVTNT_SCRIPTS_DIR) UNPACK_TARGETS=$(UNPACK_TARGETS)"
	$(Q)if test ! -d $(BUILD_DIR); then mkdir -p $(BUILD_DIR); fi
	$(Q)$(MAKE) BUILD=true -j$(NUM_CORES) -C $(BUILD_DIR) -f $(SVTNT_TESTS_DIR)/Makefile __unpack 
	$(Q)$(MAKE) BUILD=true -j$(NUM_CORES) -C $(BUILD_DIR) -f $(SVTNT_TESTS_DIR)/Makefile __build
	$(Q)mkdir -p $(SVTNT_TESTS_DIR)/rundir
	$(Q)cd $(SVTNT_TESTS_DIR)/rundir ; $(BUILD_DIR)/svtnt_tests$(EXEEXT) $(GTEST_ARGS)
	
ifeq (true,$(BUILD))

__unpack : $(UNPACK_TARGETS)

__build : svtnt_tests$(EXEEXT)

svtnt_tests$(EXEEXT) : \
      $(SVTNT_TESTS_SRC:.cpp=.o) \
      gtest-all.o gtest_main.o
	$(Q)$(LINK_EXE) -lpthread

include $(SVTNT_SCRIPTS_DIR)/common.mk

endif

$(PACKAGES_DIR)/$(GOOGLETEST_ZIP) :
	if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	cd $(PACKAGES_DIR) ; wget -O $(GOOGLETEST_ZIP) $(GOOGLETEST_URL)

$(BUILD_DIR)/googletest.unpack : $(PACKAGES_DIR)/$(GOOGLETEST_ZIP)
	if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	cd $(BUILD_DIR) ; $(UNTARGZ) $^
	touch $@
