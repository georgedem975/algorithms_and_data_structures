#include <iostream>
#include <vector>
#include <algorithm>

namespace qs
{
    void quickSort(std::vector<int>& temp, int l, int r);

    void quickSort(std::vector<int>& temp)
    {
        quickSort(temp, 0, temp.size() - 1);
    }

    int partition(std::vector<int>& temp, int l, int r)
    {
        int v = temp[(l + r) / 2];
        int i = l;
        int j = r;
        while (i <= j)
        {
            while (temp[i] < v)
                i++;
            while (temp[j] > v)
                j--;

            if (i >= j)
            {
                break;
            }

            std::swap(temp[i++], temp[j--]);
        }
        return j;
    }

    void quickSort(std::vector<int>& temp, int l, int r)
    {
        if (l < r)
        {
            int q = partition(temp, l, r);
            quickSort(temp, l, q);
            quickSort(temp, q + 1, r);
        }
    }
}

int main()
{
    std::vector<int> temp = {1, 8, 3, 0, 7, 2};

    qs::quickSort(temp);

    for (int i = 0; i < temp.size(); i++)
    {
        std::cout << temp[i] << " ";
    }

    return 0;
}