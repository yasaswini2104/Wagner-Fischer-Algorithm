/***************************WAGNER FISCHERS ALGORITHM: Minimum Edit Distance***************************/

#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<stack>

using namespace std;

// Function to calculate the minimum edit distance between two strings and backtrack the operations
int minEditDistance(const string& str1, const string& str2) 
{
    //calculate length of strings
    int m = str1.length();
    int n = str2.length();

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
                dp[i][j] = 1 + min({ dp[i - 1][j - 1], //Insert
                dp[i - 1][j],    //Remove
                dp[i][j - 1] }); //Replace
            }
        }
    }

    // Backtrack to find operations, pushing them into a stack.
    int i = m, j = n;
    stack<string> operations;
    while (i > 0 || j > 0) 
    {
        if (i > 0 && j > 0 && str1[i - 1] == str2[j - 1]) 
        {
            i--;
            j--;
        } 
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) 
        {
            operations.push("INSERT " + string(1, str2[j - 1]));
            j--;
        } 
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) 
        {
            operations.push("DELETE " + string(1, str1[i - 1]));
            i--;
        } 
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) 
        {
            operations.push("REPLACE " + string(1, str1[i - 1]) + " with " + string(1, str2[j - 1]));
            i--;
            j--;
        }
    }

    // Print the operations, pop the operations stack
    cout << "Minimum Edit Distance: " << dp[m][n] << endl;
    cout << "Operations: " << endl;
    int operationNumber = 1;
    while (!operations.empty()) 
    {
        cout << operationNumber++ << ") " << operations.top() << endl;
        operations.pop();
    }

    return dp[m][n];
}

int main() 
{
    string str1, str2;

    cout << "Enter the file name: ";
    string fileName;
    cin >> fileName;

    ifstream inputFile(fileName); // Open the input file

    // Check if the file is open
    if (!inputFile.is_open()) 
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Read the strings from the file
    inputFile >> str1 >> str2;

    inputFile.close(); // Close the input file

    cout << "Minimum Edit Distance between " << str1 << " and " << str2 << " is: " << minEditDistance(str1, str2) << endl;

    return 0;
}