Hash Table Implementation in C
This project provides an implementation of a hash table in C with support for insertion, deletion, resizing, and collision handling using double hashing. The project also includes utilities for prime number calculations used for dynamic resizing of the hash table.

Project Structure
.
├── hash_table.c         - Hash table implementation
├── main.c               - Main program to test the hash table
├── prime.c              - Prime number utilities
├── prime.h              - Header file for prime number functions
└── hash_table.h         - Header file for the hash table (not included in the provided files)

Files Overview
hash_table.c
Implements core hash table functionality:
Insertion (ht_insert) with dynamic resizing when load factor exceeds 70%.
Deletion (ht_delete) with resizing when load factor falls below 10%.
Search (ht_search) for retrieving values by key.
Double Hashing for collision resolution.
Functions include:
ht_new() - Create a new hash table.
ht_insert(ht, key, value) - Insert a key-value pair.
ht_search(ht, key) - Search for a value by key.
ht_delete(ht, key) - Delete a key-value pair.
ht_del_hash_table(ht) - Free the memory allocated for the hash table.

main.c
A test suite for the hash table implementation:
Basic Operations: Insertion, search, and deletion.
Collision Handling: Demonstrates handling of key collisions.
Resizing: Inserts 100 items to trigger resizing and ensures data integrity.

Example output after running main.c:
-----------------------------------------
Basic Insertion and Searching
-----------------------------------------
name: Alice
age: 25
city: London

-----------------------------------------
Key Collision Handling
-----------------------------------------
name: Alice
eman: Bob

-----------------------------------------
Update existing key
-----------------------------------------
Before update: Alice
After update: Bob

-----------------------------------------
Deleting a key
-----------------------------------------
age: NULL
name: Alice

-----------------------------------------
Inserting 100 items to trigger resizing
-----------------------------------------
key0: val0
key50: val50
key99: val99

prime.c and prime.h
Prime Number Utilities for resizing the hash table:
is_prime(x) - Check if a number is prime.
next_prime(x) - Find the next prime number greater than x.

Compilation and Execution
Compile the project using gcc:
gcc main.c hash_table.c prime.c -o hash_table

Run the executable:
./hash_table

Features
Dynamic Resizing: The hash table automatically resizes when the load factor exceeds 70% (expand) or falls below 10% (shrink).
Collision Handling: Uses double hashing for resolving collisions.
Memory Management: Proper allocation and deallocation of memory to prevent leaks.
Prime Number Optimization: The table size is adjusted to the next prime number to reduce clustering.

Dependencies
Standard Libraries:
<stdio.h>
<stdlib.h>
<string.h>
<math.h>