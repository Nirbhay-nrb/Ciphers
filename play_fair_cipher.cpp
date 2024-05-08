#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// function to remove spaces from the message
void removeSpaces(string &message)
{
    message.erase(remove(message.begin(), message.end(), ' '), message.end());
}

// function to generate 5x5 key matrix
void populate_matrix(vector<vector<char>> &population_matrix, string key)
{
    int freq[26] = {0};
    int i = 0, j = 0;
    for (char c : key)
    {
        if (freq[c - 'A'] == 0)
        {
            population_matrix[i][j] = c;
            freq[c - 'A'] = 1;
            j++;
            if (j == 5)
            {
                j = 0;
                i++;
            }
        }
    }
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c == 'J')
            continue;
        if (freq[c - 'A'] == 0)
        {
            population_matrix[i][j] = c;
            freq[c - 'A'] = 1;
            j++;
            if (j == 5)
            {
                j = 0;
                i++;
            }
        }
    }
}

// Function to make pairs 
string prepare(string str) {
    string s;
    for(int i=0 ; i<str.length() ; i+=2) {
        if(i+1 >= str.length()){
            s.push_back(str[i]);
            s.push_back('X');
            break;
        }
        if(str[i] != str[i+1]){
            s.push_back(str[i]);
            s.push_back(str[i+1]);
        }
        else {
            s.push_back(str[i]);
            s.push_back('X');
            i--;
        }
    }
    cout<<"string after pairs: "<<s<<endl;
    
    return s;
}

// function to search for the position of characters in the matrix
void search(vector<vector<char>> &population_matrix, char a, char b, vector<int> &arr)
{
    int i, j;
    if (a == 'J')
        a = 'I';
    else if (b == 'J')
        b = 'I';
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (population_matrix[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (population_matrix[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

// function to encrypt the message
// Function to encrypt using Playfair Cipher
string encryptByPlayfairCipher(string &str, vector<vector<char>> &population_matrix) {
    string s = prepare(str);
    int ps = s.length();
    
    // Encrypt using Playfair Cipher
    for (int i = 0; i < ps; i += 2) {
        vector<int> a(4);
        search(population_matrix, s[i], s[i + 1], a);

        if (a[0] == a[2]) {
            s[i] = population_matrix[a[0]][(a[1] + 1) % 5];
            s[i + 1] = population_matrix[a[0]][(a[3] + 1) % 5];
        }
        else if (a[1] == a[3]) {
            s[i] = population_matrix[(a[0] + 1) % 5][a[1]];
            s[i + 1] = population_matrix[(a[2] + 1) % 5][a[1]];
        }
        else {
            s[i] = population_matrix[a[0]][a[3]];
            s[i + 1] = population_matrix[a[2]][a[1]];
        }
    }

    return s;
}


// Function to call decrypt
string decryptByPlayfairCipher(string& str, vector<vector<char>>& population_matrix)
{
    int ps = str.length();
    string s=str;
    // Decrypt using Playfair Cipher
    for (int i = 0; i < ps; i += 2) {
        vector<int> a(4);
        search(population_matrix, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            s[i] = population_matrix[a[0]][(a[1] - 1+5)%5];
            s[i + 1] = population_matrix[a[0]][(a[3] - 1+5)%5];
        }
        else if (a[1] == a[3]) {
            s[i] = population_matrix[(a[0] - 1+5)%5][a[1]];
            s[i + 1] = population_matrix[(a[2] - 1+5)%5][a[1]];
        }
        else {
            s[i] = population_matrix[a[0]][a[3]];
            s[i + 1] = population_matrix[a[2]][a[1]];
        }
    }
    return s;
}


int main()
{
    string key;
    cout << "Enter the key without any spaces: ";
    cin >> key;
    // Clear the input buffer to remove the newline character
    cin.ignore();
    string message;
    cout << "Enter the message: \n";
    getline(cin, message);
    transform(message.begin(), message.end(), message.begin(), ::toupper);
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    cout << message << endl;
    // removing spaces from the message
    removeSpaces(message);
    cout << message << endl;
    // generating the population matrix
    vector<vector<char>> population_matrix(5, vector<char>(5, '0'));
    populate_matrix(population_matrix, key);
    // printing the population matrix
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << population_matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Encrypt the message using Playfair Cipher
    string encrypted_message = "";
    string decrypted_message = "";
    encrypted_message = encryptByPlayfairCipher(message, population_matrix);
    decrypted_message = decryptByPlayfairCipher(encrypted_message, population_matrix);
    cout << "Encrypted message: " << encrypted_message << endl;
    cout << "Decrypted message: " << decrypted_message << endl;
    return 0;
}