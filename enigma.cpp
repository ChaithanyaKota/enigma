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

    // For when character goes throgh rotors for the first time
    int encrypt(int input) {
        int output = wiring[input + position];

        return output + 'A';
    }

    // When char goes through rotors after passing through reflector
    int reverseEncrypt(int input) { 
        int offset =  'A' - position;
        auto it = find(wiring.begin(), wiring.end(), input);
        int output = distance(wiring.begin(), it);

        output = (output - offset + 26) % 26;

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
    EnigmaMachine(const vector<vector<int>>& rotorConfig) { 
        for(const auto &wiring: rotorConfig) {
            rotors.emplace_back(wiring, 0); // Notches set to 0
        }
    }

    void setRotorPositions(const vector<int> positions) { 
        for(int i = 0; i < rotors.size(); i++) { 
            rotors[i].setStartPositions(positions[i]);
        }
    }

    char encrypt (char input) { 
        int output = input - 'A';

        // Encryption 
        for(auto &rotor : rotors) { 
            output = rotor.encrypt(output);
        }

        // Reflector 
        output = (output + 13) % 26;

        // Reverse Encryption
        for (auto it = rotors.rbegin(); it != rotors.rend(); ++it) {
            output = it->reverseEncrypt(output);
        }

        return static_cast<char>(output + 'A');
    }

    void rotateRotors() { 
            rotors.front().rotate();

            for(int i = 0; i < rotors.size() - 1; i++) { 
                if((rotors[i].getPosition() - 'A') % 26 == rotors[i+1].getNotch()) { 
                    rotors[i+1].rotate();
                }
            }
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

    // Encryption
    enigma.setRotorPositions(rotorPositions);
    for(char c: message) { 
        if(isalpha(c)) { 
            char encryptedChar = enigma.encrypt(toupper(c));
            encryptedMessage += encryptedChar;
            enigma.rotateRotors();
        }
        else { 
            encryptedMessage += c; 
        }
    }


    cout << "Original Message: " << message << endl;
    cout << "Encrypted Message: " << encryptedMessage << endl;


    return 0; 
}
