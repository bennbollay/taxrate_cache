# Demonstration Answer for Cache

This repository demonstrates a simple answer for a "make a cache" type interview question, including memory leak testing (via valgrind), and coverage reporting (via lcov).

The implementation provides a simple, fairly naive LRU based on a `std::map` for lookups, and a `std::list` for managing LRU eviction.  In lieu of actually generating sensical tax rate values, a random number is utilized.

The `taxratelru.hpp` file contains the implementation.  Test code is provided in `test.cpp`.

The coverage report has been committed and can be viewed [here](https://htmlpreview.github.io/?https://raw.githubusercontent.com/bennbollay/taxrate_cache/master/test_coverage/coding_test/index.html).

## Usage

```
$ make test
g++ test.cpp -o test
./test
valgrind --leak-check=full ./test
==64621== Memcheck, a memory error detector
==64621== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==64621== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==64621== Command: ./test
==64621== 
==64621== 
==64621== HEAP SUMMARY:
==64621==     in use at exit: 0 bytes in 0 blocks
==64621==   total heap usage: 50 allocs, 50 frees, 74,504 bytes allocated
==64621== 
==64621== All heap blocks were freed -- no leaks are possible
==64621== 
==64621== For counts of detected and suppressed errors, rerun with: -v
==64621== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
$
```

Or, for coverage reporting:

```
$ make test.cov
g++ test.cpp -o test.cov -fprofile-arcs -ftest-coverage --coverage
lcov --base-directory . --directory . --zerocounters -q
./test.cov
lcov --base-directory . --directory . -c -o test.info
Capturing coverage data from .
Found gcov version: 7.2.0
Scanning . for .gcda files ...
Found 1 data files in .
Processing test.gcda
Finished .info-file creation
lcov --remove test.info "/usr*" -o test.info # remove output for external libraries
Reading tracefile test.info
Removing /usr/include/c++/7/bits/alloc_traits.h
Removing /usr/include/c++/7/bits/allocated_ptr.h
Removing /usr/include/c++/7/bits/allocator.h
Removing /usr/include/c++/7/bits/basic_string.h
Removing /usr/include/c++/7/bits/list.tcc
Removing /usr/include/c++/7/bits/move.h
Removing /usr/include/c++/7/bits/stl_function.h
Removing /usr/include/c++/7/bits/stl_list.h
Removing /usr/include/c++/7/bits/stl_map.h
Removing /usr/include/c++/7/bits/stl_pair.h
Removing /usr/include/c++/7/bits/stl_tree.h
Removing /usr/include/c++/7/ext/aligned_buffer.h
Removing /usr/include/c++/7/ext/new_allocator.h
Removing /usr/include/c++/7/new
Deleted 14 files
Writing data to test.info
Summary coverage rate:
  lines......: 100.0% (65 of 65 lines)
  functions..: 90.9% (10 of 11 functions)
  branches...: no data found
rm -rf test_coverage
genhtml -o test_coverage -t "test coverage" --num-spaces 4 test.info
Reading data file test.info
Found 2 entries.
Found common filename prefix "/home/user/pp"
Writing .css and .png files.
Generating output.
Processing file coding_test/test.cpp
Processing file coding_test/taxratelru.hpp
Writing directory view page.
Overall coverage rate:
  lines......: 100.0% (65 of 65 lines)
  functions..: 90.9% (10 of 11 functions)
$
```
