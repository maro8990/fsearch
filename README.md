# fsearch

`fsearch` is a lightweight command-line file search utility written in C++17 and inspired by Unix tools such as `grep`.

The program recursively searches through a directory and its subdirectories, scans text files for a specified search term, and reports every matching line together with its file path and line number.

The project demonstrates practical use of the C++ Standard Library for filesystem traversal, file I/O, string searching, structured data, and command-line argument processing.

---

## Features

- Recursively searches directories and subdirectories
- Searches `.txt` files for a specified text pattern
- Displays the path of every matching file
- Reports the exact line number of each match
- Displays the complete matching line
- Counts the number of files searched
- Counts the total number of matching lines
- Reports files that could not be opened
- Validates that the supplied directory exists
- Uses only the C++ Standard Library

---

## Example

Given a directory containing several text files:

```text
documents/
├── notes.txt
├── report.txt
└── archive/
    └── log.txt
```

A search can be performed with:

```bash
./fsearch ./documents network
```

Example output:

```text
Searching for: network
Directory : ./documents

The file path: "./documents/report.txt"

Line 14: The network connection was successfully established.

The file path: "./documents/archive/log.txt"

Line 7: Network configuration completed.

Number of searching files: 3
Number of matching lines: 2
```

---

## Usage

```bash
./fsearch <directory> <search-term>
```

### Example

```bash
./fsearch ./documents error
```

If the search term contains spaces, place it inside quotation marks:

```bash
./fsearch ./documents "connection failed"
```

---

## Building the Project

### Requirements

- A C++ compiler with **C++17** support
- GCC, Clang, or another standards-compliant C++ compiler

C++17 is required because the project uses `std::filesystem`.

### Compile with GCC

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o fsearch
```

### Run on Linux/macOS

```bash
./fsearch <directory> <search-term>
```

### Run on Windows

```text
fsearch.exe <directory> <search-term>
```

Example:

```text
fsearch.exe C:\Documents network
```

---

## How It Works

The program receives two command-line arguments:

```text
fsearch <directory> <search-term>
```

It then performs the following steps:

1. Validates that the supplied directory exists.
2. Creates a recursive directory iterator.
3. Traverses the directory and all of its subdirectories.
4. Selects regular files with the `.txt` extension.
5. Opens each file and reads it line by line.
6. Searches each line for the requested search term.
7. Stores information about each match.
8. Displays matching file paths, line numbers, and content.
9. Reports the total number of files searched and matching lines.

---

## Search Results

Each search result is represented using a structure containing:

```cpp
struct search_result {
    filesystem::path file_path;
    int linenum;
    string Line;
};
```

This stores:

- the path of the matching file
- the line number where the match occurred
- the content of the matching line

Matches are collected in:

```cpp
vector<search_result>
```

This separates the search result data from the filesystem traversal itself and allows results to be retained for further processing.

---

## Recursive Directory Traversal

Directory traversal is performed using:

```cpp
filesystem::recursive_directory_iterator
```

Unlike a regular directory iterator, this allows `fsearch` to automatically descend into nested directories.

For example:

```text
project/
├── file1.txt
├── file2.txt
└── logs/
    ├── log1.txt
    └── old/
        └── log2.txt
```

A search starting from `project/` can inspect text files at every level of the directory tree.

---

## Text Searching

Files are processed one line at a time using:

```cpp
getline(file, line)
```

The search itself uses:

```cpp
line.find(searchTerm)
```

A match is detected when:

```cpp
line.find(searchTerm) != string::npos
```

The current implementation therefore performs a **case-sensitive substring search**.

For example, searching for:

```text
network
```

will match:

```text
The network is available.
```

but will not match:

```text
The Network is available.
```

because uppercase and lowercase characters are treated differently.

---

## File Filtering

The current implementation searches regular files whose extension is:

```text
.txt
```

For example:

```text
notes.txt       ✓ searched
report.txt      ✓ searched
main.cpp        ✗ ignored
image.png       ✗ ignored
README.md       ✗ ignored
```

This keeps the current implementation focused specifically on plain-text file searching.

---

## Error Handling

`fsearch` performs several basic validation and error-reporting operations.

It checks whether the requested directory exists before beginning the search.

If an individual text file cannot be opened, the program continues searching the remaining files and reports the files that could not be accessed.

This prevents a single failed file operation from terminating the entire search.

---

## Standard Library Components

The project uses several components of the C++ Standard Library:

| Component | Purpose |
|---|---|
| `std::filesystem` | Directory traversal and path handling |
| `std::ifstream` | Reading files |
| `std::vector` | Storing search results and failed file paths |
| `std::string` | Search terms and line processing |
| `std::filesystem::path` | Platform-independent path representation |

No third-party libraries are required.

---

## Project Structure

```text
.
├── main.cpp
└── README.md
```

`main.cpp` contains:

- command-line argument handling
- directory validation
- recursive filesystem traversal
- text-file filtering
- line-by-line file processing
- substring matching
- result collection
- error reporting
- search statistics

---

## Learning Objectives

This project demonstrates concepts including:

- C++17 filesystem operations
- recursive directory traversal
- command-line applications
- file input/output
- string searching
- structured data
- vectors and collections
- filesystem paths
- input validation
- error handling
- separation of functionality into functions

---

## Current Limitations

The current version:

- Searches only `.txt` files
- Performs case-sensitive searches
- Uses literal substring matching rather than regular expressions
- Searches files sequentially
- Outputs results directly to the terminal

These constraints keep the implementation simple while providing opportunities for future development.

---

## Potential Improvements

Possible future extensions include:

- Case-insensitive searching
- Regular expression support
- Support for multiple file extensions
- User-defined file filters
- Match highlighting
- Optional recursive/non-recursive modes
- Counting matches without displaying them
- Searching for multiple patterns
- Excluding selected directories
- Exporting results to a file
- Improved handling of filesystem permission errors
- Parallel file searching
- Automated unit tests
- Additional command-line options similar to `grep`

Example future syntax could include:

```bash
./fsearch -i ./documents network
```

for case-insensitive searching, or:

```bash
./fsearch -e ".cpp" ./src TODO
```

for searching only selected file types.

---

## About

`fsearch` is a C++17 command-line project exploring filesystem traversal and text searching through a simplified grep-inspired utility.

The project combines recursive directory traversal, file processing, substring matching, result tracking, and error handling into a small standalone application built entirely with the C++ Standard Library.


