#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

#define A last_4[0]
#define B last_4[1]
#define C last_4[2]
#define D last_4[3]
#define E last_4[4]

using namespace std;

/**
 * Initializes five bitsets of size 5 to keep track of 5-bit groupings
 * last_4 is used to store the last 4 outcomes
 * list is used to store all the 5-bit bitsets
 * counter is used to keep track of which outcome the program is predicting
 */
bitset<5> bitset1 (string("00000")); 
bitset<5> bitset2 (string("00000")); 
bitset<5> bitset3 (string("00000")); 
bitset<5> bitset4 (string("00000")); 
bitset<5> bitset5 (string("00000")); 
bitset<4> last_4 (string("0000")); 
vector<bitset<5>> list; 
int counter = 0;


/**
 * Loops through the vector and compares all the bitsets to the last 4 outcomes and makes a prediction 
 * based on the relationship between them. If there are no bitsets in the vector or there is no relationship between
 * the last four outcomes and any bitset in the vector, then predict 1 because 1's occur the most between the two 
 * branch files.  
 */ 

int getPrediction() {
    int taken = 0;
    int notTaken = 0;
    for(vector<bitset<5>>::iterator it = list.end(); it != list.begin(); it--) {
        if(D == (*it)[0] && C == (*it)[1] && B == (*it)[2] && A == (*it)[3]) {
            if((*it)[4] == 1) {
                taken++;
            }
            else {
                notTaken++;
            }
        }
    }
    if(notTaken > taken) {return 0;}
    return 1;
}

/**
 * Left shift the outcomes into the bitsets.
 * Once a bitset is filled with outcomes the bitset will be pushed into the vector
 */
void updatePrediction(int outcome) {
    last_4 <<= 1;
    if(outcome == 1) {last_4.set(0,1);}

    if(counter == 1) {
        bitset1 <<= 1;
        if(outcome == 1) {bitset1.set(0,1);}
    }
    else if(counter == 2) {
        bitset1 <<= 1;
        bitset2 <<= 1;
        if(outcome == 1) {bitset1.set(0,1); bitset2.set(0,1);}
    }
    else if(counter == 3) {
        bitset1 <<= 1; bitset2 <<= 1; bitset3 <<= 1;
        if(outcome == 1) {bitset1.set(0,1); bitset2.set(0,1); bitset3.set(0,1);}
    }
    else if(counter == 4) {
        bitset1 <<= 1; bitset2 <<= 1; bitset3 <<= 1; bitset4 <<= 1;
        if(outcome == 1) {bitset1.set(0,1); bitset2.set(0,1); bitset3.set(0,1); bitset4.set(0,1);} 
    }
    else {//counter >= 5
        bitset1 <<= 1; bitset2 <<= 1; bitset3 <<= 1; bitset4 <<= 1; bitset5 <<= 1;
        if(outcome == 1) {bitset1.set(0,1); bitset2.set(0,1); bitset3.set(0,1); bitset4.set(0,1); bitset5.set(0,1);}
        if(counter % 5 == 0) {
            list.push_back(bitset1);
            bitset1.set();
        }
        else if((counter-1) % 5 == 0) {
            list.push_back(bitset2);
            bitset2.set();
        }
        else if((counter-2) % 5 == 0) {
            list.push_back(bitset3);
            bitset3.set();
        }
        else if((counter-3) % 5 == 0) {
            list.push_back(bitset4);
            bitset4.set();
        }
        else if((counter-4) % 5 == 0) {
            list.push_back(bitset5);
            bitset5.set();
        }
        if(list.size() > 10) {
            list.erase(list.begin());
        }
    }
    return;
}

/**
 * Opens branch files and output file and loops through the branch file to get the outcome
 * Compares the outcome to the prediction and outputs the result to the output file
 */
int main() {
    ifstream inFile;
    ofstream outFile;
    inFile.open("BranchInput1.txt");
    outFile.open("Output.txt");
    int outcome, prediction;
    int correct = 0, incorrect = 0;

    while(inFile >> outcome) {
        counter++;
        prediction = getPrediction();
        outFile << "I guessed " << prediction << "\t";
        updatePrediction(outcome);
        if(prediction == outcome) {outFile << "Prediciton " << counter << " was correct" << endl; correct++;}
        else {outFile << "Prediction " << counter << " was incorrect" << endl; incorrect++;}
    }
    inFile.close();
    outFile << "Correct: " << correct << "\t Incorrect: " << incorrect << endl;
    outFile.close();
    return 0;
}