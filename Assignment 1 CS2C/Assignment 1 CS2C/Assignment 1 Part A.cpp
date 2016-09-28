#include <vector>
#include <iostream>
using namespace std;

class Sublist
{
public:
   Sublist(vector<int> *orig = NULL)
      : sum(0), originalObjects(orig) { }
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector<int> *originalObjects;
   vector<int> indices;
};

Sublist Sublist::addItem(int indexOfItemToAdd)
{
   Sublist newSublist = *this;
   newSublist.indices.push_back(indexOfItemToAdd);
   newSublist.sum = newSublist.sum + originalObjects->at(indexOfItemToAdd);
   return newSublist;
}

void Sublist::showSublist() const
{
   cout << "Sublist -----------------------------" << '\n'
      << "sum: " << sum << endl;

   for (unsigned int i = 0; i < indices.size() - 1; i++)
   {
      cout << "array[" << indices[i] << "] = " << originalObjects->at(indices[i]) << ",   ";
      if ((i + 1) % 4 == 0)
         cout << '\n';
   }

   cout << "array[" << indices[indices.size() - 1] << "] = " << originalObjects->at(indices[indices.size() - 1])
      << '\n' << '\n';
}

int main()
{
   int TARGET = 1000;
   vector<int> dataSet;
   vector<Sublist> choices;
   int max = 0, masterSum = 0, bestIndex;
   bool foundPerfect = false;

   dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(15);
   dataSet.push_back(15); dataSet.push_back(25);
   dataSet.push_back(19); dataSet.push_back(29);
   dataSet.push_back(18);
   dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);

   choices.clear();
   cout << "Target time: " << TARGET << endl;

   choices.push_back(Sublist(&dataSet));

   for (unsigned int i = 0; i < dataSet.size(); i++)
   {
      masterSum += dataSet[i];
   }

   if (masterSum <= TARGET)
   {
      Sublist masterSublist = Sublist(&dataSet);
      for (unsigned int i = 0; i < dataSet.size(); i++)
      {
         masterSublist = masterSublist.addItem(i);
      }
      choices.push_back(masterSublist);
      bestIndex = choices.size() - 1;
      foundPerfect = true;
   }

   for (unsigned int i = 0; i < dataSet.size() && !foundPerfect; i++)
   {
      int loopEndIndex = choices.size();
      for (int z = 0; z < loopEndIndex && !foundPerfect; z++)
      {
         Sublist newSublist = choices[z].addItem(i);
         if (newSublist.getSum() <= TARGET)
         {
            choices.push_back(newSublist);
            if (newSublist.getSum() == TARGET)
            {
               bestIndex = choices.size() - 1;
               foundPerfect = true;
            }
            if (newSublist.getSum() > max)
            {
               bestIndex = choices.size() - 1;
               max = newSublist.getSum();
            }
         }
      }
   }

   choices[bestIndex].showSublist();

   return 0;
}

/*
Test Runs:

Target time: 180
Sublist -----------------------------
sum: 179
array[0] = 20,   array[1] = 12,   array[3] = 15,   array[4] = 25,
array[5] = 19,   array[6] = 29,   array[7] = 18,   array[8] = 11,
array[9] = 13,   array[10] = 17

Press any key to continue . . .

Target time: 1000
Sublist -----------------------------
sum: 201
array[0] = 20,   array[1] = 12,   array[2] = 22,   array[3] = 15,
array[4] = 25,   array[5] = 19,   array[6] = 29,   array[7] = 18,
array[8] = 11,   array[9] = 13,   array[10] = 17

Press any key to continue . . .

Target time: 180
Sublist -----------------------------
sum: 180
array[0] = 20,   array[1] = 13,   array[3] = 15,   array[4] = 25,
array[5] = 19,   array[6] = 29,   array[7] = 18,   array[8] = 11,
array[9] = 13,   array[10] = 17

Press any key to continue . . .

Target time: 180
Sublist -----------------------------
sum: 180
array[1] = 130,   array[2] = 20,   array[5] = 19,   array[8] = 11

Press any key to continue . . .
*/