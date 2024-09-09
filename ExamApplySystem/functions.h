#pragma once
#include <iostream>
#include "basics.h"
using namespace std;

void printOutcome(const char* ch, const Info& info);

Info BubbleSort(int arr[], int length);

Info SelectionSort(int arr[], int length);