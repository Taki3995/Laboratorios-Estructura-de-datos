#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * tree = (TreeMap *)malloc(sizeof(TreeMap));
  tree->lower_than = lower_than;
  return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
  tree->current = tree->root;
  TreeNode* parent = NULL;
  
  while (tree->current != NULL) 
  {
    if (is_equal(tree,tree->current->pair->key, key) == 1) 
    {
      return;
    }

    parent = tree->current;
      
    if (tree->lower_than(key, tree->current->pair->key)) 
    {
      tree->current = tree->current->left;
    }
      
    else
    {
      tree->current = tree->current->right;
    }
  }

  TreeNode * nodo = createTreeNode(key, value);
  nodo->parent = parent;
  if (parent == NULL)
  {
    tree->root = nodo;
    tree->current = tree->root;
  }
  else if (tree->lower_than(key, parent->pair->key))
  {
    parent->left = nodo;
    tree->current = parent->left;
  }
  else
  {
    parent->right = nodo;
    tree->current = parent->right;
  }
}


TreeNode * minimum(TreeNode * x)
{
  while (x->left != NULL) 
  {
    x = x->left;
  }
  return x;
}

TreeNode* EncontrarParent(TreeMap * tree, TreeNode* node) 
{
  if(is_equal(tree, node, tree->root))
  {
    return NULL;
  }
  tree->current = tree->root;
  while (tree->current != NULL)
    {
      if(tree->lower_than(node->pair->key,tree->current->pair->key))
      {
        if(is_equal(tree, tree->current->left, node)==1)
        {
          return tree->current;
        }
          
        else
        {
          tree->current = tree->current->left;
        }
      }
      else
      {
        if(is_equal(tree, tree->current->right, node)==1)
        {
          return tree->current;
        }
        else
        {
          tree->current = tree->current->right;
        }
      }
    }
  return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
  if (node == NULL)
  {
    return;
  }

  if(node->left == NULL && node->right == NULL)
  {
    if (is_equal(tree, node->pair->key, tree->root->pair->key)==1)
    {
      tree->root = NULL;
    }
    else
    {
      TreeNode* parent = EncontrarParent(tree, node);
      if(parent->left != NULL && is_equal(tree, parent->left->pair->key, node->pair->key)==1)
      {
        parent->left = NULL;
      }
      else
      {
        parent->right = NULL;
      }
    }
    free(node);
    return;
  }

  if (node->left == NULL || node->right == NULL)
  {
    TreeNode * hijo;
    if (node->left != NULL)
    {
      hijo = node->left;
    }
    else
    {
      hijo = node->right;
    }

    if (is_equal(tree, node->pair->key, tree->root->pair->key) == 1)
    {
      tree->root = hijo;
    }
    else
    {
      TreeNode * parent = EncontrarParent(tree, node);
      if (parent->left != NULL && is_equal(tree, parent->left->pair->key, node->pair->key)==1)
      {
        parent->left = hijo;
      }
      else
      {
        parent->right = hijo;
      }
    }
    free(node);
    return;
  }

  TreeNode * minNode = minimum(node->right);
  node->pair->key = minNode->pair->key;
  node->pair->value = minNode->pair->value;
  removeNode(tree,minNode);
  
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode* current = tree->root;
  while (current != NULL) 
  {
    if (is_equal(tree, current->pair->key, key) == 1) 
    {
      tree->current = current;
      return current->pair;
    }
    else if (tree->lower_than(key, current->pair->key)) 
    {
      current = current->left;
    }

    else 
    {
      current = current->right;
    }
  }
  
  tree->current = current;
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) 
{
  
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
  TreeNode *nodo = tree->root;
  while (nodo != NULL && nodo->left != NULL)
  {
    nodo = nodo->left;
  }

  if (nodo == NULL)
  {
    return NULL;
  }
  else
  {
    Pair *pair = (Pair *)malloc(sizeof(Pair));
    pair->key = nodo->pair->key;
    pair->value = nodo->pair->value;
    return pair;
  }
}

Pair * nextTreeMap(TreeMap * tree) 
{
  TreeNode *nodo = tree->current;
  
  if (nodo == NULL)
  {
    return NULL;
  }

  if(nodo->right != NULL)
  {
    nodo = nodo->right;
    while(nodo->left != NULL)
      {
        nodo = nodo->left;
      }
    Pair *pair = (Pair *)malloc(sizeof(Pair));
    pair->key = nodo->pair->key;
    pair->value = nodo->pair->value;
    return pair;
  }

  else
  {
    while (nodo->parent != NULL && is_equal(tree, nodo->parent->right, nodo))
      {
        nodo = nodo->parent;
      }
    if(nodo->parent == NULL)
    {
      return NULL;
    }
    else
    {
      nodo = nodo->parent->right;
      while(nodo->left != NULL)
        {
          nodo=nodo->left;
        }
      Pair *pair = (Pair *)malloc(sizeof(Pair));
      pair->key = nodo->pair->key;
      pair->value = nodo->pair->value;
      return pair;
    }
  }
}
