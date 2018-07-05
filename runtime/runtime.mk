
RUNTIME_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))
RUNTIME_SRC = $(notdir $(wildcard $(RUNTIME_DIR)/src/*.cpp))
SRC_DIRS += $(RUNTIME_DIR)/src

RUNTIME_DEPS = $(PLATFORM_LIB_DIR)/$(DLIBPREF)svtnt_runtime$(DLIBEXT)
LIB_TARGETS += $(RUNTIME_DEPS)

else # Rules

$(RUNTIME_DEPS) : $(RUNTIME_SRC:.cpp=.o)
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)$(LINK_DLIB)


-include $(RUNTIME_SRC:.cpp=.d)
endif
