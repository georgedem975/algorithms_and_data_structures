#include <fstream>
#include <vector>

class Top
{
    public:
        Top()
        {
            this->degree = 0;
        }
        
        void SetDegree(int newDegree)
        {
            this->degree = newDegree;
        }
        
        int GetDegree()
        {
            return this->degree;
        }
    
    private:
        int degree;
};

class Graph
{
    public:
        Graph(int size)
        {
            for (int i = 0; i < size; i++)
            {
                Top temp;
                this->tops.push_back(temp);
            }
        }

        int GetDegreeInGraph(int index)
        {
            return this->tops[index].GetDegree();
        }

        void add(int firstTop, int secondTop)
        {
            this->tops[firstTop].SetDegree(this->tops[firstTop].GetDegree() + 1);
            this->tops[secondTop].SetDegree(this->tops[secondTop].GetDegree() + 1);
        }
        
    private:
        std::vector<Top> tops;
};

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int v, e;

    fin >> v >> e;

    Graph graph(v);

    int x, y;
    for (int i = 0; i < e; i++)
    {
        fin >> x >> y;
        graph.add(--x, --y);
    }

    for (int i = 0; i < v; i++)
    {
        fout << graph.GetDegreeInGraph(i) << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}