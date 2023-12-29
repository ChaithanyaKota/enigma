#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std; 

class Rotor { 
private: 
    vector<int> wiring; 
    int position; 
    int notch;

public: 
    Rotor(const vector<int> &wiring, int notch) : wiring(wiring), position(0), notch(notch) {}

    void setStartPositions(int startPos) { 
        position = startPos % 26;
    }

    int encrypt(int input) {
        int output = wiring[(input + position) % 26];

        return output;
    }

    void rotate() { 
        position = (position + 1) % 26; 
    }

    int getPosition() const {
        return position; 
    }

    int getNotch() const {
        return notch;
    }
    
};

class EnigmaMachine { 
private: 
    vector<Rotor> rotors; 

public: 
    // Wiring
    EnigmaMachine(const vector<vector<int>>& rotorConfig) { 
        for(const auto &wiring: rotorConfig) {
            rotors.emplace_back(wiring, 0); // Notches set to 0
        }
    }

    // Rotor start positions
    void setRotorPositions(const vector<int> positions) { 
        for(int i = 0; i < rotors.size(); i++) { 
            rotors[i].setStartPositions(positions[i]);
        }
    }

    //Encryption
    char encrypt (char input) { 
        int output = input - 'A';

        // Encryption 
        for(auto &rotor : rotors) { 
            output = rotor.encrypt(output);
        }

        // Reflector 
        output = (output + 13) % 26;

        // Reverse Encryption
        for (auto rit = rotors.rbegin(); rit != rotors.rend(); ++rit) {
               output = rit->encrypt(output);
           }

        return (static_cast<char>(output + 'A'));
    }

    // Rotating rotors
    void rotateRotors() { 
            
        }
};

int main() { 
    vector<vector<int>> rotorConfig = {
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25}
    };

    EnigmaMachine enigma(rotorConfig);
    vector<int> rotorPositions = {0, 0, 0};

    string message = "HELLO";
    string encryptedMessage;
    string decryptedMessage;

    // Encryption
    enigma.setRotorPositions(rotorPositions);
    for(char c: message) { 
        if(isalpha(c)) { 
            char encryptedChar = enigma.encrypt(toupper(c));
            encryptedMessage += encryptedChar;

            // enigma.rotateRotors();
        }
        else { 
            encryptedMessage += c; 
        }
    }

    // Decryption
    enigma.setRotorPositions(rotorPositions);
    for(char c: encryptedMessage) { 
        if(isalpha(c)) { 
            char decryptedChar = enigma.encrypt(toupper(c));
            decryptedMessage += decryptedChar;

            // enigma.rotateRotors();
        }
        else { 
            decryptedMessage += c; 
        }
    }


    cout << "Original Message: " << message << endl;
    cout << "Encrypted Message: " << encryptedMessage << endl;
    cout << "Decrypted Message: " << decryptedMessage << endl;


    return 0; 
}
