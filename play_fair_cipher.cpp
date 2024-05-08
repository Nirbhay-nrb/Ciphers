#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

void populate_matrix(vector<vector<char>> &population_matrix, string key){
    int freq[26] = {0};
    int i=0,j=0;
    for(char c : key){
        if(freq[c-'A'] == 0){
            population_matrix[i][j] = c;
            freq[c-'A'] = 1;
            j++;
            if(j==5){
                j=0;
                i++;
            }
        }
    }
    for(char c='A'; c<='Z'; c++){
        if(c == 'J') continue;
        if(freq[c-'A'] == 0){
            population_matrix[i][j] = c;
            freq[c-'A'] = 1;
            j++;
            if(j==5){
                j=0;
                i++;
            }
        }
    }
}

int main(){
    string key;
    cout<<"Enter the key without any spaces: ";
    cin>>key;
    string message;
    cout<<"Enter the message: ";
    cin>>message;
    transform(message.begin(), message.end(), message.begin(), ::toupper);
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    vector<vector<char>> population_matrix(5, vector<char>(5, '0'));
    populate_matrix(population_matrix, key);
    // printing the population matrix
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout<<population_matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    string encrypted_message = "";
    cout<<"Encrypted message: "<<encrypted_message<<endl;
    cout<<"Decrypted message: "<<""<<endl;
    return 0;
} 