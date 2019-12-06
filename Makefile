# Top Level Makefile (MousePaw Media Build System)
# Version: 2.1.0
# Tailored For: PawLIB
#
# Author(s): Jason C. McDonald

# LICENSE (BSD-3-Clause)
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

MK_DIR = @cmake -E make_directory
CH_DIR = @cmake -E chdir
CP = @cmake -E copy
CP_DIR = @cmake -E copy_directory
RM = @cmake -E remove
RM_DIR = @cmake -E remove_directory
ECHO = @cmake -E echo
LN = @cmake -E create_symlink

none: help

help:
	$(ECHO) "=== PawLIB 1.1 ==="
	$(ECHO) "Select a build target:"
	$(ECHO) "  make ready         Build PawLIB and bundles it for distribution."
	$(ECHO) "  make clean         Clean up PawLIB and Tester."
	$(ECHO) "  make cleandebug    Clean up PawLIB and Tester Debug."
	$(ECHO) "  make cleanrelease  Clean up PawLIB and Tester Release."
	$(ECHO) "  make docs          Generate HTML docs."
	$(ECHO) "  make docs_pdf      Generate PDF docs."
	$(ECHO) "  make pawlib        Build PawLIB as release."
	$(ECHO) "  make pawlib_debug  Build PawLIB as debug."
	$(ECHO) "  make tester        Build PawLIB Tester (+PawLIB) as release."
	$(ECHO) "  make tester_debug  Build PawLIB Tester (+PawLIB) as debug."
	$(ECHO) "  make all           Build everything."
	$(ECHO) "  make allfresh      Clean and rebuild everything."
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
	$(ECHO)
	$(ECHO) "For other build options, see the 'make' command in 'docs/', 'pawlib-source/', and 'pawlib-tester/'."

clean:
	$(MAKE) clean -C pawlib-source
	$(MAKE) clean -C pawlib-tester
	$(RM) tester_debug
	$(RM) tester

cleanall: clean
	$(MAKE) clean -C docs

cleandebug:
	$(MAKE) cleandebug -C pawlib-source
	$(MAKE) cleandebug -C pawlib-tester
	$(RM) tester_debug

cleanrelease:
	$(MAKE) cleanrelease -C pawlib-source
	$(MAKE) cleanrelease -C pawlib-tester
	$(RM) tester

docs:
	$(RM_DIR) docs/build/html
	$(MAKE) html -C docs
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "View docs at 'docs/build/html/index.html'."
	$(ECHO) "-------------"

docs_pdf:
	$(MAKE) latexpdf -C docs
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "View docs at 'docs/build/latex/PawLIB.pdf'."
	$(ECHO) "-------------"

pawlib:
	$(MAKE) release -C pawlib-source
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "PawLIB is in 'pawlib-source/lib/Release'."
	$(ECHO) "-------------"

pawlib_debug:
	$(MAKE) debug -C pawlib-source
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO)  on "PawLIB is in 'pawlib-source/lib/Debug'."
	$(ECHO) "-------------"

ready: pawlib
	$(RM_DIR) pawlib
	$(ECHO) "Creating file structure..."
	$(MK_DIR) pawlib
	$(ECHO) "Copying PawLIB..."
	$(CP_DIR) pawlib-source/include/ pawlib/include/
	$(CP_DIR) pawlib-source/lib/Release/ pawlib/lib/
	$(ECHO) "Copying README and LICENSE..."
	$(CP) README.md pawlib/README.md
	$(CP) LICENSE.md pawlib/LICENSE.md
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "The libraries are in 'pawlib'."
	$(ECHO) "-------------"

tester: pawlib
	$(MAKE) release -C pawlib-tester
	$(RM) tester
	$(LN) pawlib-tester/bin/Release/pawlib-tester tester
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "PawLIB Tester is in 'pawlib-tester/bin/Release'."
	$(ECHO) "The link './tester' has been created for convenience."
	$(ECHO) "-------------"


tester_debug: pawlib_debug
	$(MAKE) debug -C pawlib-tester
	$(RM) tester_debug
	$(LN) pawlib-tester/bin/Debug/pawlib-tester tester_debug
	$(ECHO) "-------------"
	$(ECHO) "<<<<<<< FINISHED >>>>>>>"
	$(ECHO) "PawLIB Tester is in 'pawlib-tester/bin/Debug'."
	$(ECHO) "The link './tester_debug' has been created for convenience."
	$(ECHO) "-------------"

all: docs tester

allfresh: cleanall all

.PHONY: all allfresh clean cleanall cleandebug cleanrelease docs docs_pdf pawlib pawlib_debug ready tester tester_debug
