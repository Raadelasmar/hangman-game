#define _CRT_SECURE_NO_WARNINGS     /* disables MSVC warnings for scanf/fopen */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/* function declarations */
void start_or_end(char* level);
void main_menu(char* level);
int  mistakesallowed(char level);
void insertdashes(char guessed[], int wordlength);
void clear_input_stream(void);
char* randomword(int length);
void displaywrongcharacters(char wrongcharacters[], int count);

void clear_input_stream(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}  /* clear input buffer */
}

void start_or_end(char* level)
{
    char SEchoice;
    printf("Enter 'S' to start the game or 'E' to end the game:\n");
    scanf(" %c", &SEchoice);
    clear_input_stream();                           /* clean leftover input */
    SEchoice = (char)toupper(SEchoice);            /* make input uppercase */

    if (SEchoice == 'S')                           /* start game */
        main_menu(level);
    else if (SEchoice == 'E') {                   /* exit game */
        system("cls");
        puts("Hope you enjoyed the game!");
        exit(0);
    }
    else {                                        /* invalid input → retry */
        puts("Invalid character.\n");
        start_or_end(level);
    }
}

void main_menu(char* level)
{
    char levelchoice;
    do {
        /* display game instructions and levels */
        puts("Welcome to Hangman! Let's explain the rules first: "
            "A word of your desired length will be displayed with underscores, "
            "and you have to guess the letters in the word.\n");
        puts("There are 4 difficulty levels that you can choose:");
        puts("1 - Easy (10 mistakes)");
        puts("2 - Intermediate (8 mistakes)");
        puts("3 - Advanced (6 mistakes)");
        puts("4 - Master (4 mistakes)");
        puts("Enter 'E' for Easy");
        puts("Enter 'I' for Intermediate");
        puts("Enter 'A' for Advanced");
        puts("Enter 'M' for Master");
        printf("Now that we've explained the game, please pick a level: ");

        levelchoice = (char)getchar();
        clear_input_stream();
        levelchoice = (char)toupper(levelchoice);

        switch (levelchoice) {
        case 'E': case 'I': case 'A': case 'M':
            printf("You chose the %s level with %d mistakes.\n",
                (levelchoice == 'E') ? "Easy" :
                (levelchoice == 'I') ? "Intermediate" :
                (levelchoice == 'A') ? "Advanced" : "Master",
                mistakesallowed(levelchoice));
            *level = levelchoice; /* store selected level */
                break;
        default:
            puts("Invalid choice. Please select a valid option.\n");
            break;
        }
    } while (levelchoice != 'E' && levelchoice != 'I' &&
        levelchoice != 'A' && levelchoice != 'M');  /* repeat if invalid */
}

int mistakesallowed(char level)
{
    switch (level) {
    case 'E': return 10;                         /* Easy → 10 mistakes */
    case 'I': return 8;                          /* Intermediate → 8 */
    case 'A': return 6;                          /* Advanced → 6 */
    case 'M': return 4;                          /* Master → 4 */
    default:  return 0;
    }
}

void insertdashes(char guessed[], int wordlength)
{
    for (int i = 0; i < wordlength; ++i) guessed[i] = '_';  /* fill with _ */
    guessed[wordlength] = '\0';                             /* end string */
}

char* randomword(int length)
{
    FILE* fptr;
    int   randomIndex;
    char* word = NULL;

    while (1) {
        /* open correct file based on length */
        if (length < 14) {
            fptr = fopen("sortedtext.txt", "r");
            randomIndex = (rand() % 3000) + 1;  //choosing a word randomly from 3000 words
        }
        else {
            fptr = fopen("longerwords.txt", "r");
            randomIndex = (rand() % 38) + 1;  // choosign a word radnom from 38 words
        }
        if (!fptr) { perror("Error opening file"); exit(1); }

        /* allocate buffer once */
        if (word == NULL) {
            word = malloc(length + 2);           /* +2 for newline + null */
            if (word == NULL) {
                fprintf(stderr, "Memory allocation failed for word buffer\n");
                exit(EXIT_FAILURE);
            }
        }

        /* read up to random line */
        for (int line = 1; line <= randomIndex; ++line)
            fgets(word, length + 2, fptr);

        int wordlength = (int)strlen(word);
        if (word[wordlength - 1] == '\n') {
            word[wordlength - 1] = '\0';        /* strip newline */
            --wordlength;
        }
        fclose(fptr);

        if (wordlength == length) break;        /* found matching word */
    }
    return word;                                /* return word to caller */
}

void displaywrongcharacters(char wrongcharacters[], int count)
{
    printf("Wrong guesses: ");
    for (int i = 0; i < count; ++i) printf("%c ", wrongcharacters[i]);
    putchar('\n');                              /* newline after list */
}

int main(void)
{
    char level;
    srand((unsigned)time(NULL));                /* seed random generator */

    while (1) {
        start_or_end(&level);                  /* prompt to start or end */
        int allowedmistakes = mistakesallowed(level);
        int mistakes = 0, wordlength = 0;
        char wrongcharacters[10] = { 0 };      /* track wrong guesses */
        int  wrongcount = 0;

        /* asks the user to enter length of the word */
            while (1) {
                printf("Enter the desired length of the word "
                    "(3-13 for short, 14-17 for long): ");
                if (scanf("%d", &wordlength) != 1) {
                    clear_input_stream();
                    puts("Invalid input. Please enter a number.");
                    continue;
                }
                clear_input_stream();
                if (wordlength >= 3 && wordlength <= 17) break;
                puts("Invalid length. Please enter a number between 3 and 17.");
            }

        char* word = randomword(wordlength);             /* get random word */
        char* guessed = (char*)malloc(wordlength + 1);  /* create display */
        if (!guessed) { fputs("Memory error\n", stderr); exit(1); }
        insertdashes(guessed, wordlength);

        printf("Your word is:\n%s\n", guessed);

        /* main game loop */
        while (mistakes < allowedmistakes) {
            printf("Guess a letter: ");
            char guess;
            scanf(" %c", &guess);
            clear_input_stream();
            guess = (char)tolower(guess);              /* convert to lower */

            if (!isalpha(guess)) {                    /* reject non-letters */
                printf("Invalid input. Please enter a letter (A-Z).\n");
                continue;
            }

            int correct = 0;
            for (int i = 0; i < wordlength; ++i)
                if (word[i] == guess) { guessed[i] = guess; correct = 1; }

            if (!correct) {
                int already = 0;
                for (int i = 0; i < wrongcount; ++i)
                    if (wrongcharacters[i] == guess) { already = 1; break; }

                if (already)
                    printf("You've already guessed '%c'. Try a different letter.\n", guess);
                else {
                    if (wrongcount < 10) wrongcharacters[wrongcount++] = guess;
                    ++mistakes;
                    printf("Wrong guess. You have %d mistakes left.\n",
                        allowedmistakes - mistakes);
                    displaywrongcharacters(wrongcharacters, wrongcount);
                }
            }
            puts(guessed);                           /* show current word */

            if (strcmp(word, guessed) == 0) {       /* check if solved */
                puts("Congratulations! You guessed the word.");
                break;
            }
        }

        if (mistakes == allowedmistakes)           /* check if lost */
            printf("You lost, good luck next time.\nThe word was: %s\n", word);

        free(word);                               /* free memory */
        free(guessed);
    }

    return 0;
}