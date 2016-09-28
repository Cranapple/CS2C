//FHSPLAYTREE------------------------------------------------------------------

#ifndef FHSPLAYTREE_H
#define FHSPLAYTREE_H
#include "FHsearch_tree.h"

template <class Comparable>
class FHsplayTree : public FHsearch_tree < Comparable >
{
public:
   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x);
   const Comparable & find(const Comparable &x);
   const Comparable &showRoot() { return (this->mRoot == NULL) ? 
      Comparable() : this->mRoot->data; }
protected:
   void splay(FHs_treeNode<Comparable> * & root, const Comparable & x);
   void rotateWithLeftChild(FHs_treeNode<Comparable> * & k2);
   void rotateWithRightChild(FHs_treeNode<Comparable> * & k2);
};

template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable &x)
{
   if (this->mRoot == NULL)
   {
      this->mRoot = new FHs_treeNode<Comparable>(x, NULL, NULL);
      this->mSize++;
      return true;
   }

   splay(this->mRoot, x);

   if (x < this->mRoot->data)
   {
      this->mRoot = new FHs_treeNode<Comparable>(
         x, this->mRoot->lftChild, this->mRoot);
      this->mSize++;
      return true;
   }
   else if (this->mRoot->data < x)
   {
      this->mRoot = new FHs_treeNode<Comparable>(
         x, this->mRoot, this->mRoot->rtChild);
      this->mSize++;
      return true;
   }

   return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable &x)
{
   if (this->mRoot == NULL)
      return false;

   splay(this->mRoot, x);

   if (this->mRoot->data < x || x < this->mRoot->data)
      return false;

   FHs_treeNode<Comparable> *newRoot;
   if (this->mRoot->lftChild == NULL)
      newRoot = this->mRoot->rtChild;
   else
   {
      newRoot = this->mRoot->lftChild;
      splay(newRoot, x);
      newRoot->rtChild = this->mRoot->rtChild;
   }
   
   delete this->mRoot;
   this->mRoot = newRoot;
   this->mSize--;
   return true;
}

template <class Comparable>
const Comparable & FHsplayTree<Comparable>::find(const Comparable &x)
{
   if (this->mRoot == NULL)
      throw typename FHsearch_tree<Comparable>::EmptyTreeException();

   splay(this->mRoot, x);

   if (!(this->mRoot->data < x || x < this->mRoot->data))
      return this->mRoot->data;
   else
      throw typename FHsearch_tree<Comparable>::NotFoundException();
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable &x)
{
   try
   {
      find(x);
   }
   catch (typename FHsearch_tree<Comparable>::NotFoundException e)
   {
      return false;
   }
   catch (typename FHsearch_tree<Comparable>::EmptyTreeException e)
   {
      return false;
   }

   return true;
}

template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root, 
   const Comparable & x)
{
   FHs_treeNode<Comparable> *rightTree = NULL, *leftTree = NULL, 
      *rightTreeMin = NULL, *leftTreeMax = NULL;

   while (root != NULL)
   {
      if (x < root->data)
      {
         if (root->lftChild == NULL)
            break;
         
         if (x < root->lftChild->data)
         {
            rotateWithLeftChild(root);
            if (root->lftChild == NULL)
               break;
         }

         if (rightTreeMin == NULL)
         {
            rightTree = root;
            rightTreeMin = root;
         }
         else
         {
            rightTreeMin->lftChild = root;
            rightTreeMin = root;
         }
         
         root = root->lftChild;
      }
      else if (root->data < x)
      {
         if (root->rtChild == NULL)
            break;

         if (root->rtChild->data < x)
         {
            rotateWithRightChild(root);
            if (root->rtChild == NULL)
               break;
         }

         if (leftTreeMax == NULL)
         {
            leftTree = root;
            leftTreeMax = root;
         }
         else
         {
            leftTreeMax->rtChild = root;
            leftTreeMax = root;
         }
         
         root = root->rtChild;
      }
      else
      {
         break;
      }
   }

   if (leftTree != NULL)
   {
      leftTreeMax->rtChild = root->lftChild;
      root->lftChild = leftTree;
   }
   if (rightTree != NULL)
   {
      rightTreeMin->lftChild = root->rtChild;
      root->rtChild = rightTree;
   }
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(
   FHs_treeNode<Comparable> * & k2)
{
   FHs_treeNode<Comparable> *k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(
   FHs_treeNode<Comparable> * & k2)
{
   FHs_treeNode<Comparable> *k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->lftChild = k2;
   k2 = k1;
}

#endif