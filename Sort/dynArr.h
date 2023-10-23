#pragma once
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


class DynArr
{
public:
    DynArr(int lenArr);
    ~DynArr();

    void bubbleSort() const;
    void selectionSort() const;
    void insertSort(int low, int high) const;
    void mergeSort(int low, int high) const;
    void quickSort(int low, int high) const;
    void shellSort() const;
    void shellSortSedgewick() const;
    void shellSortPratt() const;
    void heapSort(int low, int high) const;
    void timSort() const;
    void introSort() const;

    void fill(int typeSort) const;
    void print() const;
    void print(ofstream& outFile) const;
    bool isSorted() const;
    void clear();

    int getBegEl() const { return  arr[0]; }
    int getEndEl() const { return  arr[getLen() - 1]; }
    int getLen() const { return lenArr; }
    bool isEmpty() const { return lenArr == 0; }

private:
    int* arr, * aux;
    int lenArr;

    void merge(int low, int mid, int high) const;

    int partition(int low, int high) const;
    int randPartition(int start, int end) const;

    void heapify(int i, int low, int sizeHeap) const;
    void buildMaxHeap(int low, int sizeHeap) const;

    void innerIntroSort(int low, int high, int maxdepth) const;

    void fill() const;
    void swap(int& left, int& right) const;
    int min(int x, int y) const { return (x < y) ? x : y; };
};
