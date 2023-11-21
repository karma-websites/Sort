#pragma once

#include <string>
#include <chrono>
#include <functional>
#include <iomanip>
#include <locale>

#include "dynArr.h"

using namespace std::chrono;


// Функции считывания из консоли

void ignoreLine();

int getValue();


// Функции обработки массива указателей на классы массивов

void newDynArr(DynArr* const dynArr, int lenDynArr);

void clDynArr(DynArr*& dynArr, int& lenDynArr);

double timeSort(DynArr* dynArr, int numSort, int i);

void listSort(DynArr* dynArr, int lenDynArr, int numSort, int typeSort, ofstream& outFile);

void printMenu(int len_NAME_SORT);

void process(DynArr* const dynArr, int lenDynArr, ofstream& outFile);


// Функция замера времени

template<typename T>
double measureTime(T function)
{
    auto startTime = steady_clock::now();
    function();
    auto endTime = steady_clock::now();
    auto elapsed = duration_cast<nanoseconds>(endTime - startTime);
    return (double)elapsed.count();
}
