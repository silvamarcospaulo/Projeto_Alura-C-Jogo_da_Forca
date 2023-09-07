#define SECRETWORD_SIZE 20
#define GUESS_SIZE 26
#include "tad.c"

void opening();

void printTrophy();

void lineBreak();

void menu();

void newWord();

void chooseWord(char secretWord[SECRETWORD_SIZE]);

void readGuess(char guess[GUESS_SIZE], int *attempts);

int verifyGuess(char guess[GUESS_SIZE], int *attempts, char word);

void printWords(char guess[GUESS_SIZE], int *attempts, char secretWord[SECRETWORD_SIZE]);

void printHangman(int body);

int hanged(char guess[GUESS_SIZE], int *attempts, char secretWord[SECRETWORD_SIZE]);

int won(char guess[GUESS_SIZE], int *attempts, char secretWord[SECRETWORD_SIZE]);

void newGame();

void rules();

void credits();

void shutDown();