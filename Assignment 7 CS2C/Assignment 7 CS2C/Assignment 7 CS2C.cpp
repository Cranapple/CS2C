#include "FHvector.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

template <typename Comparable>
void shellSort1(FHvector<Comparable> & a)
{
   int k, pos, arraySize, gap;
   Comparable tmp;

   arraySize = a.size();
   for (gap = arraySize / 2; gap > 0; gap /= 2)
      for (pos = gap; pos < arraySize; pos++)
      {
         tmp = a[pos];
         for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, int array[], int arraySize)
{
   int k, gapPos, pos, sortArraySize, gap;
   Comparable tmp;

   sortArraySize = a.size();
   gapPos = arraySize - 1;
   while (array[gapPos] >= sortArraySize)
      gapPos--;

   for (gap = array[gapPos]; gapPos >= 0; --gapPos, gap = array[gapPos])
      for (pos = gap; pos < sortArraySize; pos++)
      {
         tmp = a[pos];
         for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)
            a[k] = a[k - gap];
         a[k] = tmp;
      }
}

int main()
{
   srand(time(NULL));

   FHvector<int> fhVectorOfInts1;
   FHvector<int> fhVectorOfInts2;
   FHvector<int> fhVectorOfInts3;
   FHvector<int> fhVectorOfInts4;
   FHvector<int> fhVectorOfInts5;
   FHvector<int> fhVectorOfInts6;
   
   const int vector1Size = 10000;
   const int vector2Size = 45000;
   const int vector3Size = 91524;
   const int vector4Size = 122000;
   const int vector5Size = 170402;
   const int vector6Size = 200000;

   fhVectorOfInts1.resize(vector1Size);
   fhVectorOfInts2.resize(vector2Size);
   fhVectorOfInts3.resize(vector3Size);
   fhVectorOfInts4.resize(vector4Size);
   fhVectorOfInts5.resize(vector5Size);
   fhVectorOfInts6.resize(vector6Size);

   for (int i = 0; i < vector1Size; i++)
      fhVectorOfInts1[i] = rand();
   for (int i = 0; i < vector2Size; i++)
      fhVectorOfInts2[i] = rand();
   for (int i = 0; i < vector3Size; i++)
      fhVectorOfInts3[i] = rand();
   for (int i = 0; i < vector4Size; i++)
      fhVectorOfInts4[i] = rand();
   for (int i = 0; i < vector5Size; i++)
      fhVectorOfInts5[i] = rand();
   for (int i = 0; i < vector6Size; i++)
      fhVectorOfInts6[i] = rand();

   FHvector<int> impShellVect1(fhVectorOfInts1);
   FHvector<int> impShellVect2(fhVectorOfInts2);
   FHvector<int> impShellVect3(fhVectorOfInts3);
   FHvector<int> impShellVect4(fhVectorOfInts4);
   FHvector<int> impShellVect5(fhVectorOfInts5);
   FHvector<int> impShellVect6(fhVectorOfInts6);
   FHvector<int> expShellVect1(fhVectorOfInts1);
   FHvector<int> expShellVect2(fhVectorOfInts2);
   FHvector<int> expShellVect3(fhVectorOfInts3);
   FHvector<int> expShellVect4(fhVectorOfInts4);
   FHvector<int> expShellVect5(fhVectorOfInts5);
   FHvector<int> expShellVect6(fhVectorOfInts6);
   FHvector<int> sedgeVect1(fhVectorOfInts1);
   FHvector<int> sedgeVect2(fhVectorOfInts2);
   FHvector<int> sedgeVect3(fhVectorOfInts3);
   FHvector<int> sedgeVect4(fhVectorOfInts4);
   FHvector<int> sedgeVect5(fhVectorOfInts5);
   FHvector<int> sedgeVect6(fhVectorOfInts6);
   FHvector<int> otherVect1(fhVectorOfInts1);
   FHvector<int> otherVect2(fhVectorOfInts2);
   FHvector<int> otherVect3(fhVectorOfInts3);
   FHvector<int> otherVect4(fhVectorOfInts4);
   FHvector<int> otherVect5(fhVectorOfInts5);
   FHvector<int> otherVect6(fhVectorOfInts6);

   const int shellGapSize = 21;
   const int sedgeGapSize = 25;
   const int otherGapSize = 25;

   int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576 };
   int sedgewickArray[sedgeGapSize];
   int otherArray[otherGapSize];

   for (int i = 0, a = 0, b = 2; i < sedgeGapSize; i++)
   {
      int tempA = 9 * (pow(4.0, a) - pow(2.0, a)) + 1;
      int tempB = pow(4.0, b) - 3 * pow(2.0, b) + 1;
      if (tempA < tempB)
      {
         sedgewickArray[i] = tempA;
         a++;
      }
      else
      {
         sedgewickArray[i] = tempB;
         b++;
      }
   }

   cout << "Sedgewick gap array" << endl;
   for (int i = 0; i < sedgeGapSize; i++)
      cout << sedgewickArray[i] << ", ";
   cout << endl << endl;

   otherArray[0] = 1;
   for (int i = 1; i < otherGapSize; i++)
   {
      otherArray[i] = (pow(9.0, i + 1) - pow(4.0, i + 1)) 
         / (5 * pow(4.0, i)) + 1;
   }

   cout << "Tokuda gap array" << endl;
   for (int i = 0; i < otherGapSize; i++)
      cout << otherArray[i] << ", ";
   cout << endl << endl;

   clock_t startTime, stopTime;
   double IST1, IST2, IST3, IST4, IST5, IST6,
      EST1, EST2, EST3, EST4, EST5, EST6,
      ST1, ST2, ST3, ST4, ST5, ST6,
      OT1, OT2, OT3, OT4, OT5, OT6;

   startTime = clock();
   shellSort1(impShellVect1);
   stopTime = clock();
   IST1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(impShellVect2);
   stopTime = clock();
   IST2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(impShellVect3);
   stopTime = clock();
   IST3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(impShellVect4);
   stopTime = clock();
   IST4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(impShellVect5);
   stopTime = clock();
   IST5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSort1(impShellVect6);
   stopTime = clock();
   IST6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   //---------------------------------------------------------------------------

   startTime = clock();
   shellSortX(expShellVect1, gapArray, shellGapSize);
   stopTime = clock();
   EST1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(expShellVect2, gapArray, shellGapSize);
   stopTime = clock();
   EST2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(expShellVect3, gapArray, shellGapSize);
   stopTime = clock();
   EST3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(expShellVect4, gapArray, shellGapSize);
   stopTime = clock();
   EST4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(expShellVect5, gapArray, shellGapSize);
   stopTime = clock();
   EST5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(expShellVect6, gapArray, shellGapSize);
   stopTime = clock();
   EST6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   //---------------------------------------------------------------------------

   startTime = clock();
   shellSortX(sedgeVect1, sedgewickArray, sedgeGapSize);
   stopTime = clock();
   ST1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(sedgeVect2, sedgewickArray, sedgeGapSize);
   stopTime = clock();
   ST2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(sedgeVect3, sedgewickArray, sedgeGapSize);
   stopTime = clock();
   ST3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(sedgeVect4, sedgewickArray, sedgeGapSize);
   stopTime = clock();
   ST4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(sedgeVect5, sedgewickArray, sedgeGapSize);
   stopTime = clock();
   ST5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(sedgeVect6, sedgewickArray, sedgeGapSize);
   stopTime = clock();
   ST6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   //---------------------------------------------------------------------------

   startTime = clock();
   shellSortX(otherVect1, otherArray, otherGapSize);
   stopTime = clock();
   OT1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(otherVect2, otherArray, otherGapSize);
   stopTime = clock();
   OT2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(otherVect3, otherArray, otherGapSize);
   stopTime = clock();
   OT3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(otherVect4, otherArray, otherGapSize);
   stopTime = clock();
   OT4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(otherVect5, otherArray, otherGapSize);
   stopTime = clock();
   OT5 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   startTime = clock();
   shellSortX(otherVect6, otherArray, otherGapSize);
   stopTime = clock();
   OT6 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;

   cout << "Vector Size 1: " << vector1Size << endl
      << "Vector Size 2: " << vector2Size << endl
      << "Vector Size 3: " << vector3Size << endl
      << "Vector Size 4: " << vector4Size << endl
      << "Vector Size 5: " << vector5Size << endl
      << "Vector Size 6: " << vector6Size << endl;

   cout << endl << "IMPLIED SHELL SORT TIMES" << endl;

   cout << "Vector 1: " << IST1 << endl
      << "Vector 2: " << IST2 << endl
      << "Vector 3: " << IST3 << endl
      << "Vector 4: " << IST4 << endl
      << "Vector 5: " << IST5 << endl
      << "Vector 6: " << IST6 << endl;

   cout << endl << "EXPLICIT SHELL SORT TIMES" << endl;

   cout << "Vector 1: " << EST1 << endl
      << "Vector 2: " << EST2 << endl
      << "Vector 3: " << EST3 << endl
      << "Vector 4: " << EST4 << endl
      << "Vector 5: " << EST5 << endl
      << "Vector 6: " << EST6 << endl;

   cout << endl << "SEDGEWICK SORT TIMES" << endl;

   cout << "Vector 1: " << ST1 << endl
      << "Vector 2: " << ST2 << endl
      << "Vector 3: " << ST3 << endl
      << "Vector 4: " << ST4 << endl
      << "Vector 5: " << ST5 << endl
      << "Vector 6: " << ST6 << endl;

   cout << endl << "TOKUDA SORT TIMES" << endl;

   cout << "Vector 1: " << OT1 << endl
      << "Vector 2: " << OT2 << endl
      << "Vector 3: " << OT3 << endl
      << "Vector 4: " << OT4 << endl
      << "Vector 5: " << OT5 << endl
      << "Vector 6: " << OT6 << endl;

}

//RUNS--------------------------------------------------------------------------
/*
Sedgewick gap array
1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305,
260609, 587521, 1045505, 2354689, 4188161, 9427969, 16764929, 37730305, 6708428
9, 150958081,

Tokuda gap array
1, 4, 9, 20, 46, 103, 233, 525, 1182, 2660, 5985, 13467, 30301, 68178, 153401, 3
45152, 776591, 1747331, 3931496, 8845866, 19903198, 44782196, 100759940, 2267098
66, 510097200,

Vector Size 1: 10000
Vector Size 2: 45000
Vector Size 3: 91524
Vector Size 4: 122000
Vector Size 5: 170402
Vector Size 6: 200000

IMPLIED SHELL SORT TIMES
Vector 1: 0.015
Vector 2: 0.125
Vector 3: 0.304
Vector 4: 0.406
Vector 5: 0.657
Vector 6: 0.812

EXPLICIT SHELL SORT TIMES
Vector 1: 0.047
Vector 2: 0.437
Vector 3: 1.082
Vector 4: 2.036
Vector 5: 3.014
Vector 6: 3.746

SEDGEWICK SORT TIMES
Vector 1: 0.016
Vector 2: 0.094
Vector 3: 0.187
Vector 4: 0.281
Vector 5: 0.376
Vector 6: 0.466

TOKUDA SORT TIMES
Vector 1: 0.016
Vector 2: 0.087
Vector 3: 0.184
Vector 4: 0.276
Vector 5: 0.379
Vector 6: 0.445
Press any key to continue . . .

--------------------------------------------------------------------------------

Sedgewick gap array
1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305,
260609, 587521, 1045505, 2354689, 4188161, 9427969, 16764929, 37730305, 6708428
9, 150958081,

Tokuda gap array
1, 4, 9, 20, 46, 103, 233, 525, 1182, 2660, 5985, 13467, 30301, 68178, 153401, 3
45152, 776591, 1747331, 3931496, 8845866, 19903198, 44782196, 100759940, 2267098
66, 510097200,

Vector Size 1: 10000
Vector Size 2: 45000
Vector Size 3: 91524
Vector Size 4: 122000
Vector Size 5: 170402
Vector Size 6: 200000

IMPLIED SHELL SORT TIMES
Vector 1: 0.031
Vector 2: 0.172
Vector 3: 0.36
Vector 4: 0.39
Vector 5: 0.61
Vector 6: 0.772

EXPLICIT SHELL SORT TIMES
Vector 1: 0.047
Vector 2: 0.422
Vector 3: 1.141
Vector 4: 2.343
Vector 5: 2.67
Vector 6: 3.596

SEDGEWICK SORT TIMES
Vector 1: 0.016
Vector 2: 0.094
Vector 3: 0.203
Vector 4: 0.265
Vector 5: 0.391
Vector 6: 0.453

TOKUDA SORT TIMES
Vector 1: 0.016
Vector 2: 0.094
Vector 3: 0.187
Vector 4: 0.266
Vector 5: 0.375
Vector 6: 0.453
Press any key to continue . . .
*/

//TABLE AND ANSWERS-------------------------------------------------------------
/*                         (Using data from second run)
                                 Number of items
                 10000    45000    91524    122000    170402    200000

Implicit Shell   0.031    0.172    0.36     0.39      0.61      0.772

Explicit Shell   0.047    0.422    1.141    2.343     2.67      3.596

Sedgewick        0.016    0.094    0.203    0.265     0.391     0.453

Tokuda           0.016    0.094    0.187    0.266     0.375     0.453

The implied shell sort gives a faster time than the explicit shell sort.
This is because of how the numbers are generated. In the implied shell sort,
the numbers are generated by dividing the size by two over and over again.
This allows for the gap to have a variety of sizes that include both odd 
and even numbers, different factors in the number, etc. However, the 
explicit sort is always composed of factors of 2. This creates very
similar and uniform gaps that create a terrible situation for itself.
It constantly resorts what it just sorted the previous pass and the odds
aren't mixed with the evens until the last pass, making it significantly 
less efficient.
*/