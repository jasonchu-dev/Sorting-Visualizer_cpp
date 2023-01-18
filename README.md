# Sorting Visualizer (C++)

Sorting visualizer using C++ and SDL2 library.


||Bubble Sort|Selection Sort|Quicksort|Merge Sort|Insertion Sort|Heapsort|Shellsort
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:
|Best|$O\left(n\right)$|$O\left(n^2\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\text{ }log\text{ }n\right)$
|Average|$O\left(n^2\right)$|$O\left(n^2\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n^2\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n^{4/3}\right)$|
|Worst|$O\left(n^2\right)$|$O\left(n^2\right)$|$O\left(n^2\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n^2\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n^{3/2}\right)$|
|Memory|$1$|$1$|$O\left(log\text{ }n\right)$|$O\left(n\right)$|$1$|$1$|$1$
|Stable|Yes|No|No|Yes|Yes|No|No

<!-- ||Best|Average|Worst|Memory|Stable
|:---:|:---:|:---:|:---:|:---:|:---:
|Bubble Sort|$O\left(n\right)$|$O\left(n^2\right)$|$O\left(n^2\right)$|$1$|Yes
|Selection Sort|$O\left(n^2\right)$|$O\left(n^2\right)$|$O\left(n^2\right)$|$1$|No
|Quicksort|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n^2\right)$|$O\left(log\text{ }n\right)$|No
|Merge Sort|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\right)$|Yes
|Insertion Sort|$O\left(n\right)$|$O\left(n^2\right)$|$O\left(n^2\right)$|$1$|Yes
|Heapsort|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n\text{ }log\text{ }n\right)$|$1$|No
|Shellsort|$O\left(n\text{ }log\text{ }n\right)$|$O\left(n^{4/3}\right)$|$O\left(n^{3/2}\right)$|$1$|No -->

## Requirements
* SDL2 library

## Run
```
    $ git clone https://github.com/jasonchu-dev/Sorting-Visualizer_cpp.git
    $ cd Sorting-Visualizer_cpp
```
If you have GNU Make:
```
    $ make
```
Else do:
```
    $ g++ -I SDL2_files/include -L SDL2_files/lib main.cpp -lmingw32 -lSDL2main -lSDL2 -o a.exe
    $ ./a.exe
```