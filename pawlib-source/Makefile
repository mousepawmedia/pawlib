CMAKE = cmake ../.. -G"Unix Makefiles"
T_DEBUG = -DCMAKE_BUILD_TYPE=Debug
T_RELEASE = -DCMAKE_BUILD_TYPE=Release

P_DEF_CONF = default
P_CONF = -DCONFIG_FILENAME=
ifneq ( , $(CONFIG))
	P_CONF_PATH=$(CONFIG)
else
	P_CONF_PATH = $(P_DEF_CONF)
endif

MK_DIR = @cmake -E make_directory
CH_DIR = @cmake -E chdir
RM_DIR = @cmake -E remove_directory
ECHO = @cmake -E echo

TEMP_DIR = build_temp
BUILD_DIR = lib

EXEC_BUILD = $(CH_DIR) $(TEMP_DIR)

none: help

help:
	$(ECHO) "=== PawLIB Static Library==="
	$(ECHO) "Select a build target:"
	$(ECHO) "  make debug"
	$(ECHO) "  make release"
	$(ECHO)
	$(ECHO) "  make clean"
	$(ECHO) "  make cleandebug"
	$(ECHO) "  make cleanrelease"
	$(ECHO)
	$(ECHO) "Clang Sanitizers (requires Debug build and Clang.)"
	$(ECHO) "  SAN=address     Use AddressSanitizer"
	$(ECHO) "  SAN=leak        Use LeakSanitizer w/o AddressSanitizer (Linux only)"
	$(ECHO) "  SAN=memory      Use MemorySanitizer"
	$(ECHO) "  SAN=thread      Use ThreadSanitizer"
	$(ECHO) "  SAN=undefined   Use UndefiniedBehaviorSanitizer"
	$(ECHO)
	$(ECHO) "Optional Architecture"
	$(ECHO) "  ARCH=32         Make x86 build (-m32)"
	$(ECHO) "  ARCH=64         Make x64 build (-m64)"
	$(ECHO)
	$(ECHO) "Use Configuration File"
	$(ECHO) "  CONFIG=foo      Uses the configuration file 'foo.config'"
	$(ECHO) "                  in the root of this repository."
	$(ECHO) "  When unspecified, default.config will be used."

clean:
	$(RM_DIR) $(BUILD_DIR)
	$(RM_DIR) $(TEMP_DIR)

cleandebug:
	$(RM_DIR) $(BUILD_DIR)/Debug
	$(RM_DIR) $(TEMP_DIR)/Debug

cleanrelease:
	$(RM_DIR) $(BUILD_DIR)/Release
	$(RM_DIR) $(TEMP_DIR)/Release

debug:
	$(MK_DIR) $(TEMP_DIR)/Debug$(ARCH)
	$(CH_DIR) $(TEMP_DIR)/Debug$(ARCH) $(CMAKE) $(T_DEBUG) -DARCH=$(ARCH) -DSAN=$(SAN) $(P_CONF)$(P_CONF_PATH)
	$(EXEC_BUILD)/Debug$(ARCH) $(MAKE) VERBOSE=1

release:
	$(MK_DIR) $(TEMP_DIR)/Release$(ARCH)
	$(CH_DIR) $(TEMP_DIR)/Release$(ARCH) $(CMAKE) $(T_RELEASE) -DARCH=$(ARCH) $(P_CONF)$(P_CONF_PATH)
	$(EXEC_BUILD)/Release$(ARCH) $(MAKE) VERBOSE=1

.PHONY: clean cleandebug cleanrelease help
