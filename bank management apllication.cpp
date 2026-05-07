#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount {
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cin.ignore();
        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);
        cout << "Enter Initial Deposit: ";
        cin >> balance;
    }

    void showAccount() {
        cout << "\nAccount Number : " << accNo;
        cout << "\nAccount Holder : " << name;
        cout << "\nBalance        : " << balance << endl;
    }

    int getAccNo() {
        return accNo;
    }

    void deposit(float amt) {
        balance += amt;
    }

    void withdraw(float amt) {
        if (amt <= balance)
            balance -= amt;
        else
            cout << "\nInsufficient Balance!";
    }
};

// Create new account
void writeAccount() {
    BankAccount acc;
    ofstream outFile("bank.dat", ios::binary | ios::app);
    acc.createAccount();
    outFile.write((char*)&acc, sizeof(acc));
    outFile.close();
    cout << "\nAccount Created Successfully!\n";
}

// Display account details
void displayAccount(int n) {
    BankAccount acc;
    bool found = false;
    ifstream inFile("bank.dat", ios::binary);

    while (inFile.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccNo() == n) {
            acc.showAccount();
            found = true;
        }
    }

    inFile.close();
    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Deposit / Withdraw
void modifyAccount(int n, int option) {
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    float amt;

    while (file.read((char*)&acc, sizeof(acc)) && !found) {
        if (acc.getAccNo() == n) {
            acc.showAccount();

            if (option == 1) {
                cout << "\nEnter Amount to Deposit: ";
                cin >> amt;
                acc.deposit(amt);
            }
            else {
                cout << "\nEnter Amount to Withdraw: ";
                cin >> amt;
                acc.withdraw(amt);
            }

            int pos = (-1) * sizeof(acc);
            file.seekp(pos, ios::cur);
            file.write((char*)&acc, sizeof(acc));
            cout << "\nTransaction Successful!\n";
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

int main() {
    int choice, accNo;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Balance Check";
        cout << "\n5. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            writeAccount();
            break;

        case 2:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 1);
            break;

        case 3:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 2);
            break;

        case 4:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            displayAccount(accNo);
            break;

        case 5:
            cout << "\nThank You!";
            break;

        default:
            cout << "\nInvalid Choice!";
        }

    } while (choice != 5);

    return 0;
}