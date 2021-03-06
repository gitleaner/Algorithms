/**
 Question 1
 Download the text file here. Zipped version here. (Right click and save link as)
 The file contains the edges of a directed graph. Vertices are labeled as positive integers from 1 to 875714. Every row indicates an edge, the vertex label in first column is the tail and the vertex label in second column is the head (recall the graph is directed, and the edges are directed from the first column vertex to the second column vertex). So for example, the 11th row looks liks : "2 47646". This just means that the vertex with label 2 has an outgoing edge to the vertex with label 47646
 
 Your task is to code up the algorithm from the video lectures for computing strongly connected components (SCCs), and to run this algorithm on the given graph.
 
 Output Format: You should output the sizes of the 5 largest SCCs in the given graph, in decreasing order of sizes, separated by commas (avoid any spaces). So if your algorithm computes the sizes of the five largest SCCs to be 500, 400, 300, 200 and 100, then your answer should be "500,400,300,200,100". If your algorithm finds less than 5 SCCs, then write 0 for the remaining terms. Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100, then your answer should be "400,300,100,0,0".
 
 WARNING: This is the most challenging programming assignment of the course. Because of the size of the graph you may have to manage memory carefully. The best way to do this depends on your programming language and environment, and we strongly suggest that you exchange tips for doing this on the discussion forums.
 **/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <utility>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

bool compare (int x, int y) { return (x>y); }

void tokenizeBySpace (string line, int &startVertex, int &edge)
{
    int str;
    bool foundVertex=false;
    stringstream s(line);
    while (s >> str)
    {
        if (!foundVertex)
        {
            startVertex = str;
            foundVertex = true;
        }
        else
            edge = str;
    }
}

class graph {
private:
    map <int, list<int> > adjList;
    map <int, list<int> > adjListRev;
    map <int, bool> discovered;
    map <int, int> finishTimes;
    map <int, int> leaderOfThisVertex;
    map <int, bool> numNodes;
    map <int, bool> numNodesRev;
    
    map <int, int> leaderCount;
    int vertexCount;
    
    void initializeGraphVars ()
    {
        for (map<int, bool>::iterator mapIter = discovered.begin(); mapIter != discovered.end(); mapIter++)
            mapIter->second = false;
        
        for (map<int, int>::iterator mIter = finishTimes.begin(); mIter != finishTimes.end(); mIter++)
            mIter->second = 0;
        
        for (map<int, int>::iterator lIter = leaderOfThisVertex.begin(); lIter != leaderOfThisVertex.end(); lIter++)
            lIter->second = -1;
    }
    
    int numEdges()
    {
        int countEdges = 0;
        for (map<int, list<int> >::iterator iter=adjList.begin(); iter != adjList.end(); iter++)
        {
            countEdges += iter->second.size();
        }
        return countEdges;
    }
    
    int numEdgesRev()
    {
        int countEdges = 0;
        for (map<int, list<int> >::iterator iter=adjListRev.begin(); iter != adjListRev.end(); iter++)
        {
            countEdges += iter->second.size();
        }
        return countEdges;
    }
    
    int numEdges(int vertA)
    {
        return adjList[vertA].size();
    }
    
    int numVertices()
    {
        return numNodes.size();
    }
    
    int numVerticesRev()
    {
        return numNodesRev.size();
    }
    
    void printFinishTimes()
    {
        int max = 0; int min = 1000000;
        for (map<int, int>::iterator mIter=finishTimes.begin(); mIter!=finishTimes.end(); mIter++)
        {
            cout << mIter->first <<  " " << mIter->second << endl;
            if (mIter->second > max)
                max = mIter->second;
            if (mIter->second < min)
                min = mIter->second;
        }
        cout << "Max is : :: " << max << endl;
        cout << "Min is : :: " << min << endl;
    }
    
   
    
    void printLeader()
    {
        for (map<int, int>::iterator mIter = leaderOfThisVertex.begin(); mIter != leaderOfThisVertex.end(); mIter++)
        {
            cout << mIter->first << " " << mIter->second << endl;
            if (leaderCount.find (mIter->second) != leaderCount.end())
                leaderCount[mIter->second]++;
            else
                leaderCount.insert (make_pair(mIter->second, 1));
        }
        cout << "Num Leader count :: " << leaderCount.size() << endl;
        
        vector<int> countVec;
        for (map<int, int>::iterator mapIter=leaderCount.begin(); mapIter != leaderCount.end(); mapIter++)
        {
            countVec.push_back(mapIter->second);
        }
        sort (countVec.begin(), countVec.end(), compare);
        for (size_t i=0; (i<5) && (i<countVec.size()); i++)
            cout << countVec[i] << " ";
        cout << endl;
    }
    
public:
    graph();
    ~graph();
    void print();
    void reverseGraph();
    void printGraphReverse();
    void dfs_loop_rev();
    void dfs_loop();
    void dfs(int startVertex, int curSrcVertex);
    void dfsRev(int startVertex, int curSrcVertex);
    void replaceVertexWithFinishTimes();
};

graph::graph()
{
    /* Initialize graph here */
    fstream fread("SCC.txt");
    //fstream fread ("1.txt");
    int edge=0;
    list<int> edgeList;
    int startVertex; int count=0;
    
    while (!fread.eof())
    {
        string line;
        getline (fread, line);
        tokenizeBySpace (line, startVertex, edge);
        
        if (adjList.find(startVertex) != adjList.end())
        {
            adjList[startVertex].push_back(edge);
            if (!numNodes[edge])
                numNodes.insert (make_pair (edge, true));
        }
        else
        {
            edgeList.push_back (edge);
            adjList.insert (make_pair(startVertex, edgeList));
            
            if (!numNodes[startVertex])
                numNodes.insert (make_pair (startVertex, true));
            
            if (!numNodes[edge])
                numNodes.insert (make_pair (edge, true));

            
            discovered.insert (make_pair(startVertex, false));
            finishTimes.insert(make_pair(startVertex, 0));
            leaderOfThisVertex.insert (make_pair(startVertex, -1));
            edgeList.clear();
        }
    }
    //print();
    reverseGraph();
    vertexCount = 0;
}

void graph::print()
{
    for (map<int, list<int> >::iterator iter=adjList.begin(); iter != adjList.end(); iter++)
    {
        cout << iter->first << " ";
        for (list<int>::iterator locIter=iter->second.begin(); locIter != iter->second.end(); locIter++)
            cout << *locIter << "  ";
        cout << endl;
    }
    
    cout << " Num Edges :: " << numEdges() << endl;
    cout << " Num Vertices :: "  << numVertices() << endl;
}

void graph::printGraphReverse()
{
    for (map<int, list<int> >::iterator iter=adjListRev.begin(); iter != adjListRev.end(); iter++)
    {
        cout << iter->first << " ";
        for (list<int>::iterator locIter=iter->second.begin(); locIter != iter->second.end(); locIter++)
            cout << *locIter << "  ";
        cout << endl;
    }
    
    cout << " Num Edges :: " << numEdgesRev() << endl;
    cout << " Num Vertices :: "  << numVerticesRev() << endl;
}


void graph::reverseGraph()
{
    list<int> reverseEdgeList;
    for (map<int, list<int> >::iterator mapIter=adjList.begin(); mapIter != adjList.end(); mapIter++)
    {
        for (list<int>::iterator listIter=mapIter->second.begin(); listIter!=mapIter->second.end(); listIter++)
        {
            if (adjListRev.find(*listIter) == adjListRev.end())
            {
                reverseEdgeList.push_back(mapIter->first);
                adjListRev.insert (make_pair(*listIter, reverseEdgeList));
                
                if (!numNodesRev[*listIter])
                    numNodesRev.insert (make_pair(*listIter, true));
                
                if (!numNodesRev[mapIter->first])
                    numNodesRev.insert (make_pair(mapIter->first, true));
                
                reverseEdgeList.clear();
            }
            else
            {
                adjListRev[*listIter].push_back(mapIter->first);
                if (!numNodesRev[mapIter->first])
                    numNodesRev.insert (make_pair(mapIter->first, true));

            }
        }
    }
}

void graph::replaceVertexWithFinishTimes()
{
    for (map<int, list<int> >::iterator mIter = adjList.begin(); mIter != adjList.end(); mIter++)
    {
        for (list<int>::iterator lIter = mIter->second.begin(); lIter != mIter->second.end(); lIter++)
        {
            *lIter = finishTimes[*lIter];
        }
    }
    map<int, list<int> > tmpAdjList;
    
    for (map<int, int>::iterator fIter = finishTimes.begin(); fIter != finishTimes.end(); fIter++)
    {
        tmpAdjList.insert (make_pair(fIter->second, adjList[fIter->first]));
    }
    
    for (map<int, list<int> >::iterator mapIter = adjList.begin();mapIter != adjList.end(); mapIter++)
    {
        mapIter->second.clear();
    }
    adjList.clear();
    
    adjList = tmpAdjList ;
}


void graph::dfs_loop_rev()
{
    initializeGraphVars();
    vertexCount = 0;
    for (int i=numVertices(); i>=1 ; i--)
    {
        if (!discovered[i])
        {
            dfsRev(i,i);
        }
    }
    //printFinishTimes();
}

void graph::dfsRev(int startVertex, int curSrcVertex)
{
    discovered[startVertex] = true;
    leaderOfThisVertex[startVertex] = curSrcVertex;
    for (list<int>::iterator listIter = adjListRev[startVertex].begin(); listIter != adjListRev[startVertex].end(); listIter++)
    {
        if (!discovered[*listIter])
        {
            dfsRev (*listIter, curSrcVertex);
        }
    }
    vertexCount++;
    finishTimes[startVertex] = vertexCount;
}

void graph::dfs_loop()
{
    initializeGraphVars();
    vertexCount = 0;
    
    for (int i=numVertices(); i>=1; i--)
    {
        if (!discovered[i])
            dfs(i, i);
    }
    printLeader();
}

void graph::dfs(int startVertex, int curSrcVertex)
{
    discovered[startVertex] = true;
    leaderOfThisVertex[startVertex] = curSrcVertex;
    for (list<int>::iterator listIter = adjList[startVertex].begin(); listIter != adjList[startVertex].end(); listIter++)
    {
        if (!discovered[*listIter])
        {
            dfs (*listIter, curSrcVertex);
        }
    }
    vertexCount++;
    finishTimes[startVertex] = vertexCount;
}

graph::~graph()
{
    for (map<int, list<int> >::iterator mapIter = adjList.begin();mapIter != adjList.end(); mapIter++)
    {
        mapIter->second.clear();
    }
    adjList.clear();
}

int main()
{
int x;
    graph g;
    //g.print();   cin >> x;
    //g.printGraphReverse();
    g.dfs_loop_rev();
    g.replaceVertexWithFinishTimes();
    g.print(); cin >> x;
    g.dfs_loop();
    return 1;
}

