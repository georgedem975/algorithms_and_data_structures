#include <iostream>
#include <fstream>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, m;

    fin >> n >> m;

    int matrix[100][100] = {0};

    int x, y;

    for (int i = 0; i < m; i++)
    {
        fin >> x >> y;
        matrix[x - 1][y - 1] += 1;
        matrix[y - 1][x - 1] += 1;
        
        if (matrix[x - 1][y - 1] > 1)
        {
            fout << "YES";
            fin.close();
            fout.close();

            return 0;
        }
    }

    fout << "NO";
    fin.close();
    fout.close();

    return 0;
}