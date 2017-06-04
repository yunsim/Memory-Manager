/*
 * mem_utils.c - implementation of function check_heap
 * CSE 374 HW 6, Yunsi Mou
 * Mar 2, 2017
 */

#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include "mem_impl.h"

#define HEADER_SIZE 16
#define MAX_GAP 112

// defination and initialization of all global parameters
free_node * free_list = NULL;
uintptr_t gl_total_size = 0;

// check for possible problems with the free list data structure
void check_heap() {
  if (free_list == NULL) {
    return;
  }

  free_node * curr = free_list;
  while (curr != NULL && curr -> next != NULL) {
    // block size should be positive & no less than MAX_GAP:
    assert(curr -> size >= MAX_GAP - HEADER_SIZE);

    // blocks are ordered with increasing addresses;
    // they do not overlap or touch
    assert((uintptr_t)curr + (curr -> size) + HEADER_SIZE <
           (uintptr_t)(curr -> next));

    curr = curr -> next;
  }

  // now we hit the last block:
  if (curr != NULL) {
    assert(curr -> size >= MAX_GAP - HEADER_SIZE);
  }
  return;
}

// check if the two blocks are adjacent, if so merge them
void check_merge(free_node * front, free_node * tail) {
  if ((uintptr_t) front + front -> size + HEADER_SIZE == (uintptr_t) tail) {
    front -> size += tail -> size + HEADER_SIZE;
    front -> next = tail -> next;
  }
}

// insert the given block into the free list
void insert_block(free_node * startaddr) {
  if (free_list == NULL) {
    free_list = startaddr;
    return;
  } else {
    // check if the freed address is smaller than the first block of
    // the free list
    if ((uintptr_t) startaddr < (uintptr_t) free_list) {
      startaddr -> next = free_list;
      free_list = startaddr;
      check_merge(free_list, free_list -> next);
    } else {
      free_node * current = free_list;
      // check if the freed address should either be put at the end of
      // the free list or in the free list
      while (current -> next != NULL &&
(uintptr_t) current -> next < (uintptr_t) startaddr) {
        current = current -> next;
      }
      if (current -> next == NULL) {
        current -> next = startaddr;
        startaddr -> next = NULL;
        check_merge(current, startaddr);
      } else {
        startaddr -> next = current -> next;
        current -> next = startaddr;
        check_merge(startaddr, startaddr -> next);
        check_merge(current, current -> next);
      }
    }
  }
}
