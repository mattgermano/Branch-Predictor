#include <iostream>
#include <fstream>

using namespace std;

int getPrediction() {
    return 1; //You make this part
}

void updatePrediction(int outcome) {
    return; //You make this part
}

int main() {
    ifstream inFile;
    ofstream outFile;
    inFile.open("BranchInput1.txt");
    outFile.open("Output.txt");
    int outcome, prediction;
    int counter = 0, correct = 0, incorrect = 0;

    while(inFile >> outcome) {
        counter++;
        prediction = getPrediction();
        updatePrediction(outcome);
        if(prediction == outcome) {outFile << "Prediciton " << counter << " was correct" << endl; correct++;}
        else {outFile << "Prediction " << counter << " was incorrect" << endl; incorrect++;}
    }
    inFile.close();
    outFile << "Correct: " << correct << "\t Incorrect: " << incorrect << endl;
    inFile.close();
    return 0;
}