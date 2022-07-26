#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
 
std::ifstream gFin("bipartite.in");
std::ofstream gFout("bipartite.out");
 
enum Color
{
    White,
    Black
};
 
class Top
{
    public:
        Top(int newNumberOfTop);
        int GetNumberOfTop();
        ~Top();
        void SetOtherTops(int numberOfTop);
        int GetSize();
        int GetNumberOtherTops(int index);
        Color GetColor();
        void SetColor(Color newColor);
        int GetModificator();
        void SetModificator(int newModificator);

    private:
        int modificator;
        int numberOfTop;
        Color topColor;
        std::vector<int> otherTops;
};
 
class Graph
{
    public:
        Graph(int sizeOfGraph);
        ~Graph();
        void  SetTops(int firstTop, int secondTop);
        void viewing();
        void bfs(int index);
        bool GetFlag();
        void SetFlag();

    private:
        std::vector<Top> tops;
        bool flagOfTwo;
};
 
int main()
{
    int v, e;
 
    gFin >> v >> e;
 
    Graph graph(v);
 
    int x, y;
    for (int i = 0; i < e; i++)
    {
        gFin >> x >> y;
        graph.SetTops(--x, --y);
        if (x == y)
        {
            gFout << "NO\n";
            gFin.close();
            gFout.close();
            return 0;
        }
    }
 
    graph.viewing();
 
    if (graph.GetFlag())
    {
        gFout << "NO";
    }
    else
    {
        gFout << "YES";
    }
 
    gFin.close();
    gFout.close();
 
    return 0;
}
 
Color Top::GetColor()
{
    return this->topColor;
}
 
void Top::SetColor(Color newColor)
{
    this->topColor = newColor;
}
 
Top::Top(int newNumberOfTop)
{
    this->numberOfTop = newNumberOfTop;
    this->topColor = White;
    this->modificator = 0;
}
 
Top::~Top() {}
 
int Top::GetNumberOfTop()
{
    return this->numberOfTop;
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
 
int Top::GetModificator()
{
    return this->modificator;
}
 
void Top::SetModificator(int newModificator)
{
    this->modificator = newModificator;
}
 
Graph::Graph(int sizeOfGraph)
{
    for (int i = 1; i <= sizeOfGraph; i++)
    {
        Top top(i);
        this->tops.push_back(top);
    }
    this->flagOfTwo = 0;
}
 
void Graph::SetTops(int firstTop, int secondTop)
{
    this->tops[firstTop].SetOtherTops(secondTop);
    this->tops[secondTop].SetOtherTops(firstTop);
}
 
Graph::~Graph() {}
 
bool Graph::GetFlag()
{
    return this->flagOfTwo;
}
 
void Graph::SetFlag()
{
    this->flagOfTwo = !(this->flagOfTwo);
}
 
void Graph::viewing()
{
    for (int i = 0; i < this->tops.size() && !this->flagOfTwo; i++)
    {
        if (this->tops[i].GetColor() == White)
        {
            this->bfs(i);
        }
    }
}
 
void Graph::bfs(int index)
{
    std::queue<int> pointPosition;
    pointPosition.push(index);
    while (!pointPosition.empty() && !this->flagOfTwo)
    {
        int thatPosition = pointPosition.front();
        pointPosition.pop();
        for (int i = 0; i < this->tops[thatPosition].GetSize(); i++)
        {
            if (this->tops[this->tops[thatPosition].GetNumberOtherTops(i)].GetColor() == White)
            {
                this->tops[this->tops[thatPosition].GetNumberOtherTops(i)].SetColor(Black);
                this->tops[this->tops[thatPosition].GetNumberOtherTops(i)].SetModificator(
                        this->tops[thatPosition].GetModificator() + 1);
                pointPosition.push(this->tops[thatPosition].GetNumberOtherTops(i));
            }
            else if (this->tops[this->tops[thatPosition].GetNumberOtherTops(i)].GetModificator() % 2 ==
            this->tops[thatPosition].GetModificator() % 2)
            {
                this->flagOfTwo = 1;
            }
        }
        this->tops[thatPosition].SetColor(Black);
    }
}