#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

#define RST "\033[0m"
#define RED "\033[31m"
#define GRN "\033[32m"
#define YEL "\033[33m"
#define BLU "\033[34m"
#define MAG "\033[35m"
#define CYN "\033[36m"
#define WHT "\033[37m"
#define BLD "\033[1m"
#define BG_RED "\033[91m"
#define BG_GREEN "\033[92m"
#define BG_YELLOW "\033[93m"
#define BG_BLUE "\033[94m"
#define Blink "\033[5m"
#define ORANGE "\033[38;5;208m"
#define PINK "\033[38;5;205m"
#define PURPLE "\033[38;5;129m"
#define LIME "\033[38;5;118m"
#define TEAL "\033[38;5;30m"
#define LAVENDER "\033[38;5;183m"
#define MINT "\033[38;5;121m"
#define PEACH "\033[38;5;216m"
#define SKY "\033[38;5;117m"
#define LEMON "\033[38;5;228m"
#define ROSE "\033[38;5;217m"
#define DEEP_ORANGE "\033[38;5;208m"
#define PASTEL_YELLOW "\033[38;5;228m"
#define PASTEL_PINK "\033[38;5;217m"
#define PASTEL_BLUE "\033[38;5;117m"
#define ELEGANT_PURPLE "\033[38;5;177m"
#define GENTLE_GREEN "\033[38;5;151m"

// Declare global variable
string accountNumber;

// Control input to only allow value that is 16 digit number (reject any alphabet or special symbols)
void inputAccountNumber()
{
	// Loop until the the input value is valid
	while (true)
	{
		// Display title
		cout << ELEGANT_PURPLE << "==================================================================" << RST << endl;
		cout << BLD << MAG << "                     CREDIT LIMIT CALCULATOR                      " << RST << endl;
		cout << ELEGANT_PURPLE << "==================================================================" << RST << endl;
		cout << ROSE << "Enter account number, 16 digits (or -1 to quit): " << RST;
		getline(cin, accountNumber);
		cout << endl;
		cout << ELEGANT_PURPLE << "------------------------------------------------------------------" << RST << endl;
		int accLength = accountNumber.length();

		// Validate Account Number
		if (accountNumber != "-1")
		{
			if (accountNumber[0] != '-')
			{

				bool valid = true;
				for (char c : accountNumber)
				{
					if (!isdigit(c) && c != '.')
					{
						cout << RED << Blink << "INVALID : ACCOUNT NUMBER MUST BE A NUMBER " << RST << endl
							 << " " << endl
							 << " " << endl;
						valid = false;
						break;
					}
				}
				if (!valid)
				{
					continue;
				}
				else
				{
					if (accLength == 16)
					{
						for (int n = 0; n < accLength - 4; n++)
						{
							accountNumber[n] = '*';
						}
						return;
					}
					else
					{
						cout << RED << Blink << "INVALID : ACCOUNT NUMBER MUST BE 16 DIGIT\n \n"
							 << RST
							 << endl;
					}
				}
			}
			else
			{

				cout << RED << Blink << "INVALID : ACCOUNT NUMBER CANNOT BE A NEGATIVE VALUE\n \n"
					 << RST
					 << endl;
			}
		}
		else
		{
			cout << GRN << "Thank you for using credit limit calculator" RST << endl;
			exit(1);
		}
	}
}

// Control input to only allow value that is number (reject any alphabet or special symbols and ony can have a maximum of 2 decimal places)
double checkInput(string printedText)
{
	string input;

	// Loop until the the input value is valid
	while (true)
	{
		// Accept input from user
		cout << ROSE << "Enter " << RST << printedText;
		getline(cin, input);

		// Declare variables
		bool isValid = true;
		int decimalCount = 0;
		bool hasDecimal = false;

		if (input[0] == '-')
		{
			cout << RED << Blink << "INVALID : CANNOT BE A NEGATIVE VALUE\n\n"
				 << RST;
			continue;
		}

		// check every single character that it is digit
		for (char c : input)
		{
			if (isdigit(c))
			{
				// Count decimal places
				if (hasDecimal == true)
					decimalCount++;
			}
			else if (c == '.')
			{
				// Invalid if dots presence for twice
				if (hasDecimal == true)
				{
					isValid = false;
					break;
				}
				hasDecimal = true;
			}
			else
			{
				isValid = false;
				break;
			}
		}

		if (!isValid)
		{
			cout << RED << Blink << "INVALID : MUST BE A NUMBER\n\n"
				 << RST << endl;
			continue;
		}

		if (decimalCount > 2)
		{
			cout << RED << Blink << "INVALID : MAX TWO DECIMAL PLACES ALLOWED\n\n"
				 << RST;
			continue;
		}

		// convert value to data type double
		double value = stod(input);
		return value;
	}
}

int main()
{
	// Declare Variables
	double beginningBalance;
	double totalCharges;
	double totalCredits;
	double creditLimit;
	inputAccountNumber();

	while (accountNumber != "-1")
	{
		// Get input from user
		beginningBalance = checkInput(ROSE "beginning balance : " RST);
		totalCharges = checkInput(ROSE "total charges     : " RST);
		totalCredits = checkInput(ROSE "total credits     : " RST);
		creditLimit = checkInput(ROSE "credit limit      : " RST);

		// Calculate new Balance
		double newBalance = beginningBalance + totalCharges - totalCredits;

		// Display error message if total credit more than balance
		if (newBalance < 0)
		{
			cout << "\n";
			cout << BG_RED << "Total Credit cannot be more than Balance." << RST << endl;
			cout << "\n"
				 << "\n";
		}
		else
		{
			cout << fixed << setprecision(2);
			// Display result based on condition
			if (newBalance > creditLimit)
			{

				cout << "\n";
				cout << GENTLE_GREEN << "New balance is " << newBalance << "." << RST << endl;
				cout << ELEGANT_PURPLE << "------------------------------------------------------------------" << RST << endl;
				cout << ROSE << "Account No.     : " << RST << accountNumber << endl;
				cout << ROSE << "Credit limit    : " << RST << creditLimit << endl;
				cout << ROSE << "Balance         : " << RST << newBalance << endl;
				cout << "\n";
				cout << BG_RED << "Credit Limit Exceeded." << RST << endl
					 << " " << endl
					 << " " << endl;
				inputAccountNumber();
			}

			else
			{
				cout << "\n";
				cout << GENTLE_GREEN << "New balance is " << newBalance << "." << RST << endl;
				cout << "\n"
					 << "\n";
				inputAccountNumber();
			}
		}
	}

	return 0;
}