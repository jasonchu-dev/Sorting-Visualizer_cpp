#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

int sz = 100, t = 0;
bool running = true;

void draw_state(int* array, SDL_Renderer* renderer, int purple, int green) {
	for (int i = 0; i < sz; i++) {
        if (i == purple)
            SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
        else if (i == green)
            SDL_SetRenderDrawColor(renderer, 124, 252, 0, 255);
        else
		    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, i, 99 - array[i], i, 99);
	}
}

void insertion_sort(int* array, SDL_Renderer* renderer) {
    for (int i = 1; i < sz; i++) {
        int j = i;
        while (j > 0 && array[j - 1] > array[j]) {
            swap(array[j], array[j - 1]);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(array, renderer, i, j);
            SDL_RenderPresent(renderer);
            SDL_Delay(t);
            j--;
        }
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
            SDL_Delay(t);
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
        SDL_Delay(t);
    }
}

void quicksort(int* a, SDL_Renderer* renderer, int from, int to) {
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
        SDL_Delay(t);
	}
    swap(a[from], a[j]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_state(a, renderer, i, j);
    SDL_RenderPresent(renderer);
    SDL_Delay(t);
	quicksort(a, renderer, from, j);
	quicksort(a, renderer, j + 1, to);
}

void merge(int* a, SDL_Renderer* renderer, int from, int mid, int to)
{
	int n = to - from + 1;
	int *b = new int[n];
	int i1 = from;
	int i2 = mid + 1;
	int j = 0;
	while (i1 <= mid && i2 <= to) {
		if (a[i1] < a[i2]) {
			b[j] = a[i1];
			i1++;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(a, renderer, i1, i2);
            SDL_RenderPresent(renderer);
            SDL_Delay(t);
		}
		else {
			b[j] = a[i2];
			i2++;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(a, renderer, j, i2);
            SDL_RenderPresent(renderer);
            SDL_Delay(t);
		}
		j++;
	}
	while (i1 <= mid) {
		b[j] = a[i1];
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_state(a, renderer, j, i1);
        SDL_RenderPresent(renderer);
        SDL_Delay(t);
		i1++;
		j++;
	}
	while (i2 <= to) {
		b[j] = a[i2];
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_state(a, renderer, j, i2);
        SDL_RenderPresent(renderer);
        SDL_Delay(t);
		i2++;
		j++;
	}
	for (j = 0; j < n; j++) {
        a[from + j] = b[j];
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_state(a, renderer, from + j, j);
        SDL_RenderPresent(renderer);
        SDL_Delay(t);
    }
	delete[] b;
}

void merge_sort(int* array, SDL_Renderer* renderer, int from, int to) {
	if (from == to) return;
	int mid = (from + to) / 2;
	merge_sort(array, renderer, from, mid);
	merge_sort(array, renderer, mid + 1, to);
	merge(array, renderer, from, mid, to);
}


void heapify(int arr[], SDL_Renderer* renderer, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
		largest = left;

	if (right < n && arr[right] > arr[largest])
		largest = right;

	if (largest != i) {
		swap(arr[i], arr[largest]);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_state(arr, renderer, i, largest);
		SDL_RenderPresent(renderer);
		SDL_Delay(t);
		heapify(arr, renderer, n, largest);
	}
}

void heapsort(int arr[], SDL_Renderer* renderer) {
	for (int i = sz / 2 - 1; i >= 0; i--)
		heapify(arr, renderer, sz, i);

	for (int i = sz - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_state(arr, renderer, 0, i);
		SDL_RenderPresent(renderer);
		SDL_Delay(t);
		heapify(arr, renderer, i, 0);
	}
}

void shellsort(int arr[], SDL_Renderer* renderer) {
	for (int gap = sz / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < sz; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				draw_state(arr, renderer, j, j - gap);
				SDL_RenderPresent(renderer);
				SDL_Delay(t);
			}
			arr[j] = temp;
		}
	}
}

int main(int argc, char** argv) {
    int array[sz];
    for (int i = 0; i < sz; i++)
        array[i] = i;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(array, array + sz, default_random_engine(seed));

    int choice;

    if (argc == 2) choice = atoi(argv[1]);
    else if (argc == 3) {
        choice = atoi(argv[1]);
        t = atoi(argv[2]);
    }
    else {
        while (1) {
            cout << "Sorting Algorithms:\n";
            cout << "1) Bubble Sort\n";
            cout << "2) Selection Sort\n";
            cout << "3) Quicksort\n";
            cout << "4) Merge Sort\n";
            cout << "5) Insertion Sort\n";
            cout << "6) Heapsort\n";
            cout << "7) Shellsort\n";
            cout << "8) Do all\n";
            cout << "Select one: ";
            cin >> choice;
            if (choice > 0 && choice < 9) break;
            else cout << "Invalid, try again\n";
        }
        while (1) {
			if (choice == 8) break;
            cout << "Speed of algorithm in milliseconds: ";
            cin >> t;
            if (t < 0) cout << "Must be 0 or above, try again\n";
            else break;
        }
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(100*10, 100*10, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 10, 10);
    SDL_SetWindowTitle(window, "Sorting Visualizer");

    if (choice == 1) bubble_sort(array, renderer);
    else if (choice == 2) selection_sort(array, renderer);
    else if (choice == 3) quicksort(array, renderer, 0, sz);
    else if (choice == 4) merge_sort(array, renderer, 0, sz);
    else if (choice == 5) insertion_sort(array, renderer);
    else if (choice == 6) heapsort(array, renderer);
    else if (choice == 7) shellsort(array, renderer);
    else if (choice == 8) {
        shuffle(array, array + sz, default_random_engine(seed));
        t = 0;
        bubble_sort(array, renderer);
        SDL_Delay(500);

        shuffle(array, array + sz, default_random_engine(seed));
        t = 20;
        selection_sort(array, renderer);
        SDL_Delay(500);

        shuffle(array, array + sz, default_random_engine(seed));
        t = 10;
        quicksort(array, renderer, 0, sz);
        SDL_Delay(500);
        
        shuffle(array, array + sz, default_random_engine(seed));
        t = 2;
        merge_sort(array, renderer, 0, sz);
        SDL_Delay(500);

        shuffle(array, array + sz, default_random_engine(seed));
        t = 0;
        insertion_sort(array, renderer);
        SDL_Delay(500);

        shuffle(array, array + sz, default_random_engine(seed));
        t = 3;
        heapsort(array, renderer);
        SDL_Delay(500);

        shuffle(array, array + sz, default_random_engine(seed));
        t = 7;
        shellsort(array, renderer);
    }
    else cout << "Invalid input\n";

    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
	return 0;
}