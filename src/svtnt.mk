
SVTNT_SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
SVTNT_DIR := $(abspath $(SVTNT_SRC_DIR)/..)

ifneq (1,$(RULES))

ifeq (true,$(BUILD))
-include grammar/src.mk
-include antlr4-cpp-runtime/src.mk
endif

ANTLR_DOWNLOAD_URL:=http://www.antlr.org/download
ANTLR_VERSION:=4.7.1
# http://www.antlr.org/download/antlr4-cpp-runtime-4.7.1-source.zip
ANTLR_RUNTIME_SRC_ZIP:=antlr4-cpp-runtime-$(ANTLR_VERSION)-source.zip
ANTLR_RUNTIME_SRC_URL:=$(ANTLR_DOWNLOAD_URL)/$(ANTLR_RUNTIME_SRC_ZIP)
ANTLR_RUNTIME_WIN_ZIP:=antlr4-cpp-runtime-4.7.1-vs2015.zip
ANTLR_RUNTIME_WIN_URL:=$(ANTLR_DOWNLOAD_URL)/$(ANTLR_RUNTIME_WIN_ZIP)
ANTLR_JAR:=antlr-$(ANTLR_VERSION)-complete.jar
ANTLR_JAR_URL:=$(ANTLR_DOWNLOAD_URL)/$(ANTLR_JAR)
ANTLR_PATCH_FILE = $(SVTNT_SRC_DIR)/antlr4-cpp-runtime-$(ANTLR_VERSION)-source.patch


SRC_DIRS += $(PSS_COMPILER_SRC_DIR)
SRC_DIRS += $(ANTLR4_CPP_RUNTIME_DIR) $(ANTLR4_CPP_RUNTIME_DIR)/atn 
SRC_DIRS += $(ANTLR4_CPP_RUNTIME_DIR)/dfa $(ANTLR4_CPP_RUNTIME_DIR)/support 
SRC_DIRS += $(ANTLR4_CPP_RUNTIME_DIR)/tree $(ANTLR4_CPP_RUNTIME_DIR)/misc
SRC_DIRS += $(ANTLR4_CPP_RUNTIME_DIR)/tree/pattern 
SRC_DIRS += $(ANTLR4_CPP_RUNTIME_DIR)/tree/xpath 
SRC_DIRS += grammar 

SVTNT_SRC = $(notdir $(wildcard $(SVTNT_SRC_DIR)/*.cpp))

ANTLR4_CXXFLAGS += $(CXXFLAGS)
ANTLR4_CXXFLAGS += -DANTLR4CPP_EXPORTS

UNPACK_TARGETS += $(BUILD_DIR)/runtime.unpack


else # Rules

ifeq (true,$(VERBOSE))
antlr/%.o : %.cpp
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -c -o $@ $(ANTLR4_CXXFLAGS) $(filter %.cpp,$^)
else
antlr/%.o : %.cpp
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)echo "CXX $(notdir $^)"
	$(Q)$(CXX) -c -o $@ $(ANTLR4_CXXFLAGS) $(filter %.cpp,$^)
endif

$(BUILD_DIR)/runtime.unpack : $(PACKAGES_DIR)/$(ANTLR_RUNTIME_SRC_ZIP)
	$(Q)if test ! -d $(BUILD_DIR); then mkdir -p $(BUILD_DIR); fi
	$(Q)cd $(BUILD_DIR); rm -rf antlr4-cpp-runtime
	$(Q)cd $(BUILD_DIR); mkdir antlr4-cpp-runtime
	$(Q)cd $(BUILD_DIR)/antlr4-cpp-runtime ; $(UNZIP) $^
	$(Q)cd $(BUILD_DIR)/antlr4-cpp-runtime ; patch -p1 < $(ANTLR_PATCH_FILE)
	$(Q)touch $@

sv-grammar.gen : $(SVTNT_SRC_DIR)/systemverilog.g4 $(PACKAGES_DIR)/$(ANTLR_JAR)
	$(Q)mkdir -p grammar
	$(Q)java -jar $(PACKAGES_DIR)/$(ANTLR_JAR) \
		-Dlanguage=Cpp -visitor -o grammar $(SVTNT_SRC_DIR)/systemverilog.g4
	$(Q)touch $@

grammar/src.mk : sv-grammar.gen 
	$(Q)echo 'SV_GRAMMAR_SRC += $$(notdir $$(wildcard grammar/*.cpp))' > $@
	
antlr4-cpp-runtime/src.mk : runtime.unpack
	$(Q)echo 'ANTLR_RT_SRC += $$(notdir $$(wildcard antlr4-cpp-runtime/runtime/src/*.cpp))' > $@
	$(Q)echo 'ANTLR_RT_SRC += $$(notdir $$(wildcard antlr4-cpp-runtime/runtime/src/atn/*.cpp))' >> $@
	$(Q)echo 'ANTLR_RT_SRC += $$(notdir $$(wildcard antlr4-cpp-runtime/runtime/src/dfa/*.cpp))' >> $@
	$(Q)echo 'ANTLR_RT_SRC += $$(notdir $$(wildcard antlr4-cpp-runtime/runtime/src/support/*.cpp))' >> $@
	$(Q)echo 'ANTLR_RT_SRC += $$(notdir $$(wildcard antlr4-cpp-runtime/runtime/src/tree/*.cpp))' >> $@
	$(Q)echo 'ANTLR_RT_SRC += $$(notdir $$(wildcard antlr4-cpp-runtime/runtime/src/tree/pattern/*.cpp))' >> $@
	$(Q)echo 'ANTLR_RT_SRC += $$(notdir $$(wildcard antlr4-cpp-runtime/runtime/src/tree/xpath/*.cpp))' >> $@
	$(Q)echo 'ANTLR_RT_SRC += $$(notdir $$(wildcard antlr4-cpp-runtime/runtime/src/misc/*.cpp))' >> $@

$(PACKAGES_DIR)/$(ANTLR_JAR) : 
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)$(WGET) -O $@ $(ANTLR_JAR_URL)

$(PACKAGES_DIR)/$(ANTLR_RUNTIME_SRC_ZIP) : 
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)$(WGET) -O $@ $(ANTLR_RUNTIME_SRC_URL)
	
$(PACKAGES_DIR)/$(ANTLR_RUNTIME_WIN_ZIP) : 
	$(Q)if test ! -d `dirname $@`; then mkdir -p `dirname $@`; fi
	$(Q)$(WGET) -O $@ $(ANTLR_RUNTIME_WIN_URL)
	
-include $(SVNT_SRC:.cpp=.d)

endif
