//MAIN --------------------------------------------------------

#include <iostream>
#include <string>
#include <stack>
#include <time.h>
#include "FHlazySearchTree.h"
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
   FHlazySearchTree<int> searchTree;
   FHlazySearchTree<int> searchTree2;
   PrintObject<int> intPrinter;

   searchTree.traverse(intPrinter);

   cout << endl << endl << "Testing empty tree" << endl << endl;
   cout << "Testing findMin: ";
   try{ searchTree.findMin(); } 
   catch (FHlazySearchTree<int>::EmptyTreeException e) 
   { cout << "error" << endl; }
   cout << "Testing findMax: ";
   try{ searchTree.findMax(); }
   catch (FHlazySearchTree<int>::EmptyTreeException e) 
   { cout << "error" << endl; }
   cout << "Testing find: ";
   try{ searchTree.find(1); }
   catch (FHlazySearchTree<int>::NotFoundException e) 
   { cout << "error" << endl; }
   cout << "Testing remove (false = 0): " << searchTree.remove(1) << endl;
   cout << "Testing collectGarbage" << endl;
   searchTree.collectGarbage();

   searchTree.traverse(intPrinter);
   cout << "tree size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << endl << endl << "Testing populated tree" << endl << endl;
   cout << "Testing insertions" << endl;
   for (int i = 0; i < 20; i++)
   {
      int temp = (int)(rand() % 50);
      cout << "Inserting " << temp << endl;
      searchTree.insert(temp);
   }

   searchTree.traverse(intPrinter);
   cout << "tree size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Testing findMin: " << searchTree.findMin() << endl;
   cout << "Testing findMax: " << searchTree.findMax() << endl;
   cout << "Testing finds" << endl;
   for (int i = 0; i < 20; i++)
   {
      int temp = (int)(rand() % 50);
      try
      { 
         int found = searchTree.find(temp); 
         cout << found << " found" << endl;
      }
      catch (FHlazySearchTree<int>::NotFoundException e) 
      { 
         cout << temp << " not found" << endl; 
      }
   }
   cout << "Testing collectGarbage" << endl;
   searchTree.collectGarbage();

   searchTree.traverse(intPrinter);
   cout << "tree size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << endl << endl << "Testing semi-populated tree" << endl << endl;
   cout << "Testing removals" << endl;
   for (int i = 0; i < 20; i++)
   {
      int temp = (int)(rand() % 50);
      if (searchTree.remove(temp))
         cout << temp << " removed" << endl;
      else
         cout << temp << " not removed" << endl;
   }

   searchTree.traverse(intPrinter);
   cout << "tree size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Testing findMin: " << searchTree.findMin() << endl;
   cout << "Testing findMax: " << searchTree.findMax() << endl;
   cout << "Testing finds" << endl;
   for (int i = 0; i < 20; i++)
   {
      int temp = (int)(rand() % 50);
      try
      {
         int found = searchTree.find(temp);
         cout << found << " found" << endl;
      }
      catch (FHlazySearchTree<int>::NotFoundException e)
      {
         cout << temp << " not found" << endl;
      }
   }
   cout << "Testing = operator" << endl;
   searchTree2 = searchTree;

   cout << endl << endl << "Testing fully-removed tree" << endl << endl;
   cout << "Testing removals" << endl;
   for (int i = 0; i < 50; i++)
   {
      if (searchTree.remove(i))
         cout << i << " removed" << endl;
      else
         cout << i << " not removed" << endl;
   }

   searchTree.traverse(intPrinter);
   cout << "tree size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << "Testing findMin: ";
   try{ searchTree.findMin(); }
   catch (FHlazySearchTree<int>::EmptyTreeException e) 
   { cout << "error" << endl; }
   cout << "Testing findMax: ";
   try{ searchTree.findMax(); }
   catch (FHlazySearchTree<int>::EmptyTreeException e) 
   { cout << "error" << endl; }
   cout << "Testing find: ";
   try{ searchTree.find(1); }
   catch (FHlazySearchTree<int>::NotFoundException e) 
   { cout << "error" << endl; }
   cout << "Testing remove (false = 0): " << searchTree.remove(1) << endl;
   cout << "Testing collectGarbage" << endl;
   searchTree.collectGarbage();
   searchTree.traverse(intPrinter);
   cout << "tree size: " << searchTree.size()
      << "  Hard size: " << searchTree.sizeHard() << endl;

   cout << endl << endl << "Testing semi-populated tree (copy from previous)" 
      << endl << endl;
   
   searchTree2.traverse(intPrinter);
   cout << "tree size: " << searchTree2.size()
      << "  Hard size: " << searchTree2.sizeHard() << endl;
   
   cout << "Testing insertions for non dulplicates" << endl;
   for (int i = 0; i < 50; i++)
   {
      searchTree2.insert(i);
      cout << "inserting " << i << endl;
   }

   searchTree2.traverse(intPrinter);
   cout << "tree size: " << searchTree2.size()
      << "  Hard size: " << searchTree2.sizeHard() << endl;

   cout << "Testing clear" << endl;
   searchTree2.clear();

   searchTree2.traverse(intPrinter);
   cout << "tree size: " << searchTree2.size()
      << "  Hard size: " << searchTree2.sizeHard() << endl;

   return 0;
}

//TEST RUNS ----------------------------------------------------------
/*



Testing empty tree

Testing findMin: error
Testing findMax: error
Testing find: error
Testing remove (false = 0): 0
Testing collectGarbage
tree size: 0  Hard size: 0


Testing populated tree

Testing insertions
Inserting 42
Inserting 41
Inserting 46
Inserting 7
Inserting 9
Inserting 14
Inserting 28
Inserting 23
Inserting 45
Inserting 24
Inserting 8
Inserting 12
Inserting 28
Inserting 34
Inserting 38
Inserting 13
Inserting 19
Inserting 24
Inserting 4
Inserting 48
4 7 8 9 12 13 14 19 23 24 28 34 38 41 42 45 46 48 tree size: 18  Hard size: 18
Testing findMin: 4
Testing findMax: 48
Testing finds
38 found
13 found
31 not found
4 found
27 not found
28 found
6 not found
10 not found
24 found
4 found
43 not found
25 not found
43 not found
40 not found
46 found
33 not found
27 not found
24 found
48 found
8 found
Testing collectGarbage
4 7 8 9 12 13 14 19 23 24 28 34 38 41 42 45 46 48 tree size: 18  Hard size: 18


Testing semi-populated tree

Testing removals
10 not removed
32 not removed
13 removed
13 not removed
31 not removed
35 not removed
42 removed
3 not removed
20 not removed
47 not removed
43 not removed
14 removed
29 not removed
14 not removed
20 not removed
5 not removed
29 not removed
9 removed
22 not removed
37 not removed
4 7 8 12 19 23 24 28 34 38 41 45 46 48 tree size: 14  Hard size: 18
Testing findMin: 4
Testing findMax: 48
Testing finds
47 not found
35 not found
16 not found
31 not found
16 not found
41 found
30 not found
18 not found
21 not found
49 not found
18 not found
11 not found
21 not found
44 not found
8 found
19 found
45 found
35 not found
47 not found
12 found
Testing = operator


Testing fully-removed tree

Testing removals
0 not removed
1 not removed
2 not removed
3 not removed
4 removed
5 not removed
6 not removed
7 removed
8 removed
9 not removed
10 not removed
11 not removed
12 removed
13 not removed
14 not removed
15 not removed
16 not removed
17 not removed
18 not removed
19 removed
20 not removed
21 not removed
22 not removed
23 removed
24 removed
25 not removed
26 not removed
27 not removed
28 removed
29 not removed
30 not removed
31 not removed
32 not removed
33 not removed
34 removed
35 not removed
36 not removed
37 not removed
38 removed
39 not removed
40 not removed
41 removed
42 not removed
43 not removed
44 not removed
45 removed
46 removed
47 not removed
48 removed
49 not removed
tree size: 0  Hard size: 18
Testing findMin: error
Testing findMax: error
Testing find: error
Testing remove (false = 0): 0
Testing collectGarbage
tree size: 0  Hard size: 0


Testing semi-populated tree (copy from previous)

4 7 8 12 19 23 24 28 34 38 41 45 46 48 tree size: 14  Hard size: 18
Testing insertions for non dulplicates
inserting 0
inserting 1
inserting 2
inserting 3
inserting 4
inserting 5
inserting 6
inserting 7
inserting 8
inserting 9
inserting 10
inserting 11
inserting 12
inserting 13
inserting 14
inserting 15
inserting 16
inserting 17
inserting 18
inserting 19
inserting 20
inserting 21
inserting 22
inserting 23
inserting 24
inserting 25
inserting 26
inserting 27
inserting 28
inserting 29
inserting 30
inserting 31
inserting 32
inserting 33
inserting 34
inserting 35
inserting 36
inserting 37
inserting 38
inserting 39
inserting 40
inserting 41
inserting 42
inserting 43
inserting 44
inserting 45
inserting 46
inserting 47
inserting 48
inserting 49
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 tree size: 50  Hard
size: 50
Testing clear
tree size: 0  Hard size: 0
Press any key to continue . . .

---------------------------------------------------------------------



Testing empty tree

Testing findMin: error
Testing findMax: error
Testing find: error
Testing remove (false = 0): 0
Testing collectGarbage
tree size: 0  Hard size: 0


Testing populated tree

Testing insertions
Inserting 42
Inserting 47
Inserting 47
Inserting 8
Inserting 10
Inserting 3
Inserting 28
Inserting 40
Inserting 14
Inserting 25
Inserting 4
Inserting 38
Inserting 8
Inserting 1
Inserting 1
Inserting 33
Inserting 13
Inserting 16
Inserting 13
Inserting 39
1 3 4 8 10 13 14 16 25 28 33 38 39 40 42 47 tree size: 16  Hard size: 16
Testing findMin: 1
Testing findMax: 47
Testing finds
14 found
41 not found
35 not found
46 not found
36 not found
12 not found
9 not found
10 found
49 not found
45 not found
14 found
43 not found
29 not found
3 found
30 not found
47 found
38 found
17 not found
7 not found
35 not found
Testing collectGarbage
1 3 4 8 10 13 14 16 25 28 33 38 39 40 42 47 tree size: 16  Hard size: 16


Testing semi-populated tree

Testing removals
29 not removed
4 removed
14 removed
45 not removed
4 not removed
5 not removed
28 removed
45 not removed
20 not removed
43 not removed
32 not removed
11 not removed
7 not removed
49 not removed
33 removed
30 not removed
24 not removed
7 not removed
45 not removed
32 not removed
1 3 8 10 13 16 25 38 39 40 42 47 tree size: 12  Hard size: 16
Testing findMin: 1
Testing findMax: 47
Testing finds
31 not found
46 not found
41 not found
41 not found
15 not found
27 not found
7 not found
47 found
23 not found
46 not found
22 not found
22 not found
5 not found
28 not found
20 not found
4 not found
8 found
25 found
24 not found
0 not found
Testing = operator


Testing fully-removed tree

Testing removals
0 not removed
1 removed
2 not removed
3 removed
4 not removed
5 not removed
6 not removed
7 not removed
8 removed
9 not removed
10 removed
11 not removed
12 not removed
13 removed
14 not removed
15 not removed
16 removed
17 not removed
18 not removed
19 not removed
20 not removed
21 not removed
22 not removed
23 not removed
24 not removed
25 removed
26 not removed
27 not removed
28 not removed
29 not removed
30 not removed
31 not removed
32 not removed
33 not removed
34 not removed
35 not removed
36 not removed
37 not removed
38 removed
39 removed
40 removed
41 not removed
42 removed
43 not removed
44 not removed
45 not removed
46 not removed
47 removed
48 not removed
49 not removed
tree size: 0  Hard size: 16
Testing findMin: error
Testing findMax: error
Testing find: error
Testing remove (false = 0): 0
Testing collectGarbage
tree size: 0  Hard size: 0


Testing semi-populated tree (copy from previous)

1 3 8 10 13 16 25 38 39 40 42 47 tree size: 12  Hard size: 16
Testing insertions for non dulplicates
inserting 0
inserting 1
inserting 2
inserting 3
inserting 4
inserting 5
inserting 6
inserting 7
inserting 8
inserting 9
inserting 10
inserting 11
inserting 12
inserting 13
inserting 14
inserting 15
inserting 16
inserting 17
inserting 18
inserting 19
inserting 20
inserting 21
inserting 22
inserting 23
inserting 24
inserting 25
inserting 26
inserting 27
inserting 28
inserting 29
inserting 30
inserting 31
inserting 32
inserting 33
inserting 34
inserting 35
inserting 36
inserting 37
inserting 38
inserting 39
inserting 40
inserting 41
inserting 42
inserting 43
inserting 44
inserting 45
inserting 46
inserting 47
inserting 48
inserting 49
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 tree size: 50  Hard
size: 50
Testing clear
tree size: 0  Hard size: 0
Press any key to continue . . .

--------------------------------------------------------------------



Testing empty tree

Testing findMin: error
Testing findMax: error
Testing find: error
Testing remove (false = 0): 0
Testing collectGarbage
tree size: 0  Hard size: 0


Testing populated tree

Testing insertions
Inserting 8
Inserting 7
Inserting 33
Inserting 4
Inserting 43
Inserting 34
Inserting 41
Inserting 31
Inserting 16
Inserting 18
Inserting 46
Inserting 19
Inserting 34
Inserting 48
Inserting 11
Inserting 47
Inserting 35
Inserting 23
Inserting 9
Inserting 13
4 7 8 9 11 13 16 18 19 23 31 33 34 35 41 43 46 47 48 tree size: 19  Hard size: 1
9
Testing findMin: 4
Testing findMax: 48
Testing finds
48 found
47 found
19 found
16 found
33 found
11 found
46 found
43 found
0 not found
30 not found
47 found
44 not found
37 not found
15 not found
34 found
8 found
35 found
29 not found
33 found
18 found
Testing collectGarbage
4 7 8 9 11 13 16 18 19 23 31 33 34 35 41 43 46 47 48 tree size: 19  Hard size: 1
9


Testing semi-populated tree

Testing removals
10 not removed
28 not removed
24 not removed
7 removed
25 not removed
32 not removed
33 removed
46 removed
24 not removed
42 not removed
49 not removed
30 not removed
39 not removed
14 not removed
17 not removed
13 removed
4 removed
3 not removed
33 not removed
3 not removed
8 9 11 16 18 19 23 31 34 35 41 43 47 48 tree size: 14  Hard size: 19
Testing findMin: 8
Testing findMax: 48
Testing finds
10 not found
47 found
34 found
36 not found
20 not found
34 found
1 not found
35 found
34 found
0 not found
5 not found
27 not found
19 found
0 not found
46 not found
14 not found
46 not found
34 found
22 not found
43 found
Testing = operator


Testing fully-removed tree

Testing removals
0 not removed
1 not removed
2 not removed
3 not removed
4 not removed
5 not removed
6 not removed
7 not removed
8 removed
9 removed
10 not removed
11 removed
12 not removed
13 not removed
14 not removed
15 not removed
16 removed
17 not removed
18 removed
19 removed
20 not removed
21 not removed
22 not removed
23 removed
24 not removed
25 not removed
26 not removed
27 not removed
28 not removed
29 not removed
30 not removed
31 removed
32 not removed
33 not removed
34 removed
35 removed
36 not removed
37 not removed
38 not removed
39 not removed
40 not removed
41 removed
42 not removed
43 removed
44 not removed
45 not removed
46 not removed
47 removed
48 removed
49 not removed
tree size: 0  Hard size: 19
Testing findMin: error
Testing findMax: error
Testing find: error
Testing remove (false = 0): 0
Testing collectGarbage
tree size: 0  Hard size: 0


Testing semi-populated tree (copy from previous)

8 9 11 16 18 19 23 31 34 35 41 43 47 48 tree size: 14  Hard size: 19
Testing insertions for non dulplicates
inserting 0
inserting 1
inserting 2
inserting 3
inserting 4
inserting 5
inserting 6
inserting 7
inserting 8
inserting 9
inserting 10
inserting 11
inserting 12
inserting 13
inserting 14
inserting 15
inserting 16
inserting 17
inserting 18
inserting 19
inserting 20
inserting 21
inserting 22
inserting 23
inserting 24
inserting 25
inserting 26
inserting 27
inserting 28
inserting 29
inserting 30
inserting 31
inserting 32
inserting 33
inserting 34
inserting 35
inserting 36
inserting 37
inserting 38
inserting 39
inserting 40
inserting 41
inserting 42
inserting 43
inserting 44
inserting 45
inserting 46
inserting 47
inserting 48
inserting 49
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 tree size: 50  Hard
size: 50
Testing clear
tree size: 0  Hard size: 0
Press any key to continue . . .

--------------------------------------------------------------------



Testing empty tree

Testing findMin: error
Testing findMax: error
Testing find: error
Testing remove (false = 0): 0
Testing collectGarbage
tree size: 0  Hard size: 0


Testing populated tree

Testing insertions
Inserting 16
Inserting 21
Inserting 8
Inserting 10
Inserting 48
Inserting 29
Inserting 29
Inserting 26
Inserting 45
Inserting 25
Inserting 34
Inserting 12
Inserting 18
Inserting 20
Inserting 4
Inserting 21
Inserting 39
Inserting 47
Inserting 44
Inserting 23
4 8 10 12 16 18 20 21 23 25 26 29 34 39 44 45 47 48 tree size: 18  Hard size: 18

Testing findMin: 4
Testing findMax: 48
Testing finds
19 not found
42 not found
42 not found
6 not found
43 not found
12 found
2 not found
44 found
15 not found
46 not found
46 not found
39 found
20 found
6 not found
45 found
37 not found
20 found
15 not found
19 not found
15 not found
Testing collectGarbage
4 8 10 12 16 18 20 21 23 25 26 29 34 39 44 45 47 48 tree size: 18  Hard size: 18



Testing semi-populated tree

Testing removals
32 not removed
37 not removed
3 not removed
25 removed
44 removed
32 not removed
29 removed
29 not removed
15 not removed
37 not removed
48 removed
20 removed
41 not removed
43 not removed
35 not removed
44 not removed
44 not removed
49 not removed
43 not removed
29 not removed
4 8 10 12 16 18 21 23 26 34 39 45 47 tree size: 13  Hard size: 18
Testing findMin: 4
Testing findMax: 47
Testing finds
37 not found
32 not found
35 not found
33 not found
35 not found
5 not found
4 found
15 not found
49 not found
35 not found
40 not found
18 found
37 not found
21 found
0 not found
7 not found
2 not found
10 found
25 not found
31 not found
Testing = operator


Testing fully-removed tree

Testing removals
0 not removed
1 not removed
2 not removed
3 not removed
4 removed
5 not removed
6 not removed
7 not removed
8 removed
9 not removed
10 removed
11 not removed
12 removed
13 not removed
14 not removed
15 not removed
16 removed
17 not removed
18 removed
19 not removed
20 not removed
21 removed
22 not removed
23 removed
24 not removed
25 not removed
26 removed
27 not removed
28 not removed
29 not removed
30 not removed
31 not removed
32 not removed
33 not removed
34 removed
35 not removed
36 not removed
37 not removed
38 not removed
39 removed
40 not removed
41 not removed
42 not removed
43 not removed
44 not removed
45 removed
46 not removed
47 removed
48 not removed
49 not removed
tree size: 0  Hard size: 18
Testing findMin: error
Testing findMax: error
Testing find: error
Testing remove (false = 0): 0
Testing collectGarbage
tree size: 0  Hard size: 0


Testing semi-populated tree (copy from previous)

4 8 10 12 16 18 21 23 26 34 39 45 47 tree size: 13  Hard size: 18
Testing insertions for non dulplicates
inserting 0
inserting 1
inserting 2
inserting 3
inserting 4
inserting 5
inserting 6
inserting 7
inserting 8
inserting 9
inserting 10
inserting 11
inserting 12
inserting 13
inserting 14
inserting 15
inserting 16
inserting 17
inserting 18
inserting 19
inserting 20
inserting 21
inserting 22
inserting 23
inserting 24
inserting 25
inserting 26
inserting 27
inserting 28
inserting 29
inserting 30
inserting 31
inserting 32
inserting 33
inserting 34
inserting 35
inserting 36
inserting 37
inserting 38
inserting 39
inserting 40
inserting 41
inserting 42
inserting 43
inserting 44
inserting 45
inserting 46
inserting 47
inserting 48
inserting 49
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 tree size: 50  Hard
size: 50
Testing clear
tree size: 0  Hard size: 0
Press any key to continue . . .
*/