..  _tests:

PawLIB Tests
###########################

For instructions on using the PawLIB Tester, see :ref:`console`.

Test Namespaces
=========================

Because we use Goldilocks for multiple projects at MousePaw Media, we follow
certain conventions for test and suite IDs.

The `Live-In Testing Standard <https://standards.mousepawmedia.com/lit.html>`_
defines the first part of the ID. For example,

* ``P-`` refers to the PawLIB project.

* ``s`` is a suite, while ``t`` is a test.

* ``B`` is a "behavior" test, and ``S`` is a "stress" test, etc.

The first digit indicate the major sector of PawLIB the suite and its
tests are related to. The second digit is the specific sector, usually a
single class.

The current sectors are delineated exhaustively in the table below. Not
all sectors have tests implemented yet. ``x`` indicates that another
number is needed.

+----+--------------------+
| ID | Sector             |
+====+====================+
| 0x | Data Types         |
+----+--------------------+
| 01 | Trilean            |
+----+--------------------+
| 1x | Data Structures    |
+----+--------------------+
| 10 | FlexArray          |
+----+--------------------+
| 11 | FlexMap            |
+----+--------------------+
| 12 | FlexQueue          |
+----+--------------------+
| 13 | FlexStack          |
+----+--------------------+
| 14 | SimplyLinkedList   |
+----+--------------------+
| 15 | FlexBit            |
+----+--------------------+
| 16 | Pool               |
+----+--------------------+
| 20 | IOChannel          |
+----+--------------------+
| 30 | PawSort            |
+----+--------------------+
| 4x | Onestring (Sector) |
+----+--------------------+
| 41 | Onechar            |
+----+--------------------+
| 42 | QuickString        |
+----+--------------------+
| 43 | Onestring          |
+----+--------------------+
| 5x | Blueshell          |
+----+--------------------+
| 6x | Utilities          |
+----+--------------------+

Any subsequent digits indicate the test number. A number may be shared
between behavior and stress tests; both use the same implementation, but
vary in their variables (such as iterations).

An asterisk (``*``) at the end of test ID indicates that it is a comparative
test, used only for benchmarking.
