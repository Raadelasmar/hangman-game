# Hangman Game (C)

A fully functional console-based Hangman game written in C.

This project implements the classic Hangman word-guessing game, with random word selection from input files.

## Features
- 4 difficulty levels: Easy, Intermediate, Advanced, Master
- Random word selection from `sortedtext.txt` or `longerwords.txt`
- Input validation and error handling
- Tracks wrong guesses
- Works on Windows (tested in Visual Studio)

## Files included
- `Hangman.c` → main source code
- `sortedtext.txt` → list of short words
- `longerwords.txt` → list of longer words
- `Hangman documentation.pdf` → project documentation
- `User manual Hangman.pdf` → user instructions

## How to compile
### Using Visual Studio:
1. Open `Hangman.c` in a new empty C project
2. Build solution
3. Executable appears in `x64\Debug\`

### Using GCC (Linux/Mac):
```bash
gcc -o Hangman Hangman.c
./Hangman
