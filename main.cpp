#include <iostream>
#include <string>
#include <limits>
#include <unordered_map>

using namespace std;

#define MAX_NUM 3999
#define NUMERAL_LENGTH 7

string multiplyChar(char input, int multiplyBy) {
	/**
		* Transform a character into a string of repeated characters
		* 
		* @param input What character to repeat
		* @param multiplyBy How many times to repeat character
		* @return string of multiplied characters
	**/
	string output = "";
	for (int i = 0; i < multiplyBy; i++) {
		output += input;
	}
	return output;
}

string toRomanNumeral(int userNumber) {
	/**
		* Translate an integer into a Roman numeral string.
		*
		* @param userNumber an integer to translate
		* @return a string with the Roman numeral representation of userNumber
	**/
	char numerals[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
	int numeralValues[] = {1000, 500, 100, 50, 10, 5, 1};
	string output = "";
	int currentNumeral = 0;
	//continue until the users number gets subtracted to 0
	while (userNumber > 0) {
		//get number of characters we need to add
		int numCharacters = userNumber / numeralValues[currentNumeral];
		//if we need four characters, instead put one character then get the next highest character and add it.
		if (numCharacters == 4) {
			output += numerals[currentNumeral];
			output += numerals[currentNumeral - 1];
			//update userNumber to reflect changes
			userNumber -= numCharacters * numeralValues[currentNumeral];
		}
		//if the current checking numeral is divisible by 2 (means it is one of the 10^x numbers) and if adding the numeral 2 spots lower would add another character 
		numCharacters = userNumber / numeralValues[currentNumeral];
		if (currentNumeral % 2 == 0 && currentNumeral < NUMERAL_LENGTH - 1 && (userNumber + numeralValues[currentNumeral + 2]) / numeralValues[currentNumeral] == numCharacters + 1) {
			//add the amount of characters before the subtraction numerals are added. (In 39, this line would add XXX)
			output += multiplyChar(numerals[currentNumeral], numCharacters);
			//add the other two characters with the lower one first. (In 39, these lines would add IX)
			output += numerals[currentNumeral + 2];
			output += numerals[currentNumeral];
			//subtract the subtracted numerals from the number (in 39 this would subtract 9)
			userNumber -= numeralValues[currentNumeral] - numeralValues[currentNumeral + 2];
			//subtract the amount of characters added (in 39, this would subtract 30)
			userNumber -= numCharacters * numeralValues[currentNumeral];
		}

		//update number of characters still needed then add to output (In 3, this would be 3) 
		numCharacters = userNumber / numeralValues[currentNumeral];
		output += multiplyChar(numerals[currentNumeral], numCharacters);
		//take away from the users number the amount that was added to the roman numerals. (in 22, this would take away 20, then in later iterations take away 2)
		userNumber -= numCharacters * numeralValues[currentNumeral];
		//check the next lower numeral
		currentNumeral++;
	}
	return output;
}

void initializeMap(unordered_map<char, int>& numeralMap) {
	/**
		* Initialize a map by adding pairs of numbers representing Roman numerals.
		*
		* @param numeralMap Map to add Roman numeral pairs to.
	**/
	numeralMap.insert(pair<char, int>('I', 1));
	numeralMap.insert(pair<char, int>('V', 5));
	numeralMap.insert(pair<char, int>('X', 10));
	numeralMap.insert(pair<char, int>('L', 50));
	numeralMap.insert(pair<char, int>('C', 100));
	numeralMap.insert(pair<char, int>('D', 500));
	numeralMap.insert(pair<char, int>('M', 1000));
}

int toDecimalNumber(string romanNumeralInput) {
		/**
		* Translate a Roman numeral into a decimal number.
		*
		* @param romanNumeralInput a string of Roman numeral characters.
		* @return an integer representation of romanNumeralInput. Returns -1 on incorrect input.
	**/
	unordered_map<char, int> numeralMap;
	initializeMap(numeralMap);
	int output = 0;
	// Go through string one character at a time.
	for (int i = 0; i < romanNumeralInput.length(); i++) {
		if (numeralMap.find(romanNumeralInput.at(i)) == numeralMap.end()) {
			return -1;
		}
		
		// integer that holds the number represented by the current character.
		int currentNumber = numeralMap.at(romanNumeralInput.at(i));
		// make sure when checking next character, we will not be out of bounds. 
		if (i + 1 < romanNumeralInput.length()) {
			// get an integer representation of the next character
			int nextNumber = numeralMap.at(romanNumeralInput.at(i + 1));
			if (nextNumber > currentNumber) {
				// set current number to the difference between the next number and the current one, so it can be added to the output.
				currentNumber = nextNumber - currentNumber;
				// skip an extra character, since we already checked the next one.
				i++;
			}
		}
		output += currentNumber;
	}
	return output;
}

string getStringInput(string prompt) {
	/**
		* Print a prompt given, then get the user's inputed string
		*
		* @param prompt What to be output before getting user's input
		* @return user's input as a string
	**/
	cout << prompt << endl;
	string output;
	cin >> output;
	return output;
}

int getIntegerInput(string prompt) {
	/**
		* Print a prompt given, then get the user's inputed integer
		*
		* @param prompt What to be output before getting user's input
		* @return user's input as an integer
	**/
	cout << prompt << endl;
	int output;
	cin >> output;
	while(cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Incorrect input, please try again." << endl;
		cin >> output;
	}
	return output;
}

int main() {
  string userInput;
	cout << "Welcome to the Roman Numeral Translator!" << endl;
	
	do {
		userInput = getStringInput("Would you like to translate Roman numerals to decimal or decimal to Roman numerals? (Type r2d or d2r or enter q to quit)");
		if (userInput == "d2r") {
			int userDecimalNumber = getIntegerInput("What decimal number would you like to translate?");
			if (userDecimalNumber <= MAX_NUM && userDecimalNumber >= 0) {
				string numeralRepresentation = toRomanNumeral(userDecimalNumber);
				cout << "*****" << endl;
				cout << "The translated version of " << userDecimalNumber << " is " << numeralRepresentation << endl;
				cout << "*****" << endl;
			}
			else {
				cout << "The number you entered is out of range. Please type a number from 0 to 3999." << endl;
			}
			
		}
		else if (userInput == "r2d") {
			string userRomanNumeral = getStringInput("What Roman numeral would you like to translate?");
			int decimalRepresentation = toDecimalNumber(userRomanNumeral);

			if(decimalRepresentation < 0) {
				cout << "Incorrect input, please enter a Roman numeral with capital characters I, V, X, L, C, D, or M." << endl;
			}
			else {
				cout << "*****" << endl;
				cout << "The translated version of " << userRomanNumeral << " is " << decimalRepresentation << endl;
				cout << "*****" << endl;
			}
		}
		else if (userInput != "q") {
			cout << "Incorrect input. Please type \"d2r\" to translate to Roman Numerals and \"r2d\" to translate to decimal." << endl;
		}
		else {
			cout << "Thank you for using the Roman Numeral Translator!" << endl;
		}
	} while (userInput != "q");
}