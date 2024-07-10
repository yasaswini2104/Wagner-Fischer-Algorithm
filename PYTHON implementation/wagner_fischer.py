# function to load file
def load_input(file_path):
    file_path = input("Enter the file name: ")
    
    """
    Load input strings from a file.

    Args:
        file_path (str): The path to the input file.

    Returns:
        tuple: A tuple containing two strings loaded from the file.
    """
    
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
            str1 = lines[0].strip()
            str2 = lines[1].strip()
            return str1, str2
    except FileNotFoundError:
        print("File not found!")
        exit(1)
        
# file name is found in the file path 
# lines are read from the files
# else returns message as file not found


#function to compare two strings
def wagner_fischer(str1, str2):
    
    """
    Calculate the minimum edit distance between two strings using the Wagner-Fischer algorithm.

    Args:
        str1 (str): The first input string.
        str2 (str): The second input string.

    Returns:
        int: The minimum edit distance between the two input strings.
    """

    m, n = len(str1), len(str2)

    # Initialize a 2D array for dynamic programming
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # Base cases
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j

    # Fill in the rest of the matrix
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if str1[i - 1] == str2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = 1 + min(dp[i - 1][j - 1],  #substitution
                                   dp[i - 1][j],      #delete
                                   dp[i][j - 1])      #insert

    # Backtrack to find the operations
    i, j = m, n

    # taking an empty array for inserting operations
    operations = []
    

    # iterating through while loop
    while i > 0 or j > 0:
        
        # checking string indices are matches
        if i > 0 and j > 0 and str1[i - 1] == str2[j - 1]:
            i -= 1
            j -= 1

        # checking the positions to insert
        elif j > 0 and dp[i][j] == dp[i][j - 1] + 1:
            operations.append(f"INSERT {str2[j - 1]}")
            j -= 1

        # checking the positions to delete
        elif i > 0 and dp[i][j] == dp[i - 1][j] + 1:
            operations.append(f"DELETE {str1[i - 1]}")
            i -= 1

        # checking the positions to replace
        elif i > 0 and j > 0 and dp[i][j] == dp[i - 1][j - 1] + 1:
            operations.append(f"REPLACE {str1[i - 1]} with {str2[j - 1]}")
            i -= 1
            j -= 1
        # end of while loop

    # Print the operations accordingly
    print("Minimum Edit Distance:", dp[m][n])
    print("Operations:")
    # prints all the enumerated strings
    for idx, operation in enumerate(reversed(operations), 1):
        print(f"{idx}) {operation}")

    return dp[m][n]

# Load input from file
str1, str2 = load_input("input.txt")

# Calculate the minimum edit distance
min_distance = wagner_fischer(str1, str2)

#print the minimum edit distance
print(f"Minimum Edit Distance between {str1} and {str2} is: {min_distance}")
