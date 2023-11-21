#include "func.h"


int main()
{
    setlocale(LC_ALL, "Rus");

    cout << "Лабораторная работа №2.\n"
        "Алгоритмы сортировки.\n"
        "Автор: Попов Максим. Группа 2309\n\n" << endl;

    const string filename = "outFile.txt";
    ofstream outFile(filename);

    try
    {
        if (!outFile.is_open())
        {
            throw runtime_error("не удалось открыть файл " + filename + " для записи.\n\n");
        }
    }
    catch (const exception& ex)
    {
        cerr << "Ошибка: " << ex.what() << endl;
        return 0;
    }

    cout << "Введите необходимое количестов массивов: ";
    int lenDynArr = getValue();
    DynArr* dynArr = new DynArr[lenDynArr];

    cout << "Выделение памяти под массивы." << endl;
    newDynArr(dynArr, lenDynArr);

    process(dynArr, lenDynArr, outFile);

    //clDynArr(dynArr, lenDynArr);
    cout << "Очищение памяти успешно завершено." << endl << endl;

    return 0;
}