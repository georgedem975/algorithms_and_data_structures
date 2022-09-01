#include <iostream>
#include <vector>

namespace ms
{
    void merge(std::vector<int>& arr, int left, int right);

    void mergeSort(std::vector<int>& arr, int left, int right);

    void mergeSort(std::vector<int>& arr)
    {
        mergeSort(arr, 0, arr.size() - 1);
    }

    void mergeSort(std::vector<int>& arr, int left, int right)
    {
        if (left == right - 1 && arr[left] > arr[right])
        {
            std::swap(arr[left], arr[right]);
            return;
        }

        if (left == right || left == right - 1)
        {
            return;
        }

        mergeSort(arr, left, (right + left) / 2);
        mergeSort(arr, ((right + left) / 2) + 1, right);

        merge(arr, left, right);
    }

    void merge(std::vector<int>& arr, int left, int right)
    {
        std::vector<int> part;

        int i = left, j = ((right + left) / 2) + 1;

        while (i != ((right + left) / 2) + 1 && j <= right)
        {
            if (arr[i] > arr[j])
            {
                part.push_back(arr[j]);
                j++;
            }
            else
            {
                part.push_back(arr[i]);
                i++;
            }
        }

        while (i != ((right + left) / 2) + 1)
        {
            part.push_back(arr[i]);
            i++;
        }

        while (j <= right)
        {
            part.push_back(arr[j]);
            j++;
        }

        for (int p = left, q = 0; p <= right; p++, q++)
        {
            arr[p] = part[q];
        }
    }
}

int main()
{
    std::vector<int> temp = {1, 8, 3, 0, 7, 2};

    ms::mergeSort(temp);

    for (int i = 0; i < temp.size(); i++)
    {
        std::cout << temp[i] << " ";
    }

    return 0;
}