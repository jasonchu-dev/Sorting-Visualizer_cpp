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

int main() {
    random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> d(1, 99);
	int array[sz];
	for (int i = 0; i < sz; i++)
		array[i] = d(gen);

    cout << "Sorting Algorithms:\n";
    cout << "1) Bubble Sort\n";
    cout << "2) Insertion Sort\n";
    cout << "Select one: ";
    int choice;
    cin >> choice;

    SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(100*10, 100*10, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 10, 10);

    if (choice == 1) {
        for (int i = 0; i < *(&array + 1) - array; i++)
            for (int j = i; j < *(&array + 1) - array; j++) {
                if (array[i] > array[j]) swap(array[i], array[j]);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                draw_state(array, renderer, i, j);
                SDL_RenderPresent(renderer);
                SDL_Delay(5);
            }
    }
    else if (choice == 2) {
        for (int i = 0; i < *(&array + 1) - array - 1; i++) {
            int min_loc = i;
            for (int j = i + 1; j < *(&array + 1) - array; j++) {
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
    else cout << "yay\n";
    
	return 0;
}