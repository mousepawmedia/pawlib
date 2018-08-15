# Inner Makefile (MousePaw Media Build System)
# Version: 2.1.0
# Tailored For: PawLIB (Tester)
#
# Author(s): Jason C. McDonald

# LICENSE
# Copyright (c) 2018 MousePaw Media.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors
# may be used to endorse or promote products derived from this software without
# specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#
# CONTRIBUTING
# See https://www.mousepawmedia.com/developers for information
# on how to contribute to our projects.

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

# CHANGEME: Project name
NAME = "PawLIB Tester"

# CHANGEME: Set to 'lib' or 'bin'
BUILD_DIR = bin

TEMP_DIR = build_temp

EXEC_BUILD = $(CH_DIR) $(TEMP_DIR)

none:
	$(ECHO) "=== $(NAME) ==="
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
