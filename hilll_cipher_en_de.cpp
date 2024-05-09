#include <iostream>
#include <math.h>
using namespace std;
float  b[3][3],  m[3][3];
int en[1][3], a[3][3], de[1][3], msg[1][3];
void getKeyMatrix()
{ // get key and message from user
    int i, j;
    char mes[3];
    cout << "Enter 3x3 matrix for key (should have inverse):\n";
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            cin >> a[i][j];
            m[i][j] = a[i][j];
        }
    cout << "\nEnter a string of 3 letter(use A through Z): ";
    cin >> mes;
    for (i = 0; i < 3; i++)
        msg[0][i] = mes[i] - 65;
    for (i = 0; i < 3; i++)
        cout<<msg[0][i]<<" ";
}
void encrypt()
{ // encrypts the message
    int i, j, k;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 1; j++)
            for (k = 0; k < 3; k++)
                en[j][i] = (en[j][i] + msg[j][k]* a[k][i])%26;
    cout << "\nEncrypted string is: ";
    for (i = 0; i < 3; i++)
        cout<<en[0][i]<<" ";
    for (i = 0; i < 3; i++)
        cout << (char)(en[0][i] + 65);
}
void inversematrix()
{ // find inverse of key matrix
    int i, j, k;
    float p, q;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            if (i == j)
                b[i][j] = 1;
            else
                b[i][j] = 0;
        }
    for (k = 0; k < 3; k++)
    {
        for (i = 0; i < 3; i++)
        {
            p = m[i][k];
            q = m[k][k];
            for (j = 0; j < 3; j++)
            {
                if (i != k)
                {
                    m[i][j] = m[i][j] * q - p * m[k][j];
                    b[i][j] = b[i][j] * q - p * b[k][j];
                }
            }
        }
    }
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            b[i][j] = b[i][j] / m[i][i];
    cout << "\n\nInverse Matrix is:\n";
    
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            cout << b[i][j] << " ";
        cout << "\n";
    }
}
void decrypt()
{ // decrypt the message
    int i, j, k;
    inversematrix();
    for (i = 0; i < 3; i++)
        for (j = 0; j < 1; j++)
            for (k = 0; k < 3; k++)
                de[j][i] = de[j][i] + b[j][k] * en[k][i];
    for (i = 0; i < 3; i++)
        cout<<de[0][i]<<" ";
    cout << "\n";
    cout << "\nDecrypted string is: ";
    for (i = 0; i < 3; i++)
        cout << (char)(fmod(de[0][i], 26) + 65); // modulo 26 is taken to get the original message
    cout << "\n";
}
int main()
{
    getKeyMatrix();
    encrypt();
    decrypt();
}