#include <iostream>
#include <fstream>
#include <vector>

enum Color
{
    NotDefined,
    Unavailable,
    InANegativeCycle,
    Achievable
};

class Top
{
    public:
        Top(long long newNumberOfTop);
        long long GetNumberOfTop();
        long long GetLenToTop();
        long long GetCountOfTops();
        Color GetMarkOfTop();
        std::pair<long long, long long> GetEdgeByIndex(long long index);
        void addEdge(long long secondTopNumber, long long lenOfEdge);
        void SetLenToTop(long long newLenToTop);
        void SetMarkOfTop(Color newMarkOfTop);

    private:
        long long numberOfTop;
        long long lenToTop;
        std::vector<std::pair<long long, long long>> edges;
        Color mark;
};

class Graph
{
    public:
        Graph(long long countOfTops);
        long long GetCountOfTopsInGraph();
        Top& GetTopByIndex(long long index);
        void dfs(long long index);
        void dfsForCycle(long long index);
        void fordBellman(long long numberOfStartTop);

    private:
        std::vector<Top> topsInGraph;
};

int main()
{
    std::ifstream fin("path.in");
    std::ofstream fout("path.out");

    long long countOfVertex = 0, countOfEdges = 0, numberOfStartTop = -1;

    fin >> countOfVertex >> countOfEdges >> numberOfStartTop;
    numberOfStartTop--;

    Graph graph(countOfVertex);

    long long firstTopNumber, secondTopNumber;
    long long lenBetweenTops;
    for (long long i = 0; i < countOfEdges; i++)
    {
        fin >> firstTopNumber >> secondTopNumber >> lenBetweenTops;
        firstTopNumber--;
        secondTopNumber--;
        graph.GetTopByIndex(firstTopNumber).addEdge(secondTopNumber, lenBetweenTops);
    }

    graph.dfs(numberOfStartTop);

    graph.fordBellman(numberOfStartTop);

    for (long long i = 0; i < graph.GetCountOfTopsInGraph(); i++)
    {
        if (graph.GetTopByIndex(i).GetMarkOfTop() == NotDefined)
        {
            fout << "*\n";
        }
        else if (graph.GetTopByIndex(i).GetMarkOfTop() == InANegativeCycle)
        {
            fout << "-\n";
        }
        else
        {
            fout << graph.GetTopByIndex(i).GetLenToTop() << std::endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}

Top::Top(long long newNumberOfTop)
{
    this->lenToTop = 9e18;
    this->mark = NotDefined;
    this->numberOfTop = newNumberOfTop;
}

long long Top::GetLenToTop()
{
    return this->lenToTop;
}

void Top::SetLenToTop(long long newLenToTop)
{
    this->lenToTop = newLenToTop;
}

void Top::addEdge(long long secondTopNumber, long long lenOfEdge)
{
    std::pair<long long, long long> temp;
    temp.first = secondTopNumber;
    temp.second = lenOfEdge;
    this->edges.push_back(temp);
}

long long Top::GetNumberOfTop()
{
    return this->numberOfTop;
}

long long Top::GetCountOfTops()
{
    return this->edges.size();
}

std::pair<long long, long long> Top::GetEdgeByIndex(long long index)
{
    return this->edges[index];
}

Color Top::GetMarkOfTop()
{
    return this->mark;
}

void Top::SetMarkOfTop(Color newMarkOfTop)
{
    this->mark = newMarkOfTop;
}

Graph::Graph(long long countOfTops)
{
    for (int i = 0; i < countOfTops; i++)
    {
        Top temp(i);
        this->topsInGraph.push_back(temp);
    }
}

long long Graph::GetCountOfTopsInGraph()
{
    return this->topsInGraph.size();
}

Top &Graph::GetTopByIndex(long long index)
{
    return this->topsInGraph[index];
}

void Graph::dfs(long long index)
{
    this->topsInGraph[index].SetMarkOfTop(Achievable);
    for (long long i = 0; i < this->topsInGraph[index].GetCountOfTops(); i++)
    {
        if (this->topsInGraph[this->topsInGraph[index].GetEdgeByIndex(i).first].GetMarkOfTop() == NotDefined)
        {
            this->dfs(this->topsInGraph[index].GetEdgeByIndex(i).first);
        }
    }
}

void Graph::dfsForCycle(long long index)
{
    this->topsInGraph[index].SetMarkOfTop(InANegativeCycle);
    for (long long i = 0; i < this->topsInGraph[index].GetCountOfTops(); i++)
    {
        if (this->topsInGraph[this->topsInGraph[index].GetEdgeByIndex(i).first].GetMarkOfTop() != InANegativeCycle)
        {
            this->dfsForCycle(this->topsInGraph[index].GetEdgeByIndex(i).first);
        }
    }
}

void Graph::fordBellman(long long numberOfStartTop)
{
    const long long maxLenLong = -1 * (9e18);
    this->topsInGraph[numberOfStartTop].SetLenToTop(0);
    for (long long v = 0; v < this->topsInGraph.size(); v++)
    {
        for (long long i = 0; i < this->topsInGraph.size(); i++)
        {
            for (long long j = 0; j < this->topsInGraph[i].GetCountOfTops(); j++)
            {
                if (this->topsInGraph[this->topsInGraph[i].GetEdgeByIndex(j).first].GetLenToTop() >
                    this->topsInGraph[i].GetLenToTop() + this->topsInGraph[i].GetEdgeByIndex(j).second)
                {
                    if (maxLenLong < this->topsInGraph[i].GetLenToTop() + this->topsInGraph[i].GetEdgeByIndex(j).second)
                    {
                        this->topsInGraph[this->topsInGraph[i].GetEdgeByIndex(j).first].SetLenToTop(this->topsInGraph[i].GetLenToTop() + this->topsInGraph[i].GetEdgeByIndex(j).second);
                        if (v == this->topsInGraph.size() - 1 && this->topsInGraph[this->topsInGraph[i].GetEdgeByIndex(j).first].GetMarkOfTop() == Achievable)
                        {
                            this->dfsForCycle(this->topsInGraph[i].GetEdgeByIndex(j).first);
                        }
                    }
                    else
                    {
                        this->topsInGraph[this->topsInGraph[i].GetEdgeByIndex(j).first].SetLenToTop(maxLenLong);
                        if (v == this->topsInGraph.size() - 1 && this->topsInGraph[this->topsInGraph[i].GetEdgeByIndex(j).first].GetMarkOfTop() == Achievable)
                        {
                            this->dfsForCycle(this->topsInGraph[i].GetEdgeByIndex(j).first);
                        }
                    }
                }
            }
        }
    }
}