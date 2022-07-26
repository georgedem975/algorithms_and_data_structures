#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
 
class Top
{
    public:
        Top(int newNumberOfTop);
        int GetNumberOfTop();
        ~Top();
        int GetDegree();
        void SetDegree(int newDegree);
        void SetOtherTops(int numberOfTop);
        int GetSize();
        int GetNumberOtherTops(int index);

    private:
        int numberOfTop;
        int degree;
        std::vector<int> otherTops;
};
 
class Graph
{
    public:
        Graph(int sizeOfGraph);
        ~Graph();
        void  SetTops(int firstTop, int secondTop);
        void GetIstok();
        void topSort();
        int GetSize();
        int GetTopIndex(int index);
        void viewing();

    private:
        std::vector<Top> tops;
        std::vector<int> sortedTops;
        int size;
        std::queue<int> istok;
};
 
int main()
{
    std::ifstream fin("topsort.in");
    std::ofstream fout("topsort.out");
 
    int v, e;
 
    fin >> v >> e;
 
    Graph graph(v);
 
    int x, y;
    for (int i = 0; i < e; i++)
    {
        fin >> x >> y;
        graph.SetTops(--x, --y);
    }
 
    graph.viewing();
 
    if (graph.GetSize() < v)
    {
        fout << -1;
    }
    else
    {
        for (int i = 0; i < graph.GetSize(); i++)
        {
            fout << graph.GetTopIndex(i) << " ";
        }
    }
 
    fin.close();
    fout.close();
 
    return 0;
}
 
Top::Top(int newNumberOfTop)
{
    this->numberOfTop = newNumberOfTop;
    this->degree = 0;
}
 
Top::~Top() {}
 
int Top::GetNumberOfTop()
{
    return this->numberOfTop;
}
 
int Top::GetDegree()
{
    return this->degree;
}
 
void Top::SetDegree(int newDegree)
{
    this->degree = newDegree;
}
 
void Top::SetOtherTops(int numberOfTop)
{
    this->otherTops.push_back(numberOfTop);
}
 
int Top::GetSize()
{
    return this->otherTops.size();
}
 
int Top::GetNumberOtherTops(int index)
{
    return this->otherTops[index];
}
 
Graph::Graph(int sizeOfGraph)
{
    for (int i = 1; i <= sizeOfGraph; i++)
    {
        Top NEW(i);
        this->tops.push_back(NEW);
    }
    this->size = 0;
}
 
void Graph::SetTops(int firstTop, int secondTop)
{
    this->tops[firstTop].SetOtherTops(secondTop);
    this->tops[secondTop].SetDegree((this->tops[secondTop].GetDegree() + 1));
}
 
Graph::~Graph() {}
 
void Graph::GetIstok()
{
    for (int i = 0; i < this->tops.size(); i++)
    {
        if (this->tops[i].GetDegree() == 0)
        {
            this->istok.push(this->tops[i].GetNumberOfTop());
        }
    }
}
 
void Graph::topSort()
{
    int temp = this->istok.front();
    this->sortedTops.push_back(temp);
    this->istok.pop();
    this->size++;
    int temp2 = temp - 1;
    this->tops[temp2].SetDegree(-1);
    for (int i = 0; i < this->tops[temp2].GetSize(); ++i)
    {
        this->tops[this->tops[temp2].GetNumberOtherTops(i)].SetDegree((this->tops[this->tops[temp2].GetNumberOtherTops(i)].GetDegree() - 1));
        if (this->tops[this->tops[temp2].GetNumberOtherTops(i)].GetDegree() == 0)
        {
            this->istok.push(this->tops[temp2].GetNumberOtherTops(i) + 1);
        }
    }
}
 
void Graph::viewing()
{
    this->GetIstok();
    while (!this->istok.empty())
    {
        this->topSort();
    }
}
 
int Graph::GetSize()
{
    return this->size;
}
 
int Graph::GetTopIndex(int index)
{
    return this->sortedTops[index];
}