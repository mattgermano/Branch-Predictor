//look at past 4-bit groupings
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

bitset<5> bitset1 (string("00000"));  //set a bitset to all 0's
bitset<5> bitset2 (string("00000"));  //set a bitset to all 0's
bitset<5> bitset3 (string("00000"));  //set a bitset to all 0's
bitset<5> bitset4 (string("00000"));  //set a bitset to all 0's
bitset<5> bitset5 (string("00000"));  //set a bitset to all 0's
bitset<4> last_4 (string("0000"));
vector<bitset<5>> list;
int counter = 0;

#define A last_4[0]
#define B last_4[1]
#define C last_4[2]
#define D last_4[3]

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

void updatePrediction(int outcome) {//creates a 5-bit bitset of each history of 5 bits long
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
            list.push_back(bitset1);//add it to the vector
            bitset1.set();//set bitset to all 1's
        }
        else if((counter-1) % 5 == 0) {
            list.push_back(bitset2);//add it to the vector
            bitset2.set();//set bitset to all 1's
        }
        else if((counter-2) % 5 == 0) {
            list.push_back(bitset3);//add it to the vector
            bitset3.set();//set bitset to all 1's
        }
        else if((counter-3) % 5 == 0) {
            list.push_back(bitset4);//add it to the vector
            bitset4.set();//set bitset to all 1's
        }
        else if((counter-4) % 5 == 0) {
            list.push_back(bitset5);//add it to the vector
            bitset5.set();//set bitset to all 1's
        }
        if(list.size() > 10) {
            list.erase(list.begin());
        }
    }
    return;
}

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