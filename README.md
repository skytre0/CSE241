# Advanced Programming

This repository contains the programming assignments for the UNIST 2-1 Advanced Programming course. Each assignment is structured into independent directories for systematic management.

## 📂 Directory Structure

Each assignment folder (`AssignmentXX`) follows a standardized structure:

- `src/`: Source code files (`.cc`, `.h`) and `Makefile`
- `report/`: Assignment documentation (PDFs) and submission archives (`.zip`)
- `data/`: Required data files for execution (e.g., `.wav` audio files)
- `build/`: Compiled object files (`.o`) and executable binaries

---

## 📝 Assignments Overview

### [Assignment 00](./Assignment00)
- **Topic**: Basic C++ Environment Setup and I/O
- **Description**: A foundational program that takes two integers as input and prints the absolute difference between them.

### [Assignment 01](./Assignment01)
- **Topic**: WAV Audio File Analysis (Peak Amplitude & Silence Detection)
- **Description**: Analyzes a `.wav` file to find its peak amplitude and detects periods of silence that last for at least 0.5 seconds.
- **Key Features**:
  - `find_silence` function for detecting contiguous silence
  - Precise amplitude calculation handling the `short` data type range limitations
  - Memory safety ensured by compiling with Address Sanitizer

### [Assignment 02](./Assignment02)
- **Topic**: Expression Tree Implementation & Symbolic Differentiation
- **Description**: Parses a mathematical expression into a tree structure, evaluates it at a given point, and performs symbolic differentiation.
- **Key Features**:
  - Class hierarchy design using `int_literal`, `monomial`, `addition`, `multiplication`, and `division`
  - Expression optimization/simplification (e.g., $1 \times x \to x$, $0 + x \to x$)
  - Evaluation of functions and their derivatives at specific points

---

## 🚀 How to Run

All assignments can be built using their respective `Makefile`. Execute the following commands within the `src` directory of each assignment.

### Assignment 00
```bash
cd Assignment00/src
make do
./do
# Enter two integers (e.g., 10 20)
```

### Assignment 01
```bash
cd Assignment01/src
make a01
./a01
# Enter the path to a wav file (e.g., ../data/s02.wav)
```

### Assignment 02
```bash
cd Assignment02/src
make main
./main
# Enter a mathematical expression (e.g., x2 + 3*x + 1)
# Enter an x value to evaluate at (e.g., 2)
```
