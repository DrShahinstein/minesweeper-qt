# Minesweeper

Minesweeper game written in C++ using Qt6.

## Preview

https://github.com/user-attachments/assets/66a7b4fd-64ed-4994-a101-addfaca5b0e4

## Build

See [releases](https://github.com/DrShahinstein/minesweeper-qt/releases/tag/Stable).
If you want to build by hand, make sure you have [cmake](https://cmake.org/) and [qt](https://www.qt.io/download-open-source) installed on your machine.

### Linux
```bash
$ mkdir build
$ cd build     
$ cmake ..
$ make
$ ./minesweeper

# or

$ ./run
```

### Windows

Using [w64devkit](https://github.com/skeeto/w64devkit) terminal is recommended.

```bash
$ mkdir build
$ cd build
$ cmake -G "MinGW Makefiles" ..
$ make
$ ./minesweeper
```
