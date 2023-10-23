#include "dynArr.h"


DynArr::DynArr(int lenArr)
{
    try
    {
        arr = new int[lenArr];
        aux = new int[lenArr];
        this->lenArr = lenArr;
        fill();
    }
    catch (const exception& ex)
    {
        cerr << "Ошибка: " << ex.what() << endl;
        exit(0);
    }
}


DynArr::~DynArr()
{
    clear();
}


void DynArr::clear()
{
    delete[] arr;
    delete[] aux;
    arr = aux = nullptr;
    lenArr = 0;
}


void DynArr::fill(int typeSort) const
{
    switch (typeSort)
    {
    case 0:
        for (int i = 0; i < lenArr; i++)
        {
            arr[i] = i + 100;
        }
        break;
    case 1:
        for (int i = 0; i < lenArr; i++)
        {
            if (i > int(lenArr * 0.8) - 1 && i < lenArr * 0.9)
            {
                arr[i] = rand() % 1000 + 100;
            }
            else arr[i] = i + 100;
        }
        break;
    case 2:
        for (int i = 0; i < lenArr; i++)
        {
            arr[i] = lenArr - i - 1 + 100;
        }
        break;
    case 3:
        for (int i = 0; i < lenArr; i++)
        {
            arr[i] = rand() % 1000;
        }
        break;
    default:
        cerr << "\n\nОшибка: выбранного режима заполнения массива не существует.\n" << endl;
        exit(0);
    }
}


void DynArr::print() const
{
    for (size_t i = 0; i < lenArr; i++)
    {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}


void DynArr::print(ofstream& outFile) const
{
    for (size_t i = 0; i < lenArr; i++)
    {
        outFile << *(arr + i) << " ";
    }
    outFile << endl;
}


void DynArr::fill() const
{
    for (size_t i = 0; i < lenArr; i++)
    {
        aux[i] = arr[i] = 0;
    }
}


bool DynArr::isSorted() const
{
    for (int i = 1; i < getLen(); i++) 
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}


void DynArr::swap(int& left, int& right) const
{
    int temp = left;
    left = right;
    right = temp;
}


void DynArr::bubbleSort() const
{
    bool flag = true;
    int size = getLen();
    while (flag)
    {
        flag = false;
        for (int i = 1; i < size; i++)
        {
            if (arr[i - 1] > arr[i])
            {
                swap(arr[i - 1], arr[i]);
                flag = true;
            }
        }
        size--;
    }
}


void DynArr::selectionSort() const
{
    for (int i = 0; i < getLen() - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < getLen(); j++)
        {
            if (arr[minIndex] > arr[j]) minIndex = j;
        }
        if (minIndex != i)
        {
            swap(arr[minIndex], arr[i]);
        }
    }
}


void DynArr::insertSort(int low, int high) const
{
    if (low < 0 || low >= getLen() || high < 0 || high >= getLen())
        return;
    for (int i = low + 1; i <= high; i++)
    {
        int sorted = i - 1;
        while (sorted >= low && arr[sorted] > arr[sorted + 1])
        {
            swap(arr[sorted], arr[sorted + 1]);
            sorted--;
        }
    }
}


void DynArr::merge(int low, int mid, int high) const
{
    int k = low, i = low, j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            aux[k++] = arr[i++];
        else
            aux[k++] = arr[j++];
    }

    while (i <= mid)
    {
        aux[k++] = arr[i++];
    }

    while (j <= high)
    {
        aux[k++] = arr[j++];
    }

    for (int i = low; i <= high; i++)
    {
        arr[i] = aux[i];
    }
}


void DynArr::mergeSort(int low, int high) const
{
    if (low < 0 || low >= getLen() || high < 0 || high >= getLen())
        return;

    if (high <= low) return;

    int mid = (low + ((high - low) >> 1));

    mergeSort(low, mid);
    mergeSort(mid + 1, high);

    merge(low, mid, high);
}


// Разделение массива по схеме Lomuto
int DynArr::partition(int low, int high) const
{
    int pivot = arr[high];

    // элементы, меньшие точки поворота, будут перемещены влево от `pIndex`
    // элементы больше, чем точка поворота, будут сдвинуты вправо от `pIndex`
    // равные элементы могут идти в любом направлении
    int pIndex = low;

    for (int i = low; i < high; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(arr[i], arr[pIndex]);
            pIndex++;
        }
    }

    // поменять местами pIndex с пивотом
    swap(arr[pIndex], arr[high]);

    // вернуть индекс опорного элемента
    return pIndex;
}


int DynArr::randPartition(int low, int high) const
{
    int pivotIndex = rand() % (high - low + 1) + low;

    swap(arr[pivotIndex], arr[high]);

    return partition(low, high);
}


void DynArr::quickSort(int low, int high) const
{
    if (low < 0 || low >= getLen() || high < 0 || high >= getLen())
        return;

    if (low >= high) return;

    int pivot = randPartition(low, high);

    quickSort(low, pivot - 1);
    quickSort(pivot + 1, high);
}


// Сортировка Шелла с классической последовательностью gap
void DynArr::shellSort() const
{
    int n = getLen();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


// Сортировка Шелла с шагом "1, 3, 7, 15, 31, ..." (последовательность Седжвика)
void DynArr::shellSortSedgewick() const
{
    int n = getLen(), gap = 1;

    while (gap < n / 3)
    {
        gap = 3 * gap + 1;
    }
       
    while (gap >= 1) 
    {
        for (int i = gap; i < n; i++) 
        {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
        gap /= 2;
    }
}


// Сортировка Шелла с шагом "1, 4, 13, 40, 121, ..." (последовательность пратт)
void DynArr::shellSortPratt() const
{
    int n = getLen(), gap = 1;

    while (gap < n)
    {
        gap = 3 * gap + 1;
    }

    while (gap > 0) 
    {
        for (int i = gap; i < n; i++) 
        {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
        gap /= 3;
    }
}


void DynArr::heapify(int i, int low, int sizeHeap) const
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int largest = i;

    if (left < sizeHeap && arr[low + left] > arr[low + largest])
        largest = left;

    if (right < sizeHeap && arr[low + right] > arr[low + largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[low + i], arr[low + largest]);
        heapify(largest, low, sizeHeap);
    }
}


void DynArr::buildMaxHeap(int low, int sizeHeap) const
{
    int i = (sizeHeap - 2) / 2;
    while (i >= 0)
    {
        heapify(i--, low, sizeHeap);
    }
}


void DynArr::heapSort(int low, int high) const
{
    if (low < 0 || low >= getLen() || high < 0 || high >= getLen() || low >= high)
        return;

    int sizeHeap = high - low + 1;

    buildMaxHeap(low, sizeHeap);

    while (sizeHeap != 1)
    {
        swap(arr[low], arr[low + sizeHeap - 1]);

        sizeHeap--;

        heapify(0, low, sizeHeap);
    }
}


const int RUN = 32;
void DynArr::timSort() const
{
    int n = getLen();

    for (int i = 0; i < n; i += RUN)
    {
        insertSort(i, min((i + RUN - 1), (n - 1)));
    }

    for (int size = RUN; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right) merge(left, mid, right);
        }
    }
}


void DynArr::introSort() const
{
    int maxDepth = (int)(log(getLen()) * 2);
    innerIntroSort(0, getLen() - 1, maxDepth);
}


void DynArr::innerIntroSort(int low, int high, int maxDepth) const
{
    if ((high - low) < 16)
    {
        insertSort(low, high);
    }
    else if (maxDepth == 0)
    {
        heapSort(low, high);
    }
    else
    {
        int pivot = randPartition(low, high);
        innerIntroSort(low, pivot - 1, maxDepth - 1);
        innerIntroSort(pivot + 1, high, maxDepth - 1);
    }
}
