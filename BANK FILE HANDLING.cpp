#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "PUPACCOUNTS.DAT"
#define MAX_TRIES 3 // Maximum of input retries

// initializations 
typedef struct {
	char accountNumber[11]; 	// Account Number
	char accountName [26]; 		// Account Name 
	char pin [7]; 				// Account Password
	double deposit; 			// Initial deposit
	char transactionCode; 		// B for Balance, D for Deposit, and W for Withdraw
	double amount; 				// Transaction amount
	double balance; 			// Account Balance
} Account;

void createAccounts();
void transactionProcessing();
void printRecords();
void mainMenu();
int valideAccountNumber(const char *accountNumber);
int validatePIN(const char *pin);

int main(){
	while (1) {
		mainMenu();
	}
	return 0;
}
// Main Menu 
void mainMenu(){
	int choice; 
	printf ("\n -- Welcome to PUP Bank Quezon City Branch! --\n");
	printf ("\nMain Menu\n");
	printf ("1. Create an Account\n");
	printf ("2. Transaction Process\n");
	printf ("3. Print Records\n"); 
	printf ("4. Exit\n");
	printf ("Please select a number: ");
	
	if (scanf("%d", &choice) != 1) {
		printf("Invalid input. Please select a number.\n");
	}

// Selection Menu 
switch (choice){
	case 1: 
		createAccounts();
		break; 
	case 2: 
		transactionProcessing();
		break;
	case 3:
		printRecords();
		break;
	case 4:
		printf("Exiting the program...\n");
		exit(0);
		default: 
		printf("Invalid number, please try again.\n");
	}
}
// 
void createAccounts(){
	FILE *file = fopen(FILENAME, "ab");
	if (!file){
		perror("Error opening file.");
		return;
	}


	Account acc;
	while (1){
		printf("Enter an account number (up to 10 characters, type 'end' to finish.):");
		scanf("%10s", acc.accountNumber);
		if (strcmp(acc.accountNumber, "end") == 0) break;
		if(!validateAccountNumber(acc.accountNumber)){
			printf("Invalid account number. Must be 10 characters long.\n");
			continue;
		}
		printf("Enter an account name:");
		scanf("%25[^\n]", &acc.accountName);
		
		printf("Enter your PIN (up to 6 digits):");
		scanf("%6s", acc.pin);
		if (!validatePIN(acc.pin)){
		printf("Invalid PIN. Must be exactly 6 digits.\n");
		continue;
		}
		printf("Enter initial deposit: ");
		if (scanf("%lf", &acc.deposit) != 1){
			printf("Invalid input. Please enter a valid deposit amount.\n");
		}
		
		acc.balance = acc.deposit;
		acc.transactionCode = 'B';
		acc.amount = 0.0;
		
		fwrite(&acc, sizeof(Account), 1, file);
		printf("Account created successfully.\n");
	}
	fclose(file);
}

int validateAccountNumber(const char *accountNumber){
	return strlen(accountNumber) == 10;
	}

int validatePIN(const char *pin) {
	return strlen(pin) == 6;
}

void transactionProcessing(){
	FILE *file - fopen(FILENAME, "rb+");
	if (!file){
		perror("Error opening file");
		return;
	}
	char accountNumber[11], pin[7];
	Account acc;
	int found = 0, tries = 0;
	
	printf("Enter account number:");
	scanf("%10s", accountNumber);
	if (!validateAccountNumber(accountNumber)) {
		printf("Invalid accoung nunber, Must be 10 characters long.\n");
		fclose(file);
		return;
	}
	while(trie < MAX_TRIES) {
		printf("Enter PIN:");
		scanf("%6s", pin);
		if (!validatePIN(pin)) {
			printf("Invalid PIN. Must be exactly 6 digits.\n");
			tries++;
			continue;
		}
	}
	rewind(file);
	while(fread(&acc, siezof(Account), 1, file)) {
		if (strcmp(acc.accountNumber, accountNumber) == 0 && strcmp(acc.pin, pin) == 0) {
			printf("VALID PIN! The account belongs to %s\n", acc.accountName);
			found = 1;
			break;
		}
	}
	if (found) break;
	printf("INVALID PIN!\n");
	tries++;
}
 if (tries == MAX_TRIES) {
 	printf("Card is captured! Please visit your bank branch to retrieve your card.\n");
 	fclose(file);
 	return;
 }
 
 char transactionCode;
 double amount;
 
 printf("Enter transaction code (B for Balance Inquiry, D for deposit, W for Withdrawal):");
 scanf("%c", &transactionCode);
 acc.transactionCode = transactionCode;
 
 switch (transactionCode){
 	case 'B':
 		printf("Account Balance is: %.2f\n", acc.balance);
 		break;
 	case 'D':
 		printf("Enter deposit amount: ");
 		if (scanf("%lf", &amount) == 1) {
 			printf("Invalid input. Please enter a valid dpeosit amount. \n");
 			break;
		 }
		 acc.amount = amount;
		 acc.balance += amount; 
		 printf("Deposit successful. New balance is : %.2f\n", acc.balance);
		 break;
	case 'W':
		printf("Enter withdrawal amount:");
		if (scanf("%lf", &amount) !=1){
			printf("Invalid input. Please enter a valid withdrawal amount.\n");
			break;
		}
		if (amount > acc.balance) {
			printf("Not enough funds. Transaction is not alllowed.\n");
		} else {
			acc.amount = amount;
			acc.balance -= amount;
			printf("withdrawal successful. New Balance is: %.2f\n", acc.balance);
		}
		break;
		default:
			printf("Invalid transaction code.\n");
			fclose(file);
			return;			
	}
// account update record

	fseek(file, -sizeof(Account), SEEK_CUR);
	fwrite(&acc, sizeof(Account), 1, file);
	
	fclose(file);
}
 void printRecords() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Account acc;
    printf("\nAccount Number  			Account Name                Account Balance\n");
    printf("-----------------------------------------------------------\n");
    while (fread(&acc, sizeof(Account), 1, file)) {
        printf("%-15s %-25s %10.2f\n", acc.accountNumber, acc.accountName, acc.balance);
    }

    fclose(file);
}
	
	

