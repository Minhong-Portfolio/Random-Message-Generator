# Random Message Generator

## Description

This project implements a command-line tool written in C that generates pseudo‑random messages of a specified length using a small built‑in dictionary. It also includes unit tests for the underlying dynamic ArrayList data structure.

Key functionalities include:

* Parsing command-line flags (`-t` to run tests, `-l <length>` to set message length)
* Dynamic `ArrayList` implementation for storing and manipulating strings
* Three-part program: ArrayList implementation, segmentation-fault bug fixes in message generator, and comprehensive unit tests
* Generating a sentence by randomly drawing words from a dictionary and inserting a special word at the midpoint

## Features

* **Command-Line Flags**: Uses `getopt` to handle `-l` and `-t` options
* **ArrayList in C**: `create_arraylist`, `add_at_index`, `append`, `remove_from_index`, `resize`, `destroy`
* **Segfault-Free Generator**: Builds messages safely with repeated `realloc`, `strcat`, and careful index validation
* **Unit Tests**: Four tests for `create`, `append`, `add_at_index`, and `remove_from_index`

## Prerequisites

* GCC (C99)
* Make
* Linux or macOS environment

## Building

```bash
# Clone the repository
# Build the generator and tests
make
```

## Usage

```bash
# Generate a random message of length 8
overlay-gen -l 8
Message: this tea is nothing more Half than hot leaf juice

# Run built-in unit tests
overlay-gen -t
```

### Command-Line Options

* `-l <length>` : Specify the number of words in the generated message
* `-t`          : Run unit tests for ArrayList implementation
* `-h`          : Display usage information

## Example Output

```
$ ./WordGenerator -l 8
Message: this tea is nothing more Half than hot leaf juice

$ ./WordGenerator -t
TEST_CREATE passes! Congratulations!
TEST_APPENDS passes! Congratulations!
TEST_ADD_AT_INDEX passes! Congratulations!
TEST_REMOVE_FROM_INDEX passes! Congratulations!
ALL TESTS PASS! Congratulations
```

## Project Structure

```
├── arraylist.h           # Header for ArrayList interface
├── arraylist.c           # ArrayList implementation in C
├── main.c                # Message generator main program
├── arraylist_tests.c     # Unit tests for ArrayList
├── main.h                # Declarations and dictionary data
├── Makefile              # Build rules for program and tests
└── README_HW4.md         # Project README
```

---

*Implementer: Minhong Cho (GTID: 903806863)*
