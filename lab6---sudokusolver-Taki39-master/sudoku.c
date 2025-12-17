#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int iniciarArray(int array[10])
{
  for(int a=0 ;a<10;a++)
    array[a]=0;
  return *array;
}

//separar en 3 funciones mas pequeñas
int is_valid(Node* n)
{
  int filas[10] , columnas[10] , subMatriz[10];
  
  for (int i=0; i<9; i++)
    {
      iniciarArray(filas);
      iniciarArray(columnas);
      for(int j=0; j<9; j++)
      {
        int num = n->sudo[i][j];
        if(num != 0)
        {
          if(filas[num]==1 || columnas[num]==1)
          {
            return 0;
          }
          else
          {
            filas[num] = 1;
            columnas[num] = 1;
          }
        }
      }
    }

  for(int k=0; k<9; k++)
    {
      iniciarArray(subMatriz);
      for(int h = 3 * (k/3); h < 3 * (k/3) + 3; h++)
        {
          for(int l = 3 * (k%3); l < 3 * (k%3) + 3; l++)
            {
              int num = n->sudo[h][l];
              if(num!=0)
              {
                if(subMatriz[num] == 1)
                {
                  return 0;
                }
                else
                {
                  subMatriz[num] = 1;
                }
              }
            }
        }
    }
  
  return 1;
}


List* get_adj_nodes(Node* n)
{
  List* list=createList();
  for (int i=0 ; i<9 ; i++)
    {
      for(int j=0 ; j<9 ; j++)
        {
          if (n->sudo[i][j]==0)
          {
            for(int k = 1; k<=9 ; k++)
              {
                Node* adj_node = copy(n);
                adj_node->sudo[i][j] = k;
                if (is_valid(adj_node)==1)
                {
                  pushBack(list, adj_node);
                }
                else
                {
                  free(adj_node);
                }
              }
            return list;
          }
        }
    }
  return list;
}


int is_final(Node* n)
{
  for(int i=0; i<9 ; i++)
    {
      for(int j=0; j<9;j++)
        {
          if(n->sudo[i][j] == 0)
            return 0;
        }
    }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack* stack = createStack();
  push(stack,initial);

  while(top(stack) != NULL)
  {
    Node* n = (Node*) top(stack);
    pop(stack);
    (*cont)++;

    if(is_final(n))
    {
      free(stack);
      return n;
    }    

    List* adj_nodes = get_adj_nodes(n);
    Node* adj_node = first(adj_nodes);

    while(adj_node != NULL)
    {
      if (is_valid(adj_node))
      {
        push(stack,adj_node);
      }
      else{
        free(adj_node);
      }
      adj_node = next(adj_nodes);
    } 
    free(n);
    free(adj_nodes);
    
  }
  free(stack);
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/