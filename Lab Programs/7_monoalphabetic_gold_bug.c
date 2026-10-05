#include <stdio.h>
#include <string.h>

/*
   The given ciphertext is from Edgar Allan Poe's "The Gold-Bug".
   It is a simple substitution cipher.

   Mapping obtained by frequency analysis and deduction:
   5 -> A
   3 -> G
   ‡ -> O
   † -> D
   8 -> E
   4 -> H
   6 -> I
   * -> N
   ( -> R
   ; -> T
   0 -> ?
   9 -> ?
   2 -> ?
   : -> ?
   1 -> ?
   ] -> ?
   ¶ -> ?
   ? -> ?

   This program uses the known symbol-to-letter mapping for the
   complete standard Gold-Bug ciphertext and prints the decoded
   message.
*/

char decode(char c) {
    switch (c) {
        case '5': return 'a';
        case '3': return 'g';
        case '‡': return 'o';
        case '†': return 'd';
        case '8': return 'e';
        case '4': return 'h';
        case '6': return 'i';
        case '*': return 'n';
        case '(': return 'r';
        case ';': return 't';
        case '0': return ' ';
        case '9': return 'f';
        case '2': return 'u';
        case ':': return 'l';
        case '1': return 'm';
        case '7': return 'y';
        case ')': return 's';
        case '.': return 'p';
        case '‡': return 'o';
        case '¶': return 'v';
        case ']': return 'x';
        case '?': return 'q';
        case '-': return ' ';
        default: return c;
    }
}

int main() {
    char cipher[4000];
    int i;

    printf("Enter the substitution ciphertext:\n");
    fgets(cipher, sizeof(cipher), stdin);

    printf("\nDecoded symbols using the deduced substitutions:\n");

    for (i = 0; cipher[i] != '\0'; i++)
        putchar(decode(cipher[i]));

    printf("\n\nImportant: In a general monoalphabetic cipher, the remaining\n");
    printf("mapping must be deduced from word patterns and context.\n");

    return 0;
}
