# Student Report Management System

A console-based Student Report Management System developed in C++ using file handling and CMake.

## Features

- Add student records
- Display all students
- Search students by roll number
- Update student details
- Delete student records
- Find the topper
- Calculate total marks, percentage, and grade
- Save and load records using a file
- Validate positive and duplicate roll numbers

## Technologies Used

- C++
- C++14
- CMake
- MinGW GCC
- File Handling

## Requirements

- Windows
- MinGW GCC compiler
- CMake
- MinGW Make

## Build Instructions

Open PowerShell in the project directory and run:

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM="C:/MinGW/bin/mingw32-make.exe" -DCMAKE_CXX_COMPILER="C:/MinGW/bin/g++.exe"
cmake --build build
```

## Run the Program

```powershell
.\build\StudentReportSystem.exe
```

## Data Storage

Student records are stored locally in `students.txt`. This file is excluded from Git to avoid publishing local student data.

## Project Structure

```text
StudentReportSystem/
├── main.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Testing

The project has been tested for compilation, CMake build, student search, update, invalid and duplicate roll numbers, topper display, and saving/loading records across program restarts.

## Author

Suraj Sharma — IQ Init