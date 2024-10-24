// define an item strcture
typedef struct{
    char *key;
    char *value;
} ht_item;

// define an ht_hash_table
typedef struct{
    int base_size;
    int size;
    int count;
    ht_item **items;
} ht_hash_table;

// define the initial base
#define HT_INITIAL_BASE_SIZE 53

// define methods
ht_hash_table* htnew();
void ht_insert(ht_hash_table *ht, const char *key, const char *value);
char *ht_search(ht_hash_table *ht, const char *key);
void ht_delete(ht_hash_table *ht, const char *key);
void ht_del_hash_table(ht_hash_table *ht);
