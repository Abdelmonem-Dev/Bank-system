#pragma once
#include "clsScreen.h"
#include "Global.h"
#include "clsUser.h"
#include "iomanip"
class clsListLoginRegisterScreen :protected clsScreen
{

private:



    static void _PrintUserRecordLine(clsUser::sRegisterLogIn sRegisterLogin)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << sRegisterLogin.DateTime;
        cout << "| " << setw(20) << left << sRegisterLogin.UserName;
        cout << "| " << setw(20) << left << sRegisterLogin.Password;
        cout << "| " << setw(10) << left << sRegisterLogin.Permissions;

    }

public:

    static void ShowLgoInRegisterList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pListLoginRegister))
        {
            return;// this will exit the function and it will not continue
        }
        vector <clsUser::sRegisterLogIn> vRegisterLogin = clsUser::GetRegisterLogInList();

        string Title = "\t Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vRegisterLogin.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vRegisterLogin.size() == 0)
            cout << "\t\t\t\tNo Record Available In the System!";
        else

            for (clsUser::sRegisterLogIn& R : vRegisterLogin)
            {

                _PrintUserRecordLine(R);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};

