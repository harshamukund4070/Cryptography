#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[1000];
    int k, i;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key (1-25): ");
    scanf("%d", &k);

    k = k % 26;

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i]))
            text[i] = 'A' + (text[i] - 'A' + k) % 26;
        else if (islower((unsigned char)text[i]))
            text[i] = 'a' + (text[i] - 'a' + k) % 26;
    }

    printf("Ciphertext: %s", text);

    return 0;
}
