#include <iostream>
using namespace std;
class MaxHeap
{
public:
    int *arr;
    int size;
    int cur;

    MaxHeap(int n)
    {
        arr = new int[n];
        size = n;
        cur = 0;
    }

    void insert(int val)
    {
        if (cur < size)
        {
            arr[cur] = val;
            cur++;
            int temp = cur - 1;
            while (temp > 0)
            {
                int parent = (temp - 1) / 2;
                if (arr[temp] > arr[parent])
                {
                    swap(arr[temp], arr[parent]);
                    temp = parent;
                }
                else
                {
                    break;
                }
            }
        }
        else if (val > arr[0])
        {
            // Replace the root and reheapify
            arr[0] = val;
            heapify(0);
        }
    }

    void heapify(int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left > cur && arr[left] > arr[largest])
        {
            largest = left;
        }
        if (right > cur && arr[right] > arr[largest])
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(largest);
        }
    }

    void display()
    {
        for (int i = 0; i < cur; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 3;
    cout << "Length of array is 10 so total windows of 3 elements are " << 10 - k + 1 << endl;
    MaxHeap h(k);
    for (int i = 0; i <= 10 - k; i++)
    {
        for (int j = i; j < i + k; j++)
        {
            h.insert(arr[j]);
        }
        cout << "The Maximum elements in " << i + 1 << " sliding window is " << h.arr[0] << endl;
    }

    return 0;
}