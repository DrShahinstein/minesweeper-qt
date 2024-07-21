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

## Not fun yet facts
* I used to prefer not to get too involved in Qt, because I used to get my blood boiling when I saw people programming in Qt with tools like QtCreator. I'm the kind of person who doesn't look beyond a text editor and a compiler to write code. Recently, my curiosity got the better of me and I started programming Qt in C++. It turns out that you can work well without the need for Qt tools, which I found cumbersome and overkill. While doing this project, I used one vim and one cmake (g++ bla bla also, same thing).

* Working around with Qt is yet a pain in the ass when it comes to Windows.
