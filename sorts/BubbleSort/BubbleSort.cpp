#include <iostream>
#include <vector>

void bubbleSort(std::vector<int>& temp)
{
    for (int i = 0; i < temp.size(); i++)
    {
        for (int j = i + 1; j < temp.size(); j++)
        {
            if (temp[i] > temp[j])
            {
                int temper = temp[i];
                temp[i] = temp[j];
                temp[j] = temper;
            }
        }
    }
}

int main()
{
    std::vector<int> temp = {1, 0, 3, 5, 2, 4, 6};

    bubbleSort(temp);

    for (int i = 0; i < temp.size(); i++)
    {
        std::cout << temp[i] << " ";
    }

    return 0;
}