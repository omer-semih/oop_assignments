#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int determineMode(char arr[]); // Function to check mode wheter -r or -u
int extractNumberGetDigit(char secretNum[], char enteredNum[]); // Function to extract number after -u and calculate it's digit
int isDigitValid(int digit); // Function to check if number has valid number of digits
void randomNumGenerator(char arr[],int size,int digit,char randomNum[]); // Function to generate random valid number
int compareNumbers(char secretNum[], char userNum[], int digit, int& count); // Function to compare entered num with secret num
int isValidNum(char alphabet[],char num[],int digit); // Function to check if entered number is a valid number

int main(int argc, char* argv[]) {

srand((unsigned) time(NULL));

if(argc != 3) { // Check if main function is called with 3 parameters , otherwise give error
    cout << "E0\n";
    return 1;
}

int mode = determineMode(argv[1]); // Get mode

if(mode == -1) { // If mode is different than -r or -u , give an error and exit
    cout << "E0\n";
    return 1;
}

const char size = 15; // size of alphabet , it won't change
char alphabet[15] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e'};
char secretNum[15],userNum[100]; // Arrays to store secret number and user entered number at each turn
int digit, totalMove=0; // variable to store digit of either random number or user entered following -u number

switch(mode) {

    case 0 : // Mode -r

    digit = stoi(argv[2]); // get digit of desired digit of random number
        if( !isDigitValid(digit) )  { // Check if the number of digits is between 1-15
            cout << "E0\n";
            return 1;           
        }

    randomNumGenerator(alphabet,size,digit,secretNum); // Generate secret num
    break;

    case 1 : // Mode -u
    digit = extractNumberGetDigit(secretNum,argv[2]); // Get number and calculate it's digit following -u

    if( !isDigitValid(digit) || !isValidNum(alphabet,secretNum,digit) )  { // Check if it's a valid number , otherwise give error
        cout << "E0\n";
        return 1;           
    }
    break;

    default : // Default case
    break;
}

char chr; // temp char variable to read user input char-by-char
int index; // index to indicate current index of partially filled array
bool foundFirstChar; // flag to skip whitespaces before input

do {

    if(totalMove == 100) { // If user can't finish the game after 100 iterations , finish the game
        cout << "FAILED" << endl;
        return 1;
    }

    index = 0; // set index to zero every iteration to be ready for the next user word
    foundFirstChar=false;

    while (cin.get(chr) && chr != '\n') {  // Read user entered num char by char until user presses enter
        if (chr == ' ' && !foundFirstChar) { // ignore whitespaces before input
            continue;
        } 
        else {
            foundFirstChar = true; // read input char by char 
            userNum[index] = chr;
            index++; // move to next index of array
        }
    }

    if(index != digit) { // Check if the digit of number's valid
        cout << "E1\n";
        return 1;
    }

    if( !isValidNum(alphabet,userNum,digit) ) { // Check if number is valid
        cout << "E2\n";
        return 1;
    }

} while( compareNumbers(secretNum, userNum, digit, totalMove) != 1); // Check finish status by comparing with secret number

    return (0);
}

int determineMode(char arr[]) { // gets main function parameters as an argument
    if( arr[0] == '-' && arr[1] == 'r' && arr[2] == '\0' ) // If the mode is -r return 0
        return 0;
    
    else if( arr[0] == '-' && arr[1] == 'u' && arr[2] == '\0' ) // If the mode is -u return 1
        return 1;
    
    else 
        return -1; // Return -1 in case of invalid mode
}

int extractNumberGetDigit(char secretNum[], char enteredNum[]) {

    int i=0;
    while(enteredNum[i] != '\0') { // Read input until user press enter
        secretNum[i] = enteredNum[i]; // store -u number in secret num to be secret
        i++; // variable i to represent number of digit
    }

    return i;
}

int isDigitValid(int digit) { // function takes digit of a number to check

    if(digit < 1 || digit > 15) return 0; // If digit's valid return 0 , otherwise return 1
    else return 1;
}

void randomNumGenerator(char arr[],int size,int digit,char randomNum[]) {

    int temp,flag;
    
    do {
    randomNum[0] = arr[rand()%15]; // Avoid selecting first digit 0
    } while(randomNum[0] == '0');
    

    for(int i=1;i<digit;i++) { // for loop to set a random number for each digit of number
	    temp = rand()%15; // Select a random number 
        flag=0;

	    for(int j=0;j<i;j++) { // check if same random number was used previous digits
		    if( arr[temp] == randomNum[j]) { // If same number selected before , set flag to 1 and create a random number again
			i--; // decrease i to go back and create a random number again
			flag=1;
			break;
		    }
	    }

	    if(!flag) randomNum[i] = arr[temp]; // if no matches , then fill random number array with the random number
	        
    }
}

int compareNumbers(char secretNum[], char userNum[], int digit, int& count) {

int a=0,b=0; // a represents C(exact) , b represents C(misplaced)

for(int i=0; i<digit; i++) { // loop for travelling user number's digits
    for(int j=0; j<digit; j++) { // loop for travelling secret number's digits
        if(userNum[i] == secretNum[j]) { // Compare user entered number with secret number
            if(i == j) // If they match in the same place , increase a by one to represent Cexact
                a++;
            else
                b++; // If they match but not in same place , icrease b by one to represent Cmisplaced

        }
    }
}

count++; // count iterations

if(a == digit && b == 0) { // Check if game finished and numbers matched
    cout << "FOUND " << count << endl;
    return 1;
}

else {
    cout << a << " " << b << endl; // If they don't match , give hints
    return 0;
}

} 

int isValidNum(char alphabet[],char num[],int digit) {

    if(num[0] == '0') return 0; // If number starts with 0 , give error

    int flag; // flag to check if match is found
    for(int i=0;i<digit;i++) {  // For loop to iterate each digit of number to be checked
        flag=0; // flag to check if match found
        for(int j=0;j<15;j++) { // loop to travel alphabet
            if( num[i] == alphabet[j] ) { // If digit couldn't be found in alphabet , set flag to 1 
                flag=1;
                break;
            }
        }

        if(!flag) return 0; // If not found in alphabet , give error
        // If found in alphabet , check if every digit is unique
        for(int k=i+1;k<digit;k++) // If the same digit occurs more than once , return 0 to indicate error
            if(num[i] == num[k]) return 0; // If match found then number is invalid
    }

    return 1;
}