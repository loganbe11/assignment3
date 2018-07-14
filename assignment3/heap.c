#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"
#include "main.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
  Heap *heap = malloc(sizeof(Heap)*1);
  //heap->nodeArray[initialSize];
  for (int i = 0; i<initialSize; i++)
  {
    heap->nodeArray[i].data = NULL;
  }
  heap->type = htype;
  heap->destroyData = destroyDataFP;
  heap->printNode = printNodeFP;
  heap->compare = compareFP;
  return heap;
}

Node *createHeapNode(void *data)
{
  //not necessary with array implementation
  return NULL;
}

void insertHeapNode(Heap *heap, void *data)
{
  int i = 0;
  while(heap->nodeArray[i].data!=NULL)
  {
    i++;
  }
  heap->nodeArray[i].data=data;
  heapify(heap);
  return;

}

void heapify(Heap *heap)
{
  int i = 0;
  int parent;

  while(heap->nodeArray[i].data!=NULL)
  {
    i++;
  }
  i--;

  for(; i>0; i--)
  {
    parent=floor((float)i/2);
    if (heap->type==MAX_HEAP)
    {
      if (heap->compare(heap->nodeArray[i].data,heap->nodeArray[parent].data)>0)
      {
        heap->nodeArray[99].data=heap->nodeArray[i].data;
        heap->nodeArray[i].data = heap->nodeArray[parent].data;
        heap->nodeArray[parent].data = heap->nodeArray[99].data;
        heap->nodeArray[99].data=NULL;
      }
    }
    else
    {
      if (heap->compare(heap->nodeArray[i].data,heap->nodeArray[parent].data)<0)
      {
        heap->nodeArray[99].data=heap->nodeArray[i].data;
        heap->nodeArray[i].data = heap->nodeArray[parent].data;
        heap->nodeArray[parent].data = heap->nodeArray[99].data;
        heap->nodeArray[99].data=NULL;
      }
    }
  }
  return;
}

void deleteMinOrMax(Heap *heap)
{
  int i = 0;

  while(heap->nodeArray[i].data!=NULL)
  {
    i++;
  }
  i--;
  heap->nodeArray[0].data=heap->nodeArray[i].data;
  heap->nodeArray[i].data=NULL;
  heapify(heap);
}

void changeHeapType(Heap *heap)
{
  if (heap->type==MIN_HEAP)
  {
    heap->type=MAX_HEAP;
  }
  else
  {
    heap->type=MIN_HEAP;
  }
  heapify(heap);
  return;
}

void deleteHeap (Heap * heap)
{
  while(heap->nodeArray[0].data!=0)
  {
    deleteMinOrMax(heap);
  }
  free(heap);
  return;
}



