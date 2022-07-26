#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

enum Mark
{
    Open,
    Close
};

class Top
{
    public:
        Top(unsigned int numberOfNewTop);
        unsigned int GetNumberOfTop();
        void addEdgesToOtherTops(unsigned int numberOfOtherTop, unsigned int lenOfEdge);
        std::pair<unsigned int, unsigned int> GetEdgeToOtherTopsByIndex(unsigned int index);
        unsigned int GetLenToThisTop();
        void SetLenToThisTop(unsigned int newLenToThisTop);
        unsigned int GetCountEdges();
        Mark GetModifier();
        void SetModifier(Mark newModifier);

    private:
        unsigned int numberOfTop;
        std::vector<std::pair<unsigned int, unsigned int>> edgesToOtherTops;
        unsigned int lenToThisTop;
        Mark modifier;
};

class Graph
{
    public:
        Graph(int sizeOfNewGraph);
        Top& GetTopByIndex(int index);
        unsigned int GetSizeOfGraph();
        void dijkstra();

    private:
        std::vector<Top> tops;
        unsigned int sizeOfGraph;
};

int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    std::ifstream fin("pathbgep.in");
    std::ofstream fout("pathbgep.out");

    unsigned int counterOfVertex, counterOfEdges;

    fin >> counterOfVertex >> counterOfEdges;

    Graph graph(counterOfVertex);

    unsigned int firstTop, secondTop, lenBetweenTops;
    for (int i = 0; i < counterOfEdges; i++)
    {
        fin >> firstTop >> secondTop >> lenBetweenTops;
        firstTop -= 1;
        secondTop -= 1;
        graph.GetTopByIndex(firstTop).addEdgesToOtherTops(secondTop, lenBetweenTops);
        graph.GetTopByIndex(secondTop).addEdgesToOtherTops(firstTop, lenBetweenTops);
    }

    graph.dijkstra();

    for (int i = 0; i < graph.GetSizeOfGraph(); i++)
    {
        fout << graph.GetTopByIndex(i).GetLenToThisTop() << " ";
    }

    fin.close();
    fout.close();

    return 0;
}

unsigned int Top::GetNumberOfTop()
{
    return this->numberOfTop;
}

Top::Top(unsigned int numberOfNewTop)
{
    this->numberOfTop = numberOfNewTop;
    this->lenToThisTop = UINT_MAX;
    this->modifier = Open;
}

void Top::addEdgesToOtherTops(unsigned int numberOfOtherTop, unsigned int lenOfEdge)
{
    std::pair<unsigned int, unsigned int> temp;
    temp.first = numberOfOtherTop;
    temp.second = lenOfEdge;
    this->edgesToOtherTops.push_back(temp);
}

std::pair<unsigned int, unsigned int> Top::GetEdgeToOtherTopsByIndex(unsigned int index)
{
    return this->edgesToOtherTops[index];
}

unsigned int Top::GetLenToThisTop()
{
    return this->lenToThisTop;
}

void Top::SetLenToThisTop(unsigned int newLenToThisTop)
{
    this->lenToThisTop = newLenToThisTop;
}

Graph::Graph(int sizeOfNewGraph)
{
    this->sizeOfGraph = sizeOfNewGraph;
    for (int i = 0; i < this->sizeOfGraph; i++)
    {
        Top temp(i);
        this->tops.push_back(temp);
    }
}

Top& Graph::GetTopByIndex(int index)
{
    return this->tops[index];
}

unsigned int Graph::GetSizeOfGraph()
{
    return this->sizeOfGraph;
}

unsigned int Top::GetCountEdges()
{
    return this->edgesToOtherTops.size();
}

Mark Top::GetModifier()
{
    return this->modifier;
}

void Top::SetModifier(Mark newModifier)
{
    this->modifier = newModifier;
}

void Graph::dijkstra()
{
    this->tops[0].SetLenToThisTop(0);
    std::set<std::pair<unsigned int, unsigned int>> priorityQ;
    priorityQ.insert(std::pair<unsigned int, unsigned int>(0, 0));
    while (!priorityQ.empty())
    {
        unsigned int numberTop = priorityQ.begin()->second;
        priorityQ.erase(priorityQ.begin());
        for (int i = 0; i < this->tops[numberTop].GetCountEdges(); i++)
        {
            if (this->tops[this->tops[numberTop].GetEdgeToOtherTopsByIndex(i).first].GetModifier() == Open &&
            this->tops[this->tops[numberTop].GetEdgeToOtherTopsByIndex(i).first].GetLenToThisTop() >
            this->tops[numberTop].GetLenToThisTop() + this->tops[numberTop].GetEdgeToOtherTopsByIndex(i).second)
            {
                unsigned int newLen = this->tops[numberTop].GetLenToThisTop() + this->tops[numberTop].GetEdgeToOtherTopsByIndex(i).second;
                this->tops[this->tops[numberTop].GetEdgeToOtherTopsByIndex(i).first].SetLenToThisTop(newLen);
                priorityQ.insert(std::pair<unsigned int, unsigned int>(newLen, this->tops[numberTop].GetEdgeToOtherTopsByIndex(i).first));
            }
        }
        this->tops[numberTop].SetModifier(Close);
    }
}