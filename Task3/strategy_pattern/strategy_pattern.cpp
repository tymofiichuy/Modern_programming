#include <iostream>
#include <cstring>

using namespace std;

class encryption_strategy {
public:
    virtual char* encryption(const char* plaintext, int key) = 0;
    virtual char* decryption(const char* ciphertext, int key) = 0;
};

class caesar_cipher : public encryption_strategy {
public:
    char* encryption(const char* plaintext, int key) {
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
                throw runtime_error ("Unsupported text");
            }
        }
        ciphertext[len] = '\0';
        return ciphertext;
    }

    char* decryption(const char* ciphertext, int key) {
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
                throw runtime_error("Unsupported text");
            }
        }
        plaintext[len] = '\0';
        return plaintext;
    }
};

class rail_fence_cipher : public encryption_strategy {
    char* encryption(const char* plaintext, int key) {
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

    char* decryption(const char* ciphertext, int key) {
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
    encryption_strategy* strategy;
public:
    text_processor(encryption_strategy* strategy = nullptr) : strategy(strategy) {};
    ~text_processor() {
        delete this->strategy;
    }
    void set_strategy(encryption_strategy* strategy) {
        delete this->strategy;
        this->strategy = strategy;
    }
    char* encryption(const char* text, int key) {
        return this->strategy->encryption(text, key);
    }
    char* decryption(const char* text, int key) {
        return this->strategy->decryption(text, key);
    }
};

//Input signature: strategy, function, text, key
int text_processing(int argc,const char** argv) {
    if (argc != 5) {
        cerr << "Incorrect input signature";
        return 1;
    }
    else {
        encryption_strategy* strategy;
        if (strcmp(argv[1], "caesar_cipher") == 0) {
            strategy = new caesar_cipher();
        }
        else if (strcmp(argv[1], "rail_fence_cipher") == 0) {
            strategy = new rail_fence_cipher();
        }
        else {
            cerr << "Incorrect strategy";
            return 1;
        }
        text_processor processor(strategy);

        int key;
        if (atoi(argv[4]) != 0) {
            key = atoi(argv[4]);
        }
        else {
            cerr << "Incorrect key format";
            return 1;
        }

        if (strcmp(argv[2], "encryption") == 0) {
            try {
                cout << processor.encryption(argv[3], key);
            }
            catch (runtime_error& e) {
                cerr << e.what();
                return 1;
            }
            return 0;
        }
        else if (strcmp(argv[2], "decryption") == 0) {
            try {
                cout << processor.decryption(argv[3], key);
            }
            catch (runtime_error& e) {
                cerr << e.what();
                return 1;
            }
            return 0;
        }
        else {
            cerr << "Incorrect function";
            return 1;
        }
    }
}

int main(int argc,const char** argv) {
    return text_processing(argc, argv);
}
