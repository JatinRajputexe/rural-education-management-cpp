# Rural Education Management System (C++)

A C++ OOP console application that manages students, teachers, courses, attendance and learning resources for a rural education centre. It supports **SDG 4** (Quality Education) and **SDG 10** (Reduced Inequalities).

## Features
- Student registration with duplicate ID check
- Course enrollment (no duplicate enrollment)
- Attendance tracking and attendance percentage
- Marks, grades and ranking by average marks
- Learning resources per course
- Saves and loads student records from a file (`students.txt`)

## Concepts Used
Abstract class `Person`, inheritance (`Student`, `Teacher`), composition, `map`, `vector`, `sort`, `find`, file streams.

## Grading Scheme
| Marks | Grade |
|---|---|
| 80 and above | A |
| 60 to 79 | B |
| 40 to 59 | C |
| Below 40 | D |

## How to Run
Requires a C++11 (or later) compiler such as g++.
```bash
g++ -std=c++11 main.cpp -o rural
./rural
```
On Windows, run `rural.exe`.

## Sample Output
```
Asha | Maths | Attendance 80% | Marks 82 | Grade A
Asha | English | Attendance 100% | Marks 74 | Grade B
Ravi | Maths | Attendance 60% | Marks 45 | Grade C
Meena | English | Attendance 80% | Marks 68 | Grade B

Ranking by average marks:
1. Asha - 78
2. Meena - 68
3. Ravi - 45

Resources for Maths: Algebra Workbook; Fractions Video;
Loaded 3 students from students.txt
```

## Possible Improvements
- Menu-driven input instead of fixed sample data
- Exception handling for invalid input
- Save attendance and marks to files

## License
MIT
