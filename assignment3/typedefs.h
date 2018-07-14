
#ifndef _HEAP_defs_
#define _HEAP_defs_

#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char


typedef struct Node
{
  void * data;
} Node;

typedef struct Heap
{
  HEAP_TYPE type; ///< flag for choosing between min and max heap
  size_t heapSize;
  void (*destroyData)(void *data); ///< function pointer to a function to delete a single piece of data from the heap
  void (*printNode)(void *toBePrinted); ///< function pointer to a function that prints out a data element of the heap
  int (*compare)(const void *first, const void *second); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
  Node nodeArray[100];
} Heap;

void reheapify(Heap * heap);


#endif
