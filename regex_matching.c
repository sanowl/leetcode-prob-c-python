#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isMatch(char* s, char* p) {
    int sLen = strlen(s);
    int pLen = strlen(p);
    
    // DP table: dp[i][j] represents if s[0:i] matches p[0:j]
    bool** dp = (bool**)malloc((sLen + 1) * sizeof(bool*));
    for (int i = 0; i <= sLen; i++) {
        dp[i] = (bool*)calloc(pLen + 1, sizeof(bool));
    }
    
    // Base case: empty pattern matches empty string
    dp[0][0] = true;
    
    // Handle patterns starting with *
    for (int j = 1; j <= pLen; j++) {
        if (p[j-1] == '*') {
            dp[0][j] = dp[0][j-2];
        }
    }
    
    // Fill the DP table
    for (int i = 1; i <= sLen; i++) {
        for (int j = 1; j <= pLen; j++) {
            if (p[j-1] == '.' || p[j-1] == s[i-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else if (p[j-1] == '*') {
                dp[i][j] = dp[i][j-2];  // Zero occurrence
                if (p[j-2] == '.' || p[j-2] == s[i-1]) {
                    dp[i][j] = dp[i][j] || dp[i-1][j];  // One or more occurrences
                }
            }
        }
    }
    
    bool result = dp[sLen][pLen];
    
    // Free allocated memory
    for (int i = 0; i <= sLen; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// Test function
void test(char* s, char* p, bool expected) {
    bool result = isMatch(s, p);
    printf("s: \"%s\", p: \"%s\", Result: %s, Expected: %s\n", 
           s, p, result ? "true" : "false", expected ? "true" : "false");
}

int main() {
    test("aa", "a", false);
    test("aa", "a*", true);
    test("ab", ".*", true);
    test("aab", "c*a*b", true);
    test("mississippi", "mis*is*p*.", false);
    
    return 0;
}
