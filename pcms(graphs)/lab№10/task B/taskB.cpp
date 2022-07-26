#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
 
class Top
{
    public:
        Top(int newX, int newY, int newNumberOfTop);
        double lenToTop;
        char modificator;
        int numberOfTop;
        int x;
        int y;
        int numberInQueue;
};
 
class PriorityQueue
{
    private:

        std::vector<Top*> priorityMass;
        int numberOfElements = 0;

        void siftUp(Top* top, int index)
        {
            top->numberInQueue = index;
            if (index > 0 && priorityMass[index]->lenToTop < priorityMass[(index - 1) / 2]->lenToTop)
            {
                Top* temp = priorityMass[index];
                priorityMass[index] = priorityMass[(index - 1) / 2];
                priorityMass[(index - 1) / 2] = temp;
                priorityMass[index]->numberInQueue = index;
                siftUp(temp, (index - 1) / 2);
            }
        }

        void siftDown(Top* top, int index)
        {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int parent = index;

            if (leftChild < numberOfElements && priorityMass[index]->lenToTop > priorityMass[leftChild]->lenToTop)
            {
                parent = leftChild;
            }

            if (rightChild < numberOfElements && priorityMass[parent]->lenToTop > priorityMass[rightChild]->lenToTop)
            {
                parent = rightChild;
            }

            if (parent != index)
            {
                top->numberInQueue = parent;
                if (parent == leftChild)
                {
                    this->priorityMass[leftChild]->numberInQueue = index;
                }
                else
                {
                    this->priorityMass[rightChild]->numberInQueue = index;
                }
                Top* temp = priorityMass[index];
                priorityMass[index] = priorityMass[parent];
                priorityMass[parent] = temp;
                siftDown(temp, parent);
            }
        }

        int findElement(int mas)
        {
            for (int index = 0; index < numberOfElements; index++)
            {
                if (priorityMass[index]->numberOfTop == mas)
                {
                    return index;
                }
            }
        }

    public:
        PriorityQueue(int size)
        {
            for (int i = 0; i < size; i++)
            {
                Top* tmp = new Top(0, 0, 0);
                this->priorityMass.push_back(tmp);
            }
        }

        void decreaseKey(Top* t, double newElement)
        {
            priorityMass[t->numberInQueue]->lenToTop = newElement;
            siftUp(t, t->numberInQueue);
        }

        void push(Top* mas)
        {
            priorityMass[numberOfElements] = mas;
            siftUp(mas, numberOfElements);
            this->numberOfElements+=1;
        }

        int extractMin()
        {
            int value = priorityMass[0]->numberOfTop;
            priorityMass[0] = priorityMass[--numberOfElements];
            siftDown(this->priorityMass[0], 0);
            return value;
        }

        int GetMin()
        {
            return this->priorityMass[0]->numberOfTop;
        }

        bool empty()
        {
            if (this->numberOfElements > 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
};
 
class Graph
{
    public:
        Graph(int newSizeOfGraph);
        ~Graph();
        void addNewTop(int newCoordinateTopX, int newCoordinateTopY);
        void print();
        double mstLen();
        double getMinLen(int i, int j);
        int sizeOfGraf;
        int indexNextTop;
        double minLen;
        int minLenNumber;
        std::vector<Top> tops;
};
 
int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
 
    std::ifstream fin("spantree.in");
    std::ofstream fout("spantree.out");
 
    int numberOfTops = 0;
 
    fin >> numberOfTops;
 
    if (numberOfTops < 2)
    {
        fout << 0;
        fin.close();
        fout.close();
        return 0;
    }
 
    Graph graph(numberOfTops);
 
    int coordinateTopX = 0;
    int coordinateTopY = 0;
 
    for (int i = 0; i < numberOfTops; i++)
    {
        fin >> coordinateTopX >> coordinateTopY;
        graph.addNewTop(coordinateTopX, coordinateTopY);
    }
 
    fout << std::fixed << std::setprecision(10) << graph.mstLen();
 
    fin.close();
    fout.close();
 
    return 0;
}
 
 
Top::Top(int newX, int newY, int newNumberOfTop)
{
    this->x = newX;
    this->y = newY;
    this->numberOfTop = newNumberOfTop;
    this->modificator = 'o';
}
 
Graph::Graph(int newSizeOfGraph)
{
    this->sizeOfGraf = newSizeOfGraph;
    this->minLen = 1000000000000000;
}
 
void Graph::addNewTop(int newCoordinateTopX, int newCoordinateTopY)
{
    Top newTop(newCoordinateTopX, newCoordinateTopY, this->tops.size());
    this->tops.push_back(newTop);
    this->tops[this->tops.size() - 1].lenToTop = this->getMinLen(0, this->tops.size() - 1);
}
 
Graph::~Graph(){}
 
double Graph::getMinLen(int i, int j)
{
    return std::sqrt(std::pow((this->tops[i].x - this->tops[j].x), 2)
    + std::pow((this->tops[i].y - this->tops[j].y), 2));
}
 
double Graph::mstLen()
{
    for (int i = 1; i < this->tops.size() / 2; i++)
    {
        if (this->tops[i].lenToTop > this->getMinLen(i, 0))
        {
            this->tops[i].lenToTop = this->getMinLen(i, 0);
        }
    }
    PriorityQueue q(this->tops.size());
    q.push(&this->tops[0]);
    double sum = 0;
    this->tops[0].modificator = 'c';
    for (int i = 1; i < this->tops.size(); i++)
    {
        q.push(&this->tops[i]);
    }
    while (!q.empty())
    {
        int j = q.extractMin();
        for (int i = 0; i < this->tops.size(); i++)
        {
            if (this->tops[i].lenToTop > this->getMinLen(j, i) && i != j && this->tops[i].modificator != 'c')
            {
                this->tops[i].lenToTop = this->getMinLen(j, i);
                q.decreaseKey(&this->tops[i], this->tops[i].lenToTop);
            }
        }
        this->tops[j].modificator = 'c';
    }
 
    for (int i = 0; i < this->tops.size(); i++)
    {
        sum += this->tops[i].lenToTop;
    }
    return sum;
}