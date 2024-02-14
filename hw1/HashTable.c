/*
 * Copyright ©2024 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "CSE333.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "HashTable_priv.h"

///////////////////////////////////////////////////////////////////////////////
// Internal helper functions.
//
#define INVALID_IDX -1

// Grows the hashtable (ie, increase the number of buckets) if its load
// factor has become too high.
static void MaybeResize(HashTable *ht);

int HashKeyToBucketNum(HashTable *ht, HTKey_t key) {
  return key % ht->num_buckets;
}

// Searches through a given linked list for the specified key, returning true
// if found and passes a pointer back through keyvalue, false otherwise.
// Can optionally remove the queried key if rm is set to true.
static bool search(LinkedList* chain,
                   HTKey_t key,
                   HTKeyValue_t** keyvalue,
                   bool rm);

// Deallocation functions that do nothing.  Useful if we want to deallocate
// the structure (eg, the linked list) without deallocating its elements or
// if we know that the structure is empty.
static void LLNoOpFree(LLPayload_t freeme) { }
static void HTNoOpFree(HTValue_t freeme) { }


///////////////////////////////////////////////////////////////////////////////
// HashTable implementation.

HTKey_t FNVHash64(unsigned char *buffer, int len) {
  // This code is adapted from code by Landon Curt Noll
  // and Bonelli Nicola:
  //     http://code.google.com/p/nicola-bonelli-repo/
  static const uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
  static const uint64_t FNV_64_PRIME = 0x100000001b3ULL;
  unsigned char *bp = (unsigned char *) buffer;
  unsigned char *be = bp + len;
  uint64_t hval = FNV1_64_INIT;

  // FNV-1a hash each octet of the buffer.
  while (bp < be) {
    // XOR the bottom with the current octet.
    hval ^= (uint64_t) * bp++;
    // Multiply by the 64 bit FNV magic prime mod 2^64.
    hval *= FNV_64_PRIME;
  }
  return hval;
}

HashTable* HashTable_Allocate(int num_buckets) {
  HashTable *ht;
  int i;

  Verify333(num_buckets > 0);

  // Allocate the hash table record.
  ht = (HashTable *) malloc(sizeof(HashTable));
  Verify333(ht != NULL);

  // Initialize the record.
  ht->num_buckets = num_buckets;
  ht->num_elements = 0;
  ht->buckets = (LinkedList **) malloc(num_buckets * sizeof(LinkedList *));
  Verify333(ht->buckets != NULL);
  for (i = 0; i < num_buckets; i++) {
    ht->buckets[i] = LinkedList_Allocate();
  }

  return ht;
}

void HashTable_Free(HashTable *table,
                    ValueFreeFnPtr value_free_function) {
  int i;

  Verify333(table != NULL);

  // Free each bucket's chain.
  for (i = 0; i < table->num_buckets; i++) {
    LinkedList *bucket = table->buckets[i];
    HTKeyValue_t *kv;

    // Pop elements off the chain list one at a time.  We can't do a single
    // call to LinkedList_Free since we need to use the passed-in
    // value_free_function -- which takes a HTValue_t, not an LLPayload_t -- to
    // free the caller's memory.
    while (LinkedList_NumElements(bucket) > 0) {
      Verify333(LinkedList_Pop(bucket, (LLPayload_t *)&kv));
      value_free_function(kv->value);
      free(kv);
    }
    // The chain is empty, so we can pass in the
    // null free function to LinkedList_Free.
    LinkedList_Free(bucket, LLNoOpFree);
  }

  // Free the bucket array within the table, then free the table record itself.
  free(table->buckets);
  free(table);
}

int HashTable_NumElements(HashTable *table) {
  Verify333(table != NULL);
  return table->num_elements;
}

bool HashTable_Insert(HashTable *table,
                      HTKeyValue_t newkeyvalue,
                      HTKeyValue_t *oldkeyvalue) {
  int bucket;
  LinkedList *chain;

  Verify333(table != NULL);
  MaybeResize(table);

  // Calculate which bucket and chain we're inserting into.
  bucket = HashKeyToBucketNum(table, newkeyvalue.key);
  chain = table->buckets[bucket];

  // STEP 1: finish the implementation of InsertHashTable.
  // This is a fairly complex task, so you might decide you want
  // to define/implement a helper function that helps you find
  // and optionally remove a key within a chain, rather than putting
  // all that logic inside here.  You might also find that your helper
  // can be reused in steps 2 and 3.

  HTKeyValue_t* oldItem = NULL;
  HTKeyValue_t* newItem;
  bool present;

  // Helper method searches the chain for the given key
  present = search(chain, newkeyvalue.key, &oldItem, false);

  if (oldItem != NULL) {
    // Copy old key/value pair into return pointer
    oldkeyvalue->key = oldItem->key;
    oldkeyvalue->value = oldItem->value;
    oldItem->value = newkeyvalue.value;
  } else {
    // Copy new key/value pair into dynamic memory so it's accessible later.
    newItem = (HTKeyValue_t*) malloc(sizeof(HTKeyValue_t));
    newItem->key = newkeyvalue.key;
    newItem->value = newkeyvalue.value;

    LinkedList_Append(chain, newItem);
    table->num_elements++;
  }
  return present;
}

bool HashTable_Find(HashTable *table,
                    HTKey_t key,
                    HTKeyValue_t *keyvalue) {
  Verify333(table != NULL);

  // STEP 2: implement HashTable_Find.

  int bucket;
  LinkedList *chain;
  HTKeyValue_t* oldItem = NULL;
  bool present = false;

  // Calculate which bucket and chain we're searching in.
  bucket = HashKeyToBucketNum(table, key);
  chain = table->buckets[bucket];

  present = search(chain, key, &oldItem, false);

  if (present && oldItem != NULL) {
    keyvalue->key = oldItem->key;
    keyvalue->value = oldItem->value;
  }
  return present;
}

bool HashTable_Remove(HashTable *table,
                      HTKey_t key,
                      HTKeyValue_t *keyvalue) {
  Verify333(table != NULL);

  // STEP 3: implement HashTable_Remove.

  int bucket;
  LinkedList *chain;
  HTKeyValue_t* oldItem = NULL;
  bool present = false;

  // Calculate which bucket and chain we're removing from.
  bucket = HashKeyToBucketNum(table, key);
  chain = table->buckets[bucket];

  present = search(chain, key, &oldItem, true);

  if (present) {
    keyvalue->key = oldItem->key;
    keyvalue->value = oldItem->value;
    free(oldItem);
    table->num_elements--;
  }
  return present;
}


///////////////////////////////////////////////////////////////////////////////
// HTIterator implementation.

HTIterator* HTIterator_Allocate(HashTable *table) {
  HTIterator *iter;
  int         i;

  Verify333(table != NULL);

  iter = (HTIterator *) malloc(sizeof(HTIterator));
  Verify333(iter != NULL);

  // If the hash table is empty, the iterator is immediately invalid,
  // since it can't point to anything.
  if (table->num_elements == 0) {
    iter->ht = table;
    iter->bucket_it = NULL;
    iter->bucket_idx = INVALID_IDX;
    return iter;
  }

  // Initialize the iterator.  There is at least one element in the
  // table, so find the first element and point the iterator at it.
  iter->ht = table;
  for (i = 0; i < table->num_buckets; i++) {
    if (LinkedList_NumElements(table->buckets[i]) > 0) {
      iter->bucket_idx = i;
      break;
    }
  }
  Verify333(i < table->num_buckets);  // make sure we found it.
  iter->bucket_it = LLIterator_Allocate(table->buckets[iter->bucket_idx]);
  return iter;
}

void HTIterator_Free(HTIterator *iter) {
  Verify333(iter != NULL);
  if (iter->bucket_it != NULL) {
    LLIterator_Free(iter->bucket_it);
    iter->bucket_it = NULL;
  }
  free(iter);
}

bool HTIterator_IsValid(HTIterator *iter) {
  Verify333(iter != NULL);

  // STEP 4: implement HTIterator_IsValid.

  Verify333(iter != NULL);
  Verify333(iter->ht != NULL);

  if (iter->bucket_idx >= iter->ht->num_buckets) {  // Ran past the end.
    return false;
  }
  if (iter->ht->num_elements <= 0) {  // No items.
    return false;
  }
  return true;
}

bool HTIterator_Next(HTIterator *iter) {
  Verify333(iter != NULL);

  // STEP 5: implement HTIterator_Next.

  if (!HTIterator_IsValid(iter)) {
    return false;
  }

  Verify333(LLIterator_IsValid(iter->bucket_it));
  bool moreItems = LLIterator_Next(iter->bucket_it);

  if (moreItems) {  // Current chain has more items.
    return true;

  } else {  // Iterator has gone off the end of the bucket, find the next one.
    LLIterator_Free(iter->bucket_it);
    iter->bucket_it = NULL;
    iter->bucket_idx++;

    LinkedList* bucket;
    while (iter->bucket_idx < iter->ht->num_buckets) {
      // Check if iterator is still valid with new bucket index.
      if (!HTIterator_IsValid(iter)) {
        return false;
      }

      bucket = iter->ht->buckets[iter->bucket_idx];
      if (LinkedList_NumElements(bucket) > 0) {
        iter->bucket_it = LLIterator_Allocate(bucket);
        return true;
      } else {
        iter->bucket_idx++;
      }
    }
    // Iter has hit the end of the table and is now invalid.
    iter->bucket_it = NULL;
    return false;
  }
}

bool HTIterator_Get(HTIterator *iter, HTKeyValue_t *keyvalue) {
  Verify333(iter != NULL);

  // STEP 6: implement HTIterator_Get.

  if (!HTIterator_IsValid(iter)) {
    return false;
  }

  HTKeyValue_t* item = NULL;
  if (LLIterator_IsValid(iter->bucket_it)) {
    LLIterator_Get(iter->bucket_it, (void **)&item);
    if (item != NULL) {
      keyvalue->key = item->key;
      keyvalue->value = item->value;
      return true;
    }
  }
  return false;
}

bool HTIterator_Remove(HTIterator *iter, HTKeyValue_t *keyvalue) {
  HTKeyValue_t kv;

  Verify333(iter != NULL);

  // Try to get what the iterator is pointing to.
  if (!HTIterator_Get(iter, &kv)) {
    return false;
  }

  // Advance the iterator.  Thanks to the above call to
  // HTIterator_Get, we know that this iterator is valid (though it
  // may not be valid after this call to HTIterator_Next).
  HTIterator_Next(iter);

  // Lastly, remove the element.  Again, we know this call will succeed
  // due to the successful HTIterator_Get above.
  Verify333(HashTable_Remove(iter->ht, kv.key, keyvalue));
  Verify333(kv.key == keyvalue->key);
  Verify333(kv.value == keyvalue->value);

  return true;
}

static void MaybeResize(HashTable *ht) {
  HashTable *newht;
  HashTable tmp;
  HTIterator *it;

  // Resize if the load factor is > 3.
  if (ht->num_elements < 3 * ht->num_buckets)
    return;

  // This is the resize case.  Allocate a new hashtable,
  // iterate over the old hashtable, do the surgery on
  // the old hashtable record and free up the new hashtable
  // record.
  newht = HashTable_Allocate(ht->num_buckets * 9);

  // Loop through the old ht copying its elements over into the new one.
  for (it = HTIterator_Allocate(ht);
       HTIterator_IsValid(it);
       HTIterator_Next(it)) {
    HTKeyValue_t item, unused;

    Verify333(HTIterator_Get(it, &item));
    HashTable_Insert(newht, item, &unused);
  }

  // Swap the new table onto the old, then free the old table (tricky!).  We
  // use the "no-op free" because we don't actually want to free the elements;
  // they're owned by the new table.
  tmp = *ht;
  *ht = *newht;
  *newht = tmp;

  // Done!  Clean up our iterator and temporary table.
  HTIterator_Free(it);
  HashTable_Free(newht, &HTNoOpFree);
}

static bool search(LinkedList* chain,
                   HTKey_t key,
                   HTKeyValue_t** keyvalue,
                   bool rm) {
  // Construct an iterator over the chain.
  LLIterator* iter = LLIterator_Allocate(chain);
  HTKeyValue_t* item = NULL;
  bool flag = false;

  // Iterate through every item in the list, checking for our key.
  while (LLIterator_IsValid(iter)) {
    // Check each item against the key, exiting early if it is found.
    LLIterator_Get(iter, (void **)&item);
    if (item->key == key) {
      flag = true;
      *keyvalue = item;
      if (rm) {  // Remove the item if specified in arguments.
        LLIterator_Remove(iter, HTNoOpFree);
      }
      break;
    }
    LLIterator_Next(iter);
  }
  // Free the iterator since we're done.
  LLIterator_Free(iter);
  return flag;
}
