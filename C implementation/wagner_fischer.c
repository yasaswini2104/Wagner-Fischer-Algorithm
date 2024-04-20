#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to calculate the minimum of three numbers
int min(int a, int b, int c) 
{
    int min_val = a;
    if (b < min_val) min_val = b;
    if (c < min_val) min_val = c;
    return min_val;
}

// Function to calculate the minimum edit distance between two strings and print the operations
int minEditDistance(char* str1, char* str2) 
{
    int m = strlen(str1);
    int n = strlen(str2);

    // Initialize a 2D array for dynamic programming
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) 
    {
        dp[i][0] = i; // If the second string is empty, we need to delete all characters of the first string
    }

    for (int j = 0; j <= n; j++) 
    {
        dp[0][j] = j; // If the first string is empty, we need to insert all characters of the second string
    }

    // Fill in the rest of the matrix
    for (int i = 1; i <= m; i++) 
    {
        for (int j = 1; j <= n; j++) 
        {
            if (str1[i - 1] == str2[j - 1]) 
            {
                // If the characters at this position are the same, no operation needed, take the value from the diagonal
                dp[i][j] = dp[i - 1][j - 1];
            } 
            else 
            {
                // If the characters are different, consider all possibilities and find the minimum
                dp[i][j] = 1 + min(dp[i - 1][j - 1], //Insert
                                   dp[i - 1][j],     //Remove
                                   dp[i][j - 1]);    //Replace
            }
        }
    }

    // Print the operations
    printf("Minimum Edit Distance: %d\n", dp[m][n]);

    // Backtrack to find the operations
    int i = m, j = n;
    char operations[m + n][100];
    int operationNumber = 0;
    while (i > 0 || j > 0) 
    {
        if(i > 0 && j > 0 && str1[i - 1] == str2[j - 1]) 
        {
            i--;
            j--;
        } 
        else if(j > 0 && dp[i][j] == dp[i][j - 1] + 1) 
        {
            sprintf(operations[operationNumber++], "INSERT %c", str2[j - 1]);
            j--;
        } 
        else if(i > 0 && dp[i][j] == dp[i - 1][j] + 1) 
        {
            sprintf(operations[operationNumber++], "DELETE %c", str1[i - 1]);
            i--;
        } 
        else if(i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) 
        {
            sprintf(operations[operationNumber++], "REPLACE %c with %c", str1[i - 1], str2[j - 1]);
            i--;
            j--;
        }
    }

    // Print the operations
    printf("Operations:\n");
    for (int k = operationNumber - 1; k >= 0; k--) 
    {
        printf("%s\n", operations[k]);
    }

    // Print the minimum edit distance
    printf("Minimum Edit Distance: %d\n", dp[m][n]);

    return dp[m][n];
}

int main() {
    char str1[100], str2[100];
    char fileName[100];

    printf("Enter the file name: ");
    scanf("%s", fileName);

    FILE *inputFile = fopen(fileName, "r");

    // Check if the file is open
    if (inputFile == NULL) 
    {
        printf("Error opening file!\n");
        return 1;
    }

    // Read the strings from the file
    fscanf(inputFile, "%s %s", str1, str2);

    fclose(inputFile); // Close the input file

    printf("Minimum Edit Distance between %s and %s is: %d\n", str1, str2, minEditDistance(str1, str2));

    return 0;
}
