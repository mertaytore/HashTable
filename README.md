# Thread-safe Hash Table
Thread-safe hash table implementation, written in C. app.c file simulates a multi-threaded application using the hash table library. Also by using this library, one can create one or more hash tables and access them from multiple threads by running them concurrently. Latly, this library requires N and M parameters given. N sets the amount of buckets there will be in the hash table. M sets the total amount of regions where mutex_locks will be used. There will be N/M = K regions that multiple threads won't be able to access at the same time.
<br>
## Sample run
./app N M <br>
./app 1000 500

## Functions
The library implements 5 functions, hash_init, hash insert, hash_delete, hash_get and hash_destroy.

* **HashTable *hash_init (int N, int M):** <br>Creates a hash table of N buckets protected by M locks. Each bucket will have an associated linked list (chain) initialized to empty list. Returns a pointer to the hash table created if success; otherwise returns NULL.

* **int hash_insert (Hash Table *hp, int k, int v):** <br>Inserts key k and the associated value v into the hash table hp. If success returns 0, otherwise returns -1. If key already presents, does nothing and returns -1.

* **int hash_delete (HashTable *hp, int k):** <br>Removes key k and the associated value v from the hash table hp. If success returns 0, otherwise returns -1.

* **int hash_get (HashTable *hp, int k, int *vptr):** <br>The value associated with key k is retrieved into integer variable with address vptr. If success returns 0, otherwise -1.

* **int hash_destroy (HashTable *hp):** <br>Destroys the hash table and frees all resources used by it.

