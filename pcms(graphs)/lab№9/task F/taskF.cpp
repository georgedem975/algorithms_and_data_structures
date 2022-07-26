#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
 
class Top
{
    public:
        Top(int newNumberOfTop);
        ~Top();
        void SetOtherTops(int numberOfTop);
        int GetSize();
        int GetNumberOtherTops(int index);
        int GetStok();
        void SetStok();
        char GetMark();
        void SetMark(char newMark);
        bool TopMarkTwo = 1;

    private:
        char topMark;
        bool stok = 1;
        std::vector<int> otherTops;
};
 
class Graph
{
    public:
        Graph(int sizeOfGraph);
        ~Graph();
        void  SetTops(int firstTop, int secondTop);
        void GetStok();
        void viewing();
        void loseOrWin();
        char GetMarkIndex(int index);

    private:
        std::vector<Top> tops;
        std::queue<int> stok;
};
 
int main()
{
    std::ifstream fin("game.in");
    std::ofstream fout("game.out");
 
    int v, e, firstPosition;
 
    fin >> v >> e >> firstPosition;
 
    Graph graph(v);
 
    int x, y;
    for (int i = 0; i < e; i++)
    {
        fin >> x >> y;
        graph.SetTops(--x, --y);
    }
 
    graph.viewing();
 
    if (graph.GetMarkIndex(--firstPosition) == 'l')
    {
        fout << "Second player wins";
    }
    else
    {
        fout << "First player wins";
    }
 
    fin.close();
    fout.close();
 
    return 0;
}
 
char Graph::GetMarkIndex(int index)
{
    return this->tops[index].GetMark();
}
 
Top::Top(int newNumberOfTop)
{
    this->topMark = 'l';
}
 
Top::~Top() {}
 
int Top::GetStok()
{
    return this->stok;
}
 
void Top::SetStok()
{
    this->stok = 0;
}
 
void Top::SetOtherTops(int NumberOfTop)
{
    this->otherTops.push_back(NumberOfTop);
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
        Top top(i);
        this->tops.push_back(top);
    }
}
 
void Graph::SetTops(int firstTop, int secondTop)
{
    this->tops[secondTop].SetOtherTops(firstTop);
    this->tops[firstTop].SetStok();
}
 
Graph::~Graph() {}
 
void Graph::GetStok()
{
    for (int i = 0; i < this->tops.size(); i++)
    {
        if (this->tops[i].GetStok())
        {
            this->stok.push(i);
        }
    }
}
 
void Graph::viewing()
{
    this->GetStok();
    while (!this->stok.empty())
    {
        loseOrWin();
    }
}
 
char Top::GetMark()
{
    return this->topMark;
}
 
void Top::SetMark(char newMark)
{
    this->topMark = newMark;
}
 
void Graph::loseOrWin()
{
    int temp = this->stok.front();
    this->stok.pop();
    for (int i = 0; i < this->tops[temp].GetSize(); i++)
    {
        if (this->tops[temp].GetMark() == 'l')
        {
            this->tops[this->tops[temp].GetNumberOtherTops(i)].SetMark('w');
        }
        if (this->tops[this->tops[temp].GetNumberOtherTops(i)].TopMarkTwo)
        {
            this->stok.push(this->tops[temp].GetNumberOtherTops(i));
            this->tops[this->tops[temp].GetNumberOtherTops(i)].TopMarkTwo = 0;
        }
    }
}