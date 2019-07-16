Setup and Compiling
################################

..  _setup-building:

Building
================================

PawLIB is a static library which needs to be compiled before it can
be used.

..  NOTE:: Complete building instructions can be found in BUILDING.md

..  _setup-building-deps:

Environment and Dependencies
------------------------------------

To build PawLIB, you must have the following installed on your system:

* CMake 3.1+ (`cmake.org <https://cmake.org/>`_)

* Clang 3.4+ OR GCC 5.3+ (MSVC is not presently supported.)

* CPGF 1.60, from either:

  * `libdeps 1.0 (GitHub) <https://github.com/mousepawmedia/libdeps/tree/v1.0.0>`_  [recommended], *or*

  * `CPGF (GitHub) <https://github.com/cpgf/cpgf/tree/1.6.0>`_.

..  _setup-building-config:

Build Configuration
-------------------------------------

If you use our ``libdeps`` repository, it is recommended that you clone it
adjacent to the ``pawlib`` folder. In that scenario, you can skip this section,
as the default configuration will work for you.

If you put ``libdeps`` somewhere else, or provide CPGF yourself, be sure to
create a build configuration file.

To do this, make a copy of ``build.config.txt`` in the root of the
PawLIB repository, and name it ``build.config``. Optionally, you may
replace "build" with any name, so long as the filename ends in ``.config``.

Edit the file, and change the following section to point to the location
of CPGF's `include` and `lib` directories.

..  code-block:: cmake

    set(CPGF_DIR
    	${CMAKE_HOME_DIRECTORY}/../../libdeps/libs
    )

In that path, the variable ``${CMAKE_HOME_DIRECTORY}`` refers to either the
:file:`pawlib-source/` or :file:`pawlib-tester/` directories in the PawLIB
repository, since the same configuration file is used in compiling both.

Save and close.

..  _setup-building-compile:

Compiling PawLIB
-------------------------------------

Make sure that CPGF is built. If you're using ``libdeps``, you can simply
run ``make cpgf`` in that repository.

In the PawLIB repository, run ``make ready`` to build PawLIB as a static
library.

..  NOTE:: If you experience any errors in compiling, we invite you to
    contact us. See :ref:`support`.

..  _setup-linking:

Linking to PawLIB
==============================

To use PawLIB in your C++ project, you will need to statically link to
both it and CPGF.

..  IMPORTANT:: Linking order is important in C++! You should link to
    PawLIB first, and then its dependencies (namely CPGF) second.

You can point your compiler and linker at the
:file:`pawlib/include/` and :file:`pawlib/lib/`
directories.

If you need help finding the paths for CPGF, refer to the path in the PawLIB
build configuration (see :ref:`setup-building-config`). The :file:`include/`
and :file:`lib/` directories should be in the path specified.

.. _setup-build-tester:

Using PawLIB
==============================

All ``#include`` commands follow the format ``#include "pawlib/HEADER.hpp"``,
where ``HEADER.hpp`` is the header file you wish to include.

Everything in PawLIB is in ``namespace pawlib``. When using IOChannel, the
formatting enumerations are in ``namespace pawlib::ioformat``.

Building Tester
============================

If you want to use the PawLIB tester application, you can build that as well.
Once you've confirmed that PawLIB itself can build without errors, run
``make tester`` to build the tester.
