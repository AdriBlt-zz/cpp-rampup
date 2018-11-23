#pragma once

template <class T>
void swap(T* a, T* b) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

template <class T>
void shuffle(T* list, int length) {
	for (int i = length-1; i > 0; i--) {
		// Each turn, we decide which index is going to
		// be in the i-th place.
		int index = rand() % (i+1); // return a number between [0;i]
		if (index != i) {
			swap(&list[index], &list[i]);
		}
	}
}

template <class T>
void bubbleSort(T* list, int length) {
	if (length == 1) {
		return;
	}

	int maxElementIndex;
	T* maxElementPtr;
	for (int len = length; len > 1; len--) {
		maxElementIndex = 0;
		maxElementPtr = &list[0];
		for (int i = 1; i < len; i++) {
			if (list[i] > *maxElementPtr) {
				maxElementIndex = i;
				maxElementPtr = &list[i];
			}
		}

		if (maxElementIndex != len - 1) {
			swap(maxElementPtr, &list[len - 1]);
		}
	}
}
