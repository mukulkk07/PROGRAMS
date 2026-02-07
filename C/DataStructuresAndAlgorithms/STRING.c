#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 1000
#define d 256     /* Number of characters in the input alphabet for Rabin-Karp */
#define PRIME 101 /* A prime number for Rabin-Karp hashing */

/* --- Utility Functions --- */

int max_val(int a, int b) { return (a > b) ? a : b; }
int min_val(int a, int b) { return (a < b) ? a : b; }
int min3_val(int a, int b, int c) { return min_val(min_val(a, b), c); }

void cleanInput(char* str) {
    if ((strlen(str) > 0) && (str[strlen(str) - 1] == '\n'))
        str[strlen(str) - 1] = '\0';
}

/* ---------------------------------------------------------
   1. BASIC MANIPULATION
   --------------------------------------------------------- */

void reverseString(char* str) {
    int n = strlen(str);
    int i;
    for (i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
    printf("Reversed String: %s\n", str);
}

void checkPalindrome(char* str) {
    int l = 0;
    int h = strlen(str) - 1;
    while (h > l) {
        if (str[l++] != str[h--]) {
            printf("\"%s\" is NOT a Palindrome.\n", str);
            return;
        }
    }
    printf("\"%s\" is a Palindrome.\n", str);
}

/* ---------------------------------------------------------
   2. PATTERN SEARCHING ALGORITHMS
   --------------------------------------------------------- */

/* --- A. Naive Search --- */
void naiveSearch(char* txt, char* pat) {
    int M = strlen(pat);
    int N = strlen(txt);
    int found = 0;
    int i, j;

    for (i = 0; i <= N - M; i++) {
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pat[j])
                break;
        }
        if (j == M) {
            printf("Pattern found at index %d\n", i);
            found = 1;
        }
    }
    if (!found) printf("Pattern not found.\n");
}

/* --- B. KMP Algorithm --- */
void computeLPSArray(char* pat, int M, int* lps) {
    int len = 0;
    int i = 1;
    lps[0] = 0;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char* txt, char* pat) {
    int M = strlen(pat);
    int N = strlen(txt);
    int i = 0; 
    int j = 0; 
    int found = 0;
    
    /* Dynamic allocation to replace VLA for C90 compatibility */
    int *lps = (int*)malloc(sizeof(int) * M);
    if (lps == NULL) { printf("Memory failure\n"); return; }

    computeLPSArray(pat, M, lps);

    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
            found = 1;
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    if (!found) printf("Pattern not found.\n");
    
    free(lps); /* Always free dynamically allocated memory */
}

/* --- C. Rabin-Karp Algorithm --- */
void rabinKarpSearch(char* txt, char* pat) {
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; 
    int t = 0; 
    int h = 1;
    int found = 0;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % PRIME;

    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % PRIME;
        t = (d * t + txt[i]) % PRIME;
    }

    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == M) {
                printf("Pattern found at index %d\n", i);
                found = 1;
            }
        }
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % PRIME;
            if (t < 0) t = (t + PRIME);
        }
    }
    if (!found) printf("Pattern not found.\n");
}

/* ---------------------------------------------------------
   3. DYNAMIC PROGRAMMING ALGORITHMS
   --------------------------------------------------------- */

/* --- A. Longest Common Subsequence (LCS) --- */
void longestCommonSubsequence(char* S1, char* S2) {
    int m = strlen(S1);
    int n = strlen(S2);
    int i, j;
    
    /* Using malloc for 2D array simulation to avoid Stack Overflow and VLA errors */
    /* We map 2D coordinates (r, c) to 1D index: r * (n+1) + c */
    int *L = (int*)malloc(sizeof(int) * (m + 1) * (n + 1));
    
    if (L == NULL) { printf("Memory allocation failed\n"); return; }

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i * (n + 1) + j] = 0;
            else if (S1[i - 1] == S2[j - 1])
                L[i * (n + 1) + j] = L[(i - 1) * (n + 1) + (j - 1)] + 1;
            else
                L[i * (n + 1) + j] = max_val(L[(i - 1) * (n + 1) + j], L[i * (n + 1) + (j - 1)]);
        }
    }
    printf("Length of LCS is: %d\n", L[m * (n + 1) + n]);
    free(L);
}

/* --- B. Edit Distance (Levenshtein) --- */
void editDistance(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);
    int i, j;

    /* Using malloc for 2D array simulation */
    int *dp = (int*)malloc(sizeof(int) * (m + 1) * (n + 1));
    
    if (dp == NULL) { printf("Memory allocation failed\n"); return; }

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0)
                dp[i * (n + 1) + j] = j; 
            else if (j == 0)
                dp[i * (n + 1) + j] = i; 
            else if (str1[i - 1] == str2[j - 1])
                dp[i * (n + 1) + j] = dp[(i - 1) * (n + 1) + (j - 1)];
            else
                dp[i * (n + 1) + j] = 1 + min3_val(dp[i * (n + 1) + (j - 1)],       /* Insert */
                                                   dp[(i - 1) * (n + 1) + j],       /* Remove */
                                                   dp[(i - 1) * (n + 1) + (j - 1)]);/* Replace */
        }
    }
    printf("Minimum Edit Distance: %d\n", dp[m * (n + 1) + n]);
    free(dp);
}

/* ---------------------------------------------------------
   MAIN DRIVER
   --------------------------------------------------------- */

int main() {
    int choice;
    char str1[MAX], str2[MAX];

    while (1) {
        printf("\n========================================\n");
        printf("   MASTER STRING ALGORITHM SUITE\n");
        printf("========================================\n");
        printf("1. Reverse String\n");
        printf("2. Check Palindrome\n");
        printf("3. Naive Pattern Search\n");
        printf("4. KMP Pattern Search\n");
        printf("5. Rabin-Karp Pattern Search\n");
        printf("6. Longest Common Subsequence (LCS)\n");
        printf("7. Edit Distance (Levenshtein)\n");
        printf("0. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) { 
            while(getchar() != '\n'); /* Clear input buffer on error */
            continue; 
        }
        getchar(); /* Consume newline */

        if (choice == 0) break;

        switch (choice) {
        case 1:
            printf("Enter string: ");
            if (fgets(str1, MAX, stdin)) {
                cleanInput(str1);
                reverseString(str1);
            }
            break;
        case 2:
            printf("Enter string: ");
            if (fgets(str1, MAX, stdin)) {
                cleanInput(str1);
                checkPalindrome(str1);
            }
            break;
        case 3:
        case 4:
        case 5:
            printf("Enter Text: ");
            if (fgets(str1, MAX, stdin)) {
                cleanInput(str1);
                printf("Enter Pattern: ");
                if (fgets(str2, MAX, stdin)) {
                    cleanInput(str2);
                    
                    if (choice == 3) {
                        printf("--- Naive Search Results ---\n");
                        naiveSearch(str1, str2);
                    } else if (choice == 4) {
                        printf("--- KMP Search Results ---\n");
                        KMPSearch(str1, str2);
                    } else {
                        printf("--- Rabin-Karp Search Results ---\n");
                        rabinKarpSearch(str1, str2);
                    }
                }
            }
            break;
        case 6:
            printf("Enter First String: ");
            if (fgets(str1, MAX, stdin)) {
                cleanInput(str1);
                printf("Enter Second String: ");
                if (fgets(str2, MAX, stdin)) {
                    cleanInput(str2);
                    longestCommonSubsequence(str1, str2);
                }
            }
            break;
        case 7:
            printf("Enter Source String: ");
            if (fgets(str1, MAX, stdin)) {
                cleanInput(str1);
                printf("Enter Target String: ");
                if (fgets(str2, MAX, stdin)) {
                    cleanInput(str2);
                    editDistance(str1, str2);
                }
            }
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}