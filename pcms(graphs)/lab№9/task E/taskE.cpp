#include <iostream>
#include <fstream>
#include <vector>
  
std::ifstream gFin("hamiltonian.in");
std::ofstream gFout("hamiltonian.out");
  
enum Color
{
    White,
    Red,
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
        void SetTopsToTop(int numberOfTop);
        int GetNumberTopsToTop(int index);
        int GetSizeTopsToTop();
        int GetNumberOfComponent();
        void SetNumberOfComponent(int newNumberOfComponent);
        int modificatorIn = 0;
        int modificatorOut = 0;

    private:
        int modificator;
        int numberOfComponent;
        int numberOfTop;
        Color topColor;
        std::vector<int> otherTops;
        std::vector<int> topsToTop;
};
 
class Graph
{
    public:
        Graph(int sizeOfGraph);
        ~Graph();
        void  SetTops(int firstTop, int secondTop);
        void viewing();
        void dfs(int index);
        bool GetFlag();
        void SetFlag();
        void lastBfs(int index);
        int GetMaxComponent();
        int GetTopsComponent(int index);
        int GetModificatorInOfTop(int index);
        int GetModificatorOutOfTop(int index);
        bool check(int index);

    private:
        std::vector<int> numbersOfBfs;
        std::vector<Top> tops;
        int maxComponent;
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
    }
 
    int counterOne = 0;
    int counterTwo = 0;
 
    bool flag = true;
 
    for (int i = 0; i < v; i++)
    {
        if (graph.GetModificatorInOfTop(i) == 0)
        {
            counterOne++;
        }
        if (graph.GetModificatorOutOfTop(i) == 0)
        {
            counterTwo++;
        }
        if (graph.GetModificatorOutOfTop(i) > 1)
        {
            flag = graph.check(i);
        }
    }
 
    if ((counterOne != 1 || counterTwo != 1) && (v != 1 || v == 0) || !flag)
    {
        gFout << "NO\n";
    }
    else
    {
        gFout << "YES\n";
    }
 
    gFin.close();
    gFout.close();
 
    return 0;
}
 
bool Graph::check(int index) 
{
    for (int i = 0; i < this->tops[index].GetSize(); i++) 
    {
        if (this->tops[this->tops[index].GetNumberOtherTops(i)].modificatorOut != 1 ||
        this->tops[this->tops[index].GetNumberOtherTops(i)].modificatorIn != 1)
        {
            return true;
        }
    }
    return false;
}
 
int Graph::GetModificatorInOfTop(int index)
{
    return this->tops[index].modificatorIn;
}
 
int Graph::GetModificatorOutOfTop(int index)
{
    return this->tops[index].modificatorOut;
}
 
int Graph::GetTopsComponent(int index)
{
    return this->tops[index].GetNumberOfComponent();
}
 
int Top::GetNumberOfComponent()
{
    return this->numberOfComponent;
}
 
void Top::SetNumberOfComponent(int newNumberOfComponent)
{
    this->numberOfComponent = newNumberOfComponent;
}
 
int Top::GetNumberTopsToTop(int index)
{
    return this->topsToTop[index];
}
 
void Top::SetTopsToTop(int numberOfTop)
{
    this->topsToTop.push_back(numberOfTop);
}
 
int Top::GetSizeTopsToTop()
{
    return this->topsToTop.size();
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
    this->numberOfComponent = 0;
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
    this->maxComponent = 0;
}
 
void Graph::SetTops(int firstTop, int secondTop)
{
    this->tops[firstTop].SetOtherTops(secondTop);
    this->tops[secondTop].SetTopsToTop(firstTop);
    this->tops[firstTop].modificatorOut++;
    this->tops[secondTop].modificatorIn++;
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
 
int Graph::GetMaxComponent()
{
    return this->maxComponent;
}
 
void Graph::viewing()
{
    for (int i = 0; i < this->tops.size(); i++)
    {
        if (this->tops[i].GetColor() == White)
        {
            this->dfs(i);
        }
    }
 
    for (int i = this->tops.size() - 1; i >= 0; i--)
    {
        if (this->tops[numbersOfBfs[i]].GetColor() == Red)
        {
            this->lastBfs(numbersOfBfs[i]);
            this->maxComponent++;
        }
    }
}
 
void Graph::dfs(int index)
{
    this->tops[index].SetColor(Red);
    for (int i = 0; i < this->tops[index].GetSize(); i++)
    {
        if (this->tops[this->tops[index].GetNumberOtherTops(i)].GetColor() == White)
        {
            this->dfs(this->tops[index].GetNumberOtherTops(i));
        }
    }
    this->numbersOfBfs.push_back(index);
}
 
void Graph::lastBfs(int index)
{
    this->tops[index].SetColor(Black);
    this->tops[index].SetNumberOfComponent(this->maxComponent + 1);
    for (int i = 0; i < this->tops[index].GetSizeTopsToTop(); i++)
    {
        if (this->tops[this->tops[index].GetNumberTopsToTop(i)].GetColor() == Red)
        {
            this->lastBfs(this->tops[index].GetNumberTopsToTop(i));
        }
    }
}