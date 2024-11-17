#include <iostream>
using namespace std;

class MinHeap
{
public:
    int *arr;
    int size;
    int cur;

    MinHeap(int n)
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
                if (arr[temp] < arr[parent])
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
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < cur && arr[left] < arr[smallest])
        {
            smallest = left;
        }
        if (right < cur && arr[right] < arr[smallest])
        {
            smallest = right;
        }
        if (smallest != i)
        {
            swap(arr[i], arr[smallest]);
            heapify(smallest);
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
    int k = 3;
    int inputArr[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    MinHeap h(k);
    for (int i = 0; i < 10; i++)
    {
        h.insert(inputArr[i]);
    }

    cout << "The " << k << " largest elements are: ";
    h.display();

    return 0;
}
