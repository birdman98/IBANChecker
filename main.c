#include <stdio.h>
#include <string.h>

#define cell0 0
#define cell1 1
#define cell2 2
#define cell3 3

struct IBAN {

	char* countryCode;
	int IBANLength;

};

int checkLength(char* accountNumber, struct IBAN IBANInfo) {

	int rightLength;
	
	if (accountNumber[cell0] == IBANInfo.countryCode[cell0] && accountNumber[cell1] == IBANInfo.countryCode[cell1])
			rightLength = IBANInfo.IBANLength;
	else {
		
		printf("Podano zle dane nt. numeru IBAN!\n");
		
		return 0;
	}

	if (strlen(accountNumber) == rightLength)
		return 1;

	return 0;


}

int numberMod(char* accountNumber, const int divisor) {

	int result = 0;

	for (int i = 0; i < strlen(accountNumber); ++i) {

		result = (result * 10 + (int) accountNumber[i] - '0') % divisor;
	}

	return result;

}

int checkIBAN(char* accountNumber, struct IBAN IBANInfo) {

	if (checkLength(accountNumber, IBANInfo) == 0) {

		printf("Niepoprawna dlugosc numeru IBAN dla podanego kraju!\n");

		return 0;

	}

	const int lettersInNumberModifier = 55;

	char firstDigit[5] = { 0 };
	sprintf(firstDigit, "%d", accountNumber[cell0] - lettersInNumberModifier); 
	
	char secondDigit[5] = { 0 };
	sprintf(secondDigit, "%d", accountNumber[cell1] - lettersInNumberModifier); 

	char controlDigits[5] = { accountNumber[cell2], accountNumber[cell3] }; 
	 
	char nextDigits[30] = { 0 };

	memcpy(nextDigits, accountNumber + 4, strlen(accountNumber) - 4); 

	char numberToCheck[40] = { 0 };

	strncat(numberToCheck, nextDigits, strlen(nextDigits)); //³¹cze w jeden string 4 czêœci sk³adowe 
	strncat(numberToCheck, firstDigit, strlen(firstDigit));
	strncat(numberToCheck, secondDigit, strlen(secondDigit));
	strncat(numberToCheck, controlDigits, strlen(controlDigits));


	if (numberMod(numberToCheck, 97) == 1)

		return 1;

	else 

		return 0;


}


int main() {
	
	struct IBAN iban;
	iban.countryCode = "PL";
	iban.IBANLength = 28;

	char accountNumber[50] = { 0 };

	printf("Podaj nr konta bankowego bez spacji w formacie PLxxxxxxxxxxxxxxxxxxxxxxxxxx: \n\n");
	scanf("%s", accountNumber);
	printf("\n\n");


	if (checkIBAN(accountNumber, iban))
		printf("Podany nr konta jest prawidlowy!\n");
	else
		printf("Podany nr konta jest nieprawidlowy!\n");
	
	return 0;
}