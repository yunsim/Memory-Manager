/* 
 * mem_impl.h - header file with declarations of internal implementation
 * details shared by other functon implementation files
 * CSE 374 HW6, Yunsi Mou
 * Mar 2, 2017
 */

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#include <inttypes.h>

// Define a block of free list
typedef struct free_node {
  uintptr_t size;
  struct free_node* next;
} free_node;

// the total amount requested from the underlying system
extern uintptr_t gl_total_size;

// the total amount of storage in bytes that is currently stored
// on the free list
extern uintptr_t gl_total_free;

// the total number of individual blocks currently stored on the free list
extern uintptr_t gl_free_blocks;

// first node of free list or null if empty
extern free_node * free_list;

// check for possible problems with the free list data structure
void check_heap();

// check if the two blocks are adjacent, if so merge them
void check_merge(free_node * front, free_node * tail);

// insert the given block into the free list
void insert_block(free_node * startaddr);

#endif
