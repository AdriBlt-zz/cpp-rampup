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

template <class T>
void mergeSort(T* list, int length, int begin = 0) {
	if (length < 2) {
		return;
	}

	// Spliting the array in two
	int leftLength = length / 2;
	int rightLength = length - leftLength;
	int rightBegin = begin + leftLength;

	// Sorting each half
	// This could be done in parallel
	mergeSort(list, leftLength, begin);
	mergeSort(list, rightLength, rightBegin);

	// Merging the two sorted sub lists
	int leftIndex = begin;
	int rightIndex = rightBegin;
	int end = begin + length;
	T leftValue;
	T rightValue;
	// rightIndex = maxLeft
	while (leftIndex < rightIndex && rightIndex < end) {
		leftValue = list[leftIndex];
		rightValue = list[rightIndex];

		if (leftValue <= rightValue) {
			leftIndex++;
		}
		else {
			// We actually have to move the left array by one index to the right
			for (int i = rightIndex; i > leftIndex; i--) {
				list[i] = list[i-1];
			}

			list[leftIndex] = rightValue;
			
			// The left array has been shift by 1
			leftIndex++;

			rightIndex++;
		}
	}

	// Either the left array is empty
	// > The right array is already sorted, nothing to do
	// Or the right array is empty
	// > The Left array is already sorted and at the rigth place
}
