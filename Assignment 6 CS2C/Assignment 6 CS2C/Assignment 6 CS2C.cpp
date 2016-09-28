//MAIN--------------------------------------------------------------------------

#include <string>
#include "EBookEntry.h"
#include "FHhashQPwFind.h"
#include <time.h>
using namespace std;

// ----------- prototypes -------------

int Hash(int key);
int Hash(const string & key);
int Hash(const EBookEntry & key);

int getKey(const EBookEntry & item);
//string getKey( const EBookEntry & item);

const int NUM_RAND_IND = 25;

int main()
{
   srand(time(NULL));
   EBookEntryReader books("catalog-short4.txt");
   EBookEntry book;
   FHhashQPwFind<EBookEntry, int> hash_table; // for ID equality
   //FHhashQPwFind<EBookEntry, string> hash_table; // for any string equality

   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   //EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

   cout << books.getFileName() << endl;
   cout << books.getNumBooks() << endl << endl;

   for (int i = 0; i < books.getNumBooks(); i++)
      hash_table.insert(books[i]);

   int randNums[NUM_RAND_IND];
   for (int i = 0; i < NUM_RAND_IND; i++)
      randNums[i] = (int)(rand()) % books.getNumBooks();

   cout << NUM_RAND_IND << " RANDOM BOOKS" << endl << endl;

   for (int i = 0; i < NUM_RAND_IND; i++)
   {
      cout << "BOOK " << i << ":" << endl
         << "Title: " << (books[randNums[i]]).getTitle() << endl
         << "Creator: " << (books[randNums[i]]).getCreator() << endl
         << "Subject: " << (books[randNums[i]]).getSubject() << endl
         << "ETextNum: " << (books[randNums[i]]).getETextNum() << endl
         << endl << endl;
   }

   cout << "ACCESS SAME BOOKS FROM HASH TABLE" << endl << endl;

   for (int i = 0; i < NUM_RAND_IND; i++)
   {
      try
      {
         book = hash_table.find((books[randNums[i]]).getETextNum());
         //book = hash_table.find((books[randNums[i]]).getCreator());
         cout << "FOUND BOOK " << i << ":" << endl
            << "Title: " << book.getTitle() << endl
            << "Creator: " << book.getCreator() << endl
            << "Subject: " << book.getSubject() << endl
            << "ETextNum: " << book.getETextNum() << endl
            << endl << endl;
      }
      catch (...)
      {
         cout << "Not found" << endl;
      }
   }

   cout << endl << endl << "TESTING KNOWN FAILURES" << endl;

   try
   {
      book = hash_table.find(-3);
      //book = hash_table.find( "Jack Kerouac" );
      cout << "Found book: " << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "Not found" << endl;
   }
   try
   {
      book = hash_table.find(INT_MAX);
      //book = hash_table.find( "Liam Neeson" );
      cout << "Found book: " << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "Not found" << endl;
   }
   try
   {
      book = hash_table.find(-1);
      //book = hash_table.find( "Brobotic Jack" );
      cout << "Found book: " << book.getTitle() << endl;
   }
   catch (...)
   {
      cout << "Not found" << endl;
   }
}

/*
// used for author equality
string getKey(const EBookEntry & item)
{
   return item.getCreator() ;
}
*/

// used for ID equality
int getKey(const EBookEntry & item)
{
   return item.getETextNum();
}

int Hash(int key)
{
   return key;
}

int Hash(const string & key)
{
   unsigned int k, retVal = 0;

   for (k = 0; k < key.length(); k++)
      retVal = 37 * retVal + key[k];

   return retVal;
}

int Hash(const EBookEntry & key)
{
   // used for ID equality
   
   return key.getETextNum();
   

   // used for author equality
   /*
   unsigned int k, retVal = 0;
   const string author = key.getCreator();

   for (k = 0; k < author.length(); k++)
      retVal = 37 * retVal + author[k];

   return retVal;
   */
}


//TESTS-------------------------------------------------------------------------
/*
ENUMKEY-------------------------------------------------------------------------

catalog-short4.txt
4863

25 RANDOM BOOKS

BOOK 0:
Title: Comfort Pease and her Gold Ring
Creator: Freeman, Mary Eleanor Wilkins, 1852-1930
Subject: (no data found)
ETextNum: 17888


BOOK 1:
Title: Bert Wilson on the Gridiron
Creator: Duffield, J. W.
Subject: Football -- Juvenile fiction
ETextNum: 28728


BOOK 2:
Title: The Suffrage Cook Book
Creator: (no data found)
Subject: Women -- Suffrage -- United States
ETextNum: 26323


BOOK 3:
Title: The Life of King Edward VIIwith a sketch of the career of King George V
Creator: Hopkins, J. Castell (John Castell), 1864-1923
Subject: Edward VII, King of Great Britain, 1841-1910
ETextNum: 25112


BOOK 4:
Title: Milk for You and Me
Creator: Randell, Winifred
Subject: Milk as food -- Juvenile literature
ETextNum: 25552


BOOK 5:
Title: The Wonder
Creator: Beresford, J. D. (John Davys), 1873-1947
Subject: Science fiction
ETextNum: 27188


BOOK 6:
Title: The Traitors
Creator: Oppenheim, E. Phillips (Edward Phillips), 1866-1946
Subject: Spy stories
ETextNum: 29162


BOOK 7:
Title: Otherwise Phyllis
Creator: Nicholson, Meredith, 1866-1947
Subject: Indiana -- Fiction
ETextNum: 28017


BOOK 8:
Title: A Likely Story
Creator: Howells, William Dean, 1837-1920
Subject: American drama -- 19th century
ETextNum: 28305


BOOK 9:
Title: The Critic in the Orient
Creator: Fitch, George Hamlin, 1852-1925
Subject: Egypt -- Description and travel
ETextNum: 27233


BOOK 10:
Title: The Scottish Chiefs
Creator: Porter, Jane, 1776-1850
Subject: Scotland -- History -- War of Independence, 1285-1371 -- Fiction
ETextNum: 6086


BOOK 11:
Title: The Wonders of the Invisible WorldBeing an Account of the Tryals of Sever
al Witches LatelyExecuted in New-England, to which is added A Farther Accountof
the Tryals of the New-England Witches
Creator: Mather, Cotton, 1663-1728
Subject: Witchcraft -- New England -- Early works to 1800
ETextNum: 28513


BOOK 12:
Title: Told by the Northmen:Stories from the Eddas and Sagas
Creator: Wilmot-Buxton, E. M. (Ethel Mary)
Subject: Mythology, Norse
ETextNum: 29551


BOOK 13:
Title: Spiritual Torrents
Creator: Guyon, Jeanne Marie Bouvier de la Motte, 1648-1717
Subject: Mysticism
ETextNum: 25133


BOOK 14:
Title: Chambers's Edinburgh Journal, No. 441Volume 17, New Series, June 12, 1852

Creator: Various
Subject: Great Britain -- Social life and customs -- 19th century -- Periodicals

ETextNum: 24892


BOOK 15:
Title: Madcap
Creator: Gibbs, George, 1870-1942
Subject: (no data found)
ETextNum: 11584


BOOK 16:
Title: Ancient America, in Notes on American Archaeology
Creator: Baldwin, John D. (John Denison), 1809-1883
Subject: Indians -- Antiquities
ETextNum: 26382


BOOK 17:
Title: St. Nicholas Magazine for Boys and Girls, Vol. V,  August, 1878, No 10.Sc
ribner's Illustrated
Creator: Various
Subject: Children's literature -- Periodicals
ETextNum: 29983


BOOK 18:
Title: The Idiot
Creator: Dostoyevsky, Fyodor, 1821-1881
Subject: Russia -- Social life and customs -- 1533-1917 -- Fiction
ETextNum: 2638


BOOK 19:
Title: Goodbye, Dead Man!
Creator: Harris, Tom W.
Subject: Science fiction
ETextNum: 29963


BOOK 20:
Title: Good Stories for Holidays
Creator: Olcott, Frances Jenkins, 1872-1963
Subject: Children's literature
ETextNum: 359


BOOK 21:
Title: A Yeoman's LettersThird Edition
Creator: Ross, P. T.
Subject: South African War, 1899-1902 -- Personal narratives
ETextNum: 27765


BOOK 22:
Title:
Creator: Goodell, Abner Cheney, 1831-1914
Subject: Mark (Slave) -- Trials, litigation, etc.
ETextNum: 26446


BOOK 23:
Title: The Comings of Cousin Ann
Creator: Sampson, Emma Speed, 1868-1947
Subject: PS
ETextNum: 28439


BOOK 24:
Title: The Mascot of Sweet Briar Gulch
Creator: Phillips, Henry Wallace, 1869-1930
Subject: Miners -- Fiction
ETextNum: 25809


ACCESS SAME BOOKS FROM HASH TABLE

FOUND BOOK 0:
Title: Comfort Pease and her Gold Ring
Creator: Freeman, Mary Eleanor Wilkins, 1852-1930
Subject: (no data found)
ETextNum: 17888


FOUND BOOK 1:
Title: Bert Wilson on the Gridiron
Creator: Duffield, J. W.
Subject: Football -- Juvenile fiction
ETextNum: 28728


FOUND BOOK 2:
Title: The Suffrage Cook Book
Creator: (no data found)
Subject: Women -- Suffrage -- United States
ETextNum: 26323


FOUND BOOK 3:
Title: The Life of King Edward VIIwith a sketch of the career of King George V
Creator: Hopkins, J. Castell (John Castell), 1864-1923
Subject: Edward VII, King of Great Britain, 1841-1910
ETextNum: 25112


FOUND BOOK 4:
Title: Milk for You and Me
Creator: Randell, Winifred
Subject: Milk as food -- Juvenile literature
ETextNum: 25552


FOUND BOOK 5:
Title: The Wonder
Creator: Beresford, J. D. (John Davys), 1873-1947
Subject: Science fiction
ETextNum: 27188


FOUND BOOK 6:
Title: The Traitors
Creator: Oppenheim, E. Phillips (Edward Phillips), 1866-1946
Subject: Spy stories
ETextNum: 29162


FOUND BOOK 7:
Title: Otherwise Phyllis
Creator: Nicholson, Meredith, 1866-1947
Subject: Indiana -- Fiction
ETextNum: 28017


FOUND BOOK 8:
Title: A Likely Story
Creator: Howells, William Dean, 1837-1920
Subject: American drama -- 19th century
ETextNum: 28305


FOUND BOOK 9:
Title: The Critic in the Orient
Creator: Fitch, George Hamlin, 1852-1925
Subject: Egypt -- Description and travel
ETextNum: 27233


FOUND BOOK 10:
Title: The Scottish Chiefs
Creator: Porter, Jane, 1776-1850
Subject: Scotland -- History -- War of Independence, 1285-1371 -- Fiction
ETextNum: 6086


FOUND BOOK 11:
Title: The Wonders of the Invisible WorldBeing an Account of the Tryals of Sever
al Witches LatelyExecuted in New-England, to which is added A Farther Accountof
the Tryals of the New-England Witches
Creator: Mather, Cotton, 1663-1728
Subject: Witchcraft -- New England -- Early works to 1800
ETextNum: 28513


FOUND BOOK 12:
Title: Told by the Northmen:Stories from the Eddas and Sagas
Creator: Wilmot-Buxton, E. M. (Ethel Mary)
Subject: Mythology, Norse
ETextNum: 29551


FOUND BOOK 13:
Title: Spiritual Torrents
Creator: Guyon, Jeanne Marie Bouvier de la Motte, 1648-1717
Subject: Mysticism
ETextNum: 25133


FOUND BOOK 14:
Title: Chambers's Edinburgh Journal, No. 441Volume 17, New Series, June 12, 1852

Creator: Various
Subject: Great Britain -- Social life and customs -- 19th century -- Periodicals

ETextNum: 24892


FOUND BOOK 15:
Title: Madcap
Creator: Gibbs, George, 1870-1942
Subject: (no data found)
ETextNum: 11584


FOUND BOOK 16:
Title: Ancient America, in Notes on American Archaeology
Creator: Baldwin, John D. (John Denison), 1809-1883
Subject: Indians -- Antiquities
ETextNum: 26382


FOUND BOOK 17:
Title: St. Nicholas Magazine for Boys and Girls, Vol. V,  August, 1878, No 10.Sc
ribner's Illustrated
Creator: Various
Subject: Children's literature -- Periodicals
ETextNum: 29983


FOUND BOOK 18:
Title: The Idiot
Creator: Dostoyevsky, Fyodor, 1821-1881
Subject: Russia -- Social life and customs -- 1533-1917 -- Fiction
ETextNum: 2638


FOUND BOOK 19:
Title: Goodbye, Dead Man!
Creator: Harris, Tom W.
Subject: Science fiction
ETextNum: 29963


FOUND BOOK 20:
Title: Good Stories for Holidays
Creator: Olcott, Frances Jenkins, 1872-1963
Subject: Children's literature
ETextNum: 359


FOUND BOOK 21:
Title: A Yeoman's LettersThird Edition
Creator: Ross, P. T.
Subject: South African War, 1899-1902 -- Personal narratives
ETextNum: 27765


FOUND BOOK 22:
Title:
Creator: Goodell, Abner Cheney, 1831-1914
Subject: Mark (Slave) -- Trials, litigation, etc.
ETextNum: 26446


FOUND BOOK 23:
Title: The Comings of Cousin Ann
Creator: Sampson, Emma Speed, 1868-1947
Subject: PS
ETextNum: 28439


FOUND BOOK 24:
Title: The Mascot of Sweet Briar Gulch
Creator: Phillips, Henry Wallace, 1869-1930
Subject: Miners -- Fiction
ETextNum: 25809




TESTING KNOWN FAILURES
Not found
Not found
Not found
Press any key to continue . . .

--------------------------------------------------------------------------------

catalog-short4.txt
4863

25 RANDOM BOOKS

BOOK 0:
Title: Representative Plays by American Dramatists: 1856-1911: Rip vanWinkle
Creator: Burke, Charles, 1822-1854
Subject: American drama
ETextNum: 27552


BOOK 1:
Title: The Starvation Treatment of Diabetes
Creator: Hill, Lewis Webb, 1889-1968
Subject: Diabetes
ETextNum: 26058


BOOK 2:
Title: A Tangled Tale
Creator: Carroll, Lewis, 1832-1898
Subject: Mathematical recreations
ETextNum: 29042


BOOK 3:
Title: The Strand Magazine, Volume V, Issue 26, February 1893An Illustrated Mont
hly
Creator: Various
Subject: AP
ETextNum: 30105


BOOK 4:
Title: Diana
Creator: Warner, Susan, 1819-1885
Subject: Women -- New England -- Fiction
ETextNum: 29824


BOOK 5:
Title: Waiting for Daylight
Creator: Tomlinson, H. M. (Henry Major), 1873-1958
Subject: PR
ETextNum: 27246


BOOK 6:
Title: The Most Sentimental Man
Creator: Smith, Evelyn E., 1927-2000
Subject: Science fiction
ETextNum: 29791


BOOK 7:
Title: Daughters of Doom
Creator: Livingston, Herbert B.
Subject: Science fiction
ETextNum: 25094


BOOK 8:
Title: The Prince of ParthiaA Tragedy
Creator: Godfrey, Thomas, 1736-1763
Subject: Tragedies
ETextNum: 29222


BOOK 9:
Title: Kalitan, Our Little Alaskan Cousin
Creator: Nixon-Roulet, Mary F., -1930
Subject: (no data found)
ETextNum: 10224


BOOK 10:
Title: The Story of a Mine
Creator: Harte, Bret, 1836-1902
Subject: American fiction -- 19th century
ETextNum: 2661


BOOK 11:
Title: Finnish Legends for English Children
Creator: Eivind, R.
Subject: Folklore -- Finland
ETextNum: 24948


BOOK 12:
Title: Sketches of the Natural History of Ceylon
Creator: Tennent, James Emerson, Sir, 1804-1869
Subject: Animals -- Sri Lanka
ETextNum: 13325


BOOK 13:
Title: The Roman Traitor (Vol. 2 of 2)
Creator: Herbert, Henry William, 1807-1858
Subject: Rome -- History -- Republic, 265-30 B.C. -- Fiction
ETextNum: 25096


BOOK 14:
Title: Archaeological Essays, Vol. 1
Creator: Simpson, James Young, Sir, 1811-1870
Subject: Archaeology
ETextNum: 27354


BOOK 15:
Title: The 2001 CIA World Factbook
Creator: United States. Central Intelligence Agency
Subject: World politics -- Handbooks, manuals, etc.
ETextNum: 27638


BOOK 16:
Title: The Cruise of the Shining Light
Creator: Duncan, Norman, 1871-1916
Subject: Orphans -- Fiction
ETextNum: 29696


BOOK 17:
Title: The Dance Festivals of the Alaskan Eskimo
Creator: Hawkes, Ernest William, 1883-
Subject: Indian dance -- North America
ETextNum: 26544


BOOK 18:
Title: Shipwreck in the Sky
Creator: Binder, Eando
Subject: Science fiction
ETextNum: 29133


BOOK 19:
Title: Little Brothers of the Air
Creator: Miller, Olive Thorne, 1831-1918
Subject: Birds
ETextNum: 27277


BOOK 20:
Title: The Hohokam Dig
Creator: Pratt, Theodore, 1901-1969
Subject: Science fiction
ETextNum: 29793


BOOK 21:
Title: Five Mice in a Mouse-trapby the Man in the Moon.
Creator: Richards, Laura Elizabeth Howe, 1850-1943
Subject: Children's stories
ETextNum: 29001


BOOK 22:
Title: Punch or the London Charivari, Vol. 147, October 7, 1914
Creator: Various
Subject: English wit and humor -- Periodicals
ETextNum: 28092


BOOK 23:
Title: Rugs: Oriental and Occidental, Antique &amp; ModernA Handbook for Ready R
eference
Creator: Holt, Rosa Belle
Subject: Rugs
ETextNum: 30025


BOOK 24:
Title: Brief Reflections relative to the Emigrant French Clergy
Creator: Burney, Fanny, 1752-1840
Subject: France -- History -- Revolution, 1789-1799 -- Religious aspects
ETextNum: 29125


ACCESS SAME BOOKS FROM HASH TABLE

FOUND BOOK 0:
Title: Representative Plays by American Dramatists: 1856-1911: Rip vanWinkle
Creator: Burke, Charles, 1822-1854
Subject: American drama
ETextNum: 27552


FOUND BOOK 1:
Title: The Starvation Treatment of Diabetes
Creator: Hill, Lewis Webb, 1889-1968
Subject: Diabetes
ETextNum: 26058


FOUND BOOK 2:
Title: A Tangled Tale
Creator: Carroll, Lewis, 1832-1898
Subject: Mathematical recreations
ETextNum: 29042


FOUND BOOK 3:
Title: The Strand Magazine, Volume V, Issue 26, February 1893An Illustrated Mont
hly
Creator: Various
Subject: AP
ETextNum: 30105


FOUND BOOK 4:
Title: Diana
Creator: Warner, Susan, 1819-1885
Subject: Women -- New England -- Fiction
ETextNum: 29824


FOUND BOOK 5:
Title: Waiting for Daylight
Creator: Tomlinson, H. M. (Henry Major), 1873-1958
Subject: PR
ETextNum: 27246


FOUND BOOK 6:
Title: The Most Sentimental Man
Creator: Smith, Evelyn E., 1927-2000
Subject: Science fiction
ETextNum: 29791


FOUND BOOK 7:
Title: Daughters of Doom
Creator: Livingston, Herbert B.
Subject: Science fiction
ETextNum: 25094


FOUND BOOK 8:
Title: The Prince of ParthiaA Tragedy
Creator: Godfrey, Thomas, 1736-1763
Subject: Tragedies
ETextNum: 29222


FOUND BOOK 9:
Title: Kalitan, Our Little Alaskan Cousin
Creator: Nixon-Roulet, Mary F., -1930
Subject: (no data found)
ETextNum: 10224


FOUND BOOK 10:
Title: The Story of a Mine
Creator: Harte, Bret, 1836-1902
Subject: American fiction -- 19th century
ETextNum: 2661


FOUND BOOK 11:
Title: Finnish Legends for English Children
Creator: Eivind, R.
Subject: Folklore -- Finland
ETextNum: 24948


FOUND BOOK 12:
Title: Sketches of the Natural History of Ceylon
Creator: Tennent, James Emerson, Sir, 1804-1869
Subject: Animals -- Sri Lanka
ETextNum: 13325


FOUND BOOK 13:
Title: The Roman Traitor (Vol. 2 of 2)
Creator: Herbert, Henry William, 1807-1858
Subject: Rome -- History -- Republic, 265-30 B.C. -- Fiction
ETextNum: 25096


FOUND BOOK 14:
Title: Archaeological Essays, Vol. 1
Creator: Simpson, James Young, Sir, 1811-1870
Subject: Archaeology
ETextNum: 27354


FOUND BOOK 15:
Title: The 2001 CIA World Factbook
Creator: United States. Central Intelligence Agency
Subject: World politics -- Handbooks, manuals, etc.
ETextNum: 27638


FOUND BOOK 16:
Title: The Cruise of the Shining Light
Creator: Duncan, Norman, 1871-1916
Subject: Orphans -- Fiction
ETextNum: 29696


FOUND BOOK 17:
Title: The Dance Festivals of the Alaskan Eskimo
Creator: Hawkes, Ernest William, 1883-
Subject: Indian dance -- North America
ETextNum: 26544


FOUND BOOK 18:
Title: Shipwreck in the Sky
Creator: Binder, Eando
Subject: Science fiction
ETextNum: 29133


FOUND BOOK 19:
Title: Little Brothers of the Air
Creator: Miller, Olive Thorne, 1831-1918
Subject: Birds
ETextNum: 27277


FOUND BOOK 20:
Title: The Hohokam Dig
Creator: Pratt, Theodore, 1901-1969
Subject: Science fiction
ETextNum: 29793


FOUND BOOK 21:
Title: Five Mice in a Mouse-trapby the Man in the Moon.
Creator: Richards, Laura Elizabeth Howe, 1850-1943
Subject: Children's stories
ETextNum: 29001


FOUND BOOK 22:
Title: Punch or the London Charivari, Vol. 147, October 7, 1914
Creator: Various
Subject: English wit and humor -- Periodicals
ETextNum: 28092


FOUND BOOK 23:
Title: Rugs: Oriental and Occidental, Antique &amp; ModernA Handbook for Ready R
eference
Creator: Holt, Rosa Belle
Subject: Rugs
ETextNum: 30025


FOUND BOOK 24:
Title: Brief Reflections relative to the Emigrant French Clergy
Creator: Burney, Fanny, 1752-1840
Subject: France -- History -- Revolution, 1789-1799 -- Religious aspects
ETextNum: 29125




TESTING KNOWN FAILURES
Not found
Not found
Not found
Press any key to continue . . .

CREATORKEY----------------------------------------------------------------------

catalog-short4.txt
4863

25 RANDOM BOOKS

BOOK 0:
Title: The Junior Classics ΓÇö Volume 4
Creator: (no data found)
Subject: (no data found)
ETextNum: 6323


BOOK 1:
Title: Captain Desmond, V.C.
Creator: Diver, Maud, 1867-1945
Subject: India -- History -- British occupation, 1765-1947 -- Fiction
ETextNum: 27629


BOOK 2:
Title: The Poems of Jonathan Swift, D.D., Volume 2
Creator: Swift, Jonathan, 1667-1745
Subject: (no data found)
ETextNum: 13621


BOOK 3:
Title: The Palace of Pleasure, Volume 1
Creator: Painter, William, 1540?-1594
Subject: (no data found)
ETextNum: 20241


BOOK 4:
Title: Senate Resolution 6; 41st Congress, 1st SessionA Bill to provide statione
ry for Congress and the severaldepartments, and for other purposes
Creator: United States. Congress. Senate
Subject: Bills, Legislative -- United States.
ETextNum: 27078


BOOK 5:
Title: I'm a Stranger Here Myself
Creator: Reynolds, Mack, 1917-1983
Subject: Science fiction
ETextNum: 26741


BOOK 6:
Title: The Fifth String
Creator: Sousa, John Philip, 1854-1932
Subject: Love stories
ETextNum: 29481


BOOK 7:
Title: Cutting It OutHow to get on the waterwagon and stay there
Creator: Blythe, Samuel G. (Samuel George), 1868-1947
Subject: Alcoholism
ETextNum: 28576


BOOK 8:
Title: Astounding Stories of Super-Science, June, 1930
Creator: Various
Subject: Science fiction -- Periodicals
ETextNum: 29848


BOOK 9:
Title: The story of my first novel; How a novel is written
Creator: Duchess, 1855?-1897
Subject: Authorship
ETextNum: 27622


BOOK 10:
Title: Rural Life and the Rural School
Creator: Kennedy, Joseph, 1858-1937
Subject: Country life
ETextNum: 29600


BOOK 11:
Title: Slow and SureThe Story of Paul Hoffman the Young Street-Merchant
Creator: Alger, Horatio, 1832-1899
Subject: Boys -- Conduct of life -- Juvenile fiction
ETextNum: 25151


BOOK 12:
Title: A Manual of Moral Philosophy
Creator: Peabody, Andrew P. (Andrew Preston), 1811-1893
Subject: Ethics
ETextNum: 27531


BOOK 13:
Title: The Space Rover
Creator: Sloat, Edwin K., 1895-1986
Subject: Science fiction
ETextNum: 29702


BOOK 14:
Title: Elkan Lubliner, American
Creator: Glass, Montague, 1877-1934
Subject: Jews -- New York (State) -- New York -- Fiction
ETextNum: 27423


BOOK 15:
Title: Henry IV, Makers of History
Creator: Abbott, John S. C. (John Stevens Cabot), 1805-1877
Subject: Henry IV, King of France, 1553-1610
ETextNum: 29603


BOOK 16:
Title: Notes and Queries, Number 218, December 31, 1853A Medium of Inter-communi
cation for Literary Men, Artists,Antiquaries, Genealogists, etc
Creator: Various
Subject: Questions and answers -- Periodicals
ETextNum: 29664


BOOK 17:
Title: Mayflower (Flor de mayo)A Tale of the Valencian Seashore
Creator: Blasco Ib├í├▒ez, Vicente, 1867-1928
Subject: PQ
ETextNum: 29577


BOOK 18:
Title: The Olive Fairy Book
Creator: (no data found)
Subject: Fairy tales
ETextNum: 27826


BOOK 19:
Title: Boy LifeStories and Readings Selected From The Works of William Dean Howe
lls
Creator: Howells, William Dean, 1837-1920
Subject: Boys
ETextNum: 25383


BOOK 20:
Title: An Apostate: Nawin of Thais
Creator: Sills, Steven (Steven David Justin)
Subject: PS
ETextNum: 25730


BOOK 21:
Title: State of the Union Addresses of John Quincy Adams
Creator: Adams, John Quincy, 1767-1848
Subject: Presidents -- United States -- Messages
ETextNum: 5015


BOOK 22:
Title: Lotus Buds
Creator: Carmichael, Amy, 1867-1951
Subject: Missions -- India
ETextNum: 29427


BOOK 23:
Title: Aurelianor, Rome in the Third Century
Creator: Ware, William, 1797-1852
Subject: (no data found)
ETextNum: 21953


BOOK 24:
Title: Great Men and Famous Women. Vol. 3 of 8A series of pen and pencil sketche
s of the lives of morethan 200 of the most prominent personages in History
Creator: (no data found)
Subject: Biography
ETextNum: 26423


ACCESS SAME BOOKS FROM HASH TABLE

FOUND BOOK 0:
Title: Dick and His Cat and Other Tales
Creator: (no data found)
Subject: Animals -- Juvenile fiction
ETextNum: 28351


FOUND BOOK 1:
Title: Captain Desmond, V.C.
Creator: Diver, Maud, 1867-1945
Subject: India -- History -- British occupation, 1765-1947 -- Fiction
ETextNum: 27629


FOUND BOOK 2:
Title: Gulliver's Travels
Creator: Swift, Jonathan, 1667-1745
Subject: Fantasy fiction
ETextNum: 28946


FOUND BOOK 3:
Title: The Palace of Pleasure, Volume 1
Creator: Painter, William, 1540?-1594
Subject: (no data found)
ETextNum: 20241


FOUND BOOK 4:
Title: Senate Resolution 6; 41st Congress, 1st SessionA Bill to provide statione
ry for Congress and the severaldepartments, and for other purposes
Creator: United States. Congress. Senate
Subject: Bills, Legislative -- United States.
ETextNum: 27078


FOUND BOOK 5:
Title: Ultima Thule
Creator: Reynolds, Mack, 1917-1983
Subject: Science fiction
ETextNum: 30334


FOUND BOOK 6:
Title: The Fifth String
Creator: Sousa, John Philip, 1854-1932
Subject: Love stories
ETextNum: 29481


FOUND BOOK 7:
Title: Cutting It OutHow to get on the waterwagon and stay there
Creator: Blythe, Samuel G. (Samuel George), 1868-1947
Subject: Alcoholism
ETextNum: 28576


FOUND BOOK 8:
Title: The American Missionary ΓÇö Volume 54, No. 3, October, 1900
Creator: Various
Subject: Congregational churches -- Missions -- Periodicals
ETextNum: 28712


FOUND BOOK 9:
Title: Only an Irish Girl
Creator: Duchess, 1855?-1897
Subject: PR
ETextNum: 27839


FOUND BOOK 10:
Title: Rural Life and the Rural School
Creator: Kennedy, Joseph, 1858-1937
Subject: Country life
ETextNum: 29600


FOUND BOOK 11:
Title: Ben, the Luggage Boy;or, Among the Wharves
Creator: Alger, Horatio, 1832-1899
Subject: Runaways -- Fiction
ETextNum: 28381


FOUND BOOK 12:
Title: A Manual of Moral Philosophy
Creator: Peabody, Andrew P. (Andrew Preston), 1811-1893
Subject: Ethics
ETextNum: 27531


FOUND BOOK 13:
Title: The Space Rover
Creator: Sloat, Edwin K., 1895-1986
Subject: Science fiction
ETextNum: 29702


FOUND BOOK 14:
Title: Elkan Lubliner, American
Creator: Glass, Montague, 1877-1934
Subject: Jews -- New York (State) -- New York -- Fiction
ETextNum: 27423


FOUND BOOK 15:
Title: Louis PhilippeMakers of History Series
Creator: Abbott, John S. C. (John Stevens Cabot), 1805-1877
Subject: Louis Philippe, King of the French, 1773-1850
ETextNum: 28199


FOUND BOOK 16:
Title: The American Missionary ΓÇö Volume 54, No. 3, October, 1900
Creator: Various
Subject: Congregational churches -- Missions -- Periodicals
ETextNum: 28712


FOUND BOOK 17:
Title: Mayflower (Flor de mayo)A Tale of the Valencian Seashore
Creator: Blasco Ib├í├▒ez, Vicente, 1867-1928
Subject: PQ
ETextNum: 29577


FOUND BOOK 18:
Title: Dick and His Cat and Other Tales
Creator: (no data found)
Subject: Animals -- Juvenile fiction
ETextNum: 28351


FOUND BOOK 19:
Title: A Likely Story
Creator: Howells, William Dean, 1837-1920
Subject: American drama -- 19th century
ETextNum: 28305


FOUND BOOK 20:
Title: Tokyo to Tijuana: Gabriele Departing America
Creator: Sills, Steven (Steven David Justin)
Subject: (no data found)
ETextNum: 12733


FOUND BOOK 21:
Title: State of the Union Addresses of John Quincy Adams
Creator: Adams, John Quincy, 1767-1848
Subject: Presidents -- United States -- Messages
ETextNum: 5015


FOUND BOOK 22:
Title: Things as They AreMission Work in Southern India
Creator: Carmichael, Amy, 1867-1951
Subject: Missions -- India
ETextNum: 29426


FOUND BOOK 23:
Title: Aurelianor, Rome in the Third Century
Creator: Ware, William, 1797-1852
Subject: (no data found)
ETextNum: 21953


FOUND BOOK 24:
Title: Dick and His Cat and Other Tales
Creator: (no data found)
Subject: Animals -- Juvenile fiction
ETextNum: 28351




TESTING KNOWN FAILURES
Not found
Not found
Not found
Press any key to continue . . .

--------------------------------------------------------------------------------

catalog-short4.txt
4863

25 RANDOM BOOKS

BOOK 0:
Title: Gone Fishing
Creator: Schmitz, James H., 1911-1981
Subject: Science fiction
ETextNum: 30140


BOOK 1:
Title: The Corsair King
Creator: J├│kai, M├│r, 1825-1904
Subject: PH
ETextNum: 26865


BOOK 2:
Title: ChelseaThe Fascination of London
Creator: Mitton, G. E. (Geraldine Edith)
Subject: Chelsea (London, England) -- Description and travel
ETextNum: 27356


BOOK 3:
Title: Punch, Or The London Charivari, Volume 101, July 11, 1891
Creator: Various
Subject: English wit and humor -- Periodicals
ETextNum: 13270


BOOK 4:
Title: It's a Small Solar System
Creator: Howard, Allan
Subject: Science fiction
ETextNum: 28437


BOOK 5:
Title: The Fight for the ArgonnePersonal Experiences of a 'Y' Man
Creator: West, William Benjamin
Subject: World War, 1914-1918 -- Personal narratives
ETextNum: 28060


BOOK 6:
Title: The Faust-Legend and Goethe's 'Faust'
Creator: Cotterill, H. B. (Henry Bernard), 1846-
Subject: Faust, d. ca. 1540 -- Legends
ETextNum: 25732


BOOK 7:
Title: Punch, or the London Charivari, Vol. 147, August 26th, 1914
Creator: Various
Subject: English wit and humor -- Periodicals
ETextNum: 26693


BOOK 8:
Title: Notes and Queries, Number 197, August 6, 1853A Medium of Inter-communicat
ion for Literary Men, Artists,Antiquaries, Genealogists, etc.
Creator: Various
Subject: Questions and answers -- Periodicals
ETextNum: 23235


BOOK 9:
Title: Oedipus King of ThebesTranslated into English Rhyming Verse with Explanat
ory Notes
Creator: Sophocles, 495? BC-406 BC
Subject: Tragedies
ETextNum: 27673


BOOK 10:
Title: Abraham Lincoln: a History ΓÇö Volume 01
Creator: Hay, John, 1835-1905
Subject: (no data found)
ETextNum: 6812


BOOK 11:
Title: Cossack Fairy Tales and Folk Tales
Creator: (no data found)
Subject: Fairy tales
ETextNum: 29672


BOOK 12:
Title: The Antichrist
Creator: Nietzsche, Friedrich Wilhelm, 1844-1900
Subject: Christianity -- Controversial literature
ETextNum: 28734


BOOK 13:
Title: The World English Bible (WEB): Nahum
Creator: Anonymous
Subject: (no data found)
ETextNum: 8261


BOOK 14:
Title: Repertory Of The Comedie Humaine, Complete, A ΓÇö Z
Creator: Christophe, Jules Fran├ºois, 1840-
Subject: (no data found)
ETextNum: 17635


BOOK 15:
Title: Blackwood's Edinburgh Magazine, Volume 56, Number 348
Creator: Various
Subject: AP
ETextNum: 25066


BOOK 16:
Title: Trial of Duncan Terig, alias Clerk, and Alexander Bane Macdonaldfor the M
urder of Arthur Davis, Sergeant in General Guise'sRegiment of Foot
Creator: Scott, Walter, Sir, 1771-1832
Subject: Trials (Murder) -- Scotland
ETextNum: 26133


BOOK 17:
Title: Security
Creator: Kenyon, Ernest M.
Subject: Short stories
ETextNum: 26140


BOOK 18:
Title: Elementary Theosophy
Creator: Rogers, L. W. (Louis William), 1859-1953
Subject: Theosophy
ETextNum: 30134


BOOK 19:
Title: The Proverbs of Scotland
Creator: Hislop, Alexander, 1807-1865
Subject: Proverbs, Scottish
ETextNum: 26150


BOOK 20:
Title: Bib Ballads
Creator: Lardner, Ring, 1885-1933
Subject: American poetry
ETextNum: 25961


BOOK 21:
Title: Hidden Hand
Creator: Southworth, Emma Dorothy Eliza Nevitte, 1819-1899
Subject: Women -- United States -- Fiction
ETextNum: 29866


BOOK 22:
Title: Lady Luck
Creator: Wiley, Hugh, 1884-
Subject: African Americans -- Fiction
ETextNum: 26165


BOOK 23:
Title: Last WordsA Final Collection of Stories
Creator: Ewing, Juliana Horatia Gatty, 1841-1885
Subject: Conduct of life -- Juvenile fiction
ETextNum: 25710


BOOK 24:
Title: Harper's Young People, February 3, 1880An Illustrated Weekly
Creator: Various
Subject: Children's periodicals, American
ETextNum: 28344


ACCESS SAME BOOKS FROM HASH TABLE

FOUND BOOK 0:
Title: Gone Fishing
Creator: Schmitz, James H., 1911-1981
Subject: Science fiction
ETextNum: 30140


FOUND BOOK 1:
Title: The Corsair King
Creator: J├│kai, M├│r, 1825-1904
Subject: PH
ETextNum: 26865


FOUND BOOK 2:
Title: The Children's Book of Stars
Creator: Mitton, G. E. (Geraldine Edith)
Subject: Astronomy -- Juvenile literature
ETextNum: 28853


FOUND BOOK 3:
Title: The American Missionary ΓÇö Volume 54, No. 3, October, 1900
Creator: Various
Subject: Congregational churches -- Missions -- Periodicals
ETextNum: 28712


FOUND BOOK 4:
Title: It's a Small Solar System
Creator: Howard, Allan
Subject: Science fiction
ETextNum: 28437


FOUND BOOK 5:
Title: The Fight for the ArgonnePersonal Experiences of a 'Y' Man
Creator: West, William Benjamin
Subject: World War, 1914-1918 -- Personal narratives
ETextNum: 28060


FOUND BOOK 6:
Title: The Faust-Legend and Goethe's 'Faust'
Creator: Cotterill, H. B. (Henry Bernard), 1846-
Subject: Faust, d. ca. 1540 -- Legends
ETextNum: 25732


FOUND BOOK 7:
Title: The American Missionary ΓÇö Volume 54, No. 3, October, 1900
Creator: Various
Subject: Congregational churches -- Missions -- Periodicals
ETextNum: 28712


FOUND BOOK 8:
Title: The American Missionary ΓÇö Volume 54, No. 3, October, 1900
Creator: Various
Subject: Congregational churches -- Missions -- Periodicals
ETextNum: 28712


FOUND BOOK 9:
Title: Oedipus King of ThebesTranslated into English Rhyming Verse with Explanat
ory Notes
Creator: Sophocles, 495? BC-406 BC
Subject: Tragedies
ETextNum: 27673


FOUND BOOK 10:
Title: Abraham Lincoln: a History ΓÇö Volume 01
Creator: Hay, John, 1835-1905
Subject: (no data found)
ETextNum: 6812


FOUND BOOK 11:
Title: Dick and His Cat and Other Tales
Creator: (no data found)
Subject: Animals -- Juvenile fiction
ETextNum: 28351


FOUND BOOK 12:
Title: On the Future of our Educational Institutions
Creator: Nietzsche, Friedrich Wilhelm, 1844-1900
Subject: Nietzsche, Friedrich Wilhelm, 1844-1900 -- Views on education
ETextNum: 28146


FOUND BOOK 13:
Title: The Ladies' Work-Table BookContaining Clear and Practical Instructions in
Plain andFancy Needlework, Embroidery, Knitting, Netting and Crochet
Creator: Anonymous
Subject: Crocheting
ETextNum: 29382


FOUND BOOK 14:
Title: Repertory Of The Comedie Humaine, Complete, A ΓÇö Z
Creator: Christophe, Jules Fran├ºois, 1840-
Subject: (no data found)
ETextNum: 17635


FOUND BOOK 15:
Title: The American Missionary ΓÇö Volume 54, No. 3, October, 1900
Creator: Various
Subject: Congregational churches -- Missions -- Periodicals
ETextNum: 28712


FOUND BOOK 16:
Title: The Fortunes of Nigel
Creator: Scott, Walter, Sir, 1771-1832
Subject: (no data found)
ETextNum: 5950


FOUND BOOK 17:
Title: Security
Creator: Kenyon, Ernest M.
Subject: Short stories
ETextNum: 26140


FOUND BOOK 18:
Title: Elementary Theosophy
Creator: Rogers, L. W. (Louis William), 1859-1953
Subject: Theosophy
ETextNum: 30134


FOUND BOOK 19:
Title: The Proverbs of Scotland
Creator: Hislop, Alexander, 1807-1865
Subject: Proverbs, Scottish
ETextNum: 26150


FOUND BOOK 20:
Title: Bib Ballads
Creator: Lardner, Ring, 1885-1933
Subject: American poetry
ETextNum: 25961


FOUND BOOK 21:
Title: Hidden Hand
Creator: Southworth, Emma Dorothy Eliza Nevitte, 1819-1899
Subject: Women -- United States -- Fiction
ETextNum: 29866


FOUND BOOK 22:
Title: Lady Luck
Creator: Wiley, Hugh, 1884-
Subject: African Americans -- Fiction
ETextNum: 26165


FOUND BOOK 23:
Title: Last WordsA Final Collection of Stories
Creator: Ewing, Juliana Horatia Gatty, 1841-1885
Subject: Conduct of life -- Juvenile fiction
ETextNum: 25710


FOUND BOOK 24:
Title: The American Missionary ΓÇö Volume 54, No. 3, October, 1900
Creator: Various
Subject: Congregational churches -- Missions -- Periodicals
ETextNum: 28712




TESTING KNOWN FAILURES
Not found
Not found
Not found
Press any key to continue . . .

*/
