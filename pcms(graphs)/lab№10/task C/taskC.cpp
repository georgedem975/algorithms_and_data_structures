#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
 
enum Color
{
    Open,
    Close
};
 
class Top
{
    public:
        Top(int newNumberOfTop);
        int GetNumberOfTop();
        int GetSizeOfComponent();
        int GetMainTopInComponentNumber();
        Color GetModificator();
        void SetNumberOfTop(int newNumberOfTop);
        void SetSizeOfComponent(int newSizeOfComponent);
        void SetModificator(Color newModificator);
        void SetMainTopInComponentNumber(int newMainTopInComponentNumber);
        int mainTopInComponentNumber;
    private:
        int numberOftop;
        int sizeOfComponent;
        Color modificator;
};
 
class Adge
{
    public:
        Adge(int newNumberOfFirstTop, int newNumberOfSecondTop, int newLengthOfAdge);
        int GetNumberOfFirstTop();
        int GetNumberOfSecondTop();
        int GetLengthOfAdge();
    private:
        int numberOfFirstTop;
        int numberOfSecondTop;
        int lengthOfAdge;
};
 
class Graph
{
    public:
        friend class Top;
        Graph(int newCounterOfTops, int newCounterOfAdges);
        void addAdges(int newNumberOfFirstTop, int newNumberOfSecondTop, int newLengthOfAdge);
        int GetNumberOfMainTop(int numberThatTop);
        long long GetLenhthOfMinimalSpanningTree();
    private:
        int counterOfTops;
        int counterOfAdges;
        std::vector<Top> tops;
        std::vector<Adge> adges;
};
 
int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
 
    std::ifstream fin("spantree3.in");
    std::ofstream fout("spantree3.out");
 
    int counterOfTops, counterOfAdges;
 
    fin >> counterOfTops >> counterOfAdges;
 
    Graph graph(counterOfTops, counterOfAdges);
 
    int newNumberOfFirstTop, newNumberOfSecondTop, newLengthOfAdge;
    for (int i = 0; i < counterOfAdges; i++)
    {
        fin >> newNumberOfFirstTop >> newNumberOfSecondTop >> newLengthOfAdge;
        newNumberOfFirstTop -= 1;
        newNumberOfSecondTop -= 1;
        graph.addAdges(newNumberOfFirstTop, newNumberOfSecondTop, newLengthOfAdge);
    }
 
    fout << graph.GetLenhthOfMinimalSpanningTree();
 
    fin.close();
    fout.close();
 
    return 0;
}

Graph::Graph(int newCounterOfTops, int newCounterOfAdges)
{
    this->counterOfTops = newCounterOfTops;
    this->counterOfAdges = newCounterOfAdges;
    for (int i = 0; i < counterOfTops; i++)
    {
        Top newTopInTops(i);
        this->tops.push_back(newTopInTops);
    }
}
 
void Graph::addAdges(int newNumberOfFirstTop, int newNumberOfSecondTop, int newLengthOfAdge)
{
    Adge newAdgeInAdges(newNumberOfFirstTop, newNumberOfSecondTop, newLengthOfAdge);
    this->adges.push_back(newAdgeInAdges);
}
 
Top::Top(int newNumberOfTop)
{
    this->numberOftop = newNumberOfTop;
    this->sizeOfComponent = 1;
    this->mainTopInComponentNumber = this->numberOftop;
    this->modificator = Open;
}
 
int Top::GetNumberOfTop()
{
    return this->numberOftop;
}
 
int Top::GetSizeOfComponent()
{
    return this->sizeOfComponent;
}
 
Color Top::GetModificator()
{
    return this->modificator;
}
 
void Top::SetNumberOfTop(int newNumberOfTop)
{
    this->numberOftop = newNumberOfTop;
}
 
void Top::SetSizeOfComponent(int newSizeOfComponent)
{
    this->sizeOfComponent = newSizeOfComponent;
}
 
void Top::SetModificator(Color newModificator)
{
    this->modificator = newModificator;
}
 
Adge::Adge(int newNumberOfFirstTop, int newNumberOfSecondTop, int newLengthOfAdge)
{
    this->lengthOfAdge = newLengthOfAdge;
    this->numberOfFirstTop = newNumberOfFirstTop;
    this->numberOfSecondTop = newNumberOfSecondTop;
}
 
int Adge::GetLengthOfAdge()
{
    return this->lengthOfAdge;
}
 
int Adge::GetNumberOfFirstTop()
{
    return this->numberOfFirstTop;
}
 
int Adge::GetNumberOfSecondTop()
{
    return this->numberOfSecondTop;
}
 
int Top::GetMainTopInComponentNumber()
{
    return this->mainTopInComponentNumber;
}
 
void Top::SetMainTopInComponentNumber(int newMainTopInComponentNumber)
{
    this->mainTopInComponentNumber = newMainTopInComponentNumber;
}
 
int Graph::GetNumberOfMainTop(int numberThatTop)
{
    if (this->tops[numberThatTop].GetMainTopInComponentNumber() != this->tops[numberThatTop].GetNumberOfTop())
    {
        return this->GetNumberOfMainTop(this->tops[numberThatTop].GetMainTopInComponentNumber());
    }
    return this->tops[numberThatTop].GetNumberOfTop();
}
 
long long Graph::GetLenhthOfMinimalSpanningTree()
{
    long long lenhthOfMinimalSpanningTree = 0;
    std::sort(this->adges.begin(), this->adges.end(),  [] (Adge a, Adge b) {return a.GetLengthOfAdge() < b.GetLengthOfAdge();});
    
    int counter = 0;
    int index = 0;
    while (counter != this->counterOfTops - 1)
    {
        int NumberOfMainTopOfFirstTop = this->GetNumberOfMainTop(this->tops[this->adges[index].GetNumberOfFirstTop()].GetNumberOfTop());
        int NumberOfMainTopOfSecondTop = this->GetNumberOfMainTop(this->tops[this->adges[index].GetNumberOfSecondTop()].GetNumberOfTop());
        if (NumberOfMainTopOfFirstTop != NumberOfMainTopOfSecondTop)
        {
            if (this->tops[NumberOfMainTopOfSecondTop].GetSizeOfComponent() < this->tops[NumberOfMainTopOfFirstTop].GetSizeOfComponent())
            {
                this->tops[NumberOfMainTopOfSecondTop].SetMainTopInComponentNumber(NumberOfMainTopOfFirstTop);
                this->tops[NumberOfMainTopOfFirstTop].SetSizeOfComponent(this->tops[NumberOfMainTopOfFirstTop].GetSizeOfComponent() + 
                this->tops[NumberOfMainTopOfSecondTop].GetSizeOfComponent());
            }
            else
            {
                this->tops[NumberOfMainTopOfFirstTop].SetMainTopInComponentNumber(NumberOfMainTopOfSecondTop);
                this->tops[NumberOfMainTopOfSecondTop].SetSizeOfComponent(this->tops[NumberOfMainTopOfFirstTop].GetSizeOfComponent() +
                this->tops[NumberOfMainTopOfSecondTop].GetSizeOfComponent());
            }
            lenhthOfMinimalSpanningTree += this->adges[index].GetLengthOfAdge();
            counter++;
        }
        index++;
    }
    return lenhthOfMinimalSpanningTree;
}