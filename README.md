# CS115 Online Quiz Management System

A console-based Online Quiz Management System written in C.
CS-115 Computer Programming, Term Project, FE Batch 2026, Fall Semester 2026.
Department of Computer & Information Systems Engineering, NED University of Engineering & Technology, Karachi.

**Instructor:** Ms. Mahnoor Malik

## Group Members

| Name | Roll No. |
|---|---|
| Zeeshan Bin Faisal Shareef | CS-26078 |
| Yasir Hussain | CS-26096 |
| Shah Azam | CS-26097 |
| Aurangzeb | CS-26047 |

## Features

**Administrator**
- Log in with the administrator username and password
- Add, view, edit and delete quiz questions
- View the results of all students

**Student**
- Register and log in (usernames are unique, passwords are hidden with asterisks)
- Take the quiz and get each answer marked immediately
- View their own results

**General**
- Question IDs are generated automatically and renumbered after a deletion
- Input is validated, so invalid entries show a message instead of crashing
- Data is saved in binary files and remains after the program is closed

## Requirements

- Windows (the program uses `conio.h` and the Windows screen-clearing command)
- GCC compiler (for example, through Visual Studio Code)

## How to Compile and Run

```
gcc quiz.c -o quiz
quiz
```

## Data Files

These files are created automatically by the program in the same folder:

- `question.dat` stores the quiz questions
- `users.dat` stores student accounts
- `results.dat` stores quiz results
- `temp.dat` is a temporary file used only while editing or deleting a question

## Project Structure

- `quiz.c` is the complete source code
