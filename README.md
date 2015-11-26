libSPRITE
=========

#Installation
============
To install, type `make install` as root.

This will copy headers files to /usr/local/include/SPRITE/ and static library
to /usr/local/lib/SPRITE by default.

To uninstall, type `make uninstall` as root.

## Lua Paths
libSPRITE assumes the Lua headers are install in /usr/local/include. Some
distributions place it elsewhere. You can change where the Makefile looks for
the Lua include files by specifying the `LUA_INCLUDE` variable in the arguments
to `make`.

ex.: `make LUA_INCLUDE=/usr/include/lua5.2`

You can also change the Lua library path by setting the `LUA_LIB` variable.

# Testing
'make test' will build the unit tests for this package. You must have *cppunit*
installed to compile and run the unit tests. After compiling, run './run_test'
to execute the unit tests. You will have to run as root to execute all test cases.

NOTE: You must start from a clean systems ('make clean') before running 'make test'. Otherwise, some tests that depend on compile time assertions will fail.

# Makefile Overrides
By default, libSPRITE sends output to stdout and stderr for info, warnings, and errors. To supress these messages, you can specifiy `-DNO_PRINT_INFO -DNO_PRINT_WARNING -DNO_PRINT_ERROR`. The best way to do that is by appending to these options to the `USER_CFLAGS`. For example:

    make USER_CFLAGS='-DNO_PRINT_INFO -DNO_PRINT_WARNING'

There are also overides for CPPFLAGS (USER_CPPFLAGS) and LDFLAGS (USER_LDFLAGS).

# Using CMake
To build with `cmake`, create a directory called `build`, `cd` to the `build` directory and type `cmake ../`.

To specify the build prefix, using the `CMAKE_INSTALL_PREFIX` macro. Example

    cmake -DCMAKE_INSTALL_PREFIX=/usr/local/

By default, the build type is Release. To build unit tests us the `CMAKE_BUILD_TYPE` macro. Example:

    cmake -DCMAKE_BUILD_TYPE=Test

After specifying `cmake` with this macro, `make` will create a `run_test` executable in each folder. Execute the `run_test` executable for the folder you wish to test.

Run `cmake` with the `-DCMAKE_BUILD_TYPE=Release` option to switch back to the normal build.

# [Documentation](https://github.com/nasa/libSPRITE/wiki)
Documentation can be found on the [Wiki](https://github.com/nasa/libSPRITE/wiki)

# [Tutorial](https://github.com/dheater/libSPRITE-tutorial/wiki/Tutorial)
A growing Tutorial for developing applications using libSPRITE can be found [here](https://github.com/dheater/libSPRITE-tutorial/wiki/Tutorial)

