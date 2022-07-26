#include <iostream>
#include <fstream>

class Matrix
{
    public:
        Matrix()= default;
        ~Matrix()= default;

        void SetArrayIndex(int indexOne, int indexTwo, int newData)
        {
            this->arr[indexOne][indexTwo] = newData;
        }

        int GetArrayIndex(int indexOne, int indexTwo)
        {
            return this->arr[indexOne][indexTwo];
        }

        bool IsTrueMatrix(int index)
        {
            return this->arr[index][index];
        }

    private:
        int arr[100][100] = {0};
};

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n;
    fin >> n;
    Matrix mainMatrix;
    bool flag = true;

    int matrixCell;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> matrixCell;
            mainMatrix.SetArrayIndex(i, j, matrixCell);

            if (i == j && mainMatrix.IsTrueMatrix(i))
            {
                flag = false;
                break;
            }
        }
    }

    int offset = 1;

    if (flag)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = offset; j < n; j++)
            {
                if (mainMatrix.GetArrayIndex(i, j) != mainMatrix.GetArrayIndex(j, i))
                {
                    flag = false;
                    break;
                }
            }
            offset++;
        }
    }

    if (flag)
    {
        fout << "YES";
    }
    else
    {
        fout << "NO";
    }

    fin.close();
    fout.close();

    return 0;
}