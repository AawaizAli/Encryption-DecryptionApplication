#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string.h>

using namespace std;

void DecorativeLines(){
    cout << endl;
    cout << "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*" << endl << endl;
}

class EncryptionAlgorithm {
public:
    virtual string encrypt(string plaintext, string username) = 0;
    virtual string decrypt(string ciphertext, string username) = 0;

    virtual ~EncryptionAlgorithm() {}

};

class AtbashCipher : public EncryptionAlgorithm {
public:
    string encrypt(string plaintext, string username){
        
        string ciphertext = "";
        for (int i = 0; i < plaintext.length(); i++) {
            char c = plaintext[i];
            if (isalpha(c)) {
                if (isupper(c)) {
                    ciphertext += static_cast<char>('Z' - (c - 'A'));
                } else {
                    ciphertext += static_cast<char>('z' - (c - 'a'));
                }
            } else {
                ciphertext += c;
            }
        }

        ofstream file("encrypted.txt", ios::app);
        if (file.is_open()) {
            file << "Username: " << username << "\n";
            file << "Encrypted Text: " << ciphertext << "\n";
            file << "Plain Text: " << plaintext << "\n";
            file.close();
        }

        return ciphertext;
    }
    string decrypt(string ciphertext, string username) {

        string plaintext = "";
        int n = ciphertext.length();
        for (int i = 0; i < n; i++) {
            char c = ciphertext[i];
            if (isalpha(c)) {
                if (isupper(c)) {
                    plaintext += static_cast<char>('Z' - (c - 'A'));
                } else {
                    plaintext += static_cast<char>('z' - (c - 'a'));
                }
            } else {
                plaintext += c;
            }
        }

        ofstream file("decrypted.txt", ios::app);
        if (file.is_open()) {
            file << "Username: " << username << "\n";
            file << "Encrypted Text: " << ciphertext << "\n";
            file << "Plain Text: " << plaintext << "\n";
            file.close();
        }

        return plaintext;
    }
};

class CaesarCipher : public EncryptionAlgorithm {
private:
    int key;
public:
    CaesarCipher(int k) {
        key = k;
    }
    string encrypt(string plaintext, string username) {
        string ciphertext = "";
        for (int i = 0; i < plaintext.length(); i++) {
            char ch = plaintext[i];
            if (isalpha(ch)) {
                ch = toupper(ch);
                ch = ((ch - 'A' + key) % 26) + 'A';
            }
            ciphertext += ch;
        }
        ofstream file("encrypted.txt", ios::app);
        if (file.is_open()) {
            file << "Username: " << username << "\n";
            file << "Encrypted Text: " << ciphertext << "\n";
            file << "Plain Text: " << plaintext << "\n";
            file.close();
        }
        return ciphertext;
    }
    string decrypt(string ciphertext, string username) {
        string plaintext = "";
        for (int i = 0; i < ciphertext.length(); i++) {
            char ch = ciphertext[i];
            if (isalpha(ch)) {
                ch = toupper(ch);
                ch = ((ch - 'A' - key + 26) % 26) + 'A';
            }
            plaintext += ch;
        }
        ofstream file("decrypted.txt", ios::app);
        if (file.is_open()) {
            file << "Username: " << username << "\n";
            file << "Encrypted Text: " << ciphertext << "\n";
            file << "Plain Text: " << plaintext << "\n";
            file.close();
        }
        return plaintext;
    }
};

class VigenereCipher : public EncryptionAlgorithm {
private:
    string key;
public:
    VigenereCipher(string k) {
        key = k;
    }
    string encrypt(string plaintext, string username) {
        string ciphertext = "";
        int j = 0;
        for (int i = 0; i < plaintext.length(); i++) {
            char ch = plaintext[i];
            if (isalpha(ch)) {
                ch = toupper(ch);
                ch = ((ch - 'A' + (key[j] - 'A')) % 26) + 'A';
                j = (j + 1) % key.length();
            }
            ciphertext += ch;
        }
        ofstream file("encrypted.txt", ios::app);
        if (file.is_open()) {
            file << "Username: " << username << "\n";
            file << "Encrypted Text: " << ciphertext << "\n";
            file << "Plain Text: " << plaintext << "\n";
            file.close();
        } else {
            cout << "Error writing into file";
        }
        return ciphertext;
    }
    string decrypt(string ciphertext, string username) {
        string plaintext = "";
        int j = 0;
        for (int i = 0; i < ciphertext.length(); i++) {
            char ch = ciphertext[i];
            if (isalpha(ch)) {
                ch = toupper(ch);
                ch = ((ch - 'A' - (key[j] - 'A') + 26) % 26) + 'A';
                j = (j + 1) % key.length();
            }
            plaintext += ch;
        }
        ofstream file("decrypted.txt", ios::app);
        if (file.is_open()) {
            file << "Username: " << username << "\n";
            file << "Encrypted Text: " << ciphertext << "\n";
            file << "Plain Text: " << plaintext << "\n";
            file.close();
        }
        return plaintext;
    }
};

class Text
{
    private:
        string content;
    public:
        Text(string t)
        {
            content = t;
        }

    string getContent()
    {
        return content;
    }

    void setContent(string t)
    {
        content = t;
    }
};

void EncryptMenu(string name){

    
    string content;
    int choice;

    beginning:

    DecorativeLines();

    cout << "Enter the string you would like to encrypt: " << endl;
    fflush(stdin);
    getline(cin, content);

    DecorativeLines();

    cout << "Which encryption algorithm would you like to use? " << endl << "1. Caesar encryption" << endl << "2. Vignere encryption" << endl;
    fflush(stdin);
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
            int key;

            DecorativeLines();

            cout << "Enter encryption key: " << endl;
            cin >> key;

            Text plaintext(content);

            EncryptionAlgorithm* algo1 = new CaesarCipher(key);
            string ciphertext = algo1->encrypt(plaintext.getContent(), name);

            DecorativeLines();

            cout << "Encrypted text: " << ciphertext << endl;

            break;
        }
        case 2:
        {
            string key;

            DecorativeLines();

            cout << "Enter encryption key: " << endl;
            cin >> key;

            Text plaintext(content);

            EncryptionAlgorithm* algo1 = new VigenereCipher(key);
            string ciphertext = algo1->encrypt(plaintext.getContent(), name);

            DecorativeLines();

            cout << "Encrypted text: " << ciphertext << endl;

            break;
        }
        default:
        {
            cout << "Invalid choice " << endl;
            goto beginning;
            break;
        }
    }
}

void DecryptMenu(string name){
    string content;
    int choice;

    beginning:

    DecorativeLines();

    cout << "Enter the string you would like to decrypt: " << endl;
    fflush(stdin);
    getline(cin, content);

    DecorativeLines();

    cout << "Which encryption algorithm did you use? " << endl << "1. Caesar encryption" << endl << "2. Vignere encryption" << endl;
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
            int key;

            DecorativeLines();
            
            cout << "Enter encryption key: " << endl;
            cin >> key;

            EncryptionAlgorithm* algo1 = new CaesarCipher(key);
            string plaintext = algo1->decrypt(content, name);

            DecorativeLines();

            cout << "Decrypted text: " << plaintext << endl;

            break;
        }
        case 2:
        {
            string key;

            DecorativeLines();

            cout << "Enter encryption key: " << endl;
            cin >> key;

            EncryptionAlgorithm* algo1 = new VigenereCipher(key);
            string plaintext = algo1->encrypt(content, name);

            DecorativeLines();

            cout << "Encrypted text: " << plaintext << endl;

            break;
        }
        default:
        {
            cout << "Invalid choice " << endl;
            goto beginning;
            break;
        }
    }
}

void CheckHistory(string name){
    ifstream encryptedFile("encrypted.txt");
    ifstream decryptedFile("decrypted.txt");
    string line;
    bool foundUser = false;

    while (getline(encryptedFile, line)) {
        if (line.find("Username: " + name) != string::npos) {
            foundUser = true;
            cout << "Encrypted messages for " << name << ":\n";
            getline(encryptedFile, line); 
            cout << line << endl;
            getline(encryptedFile, line); 
            cout << line << endl << endl;
        }
    }
    if (!foundUser) {
        cout << "No encrypted messages found for " << name << endl << endl;
    }

    foundUser = false;

    while (getline(decryptedFile, line)) {
        if (line.find("Username: " + name) != string::npos) {
            foundUser = true;
            cout << "Decrypted messages for " << name << ":\n";
            getline(decryptedFile, line); 
            cout << line << endl;
            getline(decryptedFile, line); 
            cout << line << endl << endl;
        }
    }
    if (!foundUser) {
        cout << "No decrypted messages found for " << name << endl << endl;
    }
}

void signup()
{
    DecorativeLines();
    srand(time(NULL));	
    const int PATTERN_LENGTH = 8;
    const float SLEEP_TIME = 0.75;
    char pattern[PATTERN_LENGTH];
    string username;

    start:

        cout << "Enter username: ";
    cin >> username;
    ifstream infile("passwords.txt");
    string line;
    bool usernameExists = false;
    while (getline(infile, line))
    {
        if (line.find("Username: " + username) == 0)
        {
            usernameExists = true;
            break;
        }
    }

    infile.close();
    if (usernameExists)
    {
        cout << "Username already exists. Please choose a different username." << endl;
        goto start;
    }

    ofstream outfile("passwords.txt", ios_base::app);
    outfile << "Username: " << username << ", Password: ";
    cout << "Your password is: ";
    for (int i = 0; i < PATTERN_LENGTH; i++)
    {
        pattern[i] = rand() % (126 - 33 + 1) + 33;
        outfile << pattern[i];
        cout << pattern[i];
        fflush(stdout);
        usleep(SLEEP_TIME *1000000);
    }

    outfile << endl;
    outfile.close();
    cout << endl << "You have been successfully signed up" << endl;
}

const int MAX_USERNAME_LENGTH = 100;
const int MAX_PASSWORD_LENGTH = 100;

bool login(string &name)
{
    DecorativeLines();
    string username, password;
    char c;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    const int PATTERN_LENGTH = 8;
    const float SLEEP_TIME = 0.75;
    char pattern[PATTERN_LENGTH];
    ifstream infile("passwords.txt");	// Open the input file
    string line;
    bool usernameExists = false;
    bool passwordMatches = false;
    while (getline(infile, line))
    {
        if (line.find("Username: " + username) == 0)
        {
            usernameExists = true;
            size_t password_start = line.find("Password: ") + strlen("Password: ");
            string stored_password = line.substr(password_start);
            if (password == stored_password)
            {
                passwordMatches = true;
            }

            break;
        }
    }

    infile.close();
    if (!usernameExists)
    {
        cout << "Username not found." << endl;
        return false;
    }

    if (!passwordMatches)
    {
        cout << "Incorrect password." << endl;
        return false;
    }

    name = username;
    return true;
}

void MainMenu(string name)
{
    while (true){
        DecorativeLines();
        int choice;
        cout << "Would you like to: " << endl << "1. Encrypt/Decrypt new text." << endl << "2. Check history." << endl << "3. Logout and Exit." << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                DecorativeLines();
                cout << "Would you like to: " << endl << "1. Encrypt." << endl << "2. Decrypt." << endl;
                cin >> choice;
                switch (choice)
                {
                    case 1:
                    {
                        EncryptMenu(name);
                        break;
                    }
                    case 2:
                    {
                        DecryptMenu(name);
                        break;
                    }
                    default:
                    {
                        exit(1);
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                CheckHistory(name);
                break;
            }
            case 3:
            {
                exit(1);
                break;
            }
            default:
            {
                exit(1);
                break;
            }
        }
    }
}

void welcomepage(){
    DecorativeLines();
    cout << "Welcome To The HAR Encryption Decryption Software!" << endl;
    DecorativeLines();
    string username;
    int choice;
    cout << "Would you like to: " << endl << "1. Login" << endl << "2. Sign up" << endl;
    cin >> choice;

    bool ok = false;
    int tries = 0;

    if (choice == 2)
    {
        signup();
        ok = login(username);
        tries++;
    }
    else if (choice == 1)
    {
        ok = login(username);
        tries++;
    }
    else
    {
        exit(0);
    }

    while (!ok)
    {
        if (tries < 3)
        {
            cout << "Tries left: " << 3 - tries << endl;
        }

        if (tries >= 3)
        {
            cout << "Your are out of tries, Login Failed!" << endl;
            exit(0);
        }

        ok = login(username);
        tries++;
    }

    MainMenu(username);
}

int main()
{
    welcomepage();
    return 0;
}