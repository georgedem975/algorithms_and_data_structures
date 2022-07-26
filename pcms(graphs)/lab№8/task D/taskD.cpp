#include <iostream>
#include <fstream>
#include <vector>
 
class Top
{
    public:
        Top();
        
        Top(int newNumber);
        
        char GetColor()
        {
            return color;
        }
        
        void SetColor(char newColor)
        {
            color = newColor;
        }
        
        void SetNumberOfComponent(int newNumberComponent)
        {
            numberOfComponent = newNumberComponent;
        }
        
        int GetNumber()
        {
            return numberOfComponent;
        }
        
        void SetVector(int index)
        {
            this->friendTops.push_back(index);
        }
        
        int GetVector(int index)
        {
            return this->friendTops[index];
        }
        
        int GetSizeVector()
        {
            return this->friendTops.size();
        }

    protected:
        int numberOfTop;
        char color;
        int numberOfComponent = 0;
        std::vector<int> friendTops;
};
 
class Graph
{
    public:
        friend class top;
        
        Graph(int size);
        
        void addNewEdges(int numberOfFirstTop, int numberOfSecondTop)
        {
            graph[numberOfFirstTop].SetVector(numberOfSecondTop);
            graph[numberOfSecondTop].SetVector(numberOfFirstTop);
            edges.push_back(std::pair<int,int>(numberOfFirstTop, numberOfSecondTop));
        }
        
        void viewing()
        {
            for (int index = 0; index < size; index++)
            {
                if (graph[index].GetColor() == 'w')
                {
                    numberOfComponent++;
                    dfs(index);
                }
            }
        }
        
        void dfs(int numberOfTop)
        {
            graph[numberOfTop].SetColor('b');
            graph[numberOfTop].SetNumberOfComponent(numberOfComponent);
            if (!edges.empty())
            {
                for (int i = 0; i < graph[numberOfTop].GetSizeVector(); i++)
                {
                    if (graph[graph[numberOfTop].GetVector(i)].GetColor() == 'w')
                    {
                        graph[graph[numberOfTop].GetVector(i)].SetColor('b');
                        this->dfs(graph[numberOfTop].GetVector(i));
                    }
                }
            }
        }
            
        int GetNumberOfComponent()
        {
            return numberOfComponent;
        }
        
        int GetNumberOfComponent(int index)
        {
            return graph[index].GetNumber();
        }

    private:
        std::vector<Top> graph;
        std::vector<std::pair<int, int>> edges;
        int size;
        int numberOfComponent = 0;
};
 
int main()
{
    std::ifstream fin("components.in");
    std::ofstream fout("components.out");
 
    int theNumberOfVerticesOfTheGraph, numberOfEdgesOfTheGraph;
 
    fin >> theNumberOfVerticesOfTheGraph >> numberOfEdgesOfTheGraph;
 
    Graph graphInMain(theNumberOfVerticesOfTheGraph);
 
    int firstTop, secondTop;
 
    for (int counter = 0; counter < numberOfEdgesOfTheGraph; counter++)
    {
        fin >> firstTop >> secondTop;
        firstTop--;
        secondTop--;
        graphInMain.addNewEdges(firstTop, secondTop);
    }
 
    graphInMain.viewing();
 
    fout << graphInMain.GetNumberOfComponent() << "\n";
 
    for (int i = 0; i < theNumberOfVerticesOfTheGraph; i++)
    {
        fout << graphInMain.GetNumberOfComponent(i) << " ";
    }
 
    fin.close();
    fout.close();
 
    return 0;
}
 
Graph::Graph(int size)
{
    size = size;
    for (int i = 0; i < size; i++)
    {
        Top NewTop(i);
        graph.push_back(NewTop);
    }
}
 
Top::Top()
{
    numberOfTop = 0;
}
 
Top::Top(int newNumber)
{
    numberOfTop = newNumber;
    color = 'w';
}