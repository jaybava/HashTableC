#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "hash_table.h"
#include "prime.h"

// create a deleted item of type ht_item
static ht_item HT_DELETED_ITEM = {NULL, NULL};

// method to create a new ht_item
static ht_item* ht_new_item(const char* k, const char* v) {
  // allocate memory of size ht_item
  ht_item* i = malloc(sizeof(ht_item));
  // set the item's key and value to passed k and v variables
  i->key = strdup(k);
  i->value = strdup(v);
  // return the item
  return i;
}

// method to create a sized table
static ht_hash_table* ht_new_sized(const int base_size) {
  // allocate memory for hash table
  ht_hash_table* ht = malloc(sizeof(ht_hash_table));
  // set the base_size of the table to passed variable base_size
  ht-> base_size = base_size;
  // set the size to the next available prime number
  ht-> size = next_prime(ht-> base_size);
  // set count to 0 as no items are added
  ht->count = 0;
  // create buckets and initailze them all to null
  ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
  return ht;

}

// method to create a new has table
ht_hash_table* ht_new() {
  // create a new sized table with constant
  return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

// method to get the hash value given a string
static int ht_hash(const char* s, const int a, const int m) {
  // initialize hash
  long hash = 0;
  // get length of string
  const int len_s = strlen(s);
  // for each character in string
  for (int i = 0; i < len_s; i++) {
    // add the ascii value of the character multiplied by a^(len_s - remaining characters)
    hash += (long)pow(a, len_s - (i + 1)) * s[i];
    // use modulus to map to available table size
    hash %= m;
  }
  // return the int of hash
  return (int)hash;
}
// method to map the hash value to an index for the hash table using double hashing to avoid collisions
static int ht_get_hash(const char* s, const int num_buckets, const int attempt) {
  // compute first hash value
  const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
  // compute second hash value
  const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
  // return the final has value using double hashing formula
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;

}

// method to delete an item
static void ht_del_item(ht_item* i) {
  // free all the memory used by item essentially deleting it
  free(i->key);
  free(i->value);
  free(i);
}

// method to resize hash table used by insert and delete methods
static void ht_resize(ht_hash_table* ht, const int base_size) {
  // filter if size is less than initial size constant
  if(base_size < HT_INITIAL_BASE_SIZE) {
    return;
  }
  // create a new hash table called new_ht and use the size inputted to function
  ht_hash_table* new_ht = ht_new_sized(base_size);
  // for loop for moving all the items in old hash table to new one
  for (int i = 0; i < ht->size; i++) {
    // get item at index i
    ht_item* item = ht->items[i];
    // filter is item isnt null and isnt a deleted item
    if (item != NULL && item != &HT_DELETED_ITEM) {
      // insert into item from old hash table to the new hash table
      ht_insert(new_ht, item->key, item->value);
    }
  }
  // set base_size and count of new ht
  ht->base_size = new_ht->base_size;
  ht->count = new_ht->count;

  // swap new hash table's size and items with old hash table's size and item we do this to not move to another block of memory which is the new hash map
  const int tmp_size = ht->size;
  ht->size = new_ht->size;
  new_ht->size = tmp_size;

  ht_item** tmp_items = ht->items;
  ht->items = new_ht->items;
  new_ht->items = tmp_items;

  // delete new hash table which now contains the old data
  ht_del_hash_table(new_ht);
}

// method to resize the hash table up used by insert method
static void ht_resize_up(ht_hash_table* ht) {
  // multiply the base_size by 2
  const int new_size = ht->base_size * 2;
  // and resize with new_size
  ht_resize(ht, new_size);
}

// method to insert a key value pair into hash table
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
  // calculate the load
  const int load = ht->count * 100 / ht->size;
  // chcck to see if load is over 70%
  if (load > 70) {
    // call resize up method
    ht_resize_up(ht);
  }
  // allocate memory for new item
  ht_item* item = ht_new_item(key, value);
  // get index using hash function
  int index = ht_get_hash(item->key, ht->size, 0);
  // initialize variables for collision resolution
  ht_item* cur_item = ht->items[index];
  int i = 1;
  // finding a empty spot
  while (cur_item != NULL) {
    // skip over deleted items
    if (cur_item != &HT_DELETED_ITEM) {
      // if a matching key is found
      if (strcmp(cur_item->key, key) == 0) {
        // delete the item
        ht_del_item(cur_item);
        // put the new item in
        ht->items[index] = item;
        // exit the method
        return;
      }
    }
    // we use i and get new hash index
    index = ht_get_hash(item->key, ht->size, i);
    // set curr_item to new hash index
    cur_item = ht->items[index];
    // increment i
    i++;
  }
  // when empty spot is found
  //insert new item
  ht->items[index] = item;
  // increment count
  ht->count++;
}

// method to search for value given key
char* ht_search(ht_hash_table* ht, const char* key) {
  // find index using hash function
  int index = ht_get_hash(key, ht->size, 0);
  // find item at index
  ht_item* item = ht->items[index];
  int i = 1;
  // finding the correct item with matching key
  while (item != NULL) {
    // skip over deleted items
    if (item != &HT_DELETED_ITEM) {
      if (strcmp(item->key, key) == 0) {
        // if matching key is found return the value
        return item->value;
      }
    }
    // get new hash value
    index = ht_get_hash(key, ht->size, i);
    // set item to new index
    item = ht->items[index];
    i++;
  }
  // if item is not found return null
  return NULL;
}

// method to resize the hash table down used by delete method
static void ht_resize_down(ht_hash_table* ht) {
  // set new_size to half of base_size
  const int new_size = ht->base_size / 2;
  // pass new_size to resize method
  ht_resize(ht, new_size);
}

// method to delete an item given a key
void ht_delete(ht_hash_table* ht, const char* key) {
  // calculate load
  const int load = ht->count * 100 / ht->size;
  // if load is less than 10%
  if (load < 10) {
    // call resize_down method
    ht_resize_down(ht);
  }
  // get index using hash function
  int index = ht_get_hash(key, ht->size, 0);
  // set item to item at index
  ht_item* item = ht->items[index];
  // set i to 1 for while loop
  int i = 1;
  // while item isnt null
  while (item != NULL) {
    // if item isnt a deleted item
    if(item != &HT_DELETED_ITEM) {
      // and if the item matches the key
      if (strcmp(item->key, key) == 0) {
        // we deleted the item with method
        ht_del_item(item);
        // set the item to deleted item constant
        ht->items[index] = &HT_DELETED_ITEM;
        // decrement counter
        ht->count--;
        // break out of loop
        break;
      }
    }
    // if the item key doesnt match use i to get the next attempt index
    index = ht_get_hash(item->key, ht->size, i);
    // set the item to new idex
    item = ht->items[index];
    // increment i
    i++;
  }
}

// method to delete hash table
void ht_del_hash_table(ht_hash_table* ht) {
  // itterate through hash table
  for (int i = 0; i < ht->size; i++) {
    // set item to current i index
    ht_item* item = ht->items[i];
    // if the item isnt null and isnt deleted
    if (item != NULL && item != &HT_DELETED_ITEM) {
      // delete the item using method
      ht_del_item(item);
    }
  }
  // free rest of the allocations
  free(ht->items);
  free(ht);
}





