#include <iostream>
#include "SparseMat.h"
using namespace std;

#define MAT_SIZE 100000
typedef SparseMat<float> SpMat;

// --------------- main ---------------
int main()
{
   SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

   //Test get and set bounds
   if (!mat.set(-1, -1, 10))
      cout << "mat.set(-1, -1, 10) failed." << endl;

   if (!mat.set(MAT_SIZE, MAT_SIZE, 10))
      cout << "mat.set(MAT_SIZE, MAT_SIZE, 10) failed." << endl;

   try
   {
      mat.get(-1, -1);
   }
   catch (...)
   {
      cout << "mat.get(-1, -1) failed." << endl;
   }

   try
   {
      mat.get(MAT_SIZE, MAT_SIZE);
   }
   catch (...)
   {
      cout << "mat.get(MAT_SIZE, MAT_SIZE) failed." << endl;
   }


   //test gets and sets
   for (int i = 0; i < 15; i++)
      mat.set(i, i, i);

   mat.set(1, 5, 10);
   mat.set(1, 7, 42);
   mat.set(2, 1, 11);
   mat.set(4, 5, 100);
   mat.set(5, 9, 52);
   mat.set(7, 13, 18);
   mat.set(9, 3, 13);
   mat.set(13, 12, 16);
   mat.set(14, 9, 92);
   mat.set(MAT_SIZE - 1, MAT_SIZE - 1, 99);

   for (int i = 0; i < 15; i++)
      cout << "mat.get(" << i << ", " << i << "), should return " << i 
         << ":   " << mat.get(i, i) << endl;

   cout << "mat.get(2, 1), should return 11:   " << mat.get(2, 1) << endl;
   cout << "mat.get(7, 13), should return 18:   " << mat.get(7, 13) << endl;
   cout << "mat.get(13, 1), should return 0:   " << mat.get(13, 1) << endl;
   cout << "mat.get(14, 9), should return 92:   " << mat.get(14, 9) << endl;
   cout << "mat.get(1, 5), should return 10:   " << mat.get(1, 5) << endl;

   // show top left 15x15
   cout << "Top left 15x15" << endl;
   mat.showSubSquare(0, 15);

   // show bottom right 15x15
   cout << "Bottom right 15x15" << endl;
   mat.showSubSquare(MAT_SIZE - 15, 15);

   //test set overwrites and node removals
   for (int i = 0; i < 15; i++)
      mat.set(i, i, 14 - i);

   mat.set(1, 5, 0);
   mat.set(1, 7, 0);
   mat.set(2, 1, 0);
   mat.set(4, 5, 0);
   mat.set(5, 9, 0);
   mat.set(7, 13, 0);
   mat.set(9, 3, 0);
   mat.set(13, 12, 0);
   mat.set(14, 9, 0);

   cout << "Testing overwrites: All removed except reversed diagonal." << endl;

   // show top left 15x15
   cout << "Top left 15x15" << endl;
   mat.showSubSquare(0, 15);

   //test clear
   mat.clear();
   cout << "Testing clear: should be empty." << endl;

   // show top left 15x15
   cout << "Top left 15x15" << endl;
   mat.showSubSquare(0, 15);

   // show bottom right 15x15
   cout << "Bottom right 15x15" << endl;
   mat.showSubSquare(MAT_SIZE - 15, 15);
}

//RUN--------------------------------------------------------------------------
/*
mat.set(-1, -1, 10) failed.
mat.set(MAT_SIZE, MAT_SIZE, 10) failed.
mat.get(-1, -1) failed.
mat.get(MAT_SIZE, MAT_SIZE) failed.
mat.get(0, 0), should return 0:   0
mat.get(1, 1), should return 1:   1
mat.get(2, 2), should return 2:   2
mat.get(3, 3), should return 3:   3
mat.get(4, 4), should return 4:   4
mat.get(5, 5), should return 5:   5
mat.get(6, 6), should return 6:   6
mat.get(7, 7), should return 7:   7
mat.get(8, 8), should return 8:   8
mat.get(9, 9), should return 9:   9
mat.get(10, 10), should return 10:   10
mat.get(11, 11), should return 11:   11
mat.get(12, 12), should return 12:   12
mat.get(13, 13), should return 13:   13
mat.get(14, 14), should return 14:   14
mat.get(2, 1), should return 11:   11
mat.get(7, 13), should return 18:   18
mat.get(13, 1), should return 0:   0
mat.get(14, 9), should return 92:   92
mat.get(1, 5), should return 10:   10
Top left 15x15

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    1    0    0    0   10    0   42    0    0    0    0    0    0    0

0   11    2    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    3    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    4  100    0    0    0    0    0    0    0    0    0

0    0    0    0    0    5    0    0    0   52    0    0    0    0    0

0    0    0    0    0    0    6    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    7    0    0    0    0    0   18    0

0    0    0    0    0    0    0    0    8    0    0    0    0    0    0

0    0    0   13    0    0    0    0    0    9    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0   10    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0   11    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0   12    0    0

0    0    0    0    0    0    0    0    0    0    0    0   16   13    0

0    0    0    0    0    0    0    0    0   92    0    0    0    0   14

Bottom right 15x15

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0   99

Testing overwrites: All removed except reversed diagonal.
Top left 15x15

14    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0   13    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0   12    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0   11    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0   10    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    9    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    8    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    7    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    6    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    5    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    4    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    3    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    2    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    1    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

Testing clear: should be empty.
Top left 15x15

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

Bottom right 15x15

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

0    0    0    0    0    0    0    0    0    0    0    0    0    0    0

Press any key to continue . . .
*/