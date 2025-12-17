#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arraylist.h"

//normal array
typedef struct ArrayList {
    void **data;
    int capacity;
    int size;
} ArrayList;

ArrayList *createList(void) 
{
  ArrayList *l = (ArrayList*) malloc (sizeof(ArrayList));
  l->data = (void**) malloc (2*sizeof(void*));
  if(l == NULL || l->data == NULL) exit(1);
  
  l->capacity = 2;
  l->size = 0;
  
  return l;
}

void append(ArrayList * l, void * data)
{  
  if (l == NULL) return exit(1);

  if (l->size == l->capacity) 
  {
    l->data = (void*) realloc(l->data,(l->capacity*2)*sizeof(void*));
    l->size++;
    l->capacity *= 2;
    
    l->data[l->size-1] = data; 
  }
    
  else
  {
    l->size++;
    l->data[l->size-1] = data;
  }
}

void push(ArrayList * l, void * data, int i)
{
  if (l == NULL) return exit(1);

  if (i > l->size) 
  {
    EXIT_FAILURE;
  }
    
  if (l->size == l->capacity) 
  {
    l->capacity *= 2;
    l->data = (void*) realloc(l->data,(l->capacity*2)*sizeof(void*));
  }

  for (int j = l->size - 1; j >= i; j--) 
  {
    l->data[j+1] = l->data[j];
  }
  
  l->data[i] = data;
  l->size++;
}

void* pop(ArrayList * l, int i)
{
  if (i < 0)
  {
    void* eliminado = l->data[l->size-i];
    for (int j = l->size-1; j < l->size - 1; j++) 
    {
      l->data[j] = l->data[j+1];
    }
  
    l->size = l->size-1;
    return eliminado;
  }

  if (i >= l->size)
  {
    return NULL;
  }

  void* eliminado = l->data[i];
  for (int j = i; j < l->size - 1; j++) 
  {
    l->data[j] = l->data[j+1];
  }
  
  l->size = l->size-1;
  return eliminado;
  
}

void* get(ArrayList * l, int i)
{
  if (i < 0)
  {
    return l->data[l->size-1];
  }

  if (i >= l->size)
  {
    return NULL;
  }
  
  void *num = l->data[i];
  
  return num;
}

int get_size(ArrayList * l)
{
    return l->size;
}

//remove elements
void clean(ArrayList * l)
{
  l->capacity = 2;
  l->size = 0;
}
