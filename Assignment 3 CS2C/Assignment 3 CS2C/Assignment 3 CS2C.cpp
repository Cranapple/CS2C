#include <iostream>
#include <time.h>
using namespace std;

#define MAT_SIZE 1000
typedef float* DynMat[MAT_SIZE];

void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size)
{
   float tempSum;

   for (int i = 0; i < size; i++)
   {
      for (int z = 0; z < size; z++)
      {
         tempSum = 0;
         for (int k = 0; k < size; k++)
         {
            tempSum += matA[i][k] * matB[k][z];
         }
         matC[i][z] = tempSum;
      }
   }
}

void matShowDyn(const DynMat & matA, int start, int size)
{
   cout << endl << endl;
   int total = start + size;

   for (int r = start; r < total; r++)
   {
      for (int c = start; c < total; c++)
      {
         cout.width(5);
         cout.precision(3);
         cout << matA[r][c] << " ";
      }
      cout << endl << endl;
   }

   cout << endl << endl;
}

int main()
{
   int r, c;
   clock_t startTime, stopTime;
   int randRow, randCol, smallPercent;

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;

   // allocate rows and initialize to 0
   for (r = 0; r < MAT_SIZE; r++)
   {
      matDyn[r] = new float[MAT_SIZE];
      matDynAns[r] = new float[MAT_SIZE];
      for (c = 0; c < MAT_SIZE; c++)
      {
         matDyn[r][c] = 0;
         matDynAns[r][c] = 0;
      }
   }

   // generate small% non-default values bet .1 and 1
   smallPercent = MAT_SIZE / 20. * MAT_SIZE; 
   srand(time(NULL));
   for (int i = 0; i < smallPercent; i++)
   {
      do{
         randRow = rand() % MAT_SIZE;
         randCol = rand() % MAT_SIZE;
      } while (matDyn[randRow][randCol] != 0);
      
      matDyn[randRow][randCol] = (rand() % 9 + 1) / 10.0;
   }

   // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);

   startTime = clock();  // ------------------ start
   matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
   stopTime = clock();  // ---------------------- stop

   matShowDyn(matDynAns, MAT_SIZE - 10, 10);
   cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // clean up
   for (r = 0; r < MAT_SIZE; r++)
   {
      delete[] matDyn[r];
      delete[] matDynAns[r];
   }
      

      cout << endl;
}


/* 
QUESTION ANSWERS ---------------------------------------------

Find O()  and Θ() of matrix multiplication and explain how / why 
(Relative to M, the size)

The big O of the matrix multiplication is O(M^3). This is because 
the method will have to loop through every row (The first loop) and 
then through every column in said row (The second loop). Then, 
using a third loop, it will iterate through each item in matrix A's 
corresponding row and matrix B's corresponding column, multiply them 
and add them to a sum that will be stored at the end of this loop. 
Each loop multiplies another M, and as such with them nested it creates O(M^3). 
However, the theta will also be Θ(M^3) because in every instance all 
three loops loop through M times, the worse case senario. And as such, 
the actual time is always equal to the worst time, and big O = theta.


What was the smallest M that gave you a non-zero time?

100


What happened when you doubled M , tripled it, quadrupled it, etc?  
Give several M values and their times in a table.

M     Time (Seconds)
100   0.016
200   0.031
300   0.188
400   0.485
500   0.534
1000  13.6
1500  48
2000  123
3000  480


How large an M can you use before the program refuses to run 
(exception or run-time error due to memory overload) or it takes 
so long you can't wait for the run?

The program would not run at an M of 20000. However at an M of 4000
it got to the point where you had to wait a long time for it to finish.


How did the data agree or disagree with your original time complexity estimate?

The data seems to agree with my original time complexity estimate.
The smaller peices of data don't seem to follow it as well, but
their times can fluxiate a good deal. However, it still roughly follows
a cubic growth. This can be more clearly seen with the large values.
Going from 1000 to 2000 is doubling M, and as such it should produce
a run that takes 8 times longer. In this case it takes roughly 9 times.
Additionally 1000 to 1500 is a is an increase by 1.5, so the time should 
be roughly 3.4 times more. In this case it is about 3.5 times more.


*/

/* TEST RUNS ------------------------------------------------------



0     0     0     0     0     0     0     0     0     0

0.4     0     0   0.3   0.7     0     0     0     0     0

0     0   0.7     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0   0.7     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0





0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0  0.49     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0




Size = 10 Dyn Array Mult Elapsed Time: 0 seconds.


Press any key to continue . . .




0     0     0     0     0     0     0     0     0     0

0     0     0     0     0   0.1     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0   0.7     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0   0.6     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0





0     0     0  0.08     0     0     0     0     0     0

0.2  0.32     0  0.16  0.02  0.07     0   0.2     0     0

0  0.08     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0  0.63     0     0     0  0.21     0     0     0

0     0     0     0     0  0.49     0  0.28     0     0

0     0     0     0     0     0     0     0     0  0.24

0     0     0     0     0     0     0     0     0     0

0.4  0.45     0     0     0     0     0     0     0     0

0     0     0  0.16     0     0     0     0     0     0




Size = 100 Dyn Array Mult Elapsed Time: 0.016 seconds.


Press any key to continue . . .




0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0   0.8     0

0     0     0     0     0     0     0     0     0     0

0   0.7     0     0   0.8     0     0     0     0   0.4

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0   0.3     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0   0.5     0     0

0     0     0     0     0     0     0     0     0     0





1.04     0     0   0.6   0.3  0.88     0     0  0.35     0

0.01  0.09     0  0.54     0  0.69     0  0.89     0     0

0  0.54     0  0.04  0.39  0.12  0.04   0.4     0     0

0     0     0     0     0   0.1     0   0.1  0.56     0

0  0.14     0  0.06  0.16  0.14     0     0  0.05     0

0     0     0  0.06     0  0.11  0.06     0     0     0

0.08  0.35  0.24  0.15  0.33     0  0.04     0  0.48     0

0.63     0     0  0.72     0     0  0.01     0     0  0.08

0     0     0  0.56  0.85     0  0.04  0.95  0.32  0.77

0.56     0     0  0.57     0  0.48  0.08   0.4   0.1  0.64




Size = 200 Dyn Array Mult Elapsed Time: 0.031 seconds.


Press any key to continue . . .





0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0   0.2     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0   0.4

0     0     0     0     0     0     0     0   0.4     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0   0.1     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0   0.8     0     0     0     0     0     0     0





0     0     0     0     0  0.21     0     0  0.36     0

0.36     0  0.25     0  0.45  0.45     0     0     0  0.14

0.2     0     0  0.18  0.15  0.56     0  0.63  0.61     0

0     0  0.32  0.08   0.4     0     0  0.27     0  0.13

0.04  0.36     0     0     0   0.4     0     0     0  0.44

0  0.12  0.24  0.24     0     0     0  0.45     0     0

0.76  0.37     0  0.59     0  0.72     0     0     0  0.36

0  0.09     0  0.07     0  0.24     0  0.35     0  0.01

0.16  0.51     0     0     0     0   0.2     0  0.36  0.22

0.18  0.27     0  0.25  0.63  0.94     0   0.1     0     0




Size = 300 Dyn Array Mult Elapsed Time: 0.188 seconds.


Press any key to continue . . .





0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0   0.3     0     0     0     0     0     0

0     0   0.8   0.4     0     0     0     0     0     0

0   0.5     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0   0.3     0   0.1     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0   0.2     0   0.4





0.63     0     0  0.02  0.84  0.95     0  0.09     0     0

1.35  0.55     0  0.76   0.9  0.65  0.06  0.36     0  0.09

0  0.28  0.72   0.2  0.42  0.44   0.2  0.15     0     0

0.49  0.21  0.32   0.4  0.03  0.03  0.72  0.07  0.63  0.15

0  0.06     0  0.18   0.9  0.72  0.73  0.08  0.32     0

0.35     0  0.41  0.76  0.75  0.68     0     0   0.1  0.21

0.83  0.18     0  0.74     0     0     0  0.06     0     0

0  0.12  0.08  0.61     0  0.06     0  0.45  0.44     0

0.18     0  0.05   0.4  0.14   0.3  0.11     0  0.21     0

0.7  0.06     0  0.14     0   0.7   0.8  0.08  0.12  0.46




Size = 400 Dyn Array Mult Elapsed Time: 0.485 seconds.


Press any key to continue . . .





0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0   0.3     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0   0.1     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0   0.1     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0





0.6  0.45     0     0     0     0  0.13     0  0.69  0.56

0.3  0.24   0.3     0  0.44  0.54   0.8  0.16  0.36     0

0  0.07  0.25  0.14  0.33     0     0     0     0  0.08

0  1.78  0.23  0.42     0  0.06  0.27     0  0.32     0

0.43  0.63     0  0.45  0.04     0  0.21  0.42  0.64  0.24

0  0.48  0.42     0     0     0   0.1  0.01  0.45   0.2

0.24  0.36  0.36  0.88     0  0.75   0.9  0.45  1.13     0

0.56  0.81  0.08  0.12  0.14     0  0.63  0.07  0.42  1.11

1.03  0.64     0     0     0     0  0.02     0     0  0.05

0.44  0.28     0  0.24  0.12  0.36   0.6     0  0.69  0.45




Size = 500 Dyn Array Mult Elapsed Time: 0.534 seconds.


Press any key to continue . . .





0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0   0.7     0     0     0     0

0     0     0     0     0     0   0.8     0     0     0

0     0     0     0     0     0     0     0     0     0





0  0.53  0.81  0.49  0.31     1   0.2  0.46  0.93     0

0.24  1.84  0.12  0.27  0.07  0.58     0  0.96  0.48  0.99

0.6  0.01   1.2  0.61  0.69  0.35  0.14  1.54  0.36  1.01

0.81  1.19  0.21  0.66  0.51  1.02  0.02   0.3  0.14     0

0.78     0  0.33   0.3  0.02  0.93  0.04   0.2  0.54  0.05

0.03  2.11  0.12  0.37  0.51  0.38  0.36   0.1   0.3  1.26

0.3  0.32     0  0.89  1.32  0.57   1.5   0.1  0.56  1.29

0.24  1.52  0.41  0.62  0.38  1.44  0.07  1.68  1.59   0.5

0.57  0.87     0  0.59  0.52     0  0.28  0.46  1.59  0.64

1.02     0  0.88  0.27  1.03  0.79  2.02  0.92   0.3  0.88




Size = 1000 Dyn Array Mult Elapsed Time: 13.6 seconds.


Press any key to continue . . .






0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0.6     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0.5     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0     0     0

0     0     0     0     0     0     0     0   0.1     0





0.77  0.74  2.33  1.48  1.33  0.53  0.42  1.24  1.02  1.47

0.6   0.7  2.51  0.18  0.58  0.46  1.72   0.3  0.24   0.7

0.53  0.35  1.45  0.08  0.38  1.04  2.32  0.96  0.43  0.96

0.85  0.77  1.81   0.9  0.03  0.54  1.78  1.42  1.62  1.49

0.84  3.17  0.96  0.76  0.08  0.72  2.35  1.77  1.09  1.47

0.46  2.32  2.63  1.74  2.18  1.26  1.46  3.15  0.57  0.45

2.42  1.39  2.35  1.68  1.22  1.32  2.05  1.06   1.3  1.74

1.34  0.44  1.51  1.62  0.38  0.37  0.73  1.09  0.25  0.77

0.62   1.7  0.58  0.94  0.23  0.97  0.46  0.98  0.72  1.22

0.31  1.04  0.66  2.13  1.88  0.65  0.34  0.98  0.69  1.66




Size = 2000 Dyn Array Mult Elapsed Time: 123 seconds.


Press any key to continue . . .
*/
