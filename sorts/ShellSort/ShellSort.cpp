#include <iostream>
#include <vector>

void shellSort(std::vector<int>& arr)
{
    int n = arr.size();

    for (int step = n / 2; step > 0; step /= 2)
    {
        for (int i = step; i < n; i++)
        {
            int j;
            int temp = arr[i];

            for (j = i; j >= step; j -= step)
            {
                if (temp < arr[j - step])
                {
                    arr[j] = arr[j - step];
                }
                else
                {
                    break;
                }
            }
            arr[j] = temp;
        }
    }
}

int main()
{
    std::vector<int> temp = {1, 8, 3, 0, 7, 2};

    shellSort(temp);

    for (int i = 0; i < temp.size(); i++)
    {
        std::cout << temp[i] << " ";
    }

    return 0;
}