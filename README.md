# Graphs application

All the steps to install and run the project are described in this document are for Debian-based systems. If you are using another system, you may need to adapt the commands, but the steps are the same.

## Requirements

- Git

- CMake

- C++ Compiler

```bash
sudo apt update
sudo apt install git cmake g++ 
```

## Installation

```bash
cmake -B build
cmake --build build
```

## Running

```bash
build/bin/graphs
```

## Usage

To choose the graph you want to see, just type the number on you keyboard of the graph:

1. 3 vertices per triangle

2. diagonal 45 deg lines

3. filled triangles of fixed size

4. filled squares of fixed size

5. filled circles of fixed size

To draw the graph, press left mouse button in the window.

To clear the screen, press DELETE key.

To delete the last figure, press BACKSPACE key.

To exit the program, just close the window.
