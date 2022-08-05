#include <iostream>

using namespace std;

int a[] = {10, 431, 76, 21, 45, 6, 657, 76, 34, 3, 231, 4, 4, 6, 6, 7, 1};

void bubble_sort() {
	while (1) {
	    int count_swap = 0;
		for (int i = 0, j = 1; j < *(&a + 1) - a; ++i, ++j) {
			if (a[i] > a[j]) {
				swap(a[i], a[j]);
				++count_swap;
			}
		}
		if (count_swap == 0) break;
	}
}

void selection_sort() {
    for (int i = 0; i < *(&a + 1) - a - 1; i++) {
        int min_loc = i;
        for (int j = i + 1; j < *(&a + 1) - a; j++) {
            if (a[j] < a[min_loc]) min_loc = j;
        }
        if (a[min_loc] < a[i]) swap(a[i], a[min_loc]);
    }
}

void quick_sort(int from, int to) {
	if (from >= to) return;
	int pivot = a[from], i = from, j = to;
	while (i < j) {	
        do i++; while(a[i] < pivot);
        do j--; while(a[j] > pivot);
		if (i < j) swap(a[i], a[j]);
	}
    swap(a[from], a[j]);
	quick_sort(from, j);
	quick_sort(j + 1, to);
}

void merge(int from, int mid, int to)
{
	// Size of the range to be merged	
	int n = to - from + 1;
	// Merge both halves into a temporary array b
	// We allocate the array dynamically because its size is only
	// known at run time—see Section 7.4
	int *b = new int[n];
	int i1 = from;
	// Next element to consider in the first half
	int i2 = mid + 1;
	// Next element to consider in the second half
	int j = 0; // Next open position in b 
	// As long as neither i1 nor i2 is past the end, move the smaller
	// element into b
	while (i1 <= mid && i2 <= to) {
		if (a[i1] < a[i2]) {
			b[j] = a[i1];
			i1++;
		}
		else {
			b[j] = a[i2];
			i2++;
		}
		j++;
	}
	// Note that only one of the two while loops below is executed
	// Copy any remaining entries of the first half
	while (i1 <= mid) {
		b[j] = a[i1];
		i1++;
		j++;
	}
	// Copy any remaining entries of the second half
	while (i2 <= to) {
		b[j] = a[i2];
		i2++;
		j++;
	}
	// Copy back from the temporary array
	for (j = 0; j < n; j++) a[from + j] = b[j];
	// The temporary array is no longer needed
	delete[] b;
}

/************** MERGE SORT MAIN FUNCTION *****************/
void merge_sort(int from, int to) {
	if (from == to) return;
	int mid = (from + to) / 2;
	merge_sort(from, mid);
	merge_sort(mid + 1, to);
	merge(from, mid, to);
}

int main() {
    for (const int &i : a)
        cout << i << ' ';
    cout << endl;
    // merge_sort(0, *(&a + 1) - a - 1);
	bubble_sort();
    for (const int &i : a)
        cout << i << ' ';
    cout << endl;
    return 0;
}