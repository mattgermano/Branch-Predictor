/* Written by Prof. Aaron Carpenter for Lab 6 */
/* You may use this as is, but fill in getPrediction and updatePrediction */

#include <stdio.h>

int taken = 0, notTaken = 0;
//UPDATE THIS FUNCTION
int getPrediction() {
	return 1; //You make this part
}

//UPDATE THIS FUNCTION
void updatePrediction(int outcome) {
	return; //You make this part
}

int main() {
	FILE *fp, *fpw;
	fp = fopen("BranchInput2.txt", "r");
	fpw = fopen("Output.txt", "w");
	int outcome, prediction;
	int counter = 0, correct = 0, incorrect = 0;
		
	while(1){
		counter++;
		prediction = getPrediction();
		fscanf(fp, "%d", &outcome);
		updatePrediction(outcome);
		
		if(prediction == outcome){
			fprintf(fpw, "Prediction %d was correct \n", counter);
			correct++;
		}	
		else {
			incorrect++;
			fprintf(fpw, "Prediction %d was incorrect \n", counter);
		}		
		if( feof(fp) )
			break;
	}
	fprintf(fpw, "Correct: %d; \t Incorrect: %d \n", correct, incorrect);
	fclose(fp);
	fclose(fpw);
}