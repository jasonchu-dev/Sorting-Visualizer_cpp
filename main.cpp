#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

int n = 100, t = 0;
bool running = true;

void draw_state(int* array, SDL_Renderer* renderer, int purple, int green) {
	for (int i = 0; i < n; i++) {
        if (i == purple)
            SDL_SetRenderDrawColor(renderer, 127, 0, 255, 255);
        else if (i == green)
            SDL_SetRenderDrawColor(renderer, 124, 252, 0, 255);
        else
		    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, i, 99 - array[i], i, 99);
	}
}

void insertionSort(int* array, SDL_Renderer* renderer) {
    for (int i = 1; i < n; i++) {
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

void bubbleSort(int* array, SDL_Renderer* renderer) {
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            if (array[i] > array[j]) swap(array[i], array[j]);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(array, renderer, i, j);
            SDL_RenderPresent(renderer);
            SDL_Delay(t);
        }
}

void selectionSort(int* array, SDL_Renderer* renderer) {
    for (int i = 0; i < n; i++) {
        int min_loc = i;
        for (int j = i + 1; j < n; j++) {
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

void quickSort(int* a, SDL_Renderer* renderer, int from, int to) {
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
	quickSort(a, renderer, from, j);
	quickSort(a, renderer, j + 1, to);
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

void mergeSort(int* array, SDL_Renderer* renderer, int from, int to) {
	if (from == to) return;
	int mid = (from + to) / 2;
	mergeSort(array, renderer, from, mid);
	mergeSort(array, renderer, mid + 1, to);
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

void heapSort(int arr[], SDL_Renderer* renderer) {
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, renderer, n, i);

	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_state(arr, renderer, 0, i);
		SDL_RenderPresent(renderer);
		SDL_Delay(t);
		heapify(arr, renderer, i, 0);
	}
}

void shellSort(int arr[], SDL_Renderer* renderer) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
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
    int array[n];
    for (int i = 0; i < n; i++)
        array[i] = i;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(array, array + n, default_random_engine(seed));

    int choice;

    if (argc == 2) choice = atoi(argv[1]);
    else if (argc == 3) {
        choice = atoi(argv[1]);
        t = atoi(argv[2]);
    }
    else {
        while (1) {
            cout << endl;
            cout << "Time complexities:" << endl << endl;
            cout << "            | Bubble Sort | Selection Sort | Quicksort | Merge Sort | Insertion Sort | Heapsort | Shellsort |" << endl;
            cout << "   ----------------------------------------------------------------------------------------------------------" << endl;
            cout << "    Best    |      n      |       n^2      |  n log n  |   n log n  |        n       |  n log n |  n log n  |" << endl;
            cout << "   ----------------------------------------------------------------------------------------------------------" << endl;
            cout << "    Average |     n^2     |       n^2      |  n log n  |   n log n  |       n^2      |  n log n |  n^(4/3)  |" << endl;
            cout << "   ----------------------------------------------------------------------------------------------------------" << endl;
            cout << "    Worst   |     n^2     |       n^2      |    n^2    |   n log n  |       n^2      |  n log n |  n^(3/2)  |" << endl;
            cout << "   ----------------------------------------------------------------------------------------------------------" << endl;
            cout << "    Memory  |      1      |        1       |   log n   |      n     |        1       |     1    |     1     |" << endl;
            cout << "   ----------------------------------------------------------------------------------------------------------" << endl;
            cout << "    Stable  |      Y      |        N       |     N     |      Y     |        Y       |     N    |     N     |" << endl;
            cout << endl;
            cout << "Sorting Algorithms:" << endl << endl;
            cout << "   1) Bubble Sort" << endl;
            cout << "   2) Selection Sort" << endl;
            cout << "   3) Quicksort" << endl;
            cout << "   4) Merge Sort" << endl;
            cout << "   5) Insertion Sort" << endl;
            cout << "   6) Heapsort" << endl;
            cout << "   7) Shellsort" << endl;
            cout << "   8) Do all" << endl;
            cout << endl << "Select one: ";
            cin >> choice;
            if (choice > 0 && choice < 9) break;
            else cout << "Invalid, try again";
        }
        while (1) {
			if (choice == 8) break;
            cout << "Speed of algorithm in milliseconds: ";
            cin >> t;
            if (t < 0) cout << "Must be 0 or above, try again";
            else break;
        }
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(100*10, 100*10, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 10, 10);
    SDL_SetWindowTitle(window, "Sorting Visualizer");

    if (choice == 1) bubbleSort(array, renderer);
    else if (choice == 2) selectionSort(array, renderer);
    else if (choice == 3) quickSort(array, renderer, 0, n);
    else if (choice == 4) mergeSort(array, renderer, 0, n);
    else if (choice == 5) insertionSort(array, renderer);
    else if (choice == 6) heapSort(array, renderer);
    else if (choice == 7) shellSort(array, renderer);
    else if (choice == 8) {
        shuffle(array, array + n, default_random_engine(seed));
        t = 0;
        bubbleSort(array, renderer);
        SDL_Delay(500);

        shuffle(array, array + n, default_random_engine(seed));
        t = 20;
        selectionSort(array, renderer);
        SDL_Delay(500);

        shuffle(array, array + n, default_random_engine(seed));
        t = 10;
        quickSort(array, renderer, 0, n);
        SDL_Delay(500);
        
        shuffle(array, array + n, default_random_engine(seed));
        t = 2;
        mergeSort(array, renderer, 0, n);
        SDL_Delay(500);

        shuffle(array, array + n, default_random_engine(seed));
        t = 0;
        insertionSort(array, renderer);
        SDL_Delay(500);

        shuffle(array, array + n, default_random_engine(seed));
        t = 3;
        heapSort(array, renderer);
        SDL_Delay(500);

        shuffle(array, array + n, default_random_engine(seed));
        t = 7;
        shellSort(array, renderer);
    }
    else cout << "Invalid input";

    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
	return 0;
}