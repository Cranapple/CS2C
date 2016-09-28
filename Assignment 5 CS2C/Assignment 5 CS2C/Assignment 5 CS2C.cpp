//MAIN------------------------------------------------------------------

#include <iostream>
#include "FHsplayTree.h"
#include <time.h>
using namespace std;

template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << obj << " ";
   }
};

int main()
{
   srand(time(NULL));
   int k;
   FHsplayTree<int> searchTree;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);
   cout << "root: " << searchTree.showRoot()
      << " height: " << searchTree.showHeight() << endl;

   cout << endl << "INSERTIONS AND FINDS" << endl << endl;

   cout << "Initial size: " << searchTree.size() << endl;
   for (k = 1; k <= 32; k++)
      searchTree.insert(k);
   cout << "New size: " << searchTree.size() << endl;

   cout << "\nTraversal: \n";
   searchTree.traverse(intPrinter);
   cout << endl << endl;

   for (k = -1; k < 33; k++)
   {
      try
      {
         searchTree.find(k);
      }
      catch (...)
      {
         cout << " oops ";
      }
      cout << "splay " << k << " --> root: " << searchTree.showRoot()
         << " height: " << searchTree.showHeight() << endl;
   }

   cout << endl << endl << "REMOVALS AND CONTAINS" << endl << endl;

   searchTree.traverse(intPrinter);
   cout << "root: " << searchTree.showRoot()
      << " height: " << searchTree.showHeight() << endl;

   cout << "Initial size: " << searchTree.size() << endl;
   int i;
   for (k = 1; k <= 25; k++)
   {
      i = rand() % 50;
      if (searchTree.remove(i))
      {
         cout << "Removed " << i << endl;
      }
      else
      {
         cout << "Failed to remove " << i << endl;
      }
   }
   cout << "New size: " << searchTree.size() << endl;

   cout << "\nTraversal: \n";
   searchTree.traverse(intPrinter);
   cout << endl << endl;

   for (k = -1; k < 33; k++)
   {
      if (!searchTree.contains(k))
         cout << " oops ";

      cout << "splay " << k << " --> root: " << searchTree.showRoot()
         << " height: " << searchTree.showHeight() << endl;
   }

   return 0;
}

//TEST RUNS--------------------------------------------------------------
/*
root: 0 height: -1

INSERTIONS AND FINDS

Initial size: 0
New size: 32

Traversal:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
31 32

oops splay -1 --> root: 1 height: 16
oops splay 0 --> root: 1 height: 16
splay 1 --> root: 1 height: 16
splay 2 --> root: 2 height: 9
splay 3 --> root: 3 height: 6
splay 4 --> root: 4 height: 6
splay 5 --> root: 5 height: 5
splay 6 --> root: 6 height: 6
splay 7 --> root: 7 height: 6
splay 8 --> root: 8 height: 7
splay 9 --> root: 9 height: 8
splay 10 --> root: 10 height: 9
splay 11 --> root: 11 height: 10
splay 12 --> root: 12 height: 11
splay 13 --> root: 13 height: 12
splay 14 --> root: 14 height: 13
splay 15 --> root: 15 height: 14
splay 16 --> root: 16 height: 15
splay 17 --> root: 17 height: 16
splay 18 --> root: 18 height: 17
splay 19 --> root: 19 height: 18
splay 20 --> root: 20 height: 19
splay 21 --> root: 21 height: 20
splay 22 --> root: 22 height: 21
splay 23 --> root: 23 height: 22
splay 24 --> root: 24 height: 23
splay 25 --> root: 25 height: 24
splay 26 --> root: 26 height: 25
splay 27 --> root: 27 height: 26
splay 28 --> root: 28 height: 27
splay 29 --> root: 29 height: 28
splay 30 --> root: 30 height: 29
splay 31 --> root: 31 height: 30
splay 32 --> root: 32 height: 31


REMOVALS AND CONTAINS

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
31 32 root: 32 height: 31
Initial size: 32
Removed 2
Failed to remove 47
Removed 10
Removed 8
Removed 1
Removed 27
Failed to remove 48
Removed 15
Removed 9
Removed 32
Failed to remove 9
Removed 30
Failed to remove 41
Failed to remove 44
Failed to remove 2
Failed to remove 33
Removed 3
Failed to remove 1
Failed to remove 1
Failed to remove 8
Failed to remove 39
Removed 22
Failed to remove 43
Failed to remove 33
Failed to remove 46
New size: 21

Traversal:
4 5 6 7 11 12 13 14 16 17 18 19 20 21 23 24 25 26 28 29 31

oops splay -1 --> root: 4 height: 7
oops splay 0 --> root: 4 height: 7
oops splay 1 --> root: 4 height: 7
oops splay 2 --> root: 4 height: 7
oops splay 3 --> root: 4 height: 7
splay 4 --> root: 4 height: 7
splay 5 --> root: 5 height: 8
splay 6 --> root: 6 height: 9
splay 7 --> root: 7 height: 8
oops splay 8 --> root: 11 height: 7
oops splay 9 --> root: 7 height: 8
oops splay 10 --> root: 11 height: 7
splay 11 --> root: 11 height: 7
splay 12 --> root: 12 height: 8
splay 13 --> root: 13 height: 8
splay 14 --> root: 14 height: 8
oops splay 15 --> root: 16 height: 9
splay 16 --> root: 16 height: 9
splay 17 --> root: 17 height: 9
splay 18 --> root: 18 height: 10
splay 19 --> root: 19 height: 11
splay 20 --> root: 20 height: 12
splay 21 --> root: 21 height: 13
oops splay 22 --> root: 23 height: 14
splay 23 --> root: 23 height: 14
splay 24 --> root: 24 height: 15
splay 25 --> root: 25 height: 16
splay 26 --> root: 26 height: 17
oops splay 27 --> root: 28 height: 18
splay 28 --> root: 28 height: 18
splay 29 --> root: 29 height: 19
oops splay 30 --> root: 31 height: 20
splay 31 --> root: 31 height: 20
oops splay 32 --> root: 31 height: 20
Press any key to continue . . .

--------------------------------------------------------

root: 0 height: -1

INSERTIONS AND FINDS

Initial size: 0
New size: 32

Traversal:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
31 32

oops splay -1 --> root: 1 height: 16
oops splay 0 --> root: 1 height: 16
splay 1 --> root: 1 height: 16
splay 2 --> root: 2 height: 9
splay 3 --> root: 3 height: 6
splay 4 --> root: 4 height: 6
splay 5 --> root: 5 height: 5
splay 6 --> root: 6 height: 6
splay 7 --> root: 7 height: 6
splay 8 --> root: 8 height: 7
splay 9 --> root: 9 height: 8
splay 10 --> root: 10 height: 9
splay 11 --> root: 11 height: 10
splay 12 --> root: 12 height: 11
splay 13 --> root: 13 height: 12
splay 14 --> root: 14 height: 13
splay 15 --> root: 15 height: 14
splay 16 --> root: 16 height: 15
splay 17 --> root: 17 height: 16
splay 18 --> root: 18 height: 17
splay 19 --> root: 19 height: 18
splay 20 --> root: 20 height: 19
splay 21 --> root: 21 height: 20
splay 22 --> root: 22 height: 21
splay 23 --> root: 23 height: 22
splay 24 --> root: 24 height: 23
splay 25 --> root: 25 height: 24
splay 26 --> root: 26 height: 25
splay 27 --> root: 27 height: 26
splay 28 --> root: 28 height: 27
splay 29 --> root: 29 height: 28
splay 30 --> root: 30 height: 29
splay 31 --> root: 31 height: 30
splay 32 --> root: 32 height: 31


REMOVALS AND CONTAINS

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
31 32 root: 32 height: 31
Initial size: 32
Removed 19
Failed to remove 43
Failed to remove 38
Failed to remove 41
Failed to remove 45
Failed to remove 44
Removed 11
Removed 1
Removed 10
Failed to remove 11
Removed 15
Failed to remove 39
Failed to remove 45
Removed 6
Removed 12
Removed 5
Failed to remove 19
Failed to remove 45
Removed 14
Removed 4
Removed 32
Removed 21
Failed to remove 6
Failed to remove 5
Failed to remove 32
New size: 20

Traversal:
2 3 7 8 9 13 16 17 18 20 22 23 24 25 26 27 28 29 30 31

oops splay -1 --> root: 2 height: 7
oops splay 0 --> root: 2 height: 7
oops splay 1 --> root: 2 height: 7
splay 2 --> root: 2 height: 7
splay 3 --> root: 3 height: 7
oops splay 4 --> root: 7 height: 6
oops splay 5 --> root: 3 height: 7
oops splay 6 --> root: 7 height: 6
splay 7 --> root: 7 height: 6
splay 8 --> root: 8 height: 6
splay 9 --> root: 9 height: 6
oops splay 10 --> root: 13 height: 6
oops splay 11 --> root: 9 height: 7
oops splay 12 --> root: 13 height: 6
splay 13 --> root: 13 height: 6
oops splay 14 --> root: 16 height: 7
oops splay 15 --> root: 13 height: 8
splay 16 --> root: 16 height: 7
splay 17 --> root: 17 height: 7
splay 18 --> root: 18 height: 8
oops splay 19 --> root: 20 height: 9
splay 20 --> root: 20 height: 9
oops splay 21 --> root: 22 height: 10
splay 22 --> root: 22 height: 10
splay 23 --> root: 23 height: 11
splay 24 --> root: 24 height: 12
splay 25 --> root: 25 height: 13
splay 26 --> root: 26 height: 14
splay 27 --> root: 27 height: 15
splay 28 --> root: 28 height: 16
splay 29 --> root: 29 height: 17
splay 30 --> root: 30 height: 18
splay 31 --> root: 31 height: 19
oops splay 32 --> root: 31 height: 19
Press any key to continue . . .
*/