libSPRITE
=========

Installation
============
To install, type 'make install' as root.

This will copy headers files to /usr/local/include/SPRITE/ and static library
to /usr/local/lib/SPRITE by default.

To uninstall, type 'make uninstall' as root.

Testing
=======
'make test' will build the unit tests for this package. You must have *cppunit*
installed to compile and run the unit tests. After compiling, run './run_test'
to execute the unit tests.

NOTE: You must start from a clean systems ('make clean') before running 'make test'. Otherwise, some tests that depend on compile time assertions will fail.

The unit tests depend on lunatest which you can obtaing from here:
https://github.com/silentbicycle/lunatest.git
You may also need to apply the following patch to lunatest:
https://github.com/KINFOO/lunatest/commit/ba697adfd4512668a5f0a45c698c1b7907552ca
