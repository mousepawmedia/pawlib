# Building PawLIB

## Building Basics

CMake is used to build CPGF, PawLIB, and PawLIB Tester. For your convenience,
we've included Makefiles to automate all common build scenarios on Linux.
Type "make" in the root of this repository for more information.

At this time, the Makefiles are only designed for Linux. If you are building
on another system, you can interact with CMake directly.

Currently, PawLIB is only designed to be built by GCC (5.3 or later) or Clang (3.4 or later).

## Ready-To-Use Build

If you just want to build PawLIB to use in your own project, the fastest way
is to run "make ready". This will build CPGF, PawLIB, and the documentation,
and place them all in a folder called "pawlib". Simply copy that folder to
a convenient location, and point your compiler and linker to "pawlib/include"
and "pawlib/lib" respectively.

## Building HTML Docs

The Ready-To-Use build includes the PDF documentation. If you want the HTML
documentation instead, run "make docs". Then, grab the 'docs/build/html'
folder, or just open 'docs/build/html/index.html' in your favorite web
browser.

## Building Tester

If you want to test out PawLIB directly, run "make tester". Then, look
for the 'pawlib-tester' executable in 'pawlib-tester/bin/[Debug/Release]'.
Alternatively, you may use the symbolic link 'tester' or 'tester_debug'
in the root of this repository.

## Code::Blocks

PawLIB was written and built in CodeBlocks. The projects (.cbp) in this
repository are pre-configured to build directly in the repository.

## Source Directories

- The '/cpgf' folder contains the source code for the CPGF library, which
PawLIB uses.
- The '/docs' folder contains the Sphinx documentation for PawLIB.
- The '/pawlib-source' folder contains the source code for the PawLIB
  library.
- The '/pawlib-tester' folder contains the console application for testing
  the PawLIB library.
