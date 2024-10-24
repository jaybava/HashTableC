#include <stdio.h>

#include "hashtable.h"
#include "prime.h"


int main(){
  ht_hash_table* ht = ht_new();

  printf("-----------------------------------------\n");
  printf("Basic Insertion and Searching\n");
  printf("-----------------------------------------\n");

  // Testing Insert
  ht_insert(ht, "name", "Alice");
  ht_insert(ht, "age", "25");
  ht_insert(ht, "city", "London");

  printf("name: %s\n", ht_search(ht, "name")); // Should output "Alice"
  printf("age: %s\n", ht_search(ht, "age"));   // Should output "25"
  printf("city: %s\n", ht_search(ht, "city")); // Should output "London"

  printf("\n-----------------------------------------\n");
  printf("Key Collision Handling\n");
  printf("-----------------------------------------\n");

  ht_insert(ht, "name", "Alice");
  ht_insert(ht, "eman", "Bob");  // "eman" is a reverse of "name", might collide

  // Ensure both are accessible
  printf("name: %s\n", ht_search(ht, "name")); // Should output "Alice"
  printf("eman: %s\n", ht_search(ht, "eman")); // Should output "Bob"

  printf("\n-----------------------------------------\n");
  printf("Update exitsting key\n");
  printf("-----------------------------------------\n");

  ht_insert(ht, "name", "Alice");
  printf("Before update: %s\n", ht_search(ht, "name")); // Should output "Alice"

  ht_insert(ht, "name", "Bob"); // Update the value for the key "name"
  printf("After update: %s\n", ht_search(ht, "name"));  // Should output "Bob"

  printf("\n-----------------------------------------\n");
  printf("Deleting a key\n");
  printf("-----------------------------------------\n");

  ht_insert(ht, "name", "Alice");
  ht_insert(ht, "age", "25");

  // Delete the "age" key
  ht_delete(ht, "age");

  // Ensure "age" is deleted
  printf("age: %s\n", ht_search(ht, "age")); // Should output "NULL" or empty

  // Ensure "name" is still accessible
  printf("name: %s\n", ht_search(ht, "name")); // Should output "Alice"

  printf("\n-----------------------------------------\n");
  printf("Searching for a non-existing key\n");
  printf("-----------------------------------------\n");

  // Search for a non-existing key
  printf("gender: %s\n", ht_search(ht, "gender")); // Should output "NULL"

  printf("\n-----------------------------------------\n");
  printf("Inserting a 100 items to trigger resizing\n");
  printf("-----------------------------------------\n");

  // Insert many items to trigger resizing
  for (int i = 0; i < 100; i++) {
    char key[10];
    char value[10];
    sprintf(key, "key%d", i);
    sprintf(value, "val%d", i);
    ht_insert(ht, key, value);
  }

  // Check if a few random items are still accessible after resizing
  printf("key0: %s\n", ht_search(ht, "key0"));   // Should output "val0"
  printf("key50: %s\n", ht_search(ht, "key50")); // Should output "val50"
  printf("key99: %s\n", ht_search(ht, "key99")); // Should output "val99"

  // Cleanup
  ht_del_hash_table(ht);

}