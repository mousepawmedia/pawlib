none: help

help:
	@echo "=== PawLIB 1.0 ==="
	@echo "Select a build target:"
	@echo "  make ready         Build PawLIB and bundles it for distribution."
	@echo "  make clean         Clean up PawLIB and Tester."
	@echo "  make cleandebug    Clean up PawLIB and Tester Debug."
	@echo "  make cleanrelease  Clean up PawLIB and Tester Release."
	@echo "  make docs          Generate HTML docs."
	@echo "  make docs_pdf      Generate PDF docs."
	@echo "  make pawlib        Build PawLIB as release."
	@echo "  make pawlib_debug  Build PawLIB as debug."
	@echo "  make tester        Build PawLIB Tester (+PawLIB) as release."
	@echo "  make tester_debug  Build PawLIB Tester (+PawLIB) as debug."
	@echo "  make all           Build everything."
	@echo "  make allfresh      Clean and rebuild everything."
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
	@echo
	@echo "For other build options, see the 'make' command in 'docs/', 'pawlib-source/', 'pawlib-tester/', and 'cpgf/build/'."

clean:
	$(MAKE) clean -C pawlib-source
	$(MAKE) clean -C pawlib-tester

cleanall: clean
	$(MAKE) clean -C docs

cleandebug:
	$(MAKE) cleandebug -C pawlib-source
	$(MAKE) cleandebug -C pawlib-tester

cleanrelease:
	$(MAKE) cleanrelease -C pawlib-source
	$(MAKE) cleanrelease -C pawlib-tester

docs:
	$(MAKE) html -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/html/index.html'."
	@echo "-------------"

docs_pdf:
	$(MAKE) latexpdf -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/latex/PawLIB.pdf'."
	@echo "-------------"

pawlib:
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C pawlib-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PawLIB is in 'pawlib-source/lib/Release'."
	@echo "-------------"

pawlib_debug:
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C pawlib-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo  on "PawLIB is in 'pawlib-source/lib/Debug'."
	@echo "-------------"

ready: pawlib
	@rm -rf pawlib
	@echo "Creating file structure..."
	@mkdir -p pawlib/lib
	@echo "Copying PawLIB..."
	@cp -r pawlib-source/include pawlib/
	@cp pawlib-source/lib/Release/libpawlib.a pawlib/lib/libpawlib.a
	@echo "Copying README and LICENSE..."
	@cp README.md pawlib/README.md
	@cp LICENSE.md pawlib/LICENSE.md
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "The libraries are in 'pawlib'."
	@echo "-------------"

tester: pawlib
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C pawlib-tester
	@rm -f tester
	@ln -s pawlib-tester/bin/Release/pawlib-tester tester
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PawLIB Tester is in 'pawlib-tester/bin/Release'."
	@echo "The link './tester' has been created for convenience."
	@echo "-------------"


tester_debug: pawlib_debug
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C pawlib-tester
	@rm -f tester_debug
	@ln -s pawlib-tester/bin/Debug/pawlib-tester tester_debug
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PawLIB Tester is in 'pawlib-tester/bin/Debug'."
	@echo "The link './tester_debug' has been created for convenience."
	@echo "-------------"

all: docs tester

allfresh: cleanall all

.PHONY: all allfresh clean cleanall cleandebug cleanrelease docs docs_pdf pawlib pawlib_debug ready tester tester_debug
