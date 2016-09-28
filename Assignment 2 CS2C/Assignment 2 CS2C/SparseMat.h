#ifndef SPARSEMAT
#define SPARSEMAT

#include "FHlist.h"
#include "FHvector.h"
#include "MatNode.h"
#include <iomanip>
#include <iostream>
using namespace std;

template <class Object>
class SparseMat
{
protected:
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;

public:
   SparseMat(int r, int c, const Object & defaultVal);
   const Object & get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear();
   void showSubSquare(int start, int size);

   class OutOfBoundsException { };
};

template <class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & defaultVal)
{

   if (r > 1)
   {
      rows = MasterCol(r);
      rowSize = r;
   }
   else
   {
      rows = MasterCol(1);
      rowSize = 1;
   }

   colSize = (c > 1)? c : 1;
   this->defaultVal = defaultVal;

}

template <class Object>
const Object & SparseMat<Object>::get(int r, int c) const
{
   if (r < 0 || r >= rowSize || c < 0 || c >= colSize)
      throw OutOfBoundsException();

   const MatRow &row = rows[r];

   MatRow::const_iterator iter;
   MatRow::const_iterator endIter = row.end();
   for (iter = row.begin(); iter != endIter && (*iter).getCol() <= c; iter++)
   {
      if ((*iter).getCol() == c)
      {
         return (*iter).data;
      }
   }

   return defaultVal;
}

template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
   if (r < 0 || r >= rowSize || c < 0 || c >= colSize)
      return false;

   MatRow &row = rows[r];
   MatRow::iterator iter;
   MatRow::iterator endIter = row.end();

   for (iter = row.begin(); iter != endIter && (*iter).getCol() <= c; iter++)
   {
      if ((*iter).getCol() == c)
      {
         if (x == defaultVal)
            row.erase(iter);
         else
            *iter = x;

         return true;
      }
   }

   if (x != defaultVal)
   {
      MatNode<Object> newNode(c, x);
      row.insert(iter, newNode);
   }

   return true;

}

template <class Object>
void SparseMat<Object>::clear()
{
   for (int i = 0; i < rowSize; i++)
      rows[i].clear();
}

template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
   int total = start + size;

   if (start < 0 || size < 1 
      || total > rowSize || total > colSize)
   {
      cout << "Cannot show sub-square: Input out of bounds." << endl;
      return;
   }

   cout << '\n';

   MasterCol::const_iterator rowIter = rows.begin();
   MasterCol::const_iterator rowEndIter;
   for (int i = 0; i < start; i++)
      rowIter++;

   rowEndIter = rowIter;
   for (int i = 0; i < size; i++)
      rowEndIter++;

   MatRow::const_iterator colIter;
   MatRow::const_iterator colEndIter;
   int numColsOutput;

   for (; rowIter != rowEndIter; rowIter++)
   {
      numColsOutput = start;
      colEndIter = (*rowIter).end();
      colIter = (*rowIter).begin();
      for (; colIter != colEndIter && (*colIter).getCol() < total; 
          colIter++)
      {
         if ((*colIter).getCol() >= numColsOutput)
         {
            int endCol = (*colIter).getCol();
            for (; numColsOutput < endCol; numColsOutput++)
            {
               cout << setw(5) << defaultVal;
            }
            cout << setw(5) << (*colIter).data;
            numColsOutput++;
         }
      }

      for (; numColsOutput < total; numColsOutput++)
      {
         cout << setw(5) << defaultVal;
      }
      cout << '\n' << '\n';
   }
}

#endif