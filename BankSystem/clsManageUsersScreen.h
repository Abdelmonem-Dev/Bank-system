#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersScreen : protected clsScreen
{

private:

    enum enUsersMenuOption
    {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, GoToMainMenu = 6
    };
    static short _ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowListUsersScreen() {
        clsListUsersScreen::ShowUsersList();
    }
    static void _ShowAddNewUserScreen() {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    static void _ShowDeleteUserScreen() {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    static void _ShowUpdateUserScreen() {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }
    static void _ShowFindUserScreen() {
        clsFindUserScreen::ShowFindUserScreen();
    }
    static void _GoBackToMainMenuScreen() {
        cout << "\n\nPress any key to go back to Manage Users Menu...";
        system("pause>0");
        showUsersMenuScreen();
    }
    static void _PerformManageUsersMenuOption(enUsersMenuOption Option) {

        switch (Option)
        {
        case enUsersMenuOption::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToMainMenuScreen();
            break;
        case enUsersMenuOption::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToMainMenuScreen();
            break;
        case enUsersMenuOption::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToMainMenuScreen();
            break;
        case enUsersMenuOption::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToMainMenuScreen();
            break;
        case enUsersMenuOption::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToMainMenuScreen();
            break;
        case enUsersMenuOption::GoToMainMenu:

        {
        }
        }
    }

public:


    static void showUsersMenuScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";\

            _PerformManageUsersMenuOption((enUsersMenuOption)_ReadManageUsersMenuOption());
    }
};

