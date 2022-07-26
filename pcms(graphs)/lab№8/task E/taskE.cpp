#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

enum Color
{
    White,
    Red,
    Black,
};
 
class Top
{
    public:
        Top();
    
        Top(int newNumber)
        {
            number = newNumber;
        }
    
        void SetColor(Color color)
        {
            topColor = color;
        }
    
        void addConnection(int numberOfTop)
        {
            connection.push_back(numberOfTop);
        }
    
        int GetLength()
        {
            return length;
        }
    
        int GetSizeOfConnection()
        {
            return connection.size();
        }
    
        int GetTopInTheConnection(int index)
        {
            return connection[index];
        }
    
        Color GetColor()
        {
            return topColor;
        }
    
        void SetLength(int newLength)
        {
            length = newLength;
        }
    
    private:
        int number;
        int length = 0;
        Color topColor = White;
        std::vector<int> connection;
};
 
class Graph
{
    public:
        Graph(int newCounter)
        {
            counterOfVertices = newCounter;
            for (int i = 0; i < counterOfVertices; i++)
            {
                Top newTop(i);
                tops.push_back(newTop);
            }
        }
    
        void add(int numberOne, int numberTwo)
        {
            tops[numberOne].addConnection(numberTwo);
            tops[numberTwo].addConnection(numberOne);
        }
    
        int GetLengthToFirstPoint(int indexOfPoint)
        {
            return tops[indexOfPoint].GetLength();
        }
    
        void bfs(int start)
        {
            tops[start].SetColor(Red);
            std::queue<int> queueBfs;
            queueBfs.push(start);
            while (!queueBfs.empty())
            {
                int position = queueBfs.front();
                queueBfs.pop();
                for (int index = 0; index < tops[position].GetSizeOfConnection(); index++)
                {
                    if (tops[tops[position].GetTopInTheConnection(index)].GetColor() == White)
                    {
                        tops[tops[position].GetTopInTheConnection(index)].SetColor(Red);
                        tops[tops[position].GetTopInTheConnection(index)].SetLength(tops[position].GetLength() + 1);
                        queueBfs.push(tops[position].GetTopInTheConnection(index));
                    }
                }
                tops[position].SetColor(Black);
            }
        }
    
    private:
        std::vector<Top> tops;
        int counterOfVertices;
};
 
int main()
{
    std::ifstream fin("pathbge1.in");
    std::ofstream fout("pathbge1.out");
 
    int theNumberOfVerticesOfTheGraph, numberOfEdgesOfTheGraph;
 
    fin >> theNumberOfVerticesOfTheGraph >> numberOfEdgesOfTheGraph;
 
    Graph graph(theNumberOfVerticesOfTheGraph);
 
    int NumberOfFirstTop, NumberOfSecondTop;
 
    for (int i = 0; i < numberOfEdgesOfTheGraph; i++)
    {
        fin >> NumberOfFirstTop >> NumberOfSecondTop;
        NumberOfFirstTop--;
        NumberOfSecondTop--;
        graph.add(NumberOfFirstTop, NumberOfSecondTop);
    }

    graph.bfs(0);
 
    for (int index = 0; index < theNumberOfVerticesOfTheGraph; index++)
    {
        fout << graph.GetLengthToFirstPoint(index) << " ";
    }
 
    fin.close();
    fout.close();
 
    return 0;
}