# PawLIB

The **PawLIB** static library provides various common utility functions,
many of which are designed as high-performance, near-drop-in-replacements
for common C++ Standard Library (`std`) classes. See the [official project page][1].

PawLIB focuses on minimizing CPU usage first, and memory second, and as
such it is designed to run on older systems and those with more limited
resources.

It is used by virtually all of MousePaw Media' core projects.

 - Flex Data Structures: High performance alternatives to C++ data structures, and then some.
 - Goldilocks: Testing and benchmarking framework.
 - IOChannel: Feature-rich multi-output text output system. (Alternative to ``std::cout``)
 - Trilean: A new atomic data type with three unique states: true, false, and maybe.
 - Pool: A general-purpose implementation of the object pool design pattern.
 - Onestring: Performance string class with full Unicode support. (Alternative to ``std::string``) [Experimental]

## Authors

 - Nate Groggett
 - Jason C. McDonald
 - Michael Parkman
 - Sergio Ramirez
 - Scott Taylor
 - Jonathan Theodore
 - Jarek Thomas
 - Bowen Volwiler

## Dependencies

PawLIB depends on CPGF.

## Building

If you have the full source repository, see BUILDING.md for information
on how to build PawLIB, PawLIB Tester, and the documentation.

The Ready-To-Use version of PawLIB only contains the folders `include`
and `lib`. You can find the full source repository on [GitHub][5].

## Contributions

We do NOT accept pull requests through GitHub.
If you would like to contribute code, please read our
[Contribution Guide][3].

All contributions are licensed to us under the
[MousePaw Media Terms of Development][4].

## License

PawLIB is licensed under the BSD-3 License. (See LICENSE.md)

The project is owned and maintained by [MousePaw Media][2].

[1]: https://www.mousepawmedia.com/pawlib
[2]: https://www.mousepawmedia.com/developers
[3]: https://www.mousepawmedia.com/developers/contribution
[4]: https://www.mousepawmedia.com/termsofdevelopment
[5]: https://github.com/mousepawmedia/pawlib
