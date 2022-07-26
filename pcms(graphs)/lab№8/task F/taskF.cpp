#include <iostream>
#include <fstream>
#include <vector>

enum Mark
{
    Close,
    Open,
    OpenClosed
};

class Top
{
    public:
        Top()
        {
            topMark = Close;
        }
        
        ~Top(){}

        void SetMark(Mark newMark)
        {
            this->topMark = newMark;
        }

        void SetWay(char newWay)
        {
            this->way = newWay;
        }

        char GetWay()
        {
            return this->way;
        }

        Mark GetMark()
        {
            return this->topMark;
        }

        int countToWay = 0;
        
    private:
        Mark topMark;
        char way;
};

class Graph
{
    public:
        Graph()
        {
            for (int i = 1; i < 101; i++)
            {
                for (int j = 1; j < 101; j++)
                {
                    Top newTop;
                    matrix[i][j] = newTop;
                }
            }
        }

        void viewing(int i, int j, char newWay, int count)
        {
            if (matrix[i][j].GetMark() == Close)
            {
                return;
            }
            if (matrix[i][j].GetMark() == Open || (matrix[i][j].GetMark() == OpenClosed && count < matrix[i][j].countToWay))
            {
                matrix[i][j].SetWay(newWay);
                matrix[i][j].countToWay = count;
                matrix[i][j].SetMark(OpenClosed);
                viewing(i - 1, j, 'U', count + 1);
                viewing(i + 1, j, 'D', count + 1);
                viewing(i, j - 1, 'L', count + 1);
                viewing(i, j + 1, 'R', count + 1);
            }
        }

        ~Graph(){}

        void SetPoint(int i, int j, Mark newMark)
        {
            this->matrix[i][j].SetMark(newMark);
        }

        char GetMatrixWay(int i, int j)
        {
            return this->matrix[i][j].GetWay();
        }

    private:
        Top matrix[102][102];

};

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int x, y, xf = 120, yf = 120;

    Graph main;

    int sizeX, sizeY;

    fin >> sizeX >> sizeY;

    for (int i = 1; i <= sizeX; i++)
    {
        for (int j = 1; j <= sizeY; j++)
        {
            char temp;
            fin >> temp;
            switch (temp)
            {
                case '.':
                    main.SetPoint(i, j, Open);
                    break;
                case '#':
                    break;
                case 'S':
                    main.SetPoint(i, j, Open);
                    x = i;
                    y = j;
                    break;
                case 'T':
                    main.SetPoint(i, j, Open);
                    xf = i;
                    yf = j;
                    break;
            }
        }
    }

    main.viewing(x, y, '0', 0);

    std::vector<char> mainWay;
    char coutTemp;
    coutTemp = main.GetMatrixWay(xf, yf);
    bool flag = false;
    while(coutTemp != '0' && !flag)
    {
        coutTemp = main.GetMatrixWay(xf, yf);
        mainWay.push_back(coutTemp);
        switch (coutTemp)
        {
            case 'L':
                yf = yf + 1;
                break;
            case 'D':
                xf = xf - 1;
                break;
            case 'R':
                yf = yf - 1;
                break;
            case 'U':
                xf = xf + 1;
                break;
            case '0':
                break;
            default:
                flag = true;
        }
    }

    if (flag)
    {
        fout << "-1";
    }
    else
    {
        fout << mainWay.size() - 1 << '\n';
        for (int i = mainWay.size() - 2; i >= 0; i--)
        {
            fout << mainWay[i];
        }
    }
    
    fin.close();
    fout.close();

    return 0;
}