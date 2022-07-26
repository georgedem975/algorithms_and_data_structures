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
        matrix[x - 1][y - 1] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1)
            {
                fout << "1 ";
            }
            else
            {
                fout << "0 ";
            }
        }
        fout << "\n";
    }

    fin.close();
    fout.close();

    return 0;
}