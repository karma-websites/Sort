#include "func.h"

const char* TYPESORT[]
{
    "Sort",
    "HalfSort",
    "RevSort",
    "RandSort"
};

const char* NAMESORT[]
{
    "BubbleSort",
    "SelectionSort",
    "InsertionSort",
    "MergeSort",
    "QuickSort",
    "ShellSort",
    "ShellSort2",
    "ShellSort3",
    "HeapSort",
    "TimSort",
    "IntroSort"
};


// Функции считывания из консоли

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
            cerr << "Неверный формат ввода.\nПопробуйте ввести значение еще раз: ";
        }
        else
        {
            ignoreLine();
            return value;
        }
    }
}


// Функции обработки массива указателей на классы массивов

void newArrArr(DynArr** const arrArr, int lenArrArr)
{
    for (size_t i = 0; i < lenArrArr; i++)
    {
        cout << i + 1 << ") Введите размер массива: ";
        int lenArr = getValue();
        arrArr[i] = new DynArr(lenArr);
    }
    cout << endl << endl;
}


void clArrArr(DynArr**& arrArr, int& lenArrArr)
{
    for (size_t i = 0; i < lenArrArr; i++)
    {
        arrArr[i]->clear();
    }
    if (arrArr)
    {
        delete[] arrArr;
        arrArr = nullptr;
        lenArrArr = 0;
    }
}


double timeSort(DynArr** arrArr, int numSort, int i)
{
    double time = -1;
    switch (numSort)
    {
    case 1:
        time = measureTime(bind(&DynArr::bubbleSort, arrArr[i]));
        break;
    case 2:
        time = measureTime(bind(&DynArr::selectionSort, arrArr[i]));
        break;
    case 3:
        time = measureTime(bind(&DynArr::insertSort, arrArr[i], 0, arrArr[i]->getLen() - 1));
        break;
    case 4:
        time = measureTime(bind(&DynArr::mergeSort, arrArr[i], 0, arrArr[i]->getLen() - 1));
        break;
    case 5:
        time = measureTime(bind(&DynArr::quickSort, arrArr[i], 0, arrArr[i]->getLen() - 1));
        break;
    case 6:
        time = measureTime(bind(&DynArr::shellSort, arrArr[i]));
        break;
    case 7:
        time = measureTime(bind(&DynArr::shellSort2, arrArr[i]));
        break;
    case 8:
        time = measureTime(bind(&DynArr::shellSort3, arrArr[i]));
        break;
    case 9:
        time = measureTime(bind(&DynArr::heapSort, arrArr[i], 0, arrArr[i]->getLen() - 1));
        break;
    case 10:
        time = measureTime(bind(&DynArr::timSort, arrArr[i]));
        break;
    case 11:
        time = measureTime(bind(&DynArr::introSort, arrArr[i]));
        break;
    }
    return time;
}


// Функция определяет время работы одной сортировки для выбранного количества и типа массивов
void listSort(DynArr** arrArr, int lenArrArr, int numSort, int typeSort, ofstream& outFile)
{
    locale loc("rus");
    cout.imbue(loc);

    cout << "Время для массивов в mc: " << endl;
    outFile << "Время для массивов в mc: " << endl;

    int numValues = 5;
    for (int i = 0; i < lenArrArr; i++)
    {
        double time = - 1, averageTime = 0;
        for (size_t j = 0; j < numValues; j++)
        {
            arrArr[i]->fill(typeSort);

            time = timeSort(arrArr, numSort, i);

            if (!arrArr[i]->isSorted())
            {
                cout << "Ошибка сортировки.\n\n" << endl;
                clArrArr(arrArr, lenArrArr);
                cout << "Очищение памяти успешно завершено.\n" << endl;
                outFile.close();
                exit(0);
            }

            averageTime += time;
        }
        cout << averageTime / numValues << endl;
        outFile << (int)averageTime / numValues << endl;
    }
    outFile << endl;
    cout << endl;
}


void printMenu(int lenNAMESORT)
{
    cout << "Список сортировок: \n0) Выйти из программы" << endl;

    for (int i = 0; i < lenNAMESORT; i++)
    {
        cout << i + 1 << ") " << NAMESORT[i] << endl;
    }
}


void process(DynArr** const arrArr, int lenArrArr, ofstream& outFile)
{
    while (true)
    {
        int lenNAMESORT = sizeof(NAMESORT) / sizeof(NAMESORT[0]);

        printMenu(lenNAMESORT);

        cout << "Выберите номер сортировки из списка: ";
        int numSort = getValue();
        cout << endl << endl;

        if (numSort == 0)
        {
            cout << "Выбран выход из программы.\n\n" << endl;
            break;
        }
        else if (numSort > 0 && numSort <= lenNAMESORT)
        {
            outFile << "Сортировка №" << numSort << ": " << NAMESORT[numSort - 1] << endl << endl;
            cout << "Сортировка №" << numSort << ": " << NAMESORT[numSort - 1] << endl << endl;

            int lenTYPESORT = sizeof(TYPESORT) / sizeof(TYPESORT[0]);
            for (int i = 0; i < lenTYPESORT; i++)
            {
                cout << TYPESORT[i] << " массивы" << endl;
                outFile << TYPESORT[i] << " массивы\n" << endl;
                listSort(arrArr, lenArrArr, numSort, i, outFile);
            }

            cout << endl;

            outFile << setfill('-') << setw(120) << endl << endl;
        }
        else
        {
            cout << "Такого способа сортировки нет в списке.\n\n" << endl;
        }
    }
    outFile.close();
}
