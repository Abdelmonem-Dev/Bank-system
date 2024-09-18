#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsWithdrawScreen :protected clsScreen
{
    private:

        static void _PrintClient(clsBankClient Client)
        {
            cout << "\nClient Card:";
            cout << "\n___________________";
            cout << "\nFirstName   : " << Client.FirstName;
            cout << "\nLastName    : " << Client.LastName;
            cout << "\nFull Name   : " << Client.FullName();
            cout << "\nEmail       : " << Client.Email;
            cout << "\nPhone       : " << Client.Phone;
            cout << "\nAcc. Number : " << Client.AccountNumber();
            cout << "\nPassword    : " << Client.PinCode;
            cout << "\nBalance     : " << Client.AccountBalance;
            cout << "\n___________________\n";

        }

    public:

        static void ShowWithdrawScreen() {
            string Title = "\t Withdraw Screen";

            clsScreen::_DrawScreenHeader(Title);
            cout << "Enter the Account Number: ";
            string AccountNumber = clsInputValidate::ReadString();
            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "Account Number not Exists: ";
                AccountNumber = clsInputValidate::ReadString();
            }
            clsBankClient Client = clsBankClient::Find(AccountNumber);
            if (!Client.isEmpty())
            {
                cout << "\nClient Found :-)\n";
            }
            else
            {
                cout << "\nClient Was not Found :-(\n";
            }

            _PrintClient(Client);

            double Amount = 0;
            cout << "\n please enter Withdraw amount? ";
            Amount = clsInputValidate::ReadDblNumber();

            cout << "are you shore you want to perform this transaction? (Y/N) ? ";
            char Answer = 'n';
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y')
            {
                if (Client.Withdraw(Amount))
                {
                    cout << "\nAmount Withdrew Successfully.\n";
                    cout << "\nNew Balance Is: " << Client.AccountBalance;
                }
                else
                {
                    cout << "\nCannot withdraw, Insufficient Balance!\n";
                    cout << "\nAmout to withdraw is: " << Amount;
                    cout << "\nYour Balance is: " << Client.AccountBalance;

                }
            }
            else
            {
                cout << "\nOperation was cancelled.\n";
            }

        }







};

