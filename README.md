PawLIB
========================================

<img src=docs/source/pawlib_icon.svg width=200vw/>

**Performance meets elegance.**

The **PawLIB** static library provides various common data structures and
algorithms, most of which are designed as high-performance,
near-drop-in-replacements for common C++ Standard Library (`std`) classes.

PawLIB focuses on minimizing CPU usage first, and memory second, and as
such it is designed to run on older systems and those with more limited
resources.

It is used by virtually all of MousePaw Media' core projects.

See the [official project page](https://mousepawmedia.com/pawlib).

Features
----------------------------------------

 * **Flex**: High-performance sequential data structures.
 * **Pool**: A general-purpose implementation of the object pool design pattern.
 * **Onestring**: Performance string class with full Unicode support. (Alternative to ``std::string``)
 * **Trilean**: A new atomic data type with three unique states: true, false, and maybe.

> **Goldilocks** and **IOChannel** (now **IOSqueak**) have been moved to their
own projects.

Experimental Features
----------------------------------------

These are in varying stages of completion and stability.

 * **Pawsort**: Implementations of some of the fastest known sorting algorithms.
  * **Zoom**: High-performance list data structures.


Authors
----------------------------------------

 * Nate Groggett
 * Jason C. McDonald
 * Ismayil Mirzali
 * Michael Parkman
 * Sergio Ramirez
 * Scott Taylor
 * Jonathan Theodore
 * Jarek Thomas
 * Moshe Uminer
 * Bowen Volwiler

Dependencies
----------------------------------------

* eventpp 0.1.1
* Goldilocks 2.0 (not needed for Minimal)

Building
----------------------------------------

If you have the full source repository, see BUILDING.md for information
on how to build PawLIB, PawLIB Tester, and the documentation.

The Ready-To-Use version of PawLIB only contains the folders `include`
and `lib`. You can find the full source repository on
[GitHub](https://github.com/mousepawmedia/pawlib).

Contributions
----------------------------------------

We do NOT accept pull requests through GitHub.
If you would like to contribute code, please read our
[Contribution Guide](https://mousepawmedia.com/developers/contribution).

All contributions are licensed to us under the
[MousePaw Media Terms of Development](https://mousepawmedia.com/termsofdevelopment).

License
----------------------------------------

IOSqueak is licensed under the BSD-3 License. (See LICENSE.md)

The project is owned and maintained by [MousePaw Media](https://mousepawmedia.com/developers).

<img src=docs/source/mousepaw_logo_circle.svg width=200vw/>
