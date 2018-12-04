// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "IntListHelper.h"
#include "LinkedList.h"
#include "Sorting.h"

void mainLinkedList();
void mainSorting();

int main()
{
	// LinkedList
	mainLinkedList();
	
	// Sorting
	mainSorting();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

void mainLinkedList()
{
	LinkedList<int> list;
	for (int i = 0; i < 10; i++) {
		list.pushFirst(i*i);
	}

	std::cout << list.popFirst() << std::endl;
	std::cout << list.peekFirst() << std::endl;
	std::cout << list.size() << std::endl;
	std::cout << list << std::endl;
}

void DisplayList(int* list, const int size, const char* name) {
	std::cout << name << ": " << isOrdered(list, size) << " : ";
	print(list, size);
}

void ShuffleSortDisplay(int* list, const int size, const char* name, void(*sortFuncPtr)(int*, int)) {
	shuffle(list, size);
	DisplayList(list, size, "Shuffle");

	sortFuncPtr(list, size);
	DisplayList(list, size, name);
}

void mainSorting()
{
	using namespace std;
	int size = 10;

	int* list = getIntList(size);
	DisplayList(list, size, "Generate");

	ShuffleSortDisplay(list, size, "Bubble  ", bubbleSort);
	ShuffleSortDisplay(list, size, "Merge   ", mergeSort);
	ShuffleSortDisplay(list, size, "Quick   ", quickSort);

	delete[] list;
}
