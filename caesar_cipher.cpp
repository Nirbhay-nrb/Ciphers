#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string decrypt(string message, int key){
    string decrypted_message = "";
    for(char s : message){
        int c = s - 'A';
        c = (c-key + 26)%26;
        decrypted_message = decrypted_message + (char)(c+'A');
    }
    return decrypted_message;
}
string encrypt(string message, int key){
    string encrypted_message = "";
    for(char s : message){
        int c = s - 'A';
        c = (c+key)%26;
        encrypted_message = encrypted_message + (char)(c+'A');
    }
    return encrypted_message;
}

int main(){
    int key;
    cout<<"Enter the key: ";
    cin>>key;
    string message;
    cout<<"Enter the message: ";
    cin>>message;
    transform(message.begin(), message.end(), message.begin(), ::toupper);
    string encrypted_message = encrypt(message, key);
    cout<<"Encrypted message: "<<encrypted_message<<endl;
    cout<<"Decrypted message: "<<decrypt(encrypted_message, key)<<endl;
    return 0;
} 