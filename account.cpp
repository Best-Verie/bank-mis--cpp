//
// Created by verie on 6/23/2022.
//

#include<iostream>
#include <fstream>
using namespace std;

class account{
    int accountNo;
    char name[100];
    char type;
    int amount;

public:
    void createAccount();
    void showAccount() const;
    void modify();
    void deposit(int);
    void withdraw(int);
    void report() const;
    int showAccountNo() const;
    int showBalance() const;
    char showAccountType() const;

};

void account::createAccount() {
    cout<<"\n Enter the accountNo.: ";
    cin>>accountNo;
    cout<<"\n Enter the name of the account owner.: ";
    cin.ignore();
    cin.getline(name,100);
    cout<<"\n Enter the name of the type of account (C/S).: ";
    cin>>type;
    type= toupper(type);
    cout<<"\n Enter the initial deposit amount.:";
    cin>>amount;
    cout<<"\n ACCOUNT CREATED!";

}

void account::showAccount() const {
    cout<<"\n Account No. : "<<accountNo;
    cout<<"\n Account owner name. : "<<name;
    cout<<"\n Account type. : "<<type;
    cout<<"\n Account balance amount. : "<<amount;
}

int account::showAccountNo() const {
    return accountNo;
}
//void account::showAccountType() const {
//    return type;
//}

void account::deposit(int amount) {
    amount+= amount;
}

void account::withdraw(int amount) {
    amount-= amount;
}

char account::showAccountType() const {
    return type;
}

int account::showBalance() const {
    return amount;
}

void save_account();
void displayAccountDetails(int);
void intro();
void deposit_withdraw(int, int);


int main(){
    char ch;
    int accountNumber;
    intro();
    do{
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. NEW ACCOUNT";
        cout<<"\n\n\t02. DEPOSIT AMOUNT";
        cout<<"\n\n\t03. WITHDRAW AMOUNT";
        cout<<"\n\n\t04. BALANCE ENQUIRY";
        cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>ch;
//        system("cls");
        switch (ch) {
            case '1':
                save_account();
                break;

            case '2':
                cout<<"\n Enter the account number.:  ";
                cin>>accountNumber;
                deposit_withdraw(accountNumber, 1);
                break;
            case '3':
                cout<<"\n Enter the account number.:  ";
                cin>>accountNumber;
                deposit_withdraw(accountNumber, 2);
                break;

            case '4':
                cout<<"\n Enter the account number.:  ";
                cin>>accountNumber;
                displayAccountDetails(accountNumber);
                break;
            default:
                cout<<"Invalid option!"<<endl;
                break;
        }
    } while (ch!=8);

    return 0;
}

void intro(){
    cout<<"\n\t BANK";
    cout<<"\n\t MANAGEMENT";
    cout<<"\n\t SYSTEM";
    cout<<"\n\t MADE BY: verie Best";
    cout<<"\n\n\t press any key to continue";
    cin.get();
}

void save_account(){
    account account;
    ofstream outFile;
    outFile.open("account.dat", fstream::binary | fstream::out | fstream::app);
    account.createAccount();
    outFile.write(reinterpret_cast<const char *>(&account), sizeof(account));
    outFile.close();

}

void displayAccountDetails(int acNo){
    account account;
    bool flag = false;
    ifstream inFile("account.dat");

    if(!inFile){
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n ACCOUNT DETAILS";
    while (inFile.read(reinterpret_cast<char *>(&account), sizeof(account))){
        if(account.showAccountNo() == acNo){
            account.showAccount();
            flag= true;
        }
    }
    inFile.close();
    if(!flag){
        cout<<"\n\n Account number does not exist";
    }
}


void deposit_withdraw(int accNo, int option){
    int amount;
    bool found = false;
    account account;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && !found){
        File.read(reinterpret_cast<char *>(&account), sizeof(account));
        if(account.showAccountNo() == accNo){
            account.showAccount();
            if(option == 1){
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"\n\nEnter The amount to be deposited";
                cin>>amount;
                account.deposit(amount);

            }
            if(option == 2){
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                cout<<"\n\nEnter The amount to be withdraw";
                cin>>amount;
                int balance = account.showBalance() - amount;
                if((balance < 500 && account.showAccountType() == 'S') || (balance<1000 && account.showAccountType()=='C')){
                    cout<<"Insufficient balance";
                }
                else{
                    account.withdraw(amount);
                }
            }

            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&account), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    File.close();
    if(!found)
        cout<<"\n\n Record Not Found ";
}


