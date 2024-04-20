#include <iostream>
#include <cstring>

using namespace std;

class encrypyion_strategy {
public:
    virtual char* encryption(char* plaintext, int key) = 0;
    virtual char* decryption(char* ciphertext, int key) = 0;
};

class caesar_cipher : encrypyion_strategy {
public:
    char* encryption(char* plaintext, int key) {
        int len = strlen(plaintext);
        char* ciphertext = new char[len + 1];
        for (int i = 0; i < len; i++) {
            if (isalpha(plaintext[i])) {
                if (islower(plaintext[i])) {
                    ciphertext[i] = 'a' + (plaintext[i] - 'a' + key)%26;
                }
                else {
                    ciphertext[i] = 'A' + (plaintext[i] - 'A' + key) % 26;
                }
            }
            else {
                cerr << "Unsupported text";
                return nullptr;
            }
        }
        ciphertext[len] = '\0';
        return ciphertext;
    }

    char* decryption(char* ciphertext, int key) {
        int len = strlen(ciphertext);
        char* plaintext = new char[len + 1];
        for (int i = 0; i < len; i++) {
            if (isalpha(ciphertext[i])) {
                if (islower(ciphertext[i])) {
                    plaintext[i] = 'a' + (ciphertext[i] - 'a' - key + 26) % 26;
                }
                else {
                     plaintext[i] = 'A' + (ciphertext[i] - 'A' - key + 26) % 26;
                }
            }
            else {
                cerr << "Unsupported text";
                return nullptr;
            }
        }
        plaintext[len] = '\0';
        return plaintext;
    }
};

class rail_fence_cipher : encrypyion_strategy {
    char* encryption(char* plaintext, int key) {
        int len = strlen(plaintext);
        char* ciphertext = new char[len + 1];
        int cycle = 2*key - 2;
        int index = 0;
        for (int i = 0; i < key; i++) {
            for (int j = 0; j + i < len; j += cycle) {
                ciphertext[index++] = plaintext[j + i];
                if (i != 0 && i != key - 1 && j + cycle - i < len)
                    ciphertext[index++] = plaintext[j + cycle - i];
            }
        }
        ciphertext[len] = '\0';
        return ciphertext;
    }

    char* decryption(char* ciphertext, int key) {
        int len = strlen(ciphertext);
        char* plaintext = new char[len + 1];
        int cycle = 2*key - 2;
        int index = 0;
        for (int i = 0; i < key; i++) {
            int j = 0;
            while (j + i < len) {
                plaintext[j + i] = ciphertext[index++];
                if (i != 0 && i != key - 1 && j + cycle - i < len)
                    plaintext[j + cycle - i] = ciphertext[index++];
                j += cycle;
            }
        }
        plaintext[len] = '\0';
        return plaintext;
    }
};

class text_processor {
private:
    encrypyion_strategy* strategy;
public:
    text_processor(encrypyion_strategy* strategy = nullptr) : strategy(strategy) {};
    ~text_processor() {
        delete this->strategy;
    }
    void set_strategy(encrypyion_strategy* strategy) {
        delete this->strategy;
        this->strategy = strategy;
    }
    char* encryption(char* text, int key) {
        this->strategy->encryption(text, key);
    }
    char* decryption(char* text, int key) {
        this->strategy->decryption(text, key);
    }
};

int main() {
    
}