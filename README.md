PawLIB
=====================

The **PawLIB** static library provides various common utility functions,
many of which are designed as high-performance, near-drop-in-replacements
for common C++ Standard Library (std) classes. See the [official project page][1].

PawLIB focuses on minimizing CPU usage first, and memory second, and as
such it is designed to run on older systems and those with more limited
resources.

It is used by virtually all of MousePaw Games' core projects.

 - Data Structures: High performance alternatives to C++ data structures.
 - Goldilocks: Testing and benchmarking framework.
 - IOChannel: Feature-rich multi-output text output system. (Alternative to std::cout)
 - PawString: Performance string class with full Unicode support. (Alternative to std::string)
 - PuppeteerXML: OOP-based XML system based on Xerces.

Authors
-------------
 - Nate Groggett
 - Jason C. McDonald
 - Michael Parkman
 - Scott Taylor

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

<To be filled in before 1.0 release.>

Contributions
-------------
We do not accept pull requests through GitHub.
If you would like to contribute code, please read our
[Contribution Guide][3].

All contributions are licensed to us under the
[MousePaw Games Terms of Development][4].

License
-------------
PawLIB is licenced under the MIT License. (See LICENCE.md)

The project is owned and maintained by [MousePaw Games][2].

[1]: http://www.mousepawgames.com/pawlib
[2]: http://www.mousepawgames.com/opensource
[3]: http://www.mousepawgames.com/opensource#contribute
[4]: http://www.mousepawgames.com/termsofdevelopment

