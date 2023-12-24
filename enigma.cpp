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
    int reversEncrypt(int input) { 
        
    }

    void rotate() { 
        position = (position + 1) % 26; 
    }
    
};

class EnigmaMachine { 

};

int main() { 

}
