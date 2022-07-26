#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream gFin("negcycle.in");
std::ofstream gFout("negcycle.out");

enum Color
{
    Open,
    Close
};

class Top
{
    public:
        Top(long long newNumberOfTop);
        long long GetNumberOfPrevTop();
        long long GetNumberOfTop();
        long long GetLenToTop();
        long long GetCountOfNumbersOfOtherTopsFromEdges();
        std::pair<long long, long long> GetNumberOfOtherTopsFromEdgesByIndex(long long index);
        void addEdge(std::pair<long long, long long> newEdge);
        void SetLenToTop(long long newLenToTop);
        void SetNumberOfPrevTop(long long newNumberOfPrevTop);
        Color GetColorOfTop();
        void SetColorOfThisTop(Color newColorOfThisTop);

    private:
        long long numberOfTop;
        long long lenToTop;
        std::vector<std::pair<long long, long long>> numbersOfOtherTopsFromEdges;
        long long numberOfPrevTop;
        Color colorOfTop;
};

class Graph
{
    public:
        Graph(long long size);
        Top& GetTopByIndex(long long index);
        void fordBellman();
    private:
        std::vector<Top> topsInGraph;
};

int main()
{
    long long size = 0;
    gFin >> size;

    if (size == 0)
    {
        gFout << "NO";
        gFin.close();
        gFout.close();
        return 0;
    }

    Graph graph(size);

    long long weightOfEdge;
    for (long long i = 0; i < size; i++)
    {
        for (long long j = 0; j < size; j++)
        {
            gFin >> weightOfEdge;
            if (weightOfEdge < 100002)
            {
                std::pair<long long, long long> temp(j, weightOfEdge);
                graph.GetTopByIndex(i).addEdge(temp);
            }
            if (i == j && weightOfEdge < 0)
            {
                gFout << "YES\n" << 2 << std::endl << i + 1 << " " << i + 1;
                return 0;
            }
        }
    }

    graph.fordBellman();

    gFin.close();
    gFout.close();
    return 0;
}

Top::Top(long long newNumberOfTop)
{
    this->numberOfTop = newNumberOfTop;
    this->lenToTop = 100000000000;
    this->numberOfPrevTop = -1;
    this->colorOfTop = Open;
}

long long Top::GetNumberOfTop()
{
    return this->numberOfTop;
}

long long Top::GetCountOfNumbersOfOtherTopsFromEdges()
{
    return this->numbersOfOtherTopsFromEdges.size();
}

long long Top::GetLenToTop()
{
    return this->lenToTop;
}

std::pair<long long, long long> Top::GetNumberOfOtherTopsFromEdgesByIndex(long long index)
{
    return this->numbersOfOtherTopsFromEdges[index];
}

long long Top::GetNumberOfPrevTop()
{
    return this->numberOfPrevTop;
}

void Top::SetLenToTop(long long newLenToTop)
{
    this->lenToTop = newLenToTop;
}

void Top::SetNumberOfPrevTop(long long newNumberOfPrevTop)
{
    this->numberOfPrevTop = newNumberOfPrevTop;
}

void Top::addEdge(std::pair<long long, long long> newEdge)
{
    this->numbersOfOtherTopsFromEdges.push_back(newEdge);
}

Color Top::GetColorOfTop()
{
    return this->colorOfTop;
}

void Top::SetColorOfThisTop(Color newColorOfThisTop)
{
    this->colorOfTop = newColorOfThisTop;
}

Graph::Graph(long long size)
{
    for (long long i = 0; i < size; i++)
    {
        Top newTop(i);
        this->topsInGraph.push_back(newTop);
    }
}

Top& Graph::GetTopByIndex(long long index)
{
    return this->topsInGraph[index];
}

void Graph::fordBellman()
{
    const long long maxLenLong = -1 * (9e18);
    long long numberOfOneTop;
    this->topsInGraph[this->topsInGraph.size() - 1].SetLenToTop(0);
    bool resultOfSearch = false;
    for (long long k = 0; k <= this->topsInGraph.size(); k++)
    {
        bool boolContinue = false;
        for (long long i = 0; i < this->topsInGraph.size(); i++)
        {
            for (long long j = 0; j < this->topsInGraph[i].GetCountOfNumbersOfOtherTopsFromEdges(); j++)
            {
                if (this->topsInGraph[this->topsInGraph[i].GetNumberOfOtherTopsFromEdgesByIndex(j).first].GetLenToTop() >
                    this->topsInGraph[i].GetLenToTop() +
                    this->topsInGraph[i].GetNumberOfOtherTopsFromEdgesByIndex(j).second)
                {
                    if (maxLenLong < this->topsInGraph[i].GetLenToTop() + this->topsInGraph[i].GetNumberOfOtherTopsFromEdgesByIndex(j).second)
                    {
                        this->topsInGraph[this->topsInGraph[i].GetNumberOfOtherTopsFromEdgesByIndex(j).first].SetLenToTop(this->topsInGraph[i].GetLenToTop() +
                                                                                                                          this->topsInGraph[i].GetNumberOfOtherTopsFromEdgesByIndex(j).second);
                        this->topsInGraph[this->topsInGraph[i].GetNumberOfOtherTopsFromEdgesByIndex(
                                j).first].SetNumberOfPrevTop(i);
                        boolContinue = true;
                        if (k == this->topsInGraph.size())
                        {
                            resultOfSearch = true;
                            numberOfOneTop = i;
                        }
                    }
                    else
                    {
                        this->topsInGraph[this->topsInGraph[i].GetNumberOfOtherTopsFromEdgesByIndex(j).first].SetLenToTop(maxLenLong);
                        this->topsInGraph[this->topsInGraph[i].GetNumberOfOtherTopsFromEdgesByIndex(
                                j).first].SetNumberOfPrevTop(i);
                        boolContinue = true;
                        if (k == this->topsInGraph.size())
                        {
                            resultOfSearch = true;
                            numberOfOneTop = i;
                        }
                    }
                }
            }
        }
        if (!boolContinue)
            break;
    }

    if (resultOfSearch)
    {
        std::vector<long long> result;
        long long getPointInCycle = numberOfOneTop;

        for (int i = 0; i < this->topsInGraph.size(); i++)
        {
            getPointInCycle = this->topsInGraph[getPointInCycle].GetNumberOfPrevTop();
        }

        long long u = this->topsInGraph[getPointInCycle].GetNumberOfPrevTop();
        result.push_back(getPointInCycle);
        while (u != getPointInCycle)
        {
            result.push_back(u);
            u = this->topsInGraph[u].GetNumberOfPrevTop();
        }
        result.push_back(getPointInCycle);

        std::reverse(result.begin(), result.end());

        gFout << "YES\n" << result.size() << std::endl;
        for (int i = 0; i < result.size(); i++)
        {
            gFout << result[i] + 1 << " ";
        }
    }
    else
    {
        gFout << "NO\n";
    }
}