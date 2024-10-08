#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionMenuScreen :protected clsScreen
{

private:

    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3,eShowTransfer = 4,eShowTransferLog = 5, eShowMainMenue = 6
    };

    static short _ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }
    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }
    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen() {
        clsTransferLogScreen::ShowTransferLogScreen();
    }
    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();

    }

    static void _PerformTransactionsMenuOption(enTransactionsMenueOptions Option) {
        switch (Option)
        {
        case enTransactionsMenueOptions::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenueOptions::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenueOptions::eShowTotalBalance:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenueOptions::eShowTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenueOptions::eShowTransferLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenueOptions::eShowMainMenue:

        default:
            break;
        }
    }

public:

    static void ShowTransactionsMenu()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenuOption((enTransactionsMenueOptions)_ReadTransactionsMenuOption());
    }

};


