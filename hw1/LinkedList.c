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

#include "CSE333.h"
#include "LinkedList.h"
#include "LinkedList_priv.h"


///////////////////////////////////////////////////////////////////////////////
// LinkedList implementation.

LinkedList* LinkedList_Allocate(void) {
  // Allocate the linked list record.
  LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
  Verify333(ll != NULL);

  // STEP 1: initialize the newly allocated record structure.
  ll->num_elements = 0;
  ll->head = NULL;
  ll->tail = NULL;

  // Return our newly minted linked list.
  return ll;
}

void LinkedList_Free(LinkedList *list,
                     LLPayloadFreeFnPtr payload_free_function) {
  Verify333(list != NULL);
  Verify333(payload_free_function != NULL);

  // STEP 2: sweep through the list and free all of the nodes' payloads
  // (using the payload_free_function supplied as an argument) and
  // the nodes themselves.
  LinkedListNode *ln = list->head;
  LinkedListNode *next = list->head;
  while (ln != NULL) {
    next = ln->next;
    payload_free_function(ln->payload);
    free(ln);
    ln = next;
  }

  // free the LinkedList
  free(list);
}

int LinkedList_NumElements(LinkedList *list) {
  Verify333(list != NULL);
  return list->num_elements;
}

void LinkedList_Push(LinkedList *list, LLPayload_t payload) {
  Verify333(list != NULL);

  // Allocate space for the new node.
  LinkedListNode *ln = (LinkedListNode *) malloc(sizeof(LinkedListNode));
  Verify333(ln != NULL);

  // Set the payload
  ln->payload = payload;

  if (list->num_elements == 0) {
    // Degenerate case; list is currently empty
    Verify333(list->head == NULL);
    Verify333(list->tail == NULL);
    ln->next = ln->prev = NULL;
    list->head = list->tail = ln;
    list->num_elements = 1;
  } else {
    // STEP 3: typical case; list has >=1 elements
    Verify333(list->head != NULL);
    ln->prev = NULL;
    ln->next = list->head;
    list->head->prev = ln;
    list->head = ln;
    list->num_elements++;
  }
}

bool LinkedList_Pop(LinkedList *list, LLPayload_t *payload_ptr) {
  Verify333(payload_ptr != NULL);
  Verify333(list != NULL);

  // STEP 4: implement LinkedList_Pop.  Make sure you test for
  // and empty list and fail.  If the list is non-empty, there
  // are two cases to consider: (a) a list with a single element in it
  // and (b) the general case of a list with >=2 elements in it.
  // Be sure to call free() to deallocate the memory that was
  // previously allocated by LinkedList_Push().

  if (list->num_elements < 1) {
    // operation failed
    return false;
  } else {
    // pointer to the node being popped
    LinkedListNode* ln = list->head;
    *payload_ptr = list->head->payload;
    if (list->num_elements == 1) {
      // verify that head and tail are the same, then void them both
      Verify333(list->head == list->tail);
      list->head = NULL;
      list->tail = NULL;

    } else {  // list->num_elements >= 2
      // move list head to next node and cut ties to target node
      list->head = list->head->next;
      list->head->prev = NULL;
    }

    // free the removed list node
    free(ln);

    // update list size to reflect removed node
    list->num_elements--;

    // operation successful
    return true;  // you may need to change this return value
  }
}

void LinkedList_Append(LinkedList *list, LLPayload_t payload) {
  Verify333(list != NULL);

  // STEP 5: implement LinkedList_Append.  It's kind of like
  // LinkedList_Push, but obviously you need to add to the end
  // instead of the beginning.

  // Allocate space for the new node.
  LinkedListNode *ln = (LinkedListNode *) malloc(sizeof(LinkedListNode));
  Verify333(ln != NULL);

  // Set the payload and next value
  ln->payload = payload;
  ln->next = NULL;

  // If list is empty
  if (list->num_elements == 0) {
    // Insert ln as the only node in the list
    ln->prev = NULL;
    list->head = ln;
    list->tail = ln;

  } else {  // List is non-empty
    // Bind ln to the previous tail, then move the tail to ln
    Verify333(list->tail != NULL);
    ln->prev = list->tail;
    list->tail->next = ln;
    list->tail = ln;
  }

  // Update list size to account for new item
  list->num_elements++;
}

void LinkedList_Sort(LinkedList *list, bool ascending,
                     LLPayloadComparatorFnPtr comparator_function) {
  Verify333(list != NULL);
  if (list->num_elements < 2) {
    // No sorting needed.
    return;
  }

  // We'll implement bubblesort! Nnice and easy, and nice and slow :)
  int swapped;
  do {
    LinkedListNode *curnode;

    swapped = 0;
    curnode = list->head;
    while (curnode->next != NULL) {
      int compare_result = comparator_function(curnode->payload,
                                               curnode->next->payload);
      if (ascending) {
        compare_result *= -1;
      }
      if (compare_result < 0) {
        // Bubble-swap the payloads.
        LLPayload_t tmp;
        tmp = curnode->payload;
        curnode->payload = curnode->next->payload;
        curnode->next->payload = tmp;
        swapped = 1;
      }
      curnode = curnode->next;
    }
  } while (swapped);
}


///////////////////////////////////////////////////////////////////////////////
// LLIterator implementation.

LLIterator* LLIterator_Allocate(LinkedList *list) {
  Verify333(list != NULL);

  // OK, let's manufacture an iterator.
  LLIterator *li = (LLIterator *) malloc(sizeof(LLIterator));
  Verify333(li != NULL);

  // Set up the iterator.
  li->list = list;
  li->node = list->head;

  return li;
}

void LLIterator_Free(LLIterator *iter) {
  Verify333(iter != NULL);
  free(iter);
}

bool LLIterator_IsValid(LLIterator *iter) {
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);

  return (iter->node != NULL);
}

bool LLIterator_Next(LLIterator *iter) {
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // STEP 6: try to advance iterator to the next node and return true if
  // you succeed, false otherwise
  // Note that if the iterator is already at the last node,
  // you should move the iterator past the end of the list

  // Check if the iterator is already at the end of the list
  if (iter->node == NULL) {
    return false;
  } else {  // otherwise iter->node->next exists
    iter->node = iter->node->next;
    // check if iter has gone off the end of the list
    if (iter->node == NULL) {
      return false;
    }
    return true;
  }
}

void LLIterator_Get(LLIterator *iter, LLPayload_t *payload) {
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  *payload = iter->node->payload;
}

bool LLIterator_Remove(LLIterator *iter,
                       LLPayloadFreeFnPtr payload_free_function) {
  Verify333(iter != NULL);
  Verify333(iter->list != NULL);
  Verify333(iter->node != NULL);

  // STEP 7: implement LLIterator_Remove.  This is the most
  // complex function you'll build.  There are several cases
  // to consider:
  // - degenerate case: the list becomes empty after deleting.
  // - degenerate case: iter points at head
  // - degenerate case: iter points at tail
  // - fully general case: iter points in the middle of a list,
  //                       and you have to "splice".
  //
  // Be sure to call the payload_free_function to free the payload
  // the iterator is pointing to, and also free any LinkedList
  // data structure element as appropriate.

  // if list only has 1 item
  if (iter->list->num_elements < 2) {
    // check that this is really the only node in the list
    Verify333(iter->node->next == NULL);

    // free the node's payload
    payload_free_function(iter->node->payload);

    // reset iter field values to empty
    iter->list->num_elements = 0;
    iter->list->head = NULL;
    iter->list->tail = NULL;

    free(iter->node);
    iter->node = NULL;

    return false;  // list is now empty
  }

  iter->list->num_elements--;

  // if iter points to the head
  if (iter->node == iter->list->head) {
    // verify that the node is the head of a list
    Verify333(iter->node->prev == NULL);

    // free the node's payload
    payload_free_function(iter->node->payload);

    // move the list's head to the next node and remove its prev pointer
    iter->list->head = iter->list->head->next;
    iter->list->head->prev = NULL;

    // free the old node, then move the iterator to the next node in the list
    free(iter->node);
    iter->node = iter->list->head;

    return true;  // list is not empty
  }

  // if iter points to the tail
  if (iter->node == iter->list->tail) {
    // verify that the node is the tail of a list
    Verify333(iter->node->next == NULL);

    // free the node's payload
    payload_free_function(iter->node->payload);

    // move the list's tail to the prev node and remove its next pointer
    iter->list->tail = iter->list->tail->prev;
    iter->list->tail->next = NULL;

    // free the old node, move the iterator back to the prev node in the list
    free(iter->node);
    iter->node = iter->list->tail;

    return true;  // list is not empty
  }

  // general case
  LinkedListNode* next;
  // free the node's payload
  payload_free_function(iter->node->payload);

  // bind the prev and next nodes to each other, cutting node out of the list
  iter->node->prev->next = iter->node->next;
  iter->node->next->prev = iter->node->prev;

  // free the old node and move iter->next to the next node in the list
  next = iter->node->next;
  free(iter->node);
  iter->node = next;

  return true;  // list is not empty
}


///////////////////////////////////////////////////////////////////////////////
// Helper functions

bool LLSlice(LinkedList *list, LLPayload_t *payload_ptr) {
  Verify333(payload_ptr != NULL);
  Verify333(list != NULL);

  // STEP 8: implement LLSlice.

  if (list->num_elements < 1) {
    // operation failed
    return false;
  } else {
    // pointer to the node being popped
    LinkedListNode* ln = list->tail;
    *payload_ptr = list->tail->payload;


    if (list->num_elements == 1) {
      // verify that head and tail are the same, then void them both
      Verify333(list->head == list->tail);
      list->head = NULL;
      list->tail = NULL;

    } else {  // list->num_elements >= 2
      // move list tail to prev node and cut ties to target node
      list->tail = list->tail->prev;
      list->tail->next = NULL;
    }

    // free the removed list node
    free(ln);

    // update list size to reflect removed node
    list->num_elements--;

    // operation successful
    return true;
  }
}

void LLIteratorRewind(LLIterator *iter) {
  iter->node = iter->list->head;
}
