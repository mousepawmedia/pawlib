CMAKE = cmake ../.. -G"Unix Makefiles"
T_DEBUG = -DCMAKE_BUILD_TYPE=Debug
T_RELEASE = -DCMAKE_BUILD_TYPE=Release

MK_DIR = @cmake -E make_directory
CH_DIR = @cmake -E chdir
ECHO = @cmake -E echo

TEMP_DIR = build_temp
BUILD_DIR = bin

EXEC_BUILD = $(CH_DIR) $(TEMP_DIR)

none:
	@echo "=== PawLIB Tester ==="
	@echo "Select a build target:"
	@echo "Select a build target:"
	@echo "  make debug"
	@echo "  make release"
	@echo
	@echo "  make clean"
	@echo "  make cleandebug"
	@echo "  make cleanrelease"
	@echo
	@echo "Optional Architecture"
	@echo "  ARCH=32	Make x86 build (-m32)"
	@echo "  ARCH=64	Make x64 build (-m64)"

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
	$(CH_DIR) $(TEMP_DIR)/Debug$(ARCH) $(CMAKE) $(T_DEBUG) -DARCH=$(ARCH)
	$(EXEC_BUILD)/Debug$(ARCH) make $(TARGET)

release:
	$(MK_DIR) $(TEMP_DIR)/Release$(ARCH)
	$(CH_DIR) $(TEMP_DIR)/Release$(ARCH) $(CMAKE) $(T_RELEASE) -DARCH=$(ARCH)
	$(EXEC_BUILD)/Release$(ARCH) make $(TARGET)

.PHONY: clean cleandebug cleanrelease archswitch
