#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& temp)
{
    for (int i = 1; i < temp.size(); i++)
    {
        int j = i - 1;

        while (j >= 0 && temp[j] > temp[j + 1])
        {
            int temper = temp[j];
            temp[j] = temp[j + 1];
            temp[j + 1] = temper;
            j--;
        }
    }
}

int main()
{
    std::vector<int> temp = {1, 0, 3, 5, 2, 4, 6};

    insertionSort(temp);

    for (int i = 0; i < temp.size(); i++)
    {
        std::cout << temp[i] << " ";
    }

    return 0;
}