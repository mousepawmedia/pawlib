PawLIB 2.0 Documentation
################################

The **PawLIB** static library provides various common utility functions,
many of which are designed as high-performance, near-drop-in-replacements
for common C++ Standard Library (``std::``) and Boost classes.

PawLIB focuses on minimizing CPU usage first, and memory second, and as
such it is designed to run on older systems and those with more limited
resources.

See PawLIB's ``README.md``, ``CHANGELOG.md``, ``BUILDING.md``,
and ``LICENSE.md`` for more information.

Contents
====================

..  toctree::
    :maxdepth: 2
    :glob:

    general/setup
    flex/flexarray
    flex/flexqueue
    flex/flexstack
    core/trilean
    goldilocks/goldilocks
    goldilocks/shell
    iochannel/*
    onestring/*
    core/pool
    core/stdutils
    general/console
    general/tests
    general/support


Indices and tables
==================

..  NOTE:: The index is still a work in progress. If you'd like to help
    with this, please see our `Contribution Guide <https://mousepawmedia.com/developers/contributing>`_.

* :ref:`genindex`
* :ref:`search`
