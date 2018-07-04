
MODEL_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SRC_DIRS += $(MODEL_DIR)/src

MODEL_SRC = $(notdir $(wildcard $(MODEL_DIR)/src/*.cpp))

MODEL_DEPS = $(PLATFORM_LIB_DIR)/$(DLIBPREF)svtnt_model$(DLIBEXT)

LIB_TARGETS += $(MODEL_DEPS)


else # Rules

$(PLATFORM_LIB_DIR)/$(DLIBPREF)svtnt_model$(DLIBEXT) : $(MODEL_SRC:.cpp=.o)
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)$(LINK_DLIB)
	
-include $(MODEL_SRC:.cpp=.d)	

endif
