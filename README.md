# Inverted Search Engine

A high-performance text indexing and retrieval system implemented in **C** using **Hash Tables** and **Two-Tier Nested Linked Lists**. 

The system indexes terms across multiple text files, tracking their occurrence frequencies and locations to allow near instantaneous search queries, state backups, and database restoration.

## Architecture & Data Structures

The project uses an inverted index architecture with a **27-bucket Hash Table** (indices `0–25` for letters `'a'` through `'z'`, and index `26` for numbers and special characters).

Each bucket points to a **Two-Tier Linked List**:
1. **Level 1 (`MainNode`)**: Stores unique words, the total number of distinct files containing that word, and a pointer to the next word in the bucket.
2. **Level 2 (`SubNode`)**: A singly linked list attached to each `MainNode` storing the specific filename and the frequency of that word within that file.

```
HashTable (table[0..26])
   │
   ├── table[7] ('h')
   │     │
   │     └── MainNode: "hello" | file_count: 2
   │           ├── SubNode: file1.txt (count: 3) ──> SubNode: file2.txt (count: 1)
   │           │
   │           └── main_link ──> MainNode: "hii" | file_count: 1
   │                               └── SubNode: file1.txt (count: 2)
```

---

## ✨ Key Features

- **Strict Input Validation**:
  - Validates `.txt` file extensions.
  - Detects duplicate files passed in command-line arguments.
  - Ensures files exist and are non-empty.
- **Case-Insensitive Search & Indexing**: Words are normalized to lowercase during indexing and querying.
- **Fast Word Lookup**: Hash-based bucket resolution provides average $O(1)$ access to word lists.
- **Persistent Storage**: Save database memory state to structured backup files.
- **Database Restoration / Update**: Repopulates the database directly from a backup file without re-parsing original source files.
- **Zero Memory Leaks**: Clean dynamic deallocation (`free`) of all nested nodes on exit.
- **Colored CLI Interface**: ANSI color codes for enhanced readability and clear feedback.

---

## Project Structure

```text
InvertedSearch/
├── inverted.h       # Shared header file (structs, macros, prototypes)
├── main.c           # CLI menu loop and flow control
├── validation.c     # Command-line file acceptance and validation
├── create_DB.c      # Parses input files and builds the hash table
├── display_DB.c     # Displays the database in a clean tabular layout
├── search.c         # Word search and occurrence lookup
├── save_DB.c        # Dumps the database to a persistent backup file
├── update_DB.c      # Restores the database from a backup file
├── free_db.c        # Memory deallocation routines
├── Makefile         # Automated build script
└── README.md        # Project documentation
```

---

## Compilation & Execution

### 1. Build using `make`
```bash
make
```

### 2. Run the application
Pass one or more text files as command-line arguments:
```bash
./inverted_search file1.txt file2.txt text1.txt
```

### 3. Clean build artifacts
```bash
make clean
```

---

##  Menu & Functionalities

```text
========================================
         INVERTED SEARCH MENU           
========================================
1. Create Database
2. Display Database
3. Search Database
4. Save Database
5. Update Database
6. Exit

Enter your choice: 
```

### 1. Create Database
Reads all accepted text files, extracts words, and constructs the hash table and linked lists. Can only be created once per session.

### 2. Display Database
Outputs the entire indexed database formatted as a table:
```text
[---DATABASE---]
--------------------------------------------------------------------
Index    Word            Filecount       Files Name      Wordcount
--------------------------------------------------------------------
1        bye             1               text2.txt       1         
4        everyone        2               file1.txt       1         text1.txt       1         
7        hello           2               file1.txt       3         file2.txt       1         
```

### 3. Search Database
Prompts for a keyword and displays which files contain the word along with frequency counts:
```text
Enter word to search: hello

Word found!
-----------------------------------------------------------------------
Index    Word            Filecount       Files Name           Wordcount
-----------------------------------------------------------------------
7        hello           2               file1.txt            3         
7        hello           2               file2.txt            1         
```

### 4. Save Database
Saves the currently loaded database to a specified `.txt` file. If the file already exists, it prompts for overwrite confirmation (`[Y/N]`).

### 5. Update Database
Loads an existing backup file into memory. Useful when starting a session without regenerating the database from raw text files.

---

## 💾 Backup File Specification

Saved database files use the following structured multiline block format:

```text
#<bucket_index>
WORD: <word_string>
FILECOUNT: <total_files>
FILE: <filename>  WORDCOUNT: <frequency>
FILE: <filename>  WORDCOUNT: <frequency>
#
```

#### Example:
```text
#7
WORD: hello
FILECOUNT: 2
FILE: file1.txt  WORDCOUNT: 3
FILE: file2.txt  WORDCOUNT: 1
#
```

---

## 🧹 Memory Management

Because the database uses a two-tier nested hierarchy, memory is freed from the inside out when exiting:
1. Traverse each `MainNode` in every bucket.
2. Free all attached `SubNode` elements sequentially.
3. Free the `MainNode`.
4. Free the linked list of validated file names (`F_node`).
