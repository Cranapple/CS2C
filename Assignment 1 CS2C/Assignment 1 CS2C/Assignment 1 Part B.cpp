#include <vector>
#include <iostream>
#include "iTunes.h"
using namespace std;

int operator+(const int &left, const iTunesEntry &right)
{
   return left + right.getTime();
}

ostream& operator<<(ostream& os, const iTunesEntry& entry)
{
   os << entry.getTitle() << " | " << entry.getArtist() << " | " << entry.getTime();
   return os;
}

class Sublist
{
public:
   Sublist(vector<iTunesEntry> *orig = NULL)
      : sum(0), originalObjects(orig) { }
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector<iTunesEntry> *originalObjects;
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
      cout << "array[" << indices[i] << "] = " << originalObjects->at(indices[i]) << '\n';
   }

   cout << "array[" << indices[indices.size() - 1] << "] = " << originalObjects->at(indices[indices.size() - 1])
      << '\n' << '\n';
}

int main()
{
   int TARGET = 176;
   vector<iTunesEntry> dataSet;
   vector<Sublist> choices;
   int max = 0, masterSum = 0, bestIndex, array_size;
   bool foundPerfect = false;

   // read the data
   iTunesEntryReader tunes_input("itunes_file.txt");
   if (tunes_input.readError())
   {
      cout << "couldn't open " << tunes_input.getFileName()
         << " for input.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create a vector of objects for our own use:
   array_size = tunes_input.getNumTunes();
   for (int k = 0; k < array_size; k++)
      dataSet.push_back(tunes_input[k]);

   choices.clear();
   cout << "Target time: " << TARGET << endl;

   choices.push_back(Sublist(&dataSet));

   for (unsigned int i = 0; i < dataSet.size(); i++)
   {
      masterSum = masterSum + dataSet[i];
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

   // how we determine the time elapsed -------------------
   stopTime = clock();
   // report algorithm time
   cout << "\nAlgorithm Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   return 0;
}

/*
Test Runs:

Target time: 3600
Sublist -----------------------------
sum: 3600
array[0] = Cowboy Casanova | Carrie Underwood | 236
array[1] = Quitter | Carrie Underwood | 220
array[2] = Russian Roulette | Rihanna | 228
array[4] = Monkey Wrench | Foo Fighters | 230
array[5] = Pretending | Eric Clapton | 283
array[6] = Bad Love | Eric Clapton | 308
array[7] = Everybody's In The Mood | Howlin' Wolf | 178
array[8] = Well That's All Right | Howlin' Wolf | 175
array[9] = Samson and Delilah | Reverend Gary Davis | 216
array[11] = Hot Cha | Roy Buchanan | 208
array[12] = Green Onions | Roy Buchanan | 443
array[13] = I'm Just a Prisoner | Janiva Magness | 230
array[14] = You Were Never Mine | Janiva Magness | 276
array[15] = Hobo Blues | John Lee Hooker | 187
array[16] = I Can't Quit You Baby | John Lee Hooker | 182


Algorithm Elapsed Time: 3.564 seconds.

Press any key to continue . . .

---------------------------------------------------------------------

Target time: 4000
Sublist -----------------------------
sum: 4000
array[0] = Cowboy Casanova | Carrie Underwood | 236
array[1] = Quitter | Carrie Underwood | 220
array[2] = Russian Roulette | Rihanna | 228
array[3] = All My Life | Foo Fighters | 263
array[4] = Monkey Wrench | Foo Fighters | 230
array[5] = Pretending | Eric Clapton | 283
array[6] = Bad Love | Eric Clapton | 308
array[7] = Everybody's In The Mood | Howlin' Wolf | 178
array[8] = Well That's All Right | Howlin' Wolf | 175
array[9] = Samson and Delilah | Reverend Gary Davis | 216
array[11] = Hot Cha | Roy Buchanan | 208
array[12] = Green Onions | Roy Buchanan | 443
array[13] = I'm Just a Prisoner | Janiva Magness | 230
array[16] = I Can't Quit You Baby | John Lee Hooker | 182
array[17] = That's The Homie | Snoop Dogg | 343
array[18] = Gangsta Luv | Snoop Dogg | 257


Algorithm Elapsed Time: 14.824 seconds.

Press any key to continue . . .

----------------------------------------------------------------------

Target time: 1364
Sublist -----------------------------
sum: 1364
array[0] = Cowboy Casanova | Carrie Underwood | 236
array[1] = Quitter | Carrie Underwood | 220
array[2] = Russian Roulette | Rihanna | 228
array[6] = Bad Love | Eric Clapton | 308
array[7] = Everybody's In The Mood | Howlin' Wolf | 178
array[10] = Twelve Sticks | Reverend Gary Davis | 194


Algorithm Elapsed Time: 0.09 seconds.

Press any key to continue . . .

-------------------------------------------------------------------------

Target time: 176
Sublist -----------------------------
sum: 175
array[8] = Well That's All Right | Howlin' Wolf | 175


Algorithm Elapsed Time: 0.016 seconds.

Press any key to continue . . .

---------------------------------------------------------------------------

Target time: 1000000
Sublist -----------------------------
sum: 22110
array[0] = Cowboy Casanova | Carrie Underwood | 236
array[1] = Quitter | Carrie Underwood | 220
array[2] = Russian Roulette | Rihanna | 228
array[3] = All My Life | Foo Fighters | 263
array[4] = Monkey Wrench | Foo Fighters | 230
array[5] = Pretending | Eric Clapton | 283
array[6] = Bad Love | Eric Clapton | 308
array[7] = Everybody's In The Mood | Howlin' Wolf | 178
array[8] = Well That's All Right | Howlin' Wolf | 175
array[9] = Samson and Delilah | Reverend Gary Davis | 216
array[10] = Twelve Sticks | Reverend Gary Davis | 194
array[11] = Hot Cha | Roy Buchanan | 208
array[12] = Green Onions | Roy Buchanan | 443
array[13] = I'm Just a Prisoner | Janiva Magness | 230
array[14] = You Were Never Mine | Janiva Magness | 276
array[15] = Hobo Blues | John Lee Hooker | 187
array[16] = I Can't Quit You Baby | John Lee Hooker | 182
array[17] = That's The Homie | Snoop Dogg | 343
array[18] = Gangsta Luv | Snoop Dogg | 257
array[19] = Ladies and Gentleman | The Rubyz | 201
array[20] = Watch the Girl | The Rubyz | 192
array[21] = Donuts for Benny | Veggie Tales | 184
array[22] = Our Big Break | Veggie Tales | 69
array[23] = Brahms: Symphony No. 1 in C Minor Op. 68 | Berliner Philharmoniker |
839
array[24] = Brahms: Symphony No. 4 in E Minor Op. 98 | Berliner Philharmoniker |
800
array[25] = Bach: Suite for Cello No. 1 in G Major Prelude | Yo-yo Ma | 141
array[26] = Simple Gifts | Yo-yo Ma | 154
array[27] = Alimony | Ry Cooter | 175
array[28] = France Chance | Ry Cooter | 168
array[29] = The Road | Aaron Watson | 204
array[30] = Clone | Terra Incognita | 298
array[31] = Lizard Skin | Terra Incogni | 270
array[32] = Bullhead's Psalm | Blue Record | 79
array[33] = Ogeechee Hymnal | Blue Record | 155
array[34] = Oblivion | Mastadon | 348
array[35] = The Bit | Mastadon | 295
array[36] = Fire Burning | Sean Kingston | 239
array[37] = My Girlfriend | Sean Kingston | 204
array[38] = Take Your Shirt Off | T-Pain | 228
array[39] = Give It All U Got | Lil Jon | 218
array[40] = What We Talkin' About | Jay-Z | 243
array[41] = Empire State of Mind | Jay-Z | 276
array[42] = Think About It | Snoop Dog | 217
array[43] = Lil' Crips | Snoop Dog | 195
array[44] = Shuffleboard | Jeff Golub | 210
array[45] = Goin' On | Jeff Golub | 356
array[46] = Fish Fare | Jeff Golub | 299
array[47] = Noites Cariocas | Caraivana | 252
array[48] = Tico-Tico No Fuba | Caraivana | 147
array[49] = Monk/Trane | John Patitucci | 434
array[50] = Sonny Side | John Patitucci | 445
array[51] = Pirate Jenny | Nina Simone | 402
array[52] = The Other Woman | Nina Simone | 186
array[53] = Feeling Good | Nina Simone | 177
array[54] = A Love Supreme Part 1 | John Coltrane | 462
array[55] = In a Sentimental Mood | John Coltrane | 256
array[56] = Dime Si te Vas Con El | AOL Dejando Huellas | 204
array[57] = Te Amo Tanto | AOL Dejando Huella | 192
array[58] = Blues On the Corner | McCoy Tyner | 367
array[59] = Afro Blue | McCoy Tyner | 742
array[60] = Stronger | Kanye West | 311
array[61] = Good Life | Kanye West | 207
array[62] = Black Cow | Steely Dan | 310
array[63] = Kid Charlemagne | Steely Dan | 278
array[64] = Haitian Divorce | Steely Dan | 351
array[65] = Nefertiti | Herbie Hancock | 451
array[66] = Rockit | Herbie Hancock | 325
array[67] = Chameleon | Herbie Hancock | 941
array[68] = Medieval Overture | Return to Forever | 313
array[69] = Luka | Suzanne Vega | 231
array[70] = Small Blue Thing | Suzanne Vega | 235
array[71] = Something to Talk About | Bonnie Raitt | 227
array[72] = I Can't Make You Love Me | Bonnie Raitt | 331
array[73] = This Will Be | Natalie Cole | 171
array[74] = Unforgettable | Natalie Cole | 211
array[75] = Timothy | Jet | 260
array[76] = Rip It Up | Jet | 200
array[77] = Where Did Your Heart Go? | Was (Not Was) | 347
array[78] = I Blew Up The United States | Was (Not Was) | 230


Algorithm Elapsed Time: 0.155 seconds.

Press any key to continue . . .
*/