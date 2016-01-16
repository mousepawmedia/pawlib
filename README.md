PawLIB
=====================

The PawLIB static library provides various common utility functions, 
many of which are designed as high-performance, near-drop-in-replacements 
for common C++ Standard Library (std) classes.

PawLIB focuses on minimizing CPU usage first, and memory second, and as
such it is designed to run on older systems and those with more limited
resources.

It is used by virtually all of MousePaw Games' core projects.

Authors
-------------
Jason C. McDonald

Building
-------------
PawLIB was written and built in CodeBlocks. The projects (.cbp) in this
repository are pre-configured to build directly in the repository.

The '/pawlib' directory contains the compiled library ('/pawlib/XX/lib/'),
and the header files ('/pawlib/XX/include'), where 'XX' is either the
Debug or Release version of the library.

The '/pawlib-source' folder contains the source code for the PawLIB
library. It is set up to automatically update the appropriate 'pawlib'
folder (Debug or Release), depending on the build target.

The '/pawlib-tester' folder contains the console application for testing
the PawLIB library. Building this project will automatically rebuild
the PawLIB library on the same build target.

Dependencies
-------------
PawLIB depends on the following third-party libraries.

<Fill me in later.>

License and Development Terms
-------------
PawLIB is licenced under the MIT License. (See LICENCE.md)
The project is owned and maintained by [MousePaw Games][2].
All third-party contributions to this project are governed under the [MousePaw Games Terms of Development][3].

[2]: http://www.mousepawgames.com/opensource
[3]: http://www.mousepawgames.com/termsofdevelopment

