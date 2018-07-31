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
ECHO = @cmake -E echo

TEMP_DIR = build_temp
BUILD_DIR = lib

EXEC_BUILD = $(CH_DIR) $(TEMP_DIR)

none:
	@echo "=== PawLIB Static Library==="
	@echo "Select a build target:"
	@echo "  make debug"
	@echo "  make release"
	@echo
	@echo "  make clean"
	@echo "  make cleandebug"
	@echo "  make cleanrelease"
	@echo
	@echo "Clang Sanitizers (requires Debug build and Clang.)"
	@echo "  SAN=address     Use AddressSanitizer"
	@echo "  SAN=leak        Use LeakSanitizer w/o AddressSanitizer (Linux only)"
	@echo "  SAN=memory      Use MemorySanitizer"
	@echo "  SAN=thread      Use ThreadSanitizer"
	@echo "  SAN=undefined   Use UndefiniedBehaviorSanitizer"
	@echo
	@echo "Optional Architecture"
	@echo "  ARCH=32         Make x86 build (-m32)"
	@echo "  ARCH=64         Make x64 build (-m64)"
	@echo
	@echo "Use Configuration File"
	@echo "  CONFIG=foo      Uses the configuration file 'foo.config'"
	@echo "                  in the root of this repository."
	@echo "  When unspecified, default.config will be used."

clean:
	@cmake -E remove_directory $(BUILD_DIR)
	@cmake -E remove_directory $(TEMP_DIR)

cleandebug:
	@cmake -E remove_directory $(BUILD_DIR)/Debug
	@cmake -E remove_directory $(TEMP_DIR)/Debug

cleanrelease:
	@cmake -E remove_directory $(BUILD_DIR)/Release
	@cmake -E remove_directory $(TEMP_DIR)/Release

debug:
	$(MK_DIR) $(TEMP_DIR)/Debug$(ARCH)
	$(CH_DIR) $(TEMP_DIR)/Debug$(ARCH) $(CMAKE) $(T_DEBUG) -DARCH=$(ARCH) -DSAN=$(SAN) $(P_CONF)$(P_CONF_PATH)
	$(EXEC_BUILD)/Debug$(ARCH) $(MAKE) $(TARGET) VERBOSE=1

release:
	$(MK_DIR) $(TEMP_DIR)/Release$(ARCH)
	$(CH_DIR) $(TEMP_DIR)/Release$(ARCH) $(CMAKE) $(T_RELEASE) -DARCH=$(ARCH) $(P_CONF)$(P_CONF_PATH)
	$(EXEC_BUILD)/Release$(ARCH) $(MAKE) $(TARGET) VERBOSE=1

.PHONY: clean cleandebug cleanrelease
