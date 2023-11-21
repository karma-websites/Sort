#include "func.h"

const string TYPESORT[]
{
    "Sort",
    "HalfSort",
    "RevSort",
    "RandSort"
};

const string NAMESORT[]
{
    "BubbleSort",
    "SelectionSort",
    "InsertionSort",
    "MergeSort",
    "QuickSort",
    "ShellSort",
    "ShellSortKnuth",
    "ShellSortHib",
    "HeapSort",
    "TimSort",
    "IntroSort"
};


// ������� ���������� �� �������

void ignoreLine()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValue()
{
    while (true)
    {
        int value;
        cin >> value;
        if (cin.fail() || value < 0)
        {
            cin.clear();
            ignoreLine();
            cerr << "�������� ������ �����.\n���������� ������ �������� ��� ���: ";
        }
        else
        {
            ignoreLine();
            return value;
        }
    }
}


// ������� ��������� ������� ���������� �� ������ ��������

void newDynArr(DynArr* const dynArr, int lenDynArr)
{
    int lenArr = 0;
    for (size_t i = 0; i < lenDynArr; i++)
    {
        cout << i + 1 << ") ������� ������ �������: ";
        lenArr = getValue();
        dynArr[i] = DynArr(lenArr);
    }
    cout << endl << endl;
}


void clDynArr(DynArr*& dynArr, int& lenDynArr)
{
    for (size_t i = 0; i < lenDynArr; i++)
    {
        dynArr[i].clear();
    }
    if (dynArr)
    {
        delete[] dynArr;
        dynArr = nullptr;
        lenDynArr = 0;
    }
}


double timeSort(DynArr* const dynArr, int numSort, int i)
{
    double time = -1;
    switch (numSort)
    {
    case 1:
        time = measureTime(bind(&DynArr::bubbleSort, &dynArr[i]));
        break;
    case 2:
        time = measureTime(bind(&DynArr::selectionSort, &dynArr[i]));
        break;
    case 3:
        time = measureTime(bind(&DynArr::insertSort, &dynArr[i], 0, dynArr[i].getLen() - 1));
        break;
    case 4:
        time = measureTime(bind(&DynArr::mergeSort, &dynArr[i], 0, dynArr[i].getLen() - 1));
        break;
    case 5:
        time = measureTime(bind(&DynArr::quickSort, &dynArr[i], 0, dynArr[i].getLen() - 1));
        break;
    case 6:
        time = measureTime(bind(&DynArr::shellSort, &dynArr[i]));
        break;
    case 7:
        time = measureTime(bind(&DynArr::shellSortKnuth, &dynArr[i]));
        break;
    case 8:
        time = measureTime(bind(&DynArr::shellSortHib, &dynArr[i]));
        break;
    case 9:
        time = measureTime(bind(&DynArr::heapSort, &dynArr[i], 0, dynArr[i].getLen() - 1));
        break;
    case 10:
        time = measureTime(bind(&DynArr::timSort, &dynArr[i]));
        break;
    case 11:
        time = measureTime(bind(&DynArr::introSort, &dynArr[i]));
        break;
    }
    return time;
}


// ������� ���������� ����� ������ ����� ���������� ��� ���������� ���������� � ���� ��������
void listSort(DynArr* dynArr, int lenDynArr, int numSort, int typeSort, ofstream& outFile)
{
    locale loc("rus");
    cout.imbue(loc);

    cout << "����� ��� �������� � mc: " << endl;
    outFile << "����� ��� �������� � mc: " << endl;

    int numValues = 5;
    for (int i = 0; i < lenDynArr; i++)
    {
        double time = - 1, averageTime = 0;
        for (size_t j = 0; j < numValues; j++)
        {
            dynArr[i].fill(typeSort);

            time = timeSort(dynArr, numSort, i);

            if (!dynArr[i].isSorted())
            {
                cout << "������ ����������.\n\n" << endl;
                clDynArr(dynArr, lenDynArr);
                cout << "�������� ������ ������� ���������.\n" << endl;
                outFile.close();
                exit(0);
            }

            averageTime += time;
        }
        cout << averageTime / numValues << endl;
        outFile << static_cast<int>(averageTime) / numValues << endl;
    }
    outFile << endl;
    cout << endl;
}


void printMenu(int lenNAMESORT)
{
    cout << "������ ����������: \n0) ����� �� ���������" << endl;

    for (int i = 0; i < lenNAMESORT; i++)
    {
        cout << i + 1 << ") " << NAMESORT[i] << endl;
    }
}


void process(DynArr* const dynArr, int lenDynArr, ofstream& outFile)
{
    while (true)
    {
        int lenNameSort = sizeof(NAMESORT) / sizeof(NAMESORT[0]);

        printMenu(lenNameSort);

        cout << "�������� ����� ���������� �� ������: ";
        int numSort = getValue();

        cout << endl << endl;

        if (numSort == 0)
        {
            cout << "������ ����� �� ���������.\n\n" << endl;
            return;
        }
        else if (numSort > 0 && numSort <= lenNameSort)
        {
            outFile << setfill('=') << setw(120);
            outFile << "\n\n���������� �" << numSort << ": " << NAMESORT[numSort - 1] << "\n" << endl;
            cout << "���������� �" << numSort << ": " << NAMESORT[numSort - 1] << "\n" << endl;

            int lenTypeSort = sizeof(TYPESORT) / sizeof(TYPESORT[0]);
            for (int i = 0; i < lenTypeSort; i++)
            {
                cout << TYPESORT[i] << " �������" << endl;
                outFile << TYPESORT[i] << " �������\n" << endl;
                listSort(dynArr, lenDynArr, numSort, i, outFile);
            }

            cout << endl;
        }
        else
        {
            cout << "������ ������� ���������� ��� � ������.\n\n" << endl;
        }
    }
    outFile.close();
}
