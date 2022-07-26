#include <iostream>
#include <fstream>
#include <vector>
 
class Graph
{
    public:
        Graph(int newSizeOfGraph);
        int GetLenFromVertexToVertex(unsigned short int numberFirstVertex, unsigned short int numberSecondVertex);
        void SetLenFromVertexToVertex(unsigned short int numberFirstVertex, unsigned short int numberSecondVertex, int newLenFromVertexToVertex);
        void floydWarshall();
    private:
        unsigned short int sizeOfGraph;
        std::vector<std::vector<int>> matrix;
};
 
int main()
{
    std::ifstream fin("pathsg.in");
    std::ofstream fout("pathsg.out");
 
    unsigned short int counterOfVertex = 0, counterOfEdges = 0;
 
    fin >> counterOfVertex >> counterOfEdges;
 
    Graph graph(counterOfVertex);
    int lenFromFirstVertexToSecondVertex = 0;
    int numberFirstVertex = -1, numberSecondVertex = -1;
 
    for (int i = 0; i < counterOfEdges; i++)
    {
        fin >> numberFirstVertex >> numberSecondVertex >> lenFromFirstVertexToSecondVertex;
        numberFirstVertex--;
        numberSecondVertex--;
        graph.SetLenFromVertexToVertex(numberFirstVertex, numberSecondVertex, lenFromFirstVertexToSecondVertex);
    }

    graph.floydWarshall();
 
    for (int i = 0; i < counterOfVertex; i++)
    {
        for (int j = 0; j < counterOfVertex; j++)
        {
            int temp = graph.GetLenFromVertexToVertex(i, j);
            if (temp == -1)
            {
                fout << 0;
            }
            else
            {
                fout << temp;
            }
            fout << " ";
        }
        fout << "\n";
    }
 
    fin.close();
    fout.close();
 
    return 0;
}
 
Graph::Graph(int newSizeOfGraph)
{
    this->sizeOfGraph = newSizeOfGraph;
    for (int i = 0; i < this->sizeOfGraph; i++)
    {
        std::vector<int> temporaryColumn;
        for (int j = 0; j < this->sizeOfGraph; j++)
        {
            temporaryColumn.push_back(-1);
        }
        this->matrix.push_back(temporaryColumn);
    }
}
 
int Graph::GetLenFromVertexToVertex(unsigned short numberFirstVertex, unsigned short numberSecondVertex)
{
    return this->matrix[numberFirstVertex][numberSecondVertex];
}
 
void Graph::SetLenFromVertexToVertex(unsigned short numberFirstVertex, unsigned short numberSecondVertex, int newLenFromVertexToVertex)
{
    this->matrix[numberFirstVertex][numberSecondVertex] = newLenFromVertexToVertex;
}
 
void Graph::floydWarshall()
{
    for (int i = 0; i < this->sizeOfGraph; i++)
    {
        for (int j = 0; j < this->sizeOfGraph; j++)
        {
            for (int k = 0; k < this->sizeOfGraph; k++)
            {
                if (this->matrix[j][k] > this->matrix[j][i] + this->matrix[i][k] && this->matrix[j][k] != -1
                && this->matrix[j][i] != -1 && this->matrix[i][k] != -1 && k != j)
                {
                    this->matrix[j][k] = this->matrix[j][i] + this->matrix[i][k];
                }
                if (this->matrix[j][k] == -1 && this->matrix[j][i] != -1 && this->matrix[i][k] != -1 && k != j)
                {
                    this->matrix[j][k] = this->matrix[j][i] + this->matrix[i][k];
                }
            }
        }
    }
}