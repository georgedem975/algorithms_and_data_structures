#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Top
{
    public:
        Top(int newNumberOfTop);
        long long lenToTop;
        char modificator;
        int numberOfTop;
        int numberInQueue;
        std::vector<std::pair<int, long long>> otherTops;
};

class PriorityQueue
{
    public:
        PriorityQueue(int size);
        void decreaseKey(Top* top, double newElement);
        void push(Top* mas);
        void extractMin();
        int getMin();
        bool empty();

    private:
        std::vector<Top*> priorityMass;
        int numberOfElements = 0;
        void siftUp(Top* top, int index);
        void siftDown(Top* top, int index);
};

class Graph
{
    public:
        Graph(int newSizeOfGraph);
        ~Graph();
        void addNewTop();
        double mstLen();
        long long dijkstra(int startTopNumber, int finishTopNumber);
        int sizeOfGraph;
        int indexNextTop;
        double minLen;
        int minLenNumber;
        std::vector<Top> tops;
};

int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    std::ifstream fin("pathmgep.in");
    std::ofstream fout("pathmgep.out");

    int numberOfTops = 0, numberOfStartTop, numberOfFinishTop;

    fin >> numberOfTops >> numberOfStartTop >> numberOfFinishTop;

    if (numberOfTops < 2)
    {
        fout << 0;
        fin.close();
        fout.close();
        return 0;
    }

    Graph graph(numberOfTops);

    for (int i = 0; i < numberOfTops; i++)
    {
        graph.addNewTop();
    }

    int firstTopNumber, secondTopNumber, lenFromFirstTopToSecondTop;

    for (int i = 0; i < numberOfTops; i++)
    {
        for (int j = 0; j < numberOfTops; j++)
        {
            fin >> lenFromFirstTopToSecondTop;
            if (i != j && lenFromFirstTopToSecondTop >= 0)
            {
                graph.tops[i].otherTops.push_back(std::pair<int, long long>(j, lenFromFirstTopToSecondTop));
            }
        }
    }

    numberOfStartTop--;
    numberOfFinishTop--;

    fout << graph.dijkstra(numberOfStartTop, numberOfFinishTop);

    fin.close();
    fout.close();

    return 0;
}


Top::Top(int newNumberOfTop)
{
    this->numberOfTop = newNumberOfTop;
    this->modificator = 'o';
    this->lenToTop = LLONG_MAX;
}

Graph::Graph(int newSizeOfGraph)
{
    this->sizeOfGraph = newSizeOfGraph;
    this->minLen = 1000000000000000;
}

void Graph::addNewTop()
{
    Top newTop(this->tops.size());
    this->tops.push_back(newTop);
}

Graph::~Graph(){}

void PriorityQueue::siftUp(Top *top, int index)
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

void PriorityQueue::siftDown(Top *top, int index)
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

PriorityQueue::PriorityQueue(int size)
{
    for (int i = 0; i < size; i++)
    {
        Top* tmp = new Top(0);
        this->priorityMass.push_back(tmp);
    }
}

void PriorityQueue::decreaseKey(Top *top, double newElement)
{
    priorityMass[top->numberInQueue]->lenToTop = newElement;
    siftUp(top, top->numberInQueue);
}

void PriorityQueue::push(Top *mas)
{
    priorityMass[numberOfElements] = mas;
    siftUp(mas, numberOfElements);
    this->numberOfElements += 1;
}

void PriorityQueue::extractMin()
{
    priorityMass[0] = priorityMass[--numberOfElements];
    siftDown(this->priorityMass[0], 0);
}

int PriorityQueue::getMin()
{
    return this->priorityMass[0]->numberOfTop;
}

bool PriorityQueue::empty()
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

double Graph::mstLen()
{
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
        int j = q.getMin();
        q.extractMin();
        for (int i = 0; i < this->tops.size(); i++)
        {
            {
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

long long Graph::dijkstra(int startTopNumber, int finishTopNumber)
{
    PriorityQueue q(this->tops.size());
    for (int i = 0; i < this->tops.size(); i++)
    {
        q.push(&this->tops[i]);
    }
    q.decreaseKey(&this->tops[startTopNumber], 0);
    this->tops[startTopNumber].modificator = 'c';
    bool flag = true;
    while (!q.empty() && flag)
    {
        int j = q.getMin();
        q.extractMin();
        for (int i = 0; i < this->tops[j].otherTops.size(); i++)
        {
            if (this->tops[this->tops[j].otherTops[i].first].modificator != 'c' && this->tops[this->tops[j].otherTops[i].first].lenToTop > this->tops[j].lenToTop + this->tops[j].otherTops[i].second)
            {
                this->tops[this->tops[j].otherTops[i].first].lenToTop = this->tops[j].lenToTop + this->tops[j].otherTops[i].second;
                q.decreaseKey(&this->tops[this->tops[j].otherTops[i].first], this->tops[this->tops[j].otherTops[i].first].lenToTop);
            }
        }
        this->tops[j].modificator = 'c';
        if (j == finishTopNumber)
        {
            if (this->tops[j].lenToTop == LLONG_MAX)
                return -1;
            return this->tops[j].lenToTop;
        }
    }
}