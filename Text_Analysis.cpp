#include <iostream>
#include <vector>
#include <string> 
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <algorithm>
using namespace std;


// Clean up words by removing anything that isn't a straight letter and converting to lowercase
string cleanWord(const string& word) {
    string cleaned;
    for (char ch : word) {
        if (isalnum(ch)) {
            cleaned += tolower(ch);
        }
    }
    return cleaned;
}


// Function to check if a word is a palindrome
bool is_Palindrome(string text) {
    string cleaned = cleanWord(text);
    int n = cleaned.length();
    for (int i = 0; i < n / 2; i++) {       // compares the first and last characters to see if they are the same
        if (cleaned[i] != cleaned[n - i - 1]) {     // if they are not the same then it is not a palindrome
            return false;
        }
    }
    return true;
}


// Function to detect if two words are anagrams
bool isAnagram(string string1, string string2) {
    string1 = cleanWord(string1);
    string2 = cleanWord(string2);
    if (string1.length() != string2.length()) {         // if the lengths are different, then there are no anagrams
        return false;
    }
    sort(string1.begin(), string1.end());
    sort(string2.begin(), string2.end());
    return string1 == string2;
}


// Function to count the frequency of each word within the text
void countWordFrequencies(const string& text, unordered_map<string,int>& wordCount) {
    stringstream ss(text);
    string word;
    while (ss >> word) {
        string cleaned = cleanWord(word);
        if (!cleaned.empty()) {
            wordCount[cleaned]++;
        }
    }
}


// function to display the menu options to the user
void displayMenu() {
    cout << "Menu: " << endl;
    cout << "1. Count Word Frequencies." << endl;
    cout << "2. Detect a Palindrome." << endl;
    cout << "3. Detect an Anagram." << endl;
    cout << "4. Count Palindromes within text." << endl;
    cout << "5. Count Anagrams wihtin text." << endl;
    cout << "6. Exit the program." << endl;
}


int main() {
    ifstream inputFile;
    ofstream outputFile;
    string text;
    unordered_map<string, int> wordCount;       // using a map to store the word frequencies 
    string word1, word2;
    int choice;

    // opens the output file to write the results
    outputFile.open("output.txt");
    if (!outputFile) {
        cerr << "Error opening output file." << endl;
        return 1;
    }


    do {
        // Display the menu and ask the user to make their choice
        displayMenu();
        cout << "Enter your choice: " << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                // word frequencies
                string inputFileName;
                cout << "Enter input file name: " << endl;
                cin >> inputFileName;

                // opens the input file
                inputFile.open(inputFileName);
                if (!inputFile) {
                    cerr << "Error opening file." << endl;
                    break;
                }

                stringstream fileStream;
                fileStream << inputFile.rdbuf();
                text = fileStream.str();
                inputFile.close();      // close the file

                wordCount.clear();          // clears previous word frequencies
                countWordFrequencies(text, wordCount);

                // Write the results to the output file
                outputFile << "Word Frequencies: " << endl;
                for (const auto& pair : wordCount) {
                    outputFile << pair.first << ": " << pair.second << endl;
                }
                cout << "Results are written in 'output.txt' " << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                break;
            }

            case 2: {
                // Palindrome check
                cout << "Enter a word to test if it is a palindrome: " << endl;
                cin >> word1;

                if(is_Palindrome(word1)) {          // Checking for palindrome
                    outputFile << word1 << " is a palindrome" << endl;
                }
                else {
                    outputFile << word1 << " is NOT a palindrome." << endl;
                }
                cout << "Results are written in 'output.txt' " << endl;
                // Added this is to separate the menu and make it look a little cleaner
                cout << "----------------------------------------------------------------------------------" << endl;
                break;
                }   
            
            case 3: {
                cout << "Enter two words to test if they are anagrams: " << endl;
                cin >> word1;
                cin >> word2;

                if(isAnagram(word1, word2)) {
                    outputFile << word1 << " and " << word2 << " are anagrams." << endl;
                }
                else {
                    outputFile << word1 << " and " << word2 << " are NOT anagrams" << endl;
                }
                cout << "Results are written in 'output.txt' " << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                break;
            }

            case 4: {
                if(text.empty()) {
                    cout << "No file detected." << endl;
                    break;
                }

                int palindromeCount = 0;
                stringstream ss(text);
                while (ss >> word1) {
                    if (is_Palindrome(word1)) {
                        palindromeCount++;
                    }
                }
                outputFile << "Palindromes found: " << palindromeCount << endl;
                cout << "Results are written in 'output.txt' " << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                break;
            }

            case 5: {
                // count anagrams in the text 
                if (text.empty()) {
                    cout << "No file has been loaded yet." << endl;
                    break;
                }

                // checking and grouping anagrams
                unordered_map<string, vector<string> > anagramGroups;
                stringstream ss(text);
                while (ss >> word1) {
                    string cleaned = cleanWord(word1);
                    if (!cleaned.empty()) {
                        sort (cleaned.begin(), cleaned.end());
                        anagramGroups[cleaned].push_back(word1);
                    }
                }

                int anagramCount = 0;
                for (const auto& group : anagramGroups) {
                    if (group.second.size() > 1) {
                        anagramCount++;
                    }
                }

                outputFile << "Anagrams found: " << anagramCount << endl;
                cout << "Results are written in 'output.txt' " << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                break;
            }

            case 6: {
                // Exit program
                cout << "Exiting Program." << endl;
                break;
            }
        } 
    }
    while (choice != 6);
    // closes the output file
    outputFile.close();
    return 0;
}
