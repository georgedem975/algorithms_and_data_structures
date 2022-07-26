#include <iostream>
#include <fstream>
#include <vector>

class Pair
{
    public:
        int first;
        unsigned int second;
};

class Top
{
    public:
        Top(int newNumberOfTop)
        {
            this->numberOfTop = newNumberOfTop;
            this->modificator = 'o';
        }
        std::vector<Pair> adges;
        std::vector<Pair> reversedAdges;
        int numberOfTop;
        int numberOfComponent;
        int minWeight = INT_MAX;
        char modificator;
};

class Graph
{
    public:

        void vie()
        {
            for (int i = 0; i < this->topsInGraf.size(); i++)
            {
                if (this->topsInGraf[i].modificator == 'o' || this->topsInGraf[i].modificator == 'r')
                {
                    this->dfs(i);
                }
            }
        }

        void dfs(int index)
        {
            this->topsInGraf[index].modificator = 'm';
            for (int i = 0; i < this->topsInGraf[index].adges.size(); i++)
            {
                if (this->topsInGraf[index].adges[i].second == 0 && (this->topsInGraf[this->topsInGraf[index].adges[i].first].modificator == 'o' ||
                this->topsInGraf[this->topsInGraf[index].adges[i].first].modificator == 'r'))
                {
                    this->dfs(this->topsInGraf[index].adges[i].first);
                }
            }
            this->numbersOfBfs.push_back(index);
        }

        void lastBfs(int index)
        {
            this->topsInGraf[index].modificator = 'c';
            for (int i = 0; i < this->topsInGraf[index].reversedAdges.size(); i++)
            {
                if (this->topsInGraf[this->topsInGraf[index].reversedAdges[i].first].modificator == 'm' && this->topsInGraf[index].reversedAdges[i].second == 0)
                {
                    this->lastBfs(this->topsInGraf[index].reversedAdges[i].first);
                }
            }
            this->topsInGraf[index].numberOfComponent = this->maxComponent;
        }

        bool dfsBool(int index)
        {
            this->normalDfs(index);
            for (int i = 0; i < this->topsInGraf.size(); i++)
            {
                if (this->topsInGraf[i].modificator == 'o')
                {
                    return false;
                }
            }
            return true;
        }

        void secondDfs(int index)
        {
            this->topsInGraf[index].modificator = 'o';
            for (int i = 0; i < this->topsInGraf[index].adges.size(); i++)
            {
                if (this->topsInGraf[this->topsInGraf[index].adges[i].first].modificator == 'w')
                {
                    this->secondDfs(this->topsInGraf[index].adges[i].first);
                }
            }
        }

        void normalDfs(int index)
        {
            this->topsInGraf[index].modificator = 'r';
            for (int i = 0; i < this->topsInGraf[index].adges.size(); i++)
            {
                if (this->topsInGraf[index].adges[i].second == 0 && this->topsInGraf[this->topsInGraf[index].adges[i].first].modificator == 'o')
                {
                    this->normalDfs(this->topsInGraf[index].adges[i].first);
                }
            }
        }
        std::vector<Top> topsInGraf;
        std::vector<int> numbersOfBfs;
        unsigned short int maxComponent = 0;
        unsigned short int numberOfRootInGraph;
};

long long GetMST(int counterOfVerticles, Graph& graph)
{
    long long sum = 0;
    for (int i = 0; i < graph.topsInGraf.size(); i++)
    {
        if (graph.topsInGraf[i].minWeight != INT_MAX)
        {
            sum += graph.topsInGraf[i].minWeight;
        }
    }
    for (int i = 0; i < counterOfVerticles; i++)
    {
        for (int j = 0; j < graph.topsInGraf[i].reversedAdges.size(); j++)
        {
            graph.topsInGraf[i].reversedAdges[j].second -= graph.topsInGraf[i].minWeight;
        }
        for (int j = 0; j < graph.topsInGraf[i].adges.size(); j++)
        {
            graph.topsInGraf[i].adges[j].second -= graph.topsInGraf[graph.topsInGraf[i].adges[j].first].minWeight;
        }
    }

    if (graph.dfsBool(graph.numberOfRootInGraph))
    {
        return sum;
    }

    graph.vie();
    
    for (int i = graph.numbersOfBfs.size() - 1; i >= 0; i--)
    {
        if (graph.topsInGraf[graph.numbersOfBfs[i]].modificator == 'm')
        {
            graph.lastBfs(graph.numbersOfBfs[i]);
            graph.maxComponent++;
        }
    }

    Graph temp;
    
    for (int i = 0; i < graph.maxComponent; i++)
    {
        Top newTop(i);
        newTop.minWeight = INT_MAX;
        temp.topsInGraf.push_back(newTop);
    }

    temp.numberOfRootInGraph = graph.topsInGraf[graph.numberOfRootInGraph].numberOfComponent;
    int id = 0;
    for (int i = 0; i < graph.topsInGraf.size(); i++)
    {
        Pair pair;
        for (int j = 0; j < graph.topsInGraf[i].adges.size(); j++)
        {
            if (graph.topsInGraf[graph.topsInGraf[i].adges[j].first].numberOfComponent != graph.topsInGraf[i].numberOfComponent)
            {
                pair.first = graph.topsInGraf[graph.topsInGraf[i].adges[j].first].numberOfComponent;
                pair.second = graph.topsInGraf[i].adges[j].second;
                temp.topsInGraf[graph.topsInGraf[i].numberOfComponent].adges.push_back(pair);
            }
        }
        for (int j = 0; j < graph.topsInGraf[i].reversedAdges.size(); j++)
        {
            if (graph.topsInGraf[graph.topsInGraf[i].reversedAdges[j].first].numberOfComponent != graph.topsInGraf[i].numberOfComponent)
            {
                pair.first = graph.topsInGraf[graph.topsInGraf[i].reversedAdges[j].first].numberOfComponent;
                pair.second = graph.topsInGraf[i].reversedAdges[j].second;
                temp.topsInGraf[graph.topsInGraf[i].numberOfComponent].reversedAdges.push_back(pair);
                if (temp.topsInGraf[graph.topsInGraf[i].numberOfComponent].minWeight == INT_MAX || temp.topsInGraf[graph.topsInGraf[i].numberOfComponent].minWeight > pair.second)
                {
                    temp.topsInGraf[graph.topsInGraf[i].numberOfComponent].minWeight = pair.second;
                }
            }
        }
    }

    sum += GetMST(graph.maxComponent, temp);

    return sum;
}


int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);


    std::ifstream fin("chinese.in");
    std::ofstream fout("chinese.out");


    int counterOfVerticles, counterOfEdges;
    fin >> counterOfVerticles >> counterOfEdges;

    std::vector<unsigned short> degreeEnter;
    std::vector<unsigned short> degreeExit;
    for (int i = 0; i < counterOfVerticles; i++)
    {
        degreeEnter.push_back(0);
        degreeExit.push_back(0);
    }

    Graph graph;
    graph.numberOfRootInGraph = 0;

    for (int i = 0; i < counterOfVerticles; i++)
    {
        Top newTop(i);
        graph.topsInGraf.push_back(newTop);
    }

    int c = counterOfEdges;
    int x, y, z;
    for (int i = 0; i < c; i++)
    {
        fin >> x >> y >> z;
        x -= 1;
        y -= 1;
        if (y != 0)
        {
            Pair t;
            t.first = y;
            t.second = z;
            graph.topsInGraf[x].adges.push_back(t);
            degreeExit[x] += 1;
            t.first = x;
            graph.topsInGraf[y].reversedAdges.push_back(t);
            degreeEnter[y] += 1;
            if (graph.topsInGraf[y].minWeight == -1 || graph.topsInGraf[y].minWeight > z)
            {
                graph.topsInGraf[y].minWeight = z;
            }
            counterOfEdges++;
        }
        counterOfEdges--;
    }

    int counterEnter = 0;

    for (int i = 0; i < counterOfVerticles; i++)
    {
        graph.topsInGraf[i].modificator = 'w';
    }
    bool flag = true;
    graph.secondDfs(0);
    for (int i = 0; i < counterOfVerticles; i++)
    {
        if (graph.topsInGraf[i].modificator == 'w')
        {
            flag = false;
            break;
        }
    }

    if (flag)
    {
        long long sum = 0;
        sum = GetMST(counterOfVerticles, graph);
        fout << "YES\n" << sum;
    }
    else
    {
        fout << "NO";
        fin.close();
        fout.close();
        return 0;
    }

    fin.close();
    fout.close();

    return 0;
}