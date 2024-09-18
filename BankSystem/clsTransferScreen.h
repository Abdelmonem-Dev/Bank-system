#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "Global.h"
class clsTransferScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }
    static string _ReadAccountNumber()
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static float ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadFloatNumber();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }



/*    static bool _Transfer(clsBankClient FromClient, clsBankClient ToClient) {
        double Amount = 0;
        char Answer = 'n';
        cout << "\nEnter Transfer Amount?";
        cin >> Amount;
         while(!FromClient.checkAmount(Amount)) {
             cout << "Amount Exceeds the available Balance, Enter another Amount ? ";
             cin >> Amount;
        }
         cout << "\nAre you shore You want to perform this Operation? (Y/N)? ";
         cin >> Answer;

         if (Answer == 'Y' || Answer == 'y') {

             if (FromClient.Withdraw(Amount))
             {
                 ToClient.Deposit(Amount);
               
                 return true;
             }
             else
             {
                 return false;
             }
         }            
    }
     */

public:
	static void ShowTransferScreen() {
        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);


        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Failed \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);

	/*	_DrawScreenHeader("\t  Transfer Screen");
		string From = "";
		string To = "";
		cout << "\nPlease Enter the Number to Transfer From: ";
		cin >> From;
        while (!clsBankClient::IsClientExist(From))
        {
            cout << "\nInvalid Account Number, Please Enter a valid Number: ";
            cin >> From;

        }
            clsBankClient FromClient = clsBankClient::Find(From);
            _PrintClient(FromClient);
		

        cout << "\nPlease Enter the Number to Transfer To: ";
        cin >> To;
        while (!clsBankClient::IsClientExist(To))
        {
            cout << "\nInvalid Account Number, Please Enter a valid Number: ";
            cin >> To;
        }

        clsBankClient ToClient = clsBankClient::Find(To);
        _PrintClient(ToClient);

        if (_Transfer(FromClient, ToClient)) {
            cout << "\n transfer Done Successfully\n";
            clsBankClient FromClient = clsBankClient::Find(From);
            clsBankClient ToClient = clsBankClient::Find(To);

            _PrintClient(FromClient);
            _PrintClient(ToClient);
        }
        else
        {
            cout << "\n something Wrong!";

        }*/
	}
};

