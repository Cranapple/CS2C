//FHFLOWGRAPH.H-----------------------------------------------------------------
#ifndef FHFLOWGRAPH_H
#define FHFLOWGRAPH_H
#include <limits.h>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <iostream>
#include <functional>
using namespace std;

template <class Object, typename CostType>
class FHflowVertex
{
   typedef FHflowVertex<Object, CostType>* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;

public:
   static int nSortKey;
   static stack<int> keyStack;
   static enum { SORT_BY_DATA, SORT_BY_DIST } eSortType;
   static bool setNSortType( int whichType );
   static void pushSortKey() { keyStack.push(nSortKey); }
   static void popSortKey() { nSortKey = keyStack.top(); keyStack.pop(); }

   static int const INFINITY_FH = INT_MAX;
   EdgePairList flowAdjList;
   EdgePairList resAdjList;
   Object data;
   CostType dist;
   VertPtr nextInPath;

   FHflowVertex( const Object & x = Object() );

   void addToFlowAdjList(VertPtr neighbor, CostType cost);
   void addToResAdjList(VertPtr neighbor, CostType cost);
   bool operator<( const FHflowVertex<Object, CostType> & rhs) const;
   const FHflowVertex<Object, CostType> & operator=
      ( const FHflowVertex<Object, CostType> & rhs);
   void showFlowAdjList();
   void showResAdjList();
};

template <class Object, typename CostType>
int FHflowVertex<Object, CostType>::nSortKey 
   = FHflowVertex<Object, CostType>::SORT_BY_DATA;

template <class Object, typename CostType>
stack<int> FHflowVertex<Object, CostType>::keyStack;

template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::setNSortType( int whichType )
{
   switch (whichType)
   {
   case SORT_BY_DATA:
   case SORT_BY_DIST:
      nSortKey = whichType;
      return true;
   default:
      return false;
   }
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>::FHflowVertex( const Object & x) 
   : data(x), dist((CostType)INFINITY_FH),
   nextInPath(NULL)
{
   // nothing to do
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::addToFlowAdjList
(FHflowVertex<Object, CostType> *neighbor, CostType cost)
{
   flowAdjList[neighbor] = cost;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::addToResAdjList
(FHflowVertex<Object, CostType> *neighbor, CostType cost)
{
   resAdjList[neighbor] = cost;
}

template <class Object, typename CostType>
bool FHflowVertex<Object, CostType>::operator<(
   const FHflowVertex<Object, CostType> & rhs) const
{
   switch (nSortKey)
   {
   case SORT_BY_DIST:
      return (dist < rhs.dist);
   case SORT_BY_DATA:
      return (data < rhs.data);
   default:
      return false;
   }
}

template <class Object, typename CostType>
const FHflowVertex<Object, CostType> & FHflowVertex<Object, CostType>::operator=(
   const FHflowVertex<Object, CostType> & rhs)
{
   resAdjList = rhs.resAdjList;
   flowAdjList = rhs.flowAdjList;
   data = rhs.data;
   dist = rhs.dist;
   nextInPath = rhs.nextInPath;;
   return *this;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showFlowAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Adj Flow List for " << data << ": ";
   for (iter = flowAdjList.begin(); iter != flowAdjList.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}

template <class Object, typename CostType>
void FHflowVertex<Object, CostType>::showResAdjList()
{
   typename EdgePairList::iterator iter;

   cout << "Adj Res List for " << data << ": ";
   for (iter = resAdjList.begin(); iter != resAdjList.end(); ++iter)
      cout << iter->first->data << "(" << iter->second << ") ";
   cout << endl;
}

template <class Object, typename CostType>
class FHflowGraph
{
   typedef FHflowVertex<Object, CostType> Vertex;
   typedef FHflowVertex<Object, CostType>* VertPtr;
   typedef map<VertPtr, CostType> EdgePairList;
   typedef set<VertPtr> VertPtrSet;
   typedef set<Vertex> VertexSet;

private:
   VertPtrSet vertPtrSet;
   VertexSet vertexSet;
   VertPtr startVertPtr, endVertPtr;

public:
   FHflowGraph() { startVertPtr = nullptr; endVertPtr = nullptr; }
   void addEdge(const Object &source, const Object &dest, CostType cost);
   VertPtr addToVertexSet(const Object & object);
   void showFlowAdjTable();
   void showResAdjTable();
   void clear();
   bool setStartVert(const Object &x);
   bool setEndVert(const Object &x);

   // algorithms
   CostType findMaxFlow();

private:
   bool establishNextFlowPath();
   CostType getLimitingFlowOnResPath();
   bool adjustPathByCost(CostType cost);
   CostType getCostOfResEdge(VertPtr src, VertPtr dst);
   bool addCostToResEdge(VertPtr src, VertPtr dst, CostType cost);
   bool addCostToFlowEdge(VertPtr src, VertPtr dst, CostType cost);

   VertPtr getVertexWithThisData(const Object & x);
};

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::addToVertexSet(
   const Object & object)
{
   pair<typename VertexSet::iterator, bool> retVal;
   VertPtr vPtr;

   Vertex::pushSortKey();
   Vertex::setNSortType(Vertex::SORT_BY_DATA);

   retVal = vertexSet.insert( Vertex(object) );

   vPtr = (VertPtr)&*retVal.first;
   vertPtrSet.insert(vPtr);

   Vertex::popSortKey();
   return vPtr;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::clear()
{
   vertexSet.clear();
   vertPtrSet.clear();
   startVertPtr = nullptr;
   endVertPtr = nullptr;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::addEdge(
   const Object &source, const Object &dest, CostType cost )
{
   VertPtr src, dst;

   src = addToVertexSet(source);
   dst = addToVertexSet(dest);

   src->addToResAdjList(dst, cost);
   dst->addToResAdjList(src, 0);
   src->addToFlowAdjList(dst, 0);
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showFlowAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
      (*iter)->showFlowAdjList();
   cout << endl;
}

template <class Object, typename CostType>
void FHflowGraph<Object, CostType>::showResAdjTable()
{
   typename VertPtrSet::iterator iter;

   cout << "------------------------ \n";
   for (iter = vertPtrSet.begin(); iter != vertPtrSet.end(); ++iter)
      (*iter)->showResAdjList();
   cout << endl;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setStartVert(const Object &x)
{
   startVertPtr = getVertexWithThisData(x);
   if (startVertPtr)
      return true;
   else
      return false;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::setEndVert(const Object &x)
{
   endVertPtr = getVertexWithThisData(x);
   if (endVertPtr)
      return true;
   else
      return false;
}

template <class Object, typename CostType>
FHflowVertex<Object, CostType>* FHflowGraph<Object, CostType>::
   getVertexWithThisData(const Object & x)
{
   typename VertexSet::iterator findResult;
   Vertex vert(x);

   Vertex::pushSortKey();
   Vertex::setNSortType(Vertex::SORT_BY_DATA);
   findResult = vertexSet.find(vert);
   Vertex::popSortKey();

   if ( findResult == vertexSet.end() )
      return NULL;
   return  (VertPtr)&*findResult;
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::findMaxFlow()
{
   CostType limitResFlow;
   while (establishNextFlowPath())
   {
      limitResFlow = getLimitingFlowOnResPath();
      adjustPathByCost(limitResFlow);
   }

   CostType totalFlow = NULL;
   typename EdgePairList::iterator iter;
   
   for (iter = startVertPtr->flowAdjList.begin(); 
      iter != startVertPtr->flowAdjList.end(); ++iter)
      totalFlow += iter->second;
   
   return totalFlow;

}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::establishNextFlowPath()
{
   typename VertPtrSet::iterator vIter;
   typename EdgePairList::iterator edgePrIter;
   VertPtr wPtr, vPtr;
   CostType costVW;
   queue<VertPtr> partiallyProcessedVerts;

   if (startVertPtr == NULL)
      return false;

   for (vIter = vertPtrSet.begin(); vIter != vertPtrSet.end(); ++vIter)
   {
      (*vIter)->dist = Vertex::INFINITY_FH;
      (*vIter)->nextInPath = NULL;
   }

   startVertPtr->dist = 0;
   partiallyProcessedVerts.push(startVertPtr); 

   while (!partiallyProcessedVerts.empty())
   {
      vPtr = partiallyProcessedVerts.front();
      partiallyProcessedVerts.pop();

      for (edgePrIter = vPtr->resAdjList.begin();
         edgePrIter != vPtr->resAdjList.end();
         edgePrIter++)
      {
         wPtr = edgePrIter->first;
         costVW = edgePrIter->second;
         if (!(costVW == 0) && vPtr->dist + costVW < wPtr->dist)
         {
            wPtr->dist = vPtr->dist + costVW;
            wPtr->nextInPath = vPtr;

            if (wPtr == endVertPtr)
               return true;

            partiallyProcessedVerts.push(wPtr);
         }
      }
   }
   return false;
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getLimitingFlowOnResPath()
{
   VertPtr vp;
   CostType minFlow, tempEdgeCost;
   
   if (startVertPtr == NULL || endVertPtr == NULL
      || endVertPtr->nextInPath == NULL)
      return NULL;

   vp = endVertPtr->nextInPath;
   minFlow = getCostOfResEdge(vp, endVertPtr);
   for ( ; vp != startVertPtr; vp = vp->nextInPath)
   {
      if (vp->nextInPath == NULL)
      {
         return NULL;
      }
      tempEdgeCost = getCostOfResEdge(vp->nextInPath, vp);
      if (tempEdgeCost < minFlow)
         minFlow = tempEdgeCost;
   }

   return minFlow;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::adjustPathByCost(CostType cost)
{
   VertPtr vp;

   if (startVertPtr == NULL || endVertPtr == NULL || cost == NULL)
      return false;

   for (vp = endVertPtr; vp != startVertPtr; vp = vp->nextInPath)
   {
      if (vp->nextInPath == NULL)
      {
         return false;
      }
      addCostToResEdge(vp->nextInPath, vp, -cost);
      addCostToResEdge(vp, vp->nextInPath, cost);
      addCostToFlowEdge(vp->nextInPath, vp, cost);
   }

   return true;
}

template <class Object, typename CostType>
CostType FHflowGraph<Object, CostType>::getCostOfResEdge(
   VertPtr src, VertPtr dst)
{
   if (src == NULL || dst == NULL)
      return NULL;

   return src->resAdjList[dst];
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToResEdge(
   VertPtr src, VertPtr dst, CostType cost)
{
   if (src == NULL || dst == NULL || cost == NULL)
      return false;

   if (src->resAdjList[dst] += cost)
      return true;
   else
      return false;
}

template <class Object, typename CostType>
bool FHflowGraph<Object, CostType>::addCostToFlowEdge(
   VertPtr src, VertPtr dst, CostType cost)
{
   if (src == NULL || dst == NULL || cost == NULL)
      return false;

   try
   {
      src->flowAdjList.at(dst);
   }
   catch (...)
   {
      src->flowAdjList[dst] -= cost;
      return true;
   }

   src->flowAdjList[dst] += cost;
   return true;
}

#endif