
PACKAGES_DIR := $(SVTNT_DIR)/packages

BUILD_RESULT_DIR := $(BUILD_DIR)/result

uname_o := $(shell uname -o)


ifneq (1,$(RULES))

include $(SVTNT_DIR)/etc/svtnt.info

ifeq (Msys,$(uname_o))
IS_WIN := true
IS_MSYS := true
else
IS_WIN := false
IS_MSYS := false
endif

ifeq (true,$(IS_WIN))
DLIBEXT := .dll
EXEEXT := .exe
PLATFORM := win64
else
DLIBEXT := .so
EXEEXT :=
PLATFORM := linux_x86_64
endif

PREFIX ?= $(BUILD_RESULT_DIR)/svtnt-$(version)
BIN_DIR = $(PREFIX)/bin
PLATFORM_BIN_DIR = $(PREFIX)/$(PLATFORM)/bin
ifeq (true,$(IS_WIN))
PLATFORM_LIB_DIR = $(PREFIX)/$(PLATFORM)/bin
else
PLATFORM_LIB_DIR = $(PREFIX)/$(PLATFORM)/lib
endif

ifeq (true,$(IS_WIN))
	ifeq (,$(COMPILER))
#		COMPILER := cl
		COMPILER := gcc
	endif
	ifeq (cl, $(COMPILER))
	else
  	  LIB_TARGETS += win_gcc_libs.d
  	endif
else
	COMPILER := gcc
#    LIB_TARGETS += linux_gcc_libs.d
endif

ifeq (cl, $(COMPILER))
else
endif

CXXFLAGS += $(foreach d,$(SRC_DIRS),-I $(d))

ifeq (cl,$(COMPILER))
	CXX=cl
	CC=cl
	CXXFLAGS += -std:c++14 -nologo -EHsc
	LINK_EXE=link -nologo -out:$@
	LINK_DLIB=link -nologo -dll -out:$@
	DLIBPREF := 
endif

ifeq (gcc,$(COMPILER))
	GCC_VERSION := $(shell gcc --version | grep gcc | sed -e 's/^.*\([0-9]\.[0-9]\.[0-9]\).*$$/\1/g')
	GCC_VERSION_MAJOR := $(shell echo $(GCC_VERSION) | sed -e 's/^\([0-9]\).*$$/\1/g')
	GCC_VERSION_GE_7 := $(shell test $(GCC_VERSION_MAJOR) -ge 7; echo $$?)

ifeq (0,$(GCC_VERSION_GE_7))
	CXXFLAGS += -Wno-attributes -fpermissive
endif

	DLIBPREF := lib
	CXXFLAGS += -std=c++11 -fPIC -g
	LINK_EXE=$(CXX) -o $@
define LINK_DLIB
	$(Q)$(CXX) -shared -o $@ $(filter %.o,$(^)) \
		$(foreach lib,$(filter %$(DLIBEXT),$(^)),-L$(dir $(lib)) -l$(subst $(DLIBPREF),,$(subst $(DLIBEXT),,$(notdir $(lib)))))
endef
define LINK_EXE
	$(Q)$(CXX) -o $@ $(filter %.o,$(^)) \
		$(foreach lib,$(filter %$(DLIBEXT),$(^)),-L$(dir $(lib)) -l$(subst $(DLIBPREF),,$(subst $(DLIBEXT),,$(notdir $(lib)))))
endef
endif

ifeq (true,$(VERBOSE))
  UNZIP:=unzip -o
  UNTARGZ:=tar xvzf
  WGET:=wget
else 
  UNZIP:=unzip -oq
  UNTARGZ:=tar xzf
  WGET:=wget
  Q:=@
endif

else # Rules

ifeq (cl,$(COMPILER))
%.o : %.cpp
	$(Q)$(CXX) -c -Fo$(@) $(CXXFLAGS) $^
endif

ifeq (gcc,$(COMPILER))
ifeq (true,$(VERBOSE))
%.o : %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) -MD -MP -MF ${@:.o=.d} $(filter %.cpp,$^)
	
%.o : %.cc
	$(CXX) -c -o $@ $(CXXFLAGS) -MD -MP -MF ${@:.o=.d} $(filter %.cc,$^)
else
%.o : %.cpp
	@echo "CXX: $(notdir $(filter %.cpp,$^))"
	@$(CXX) -c -o $@ $(CXXFLAGS) -MD -MP -MF ${@:.o=.d} $(filter %.cpp,$^)
	
%.o : %.cc
	@echo "CXX: $(notdir $(filter %.cc,$^))"
	@$(CXX) -c -o $@ $(CXXFLAGS) -MD -MP -MF ${@:.o=.d} $(filter %.cc,$^)
endif
endif

linux_gcc_libs.d :
	$(Q)if test ! -d $(PLATFORM_LIB_DIR); then mkdir -p $(PLATFORM_LIB_DIR); fi
	libstdcpp=`$(CXX) -print-file-name=libstdc++.so`; \
	libdir=`dirname $$libstdcpp`; \
	cd $$libdir ; tar cf - libstdc++.so.* | (cd $(PLATFORM_LIB_DIR) ; tar xf -)
	touch $@

endif # Rules

