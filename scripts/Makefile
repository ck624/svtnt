
PWD := $(shell pwd)
SVTNT_SCRIPTS_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
SVTNT_DIR := $(abspath $(SVTNT_SCRIPTS_DIR)/..)

ifeq ($(PWD), $(SVTNT_SCRIPTS_DIR))
  BUILD_DIR := $(SVTNT_DIR)/build
else
  BUILD_DIR := $(PWD)
endif

include $(SVTNT_SCRIPTS_DIR)/common.mk

MK_INCLUDES += $(SVTNT_DIR)/compiler/compiler.mk
MK_INCLUDES += $(SVTNT_DIR)/model/model.mk
MK_INCLUDES += $(SVTNT_DIR)/svtnt/svtnt.mk

ifeq (true,$(BUILD))
include $(MK_INCLUDES)
else # not build
ifeq (,$(J))
NUM_CORES := $(shell cat /proc/cpuinfo | grep 'processor.*:' | wc -l)
else
NUM_CORES := $(J)
endif
endif # end not build

RULES := 1

vpath %.cpp $(SRC_DIRS)

ifeq (true,$(BUILD))
include $(MK_INCLUDES)
endif


all :
	$(Q)echo "PWD=$(PWD) SCRIPTS_DIR=$(SVTNT_SCRIPTS_DIR)"
	$(Q)if test ! -d $(BUILD_DIR); then mkdir -p $(BUILD_DIR); fi
	$(Q)$(MAKE) BUILD=true -C $(BUILD_DIR) -f $(SVTNT_SCRIPTS_DIR)/Makefile __unpack 
	$(Q)$(MAKE) BUILD=true -j$(NUM_CORES) -C $(BUILD_DIR) -f $(SVTNT_SCRIPTS_DIR)/Makefile __build
	
ifeq (true,$(BUILD))

__unpack : $(UNPACK_TARGETS)

__build : $(LIB_TARGETS) $(EXE_TARGETS)

include $(SVTNT_SCRIPTS_DIR)/common.mk

endif