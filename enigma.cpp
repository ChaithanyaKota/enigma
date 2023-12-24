#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std; 

class Rotor { 
private: 
    vector<int> wiring; 
    int position; 

public: 
    Rotor(const vector<int> &wiring) : wiring(wiring), position(0) {}

    void setStartPositions(int startPos) { 
        position = startPos % 26;
    }

    // When character goes throgh rotors for the first time
    int encrypt(int input) {
        int offset = position - 'A';
        int output = (input + offset) % 26;

        return wiring[output];
    }

    // When char goes through rotors after passing through reflector
    int reverseEncrypt(int input) { 
        int offset = position - 'A';
        auto it = find(wiring.begin(), wiring.end(), input);
        int output = distance(wiring.begin(), it);

        output = (output - offset + 26) % 26;

        return output; 
    }

    void rotate() { 
        position = (position + 1) % 26; 
    }
    
};

class EnigmaMachine { 
private: 
    vector<Rotor> rotors; 

public: 
    EnigmaMachine(const vector<vector<int>>& rotorConfig) { 
        for(const auto &wiring: rotorConfig) {
            rotors.emplace_back(wiring);
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

        void rotateRotors() { 
            rotors.front().rotate();
            
            for(int i = 0; i < rotors.size() - 1; i++) { 
                if((rotors[i].getPosition() - 'A') % 26 )
            }
        }
    }
};

int main() { 

}
