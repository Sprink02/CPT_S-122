#include <iostream>
#include <print>
#include <vector>
#include <random>
#include <limits>
#include <chrono>

#pragma once
using std::vector;
using std::print;

//std pause Wait for \n
inline void pause()
{
    std::print("Press ENTER to continue");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


//vector<int> merge(vector<int> v1, vector<int> v2)
//{
//    vector<int> v3;
//    v3.reserve(v1.size() + v2.size());
//    int i = 0, j = 0;
//
//    while (i < (int)v1.size() && j < (int)v2.size())
//    {
//        if (v1[i] < v2[j])
//        {
//            v3.push_back(v1[i]);
//            i++;
//        }
//        else
//        {
//            v3.push_back(v2[j]);
//            j++;
//        }
//    }
//
//    while (i < (int)v1.size())
//    {
//        v3.push_back(v1[i]);
//        i++;
//    }
//
//    while (j < (int)v2.size())
//    {
//        v3.push_back(v2[j]);
//        j++;
//    }
//
//    return v3;
//}

//vector<int> merge_sort(vector<int> v, int l, int r)
//{
//    vector<int> nV;
//    nV.reserve(v.size());
//
//    if (l == r)
//    {
//        nV.push_back(v[l]);
//        return nV;
//    }
//
//    int m = (l + r) / 2;
//
//    vector<int> lSorted = merge_sort(v, l, m);
//    vector<int> rSorted = merge_sort(v, m + 1, r);
//
//    nV = merge(lSorted, rSorted);
//
//    return nV;
//}

#include <iostream>
#include <vector>
using namespace std;

// base case: arr.size() = 1; 
// recursive case = keeps splitting the array 

template <typename T>

void merge(vector<T>& arr, int left, int mid, int right)
{
    vector<T> final;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
        {
            final.push_back(arr[i]);
            i++;
        }
        else
        {
            final.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid)
    {
        final.push_back(arr[i]);
        i++;
    }

    while (j <= right)
    {
        final.push_back(arr[j]);
        j++;
    }

    for (int k = 0; k < final.size(); k++)
    {
        arr[left + k] = final[k];
    }
}

template <typename T>
void mergeSort(vector<T>& arr, int left, int right)
{
    if (left == right)
    {
        return;
    }

    int mid = (left + right) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}





int main()
{
    auto start = std::chrono::system_clock::now();
    for (int k = 0; k < 100; k++)
    {
        
        std::srand(std::time(NULL));

        vector<int> v;
        v.reserve(10000);
        for (int i = 0; i < 10000; i++)
        {
            v.push_back(std::rand());
        }

        mergeSort(v, 0, 9999);
    }
    auto end = std::chrono::system_clock::now();
    
    print("total:{} \nAvg: {}", (end - start) / (double)10000000, (end - start) / (double)10000000/100);
    return 0;
}