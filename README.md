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
```

### 📏 How to Run
1. Place sortedtext.txt and longerwords.txt in the same folder as the executable
2. Run the program
3. Enter difficulty level and desired word length
4. Guess letters to complete the word
✅ Any guesses or results will only affect the current session; files remain unchanged.

### 📝 Notes
• sortedtext.txt and longerwords.txt must contain one word per line, no extra spaces.

• Words in these files should match the expected lengths (short: 3–13 letters; long: 14–17 letters).

• The program was developed and tested on Windows using Visual Studio.

• If running inside Visual Studio, set Working Directory to $(OutDir).

