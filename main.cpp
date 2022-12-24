#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>

using namespace std;

int sz = 100;

void draw_state(int* array, SDL_Renderer* renderer, int red, int blue) {
	for (int i = 0; i < sz; i++) {
        if (i == red)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (i == blue)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else
		    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, i, 99, i, array[i]);
	}
}

void bubble_sort(int* array, SDL_Renderer* renderer) {
    for (int i = 0; i < sz; i++)
        for (int j = i; j < sz; j++) {
            if (array[i] > array[j]) swap(array[i], array[j]);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(array, renderer, i, j);
            SDL_RenderPresent(renderer);
            SDL_Delay(5);
        }
}

void selection_sort(int* array, SDL_Renderer* renderer) {
    for (int i = 0; i < sz; i++) {
        int min_loc = i;
        for (int j = i + 1; j < sz; j++) {
            if (array[j] < array[min_loc]) min_loc = j;
        }
        if (array[min_loc] < array[i]) swap(array[i], array[min_loc]);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_state(array, renderer, i, min_loc);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
}

void quick_sort(int* a, SDL_Renderer* renderer, int from, int to) {
	if (from >= to) return;
	int pivot = a[from], i = from, j = to;
	while (i < j) {	
        do i++; while(a[i] < pivot);
        do j--; while(a[j] > pivot);
		if (i < j) swap(a[i], a[j]);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_state(a, renderer, i, j);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
	}
    swap(a[from], a[j]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_state(a, renderer, i, j);
    SDL_RenderPresent(renderer);
    SDL_Delay(20);
	quick_sort(a, renderer, from, j);
	quick_sort(a, renderer, j + 1, to);
}

void merge(int* a, SDL_Renderer* renderer, int from, int mid, int to)
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
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(a, renderer, i1, i2);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
		}
		else {
			b[j] = a[i2];
			i2++;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(a, renderer, j, i2);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
		}
		j++;
	}
	// Note that only one of the two while loops below is executed
	// Copy any remaining entries of the first half
	while (i1 <= mid) {
		b[j] = a[i1];
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_state(a, renderer, j, i1);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
		i1++;
		j++;
	}
	// Copy any remaining entries of the second half
	while (i2 <= to) {
		b[j] = a[i2];
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_state(a, renderer, j, i2);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
		i2++;
		j++;
	}
	// Copy back from the temporary array
	for (j = 0; j < n; j++) {
        a[from + j] = b[j];
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_state(a, renderer, from + j, j);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
	// The temporary array is no longer needed
	delete[] b;
}

void merge_sort(int* array, SDL_Renderer* renderer, int from, int to) {
	if (from == to) return;
	int mid = (from + to) / 2;
	merge_sort(array, renderer, from, mid);
	merge_sort(array, renderer, mid + 1, to);
	merge(array, renderer, from, mid, to);
}

int main() {
    random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> d(1, 99);
	int array[sz];
	for (int i = 0; i < sz; i++)
		array[i] = d(gen);

    cout << "Sorting Algorithms:\n";
    cout << "1) Bubble Sort\n";
    cout << "2) Selection Sort\n";
    cout << "3) Quick Sort\n";
    cout << "4) Merge Sort\n";
    cout << "Select one: ";
    int choice;
    cin >> choice;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(100*10, 100*10, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 10, 10);

    if (choice == 1) bubble_sort(array, renderer);
    else if (choice == 2) selection_sort(array, renderer);
    else if (choice == 3) quick_sort(array, renderer, 0, sz);
    else if (choice == 4) merge_sort(array, renderer, 0, sz);
    else cout << "yay\n";
    
	return 0;
}