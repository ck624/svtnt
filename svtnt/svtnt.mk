
SVTNT_APP_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

ifneq (1,$(RULES))

SVTNT_APP_DEPS = $(PLATFORM_LIB_DIR)/$(DLIBPREF)svtnt$(DLIBEXT)

LIB_TARGETS += $(SVTNT_APP_DEPS)
EXE_TARGETS += $(PLATFORM_BIN_DIR)/svtnt$(EXEEXT)

SRC_DIRS += $(SVTNT_APP_DIR)/src
SVTNT_APP_SRC=$(filter-out svtnt_main.cpp,$(notdir $(wildcard $(SVTNT_APP_DIR)/src/*.cpp)))

else # Rules

$(PLATFORM_LIB_DIR)/$(DLIBPREF)svtnt$(DLIBEXT) : $(SVTNT_APP_SRC:.cpp=.o)
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)$(LINK_DLIB)
	
$(PLATFORM_BIN_DIR)/svtnt$(EXEEXT) : svtnt_main.o $(SVTNT_APP_DEPS)
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)$(LINK_EXE)

endif
