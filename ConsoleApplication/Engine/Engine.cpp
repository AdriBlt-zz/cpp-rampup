// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "IntListHelper.h"
#include "Sorting.h"

int main()
{
	using namespace std;

	/* // LinkedList
	LinkedList<std::string> list;
	for (int i = 0; i < 10; i++) {
		string value = to_string(i*i);
		list.pushFirst(value);
	}

	cout << list.popFirst() << endl;
	cout << list.peekFirst() << endl;
	cout << list.size() << endl;
	cout << list.toString() << endl;
	*/

	int size = 10;

	int* list = getIntList(size);
	cout << "Generate: " << isOrdered(list, size) << " : ";
	print(list, size);

	shuffle(list, size);
	cout << "Shuffle : " << isOrdered(list, size) << " : ";
	print(list, size);

	bubbleSort(list, size);
	cout << "Bubble  : " << isOrdered(list, size) << " : ";
	print(list, size);

	shuffle(list, size);
	cout << "Shuffle : " << isOrdered(list, size) << " : ";
	print(list, size);

	mergeSort(list, size);
	cout << "Merge   : " << isOrdered(list, size) << " : ";
	print(list, size);

	shuffle(list, size);
	cout << "Shuffle : " << isOrdered(list, size) << " : ";
	print(list, size);

	quickSort(list, size);
	cout << "Quick   : " << isOrdered(list, size) << " : ";
	print(list, size);

	delete[] list;

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
