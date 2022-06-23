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

void save_account();
void displayAccountDetails(int);
void intro();


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
    outFile.open("account.txt", fstream::in | fstream::out | fstream::app);
    account.createAccount();
    outFile.write(reinterpret_cast<const char *>(&account), sizeof(account));
    outFile.close();

}

void displayAccountDetails(int acNo){
    account account;
    bool flag = false;
    ifstream inFile("account.txt");

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


