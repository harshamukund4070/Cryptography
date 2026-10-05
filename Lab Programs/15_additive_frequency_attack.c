#include <stdio.h>
#include <string.h>
#include <ctype.h>

double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

double scoreText(char text[]) {
    int count[26] = {0};
    int total = 0;
    int i;
    double chi = 0.0;

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            count[tolower((unsigned char)text[i]) - 'a']++;
            total++;
        }
    }

    if (total == 0)
        return 999999.0;

    for (i = 0; i < 26; i++) {
        double expected = total * englishFreq[i] / 100.0;

        if (expected > 0)
            chi += ((count[i] - expected) *
                    (count[i] - expected)) / expected;
    }

    return chi;
}

void decrypt(char cipher[], int shift, char plain[]) {
    int i;

    for (i = 0; cipher[i] != '\0'; i++) {
        if (cipher[i] >= 'A' && cipher[i] <= 'Z')
            plain[i] =
                'A' + (cipher[i] - 'A' - shift + 26) % 26;
        else if (cipher[i] >= 'a' && cipher[i] <= 'z')
            plain[i] =
                'a' + (cipher[i] - 'a' - shift + 26) % 26;
        else
            plain[i] = cipher[i];
    }

    plain[i] = '\0';
}

int main() {
    char cipher[5000];
    char plain[5000];

    int topN;
    int shift;
    int i, j;

    double scores[26];

    printf("ADDITIVE CIPHER FREQUENCY ATTACK\n");
    printf("Enter ciphertext:\n");
    fgets(cipher, sizeof(cipher), stdin);

    printf("How many possible plaintexts should be displayed? ");
    scanf("%d", &topN);

    if (topN < 1)
        topN = 1;

    if (topN > 26)
        topN = 26;

    /* Score every possible Caesar/additive shift */
    for (shift = 0; shift < 26; shift++) {
        decrypt(cipher, shift, plain);
        scores[shift] = scoreText(plain);
    }

    printf("\nTop %d possible plaintexts:\n\n", topN);

    /*
       Select the smallest chi-square scores one at a time.
       Smaller score means the letter distribution is closer
       to normal English frequency.
    */
    for (i = 0; i < topN; i++) {
        int best = -1;

        for (j = 0; j < 26; j++) {
            if (scores[j] >= 0 &&
                (best == -1 || scores[j] < scores[best]))
                best = j;
        }

        decrypt(cipher, best, plain);

        printf("%2d. Shift %2d  Score = %8.2f\n",
               i + 1, best, scores[best]);
        printf("    %s\n\n", plain);

        scores[best] = 999999999.0;
    }

    return 0;
}
