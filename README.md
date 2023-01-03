# Sorting Visualizer (C++)

Sorting visualizer using C++ and SDL2 library.

## Sorts implemented:
* Bubble Sort
* Insertion Sort
* Quicksort
* Merge Sort

## Requirements
* Just need SDL2 library

## Run
```
    git clone https://github.com/jasonchu-dev/Sorting-Visualizer_cpp.git
    cd Sorting-Visualizer_cpp
```
If you have GNU Make:
```
    make
```
Else do:
```
    g++ -I SDL2_files/include -L SDL2_files/lib main.cpp -lmingw32 -lSDL2main -lSDL2 -o a.exe
    ./a.exe
```