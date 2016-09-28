//MAIN--------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "FHflowGraph.h"
using namespace std;

int main()
{
   int finalFlow;
   FHflowGraph<string, int> myG;

   myG.addEdge("s", "a", 3);    myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1);    myG.addEdge("a", "c", 3); myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 2);
   myG.addEdge("d", "t", 3);

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   cout << '\n' << "---------------------------------------------"
      << '\n' << '\n';

   myG.clear();
   myG.addEdge("s", "a", 4); myG.addEdge("s", "b", 2);
   myG.addEdge("a", "b", 1); myG.addEdge("a", "c", 2); myG.addEdge("a", "d", 4);
   myG.addEdge("b", "d", 2);
   myG.addEdge("c", "t", 3);
   myG.addEdge("d", "t", 3);

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   cout << '\n' << "---------------------------------------------"
      << '\n' << '\n';

   myG.clear();
   myG.addEdge("s", "A", 1); myG.addEdge("s", "D", 4); myG.addEdge("s", "G", 6);
   myG.addEdge("A", "B", 2); myG.addEdge("A", "E", 2);
   myG.addEdge("B", "C", 2);
   myG.addEdge("C", "t", 4);
   myG.addEdge("D", "E", 3); myG.addEdge("D", "A", 3);
   myG.addEdge("E", "C", 2); myG.addEdge("E", "F", 3); myG.addEdge("E", "I", 3);
   myG.addEdge("F", "C", 1); myG.addEdge("F", "t", 3);
   myG.addEdge("G", "D", 2); myG.addEdge("G", "E", 1); myG.addEdge("G", "H", 6);
   myG.addEdge("H", "E", 2); myG.addEdge("H", "I", 6);
   myG.addEdge("I", "F", 1); myG.addEdge("I", "t", 4);

   myG.showResAdjTable();
   myG.showFlowAdjTable();

   myG.setStartVert("s");
   myG.setEndVert("t");
   finalFlow = myG.findMaxFlow();

   cout << "Final flow: " << finalFlow << endl;

   myG.showResAdjTable();
   myG.showFlowAdjTable();

}

//TEST RUN----------------------------------------------------------------------
/*
------------------------
Adj Res List for s: a(3) b(2)
Adj Res List for a: s(0) b(1) c(3) d(4)
Adj Res List for b: s(0) a(0) d(2)
Adj Res List for c: a(0) t(2)
Adj Res List for d: a(0) b(0) t(3)
Adj Res List for t: c(0) d(0)

------------------------
Adj Flow List for s: a(0) b(0)
Adj Flow List for a: b(0) c(0) d(0)
Adj Flow List for b: d(0)
Adj Flow List for c: t(0)
Adj Flow List for d: t(0)
Adj Flow List for t:

Final flow: 5
------------------------
Adj Res List for s: a(0) b(0)
Adj Res List for a: s(3) b(1) c(1) d(3)
Adj Res List for b: s(2) a(0) d(0)
Adj Res List for c: a(2) t(0)
Adj Res List for d: a(1) b(2) t(0)
Adj Res List for t: c(2) d(3)

------------------------
Adj Flow List for s: a(3) b(2)
Adj Flow List for a: b(0) c(2) d(1)
Adj Flow List for b: d(2)
Adj Flow List for c: t(2)
Adj Flow List for d: t(3)
Adj Flow List for t:


---------------------------------------------

------------------------
Adj Res List for s: a(4) b(2)
Adj Res List for a: s(0) d(4) b(1) c(2)
Adj Res List for d: a(0) t(3) b(0)
Adj Res List for t: d(0) c(0)
Adj Res List for b: s(0) a(0) d(2)
Adj Res List for c: a(0) t(3)

------------------------
Adj Flow List for s: a(0) b(0)
Adj Flow List for a: d(0) b(0) c(0)
Adj Flow List for d: t(0)
Adj Flow List for t:
Adj Flow List for b: d(0)
Adj Flow List for c: t(0)

Final flow: 5
------------------------
Adj Res List for s: a(1) b(0)
Adj Res List for a: s(3) d(3) b(1) c(0)
Adj Res List for d: a(1) t(0) b(2)
Adj Res List for t: d(3) c(2)
Adj Res List for b: s(2) a(0) d(0)
Adj Res List for c: a(2) t(1)

------------------------
Adj Flow List for s: a(3) b(2)
Adj Flow List for a: d(1) b(0) c(2)
Adj Flow List for d: t(3)
Adj Flow List for t:
Adj Flow List for b: d(2)
Adj Flow List for c: t(2)


---------------------------------------------

------------------------
Adj Res List for H: I(6) E(2) G(0)
Adj Res List for I: H(0) E(0) t(4) F(1)
Adj Res List for s: A(1) D(4) G(6)
Adj Res List for A: s(0) B(2) E(2) D(0)
Adj Res List for B: A(0) C(2)
Adj Res List for E: H(0) I(3) A(0) C(2) F(3) D(0) G(0)
Adj Res List for C: B(0) E(0) t(4) F(0)
Adj Res List for t: I(0) C(0) F(0)
Adj Res List for F: I(0) E(0) C(1) t(3)
Adj Res List for D: s(0) A(3) E(3) G(0)
Adj Res List for G: H(6) s(0) E(1) D(2)

------------------------
Adj Flow List for H: I(0) E(0)
Adj Flow List for I: t(0) F(0)
Adj Flow List for s: A(0) D(0) G(0)
Adj Flow List for A: B(0) E(0)
Adj Flow List for B: C(0)
Adj Flow List for E: I(0) C(0) F(0)
Adj Flow List for C: t(0)
Adj Flow List for t:
Adj Flow List for F: C(0) t(0)
Adj Flow List for D: A(0) E(0)
Adj Flow List for G: H(0) E(0) D(0)

Final flow: 11
------------------------
Adj Res List for H: I(5) E(0) G(3)
Adj Res List for I: H(1) E(3) t(0) F(1)
Adj Res List for s: A(0) D(0) G(0)
Adj Res List for A: s(1) B(0) E(0) D(3)
Adj Res List for B: A(2) C(0)
Adj Res List for E: H(2) I(0) A(2) C(0) F(0) D(3) G(1)
Adj Res List for C: B(2) E(2) t(0) F(0)
Adj Res List for t: I(4) C(4) F(3)
Adj Res List for F: I(0) E(3) C(1) t(0)
Adj Res List for D: s(4) A(0) E(0) G(2)
Adj Res List for G: H(3) s(6) E(0) D(0)

------------------------
Adj Flow List for H: I(1) E(2)
Adj Flow List for I: t(4) F(0)
Adj Flow List for s: A(1) D(4) G(6)
Adj Flow List for A: B(2) E(2)
Adj Flow List for B: C(2)
Adj Flow List for E: I(3) C(2) F(3)
Adj Flow List for C: t(4)
Adj Flow List for t:
Adj Flow List for F: C(0) t(3)
Adj Flow List for D: A(3) E(3)
Adj Flow List for G: H(3) E(1) D(2)

Press any key to continue . . .
*/