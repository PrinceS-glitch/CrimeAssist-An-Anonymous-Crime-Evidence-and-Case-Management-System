#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

int main(){
    string choice;


    cout<<"\\\\\\\\\\---MAIN MENU---\\\\\\\\\\"<<endl<<endl;
    cout<<"a) Admin"<<endl;
    cout<<"b) Officer"<<endl;
    cout<<"c) User"<<endl;
    cout<<"d) Help"<<endl;
    cout<<"e) Exit"<<endl<<endl;

    cout<<"Enter your choice: "<<endl;
    cin>>choice;

    if(choice=="Admin" || choice=="a"){
        void adminMenu();

    }
    else if(choice=="Officer" || choice=="b"){
        void officerMenu();
    }

    else if(choice=="User" || choice=="c"){
        void userMenu();
    }
    else if(choice=="Help"|| choice=="d"){
        void helpMenu();
    }
    else if(choice=="Exit" || choice=="e"){
        void exit();
    }

    else{
        void exit();
    }






    return 0;
}