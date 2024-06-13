# Tests for the 2nd IAED Project

This directory contains some community and the public tests for the second IAED project. 

Automatically test with the script:
```
./test.sh [flags] <path_to_executable> <path_to_tests_dir>
```
- `-d` flag shows in the terminal the diff of expect output with actual output(if `colordiff` is installed, this diff will be colorized)
- `-c` flag removes generated `.result` files (instead of testing)
- **`-v` flag runs tests in valgrind**
- `-h` flag (as usual) shows this information

