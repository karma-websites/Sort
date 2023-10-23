#pragma once
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

void newArrArr(DynArr** const arrArr, int lenArrArr);

void clArrArr(DynArr**& arrArr, int& lenArrArr);

double timeSort(DynArr** arrArr, int numSort, int i);

void listSort(DynArr** arrArr, int lenArrArr, int numSort, int typeSort, ofstream& outFile);

void printMenu(int lenNAMESORT);

void process(DynArr** const arrArr, int lenArrArr, ofstream& outFile);

template<typename T>
double measureTime(T function)
{
    auto startTime = steady_clock::now();
    function();
    auto endTime = steady_clock::now();
    auto elapsed = duration_cast<microseconds>(endTime - startTime);
    return (double)elapsed.count();
}
