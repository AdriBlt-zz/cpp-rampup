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
void mergeSort(T* list, int length, int begin) {
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

template <class T>
void mergeSort(T* list, int length) {
	mergeSort(list, length, 0);
}

template <class T>
void quickSort(T* list, int length, int begin) {
	if (length < 2) {
		return;
	}

	// Choose a pivot value and put it on the right
	int pivotIndex = begin + length - 1;
	T pivotValue = list[pivotIndex];

	int leftIndex = begin;
	int rightIndex = pivotIndex - 1;
	while (leftIndex < rightIndex) {
		// Searching from right to left values lower than the pivot
		if (list[rightIndex] >= pivotValue) {
			rightIndex--;
			continue;
		}

		// Searching from left to right values highter than the pivot
		if (list[leftIndex] <= pivotValue) {
			leftIndex++;
			continue;
		}

		// Swaping them and move to the center until the 2 indexes meet
		swap(&list[leftIndex], &list[rightIndex]);
		leftIndex++;
		rightIndex--;
	}

	// Swaping the pivot with the highter value the most on the left
	// "nextPivotIndex = rightIndex" if all values are bigger than the pivot
	int nextPivotIndex = list[rightIndex] <= pivotValue ? rightIndex + 1 : rightIndex; 

	if (nextPivotIndex != pivotIndex) {
		swap(&list[nextPivotIndex], &list[pivotIndex]);
	}

	// Calling quickSort on the two sub lists
	int leftLength = nextPivotIndex - begin;
	quickSort(list, leftLength, begin);

	int rightLength = length - leftLength - 1;
	quickSort(list, rightLength, nextPivotIndex + 1);
}

template <class T>
void quickSort(T* list, int length) {
	quickSort(list, length, 0);
}
