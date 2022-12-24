#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>

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
        SDL_Delay(t);
	}
    swap(a[from], a[j]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_state(a, renderer, i, j);
    SDL_RenderPresent(renderer);
    SDL_Delay(t);
	quick_sort(a, renderer, from, j);
	quick_sort(a, renderer, j + 1, to);
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

int main(int argc, char** argv) {
    random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> d(1, 99);
	int array[sz];
	for (int i = 0; i < sz; i++)
		array[i] = d(gen);
    
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
            cout << "3) Quick Sort\n";
            cout << "4) Merge Sort\n";
            cout << "Select one: ";
            cin >> choice;
            if (choice == 1 || choice == 2 || choice == 3 || choice == 4) break;
            else cout << "Invalid, try again\n";
        }
        while (1) {
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
    else if (choice == 3) quick_sort(array, renderer, 0, sz);
    else if (choice == 4) merge_sort(array, renderer, 0, sz);
    else cout << "Invalid input\n";

    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
	return 0;
}