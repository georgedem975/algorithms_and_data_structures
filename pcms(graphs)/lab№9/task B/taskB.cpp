#include <iostream>
#include <fstream>
#include <vector>

std::ifstream gFin("cycle.in");
std::ofstream gFout("cycle.out");

class Top
{
    public:
        Top(int newNumberOfTop);
        int GetNumberOfTop();
        ~Top();
        void SetOtherTops(int numberOfTop);
        int GetSize();
        int GetNumberOtherTops(int index);
        int GetNumberOfPPrevTop();
        void SetNumberOfPrevTop(int newNumberOfPrevTop);
        char GetColor();
        void SetColor(char newColor);

    private:
        int numberOfTop;
        int numberOfPrevTop;
        char color;
        std::vector<int> otherTops;
};

class Graph
{
    public:
        Graph(int sizeOfGraph);
        ~Graph();
        void  SetTops(int firstTop, int secondTop);
        int GetSize();
        int GetTopIndex(int index);
        void viewing();
        void bfs(int index);
        bool cycle = 0;
        int numberOfFirstTopInCycle;
        int n;
        void foutBfs(int index);
        std::vector<int> temp;

    private:
        std::vector<Top> tops;
        int size;
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
            graph.cycle = 1;
            gFout << "YES\n";
            gFout << x + 1;
            gFin.close();
            gFout.close();
            return 0;
        }
    }

    graph.viewing();

    if (graph.cycle)
    {
        gFout << "YES\n";
        graph.foutBfs(graph.numberOfFirstTopInCycle);
        int temp = graph.temp.size();
        for (int i = 0; i < temp; ++i)
        {
            gFout << graph.temp.back() << " ";
            graph.temp.pop_back();
        }
    }
    else
    {
        gFout << "NO\n";
    }

    gFin.close();
    gFout.close();

    return 0;
}

int Top::GetNumberOfPPrevTop()
{
    return this->numberOfPrevTop;
}

void Top::SetNumberOfPrevTop(int newNumberOfPrevTop)
{
    this->numberOfPrevTop = newNumberOfPrevTop;
}

char Top::GetColor()
{
    return this->color;
}

void Top::SetColor(char newColor)
{
    this->color = newColor;
}

Top::Top(int newNumberOfTop)
{
    this->numberOfTop = newNumberOfTop;
    this->color = 'w';
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

Graph::Graph(int sizeOfGraph)
{
    for (int i = 1; i <= sizeOfGraph; i++)
    {
        Top top(i);
        this->tops.push_back(top);
    }
    this->size = 0;
}

void Graph::SetTops(int firstTop, int secondTop)
{
    this->tops[firstTop].SetOtherTops(secondTop);
}

Graph::~Graph() {}

void Graph::viewing()
{
    for (int i = 0; i < this->tops.size(); i++)
    {
        if (this->tops[i].GetColor() == 'w' && !this->cycle)
        {
            this->n = i;
            this->tops[i].SetColor('r');
            this->bfs(i);
        }
    }
}

void Graph::bfs(int index)
{
    for (int i = 0; i < this->tops[index].GetSize(); i++)
    {
        if (this->tops[this->tops[index].GetNumberOtherTops(i)].GetColor() == 'r' && !this->cycle)
        {
            this->cycle = 1;
            this->numberOfFirstTopInCycle = index;
            this->n = this->tops[index].GetNumberOtherTops(i);
        }
        if (this->tops[this->tops[index].GetNumberOtherTops(i)].GetColor() == 'w' && !this->cycle)
        {
            this->tops[this->tops[index].GetNumberOtherTops(i)].SetNumberOfPrevTop(index);
            this->tops[this->tops[index].GetNumberOtherTops(i)].SetColor('r');
            this->bfs(this->tops[index].GetNumberOtherTops(i));
        }
    }
    if (!this->cycle)
    {
        this->tops[index].SetColor('b');
    }
}

void Graph::foutBfs(int index)
{
    temp.push_back(index + 1);
    if (this->tops[index].GetNumberOfPPrevTop() != this->n)
    {
        this->foutBfs(this->tops[index].GetNumberOfPPrevTop());
    }
    else
    {
        temp.push_back(this->tops[index].GetNumberOfPPrevTop() + 1);
    }
}