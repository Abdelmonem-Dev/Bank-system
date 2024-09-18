#pragma once
#include "clsPerson.h"
#include <fstream>
#include <vector>
#include "clsString.h"
#include "clsInputValidate.h"
class clsBankClient : public clsPerson
{
public:
    struct sTransferLog
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double SourceAccountBalanceAfter;
        double DestinationAccountBalanceAfter;
        string UserName;

    };
private:
	enum enMode { EmptyMode = 0 , UpdateMode = 1, AddNewMode = 2};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
    bool _MarkedForDelete = false;

   
    static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#") {
        vector<string> vClientData;
        vClientData = clsString::Split(Line,Separator);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}
    static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Separator;
        stClientRecord += Client.LastName + Separator;
        stClientRecord += Client.Email + Separator;
        stClientRecord += Client.Phone + Separator;
        stClientRecord += Client.AccountNumber() + Separator;
        stClientRecord += Client.PinCode + Separator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    string _PrepareTransferRecord(sTransferLog T, string Separator = "#//#")
    {
        string TransferRecord = "";
        TransferRecord += clsDate::GetSystemDateTimeString() + Separator;
        TransferRecord += T.SourceAccountNumber + Separator;
        TransferRecord += T.DestinationAccountNumber + Separator;
        TransferRecord += to_string(T.Amount) + Separator;
        TransferRecord += to_string(T.SourceAccountBalanceAfter) + Separator;
        TransferRecord += to_string(T.DestinationAccountBalanceAfter) + Separator;
        TransferRecord += T.UserName + Separator;

        return TransferRecord;
    }
    static sTransferLog _ConvertLineToTransferLog(string Line, string Separator = "#//#")
    {
        vector<string> _vData = clsString::Split(Line, Separator);

        sTransferLog T;
        T.DateTime = _vData[0];
        T.SourceAccountNumber = _vData[1];
        T.DestinationAccountNumber = _vData[2];
        T.Amount = stod(_vData[3]);
        T.SourceAccountBalanceAfter = stod(_vData[4]);
        T.DestinationAccountBalanceAfter = stod(_vData[5]);
        T.UserName = _vData[6];

        return  T;
    }

    static  vector <sTransferLog> _LoadTransferLogDataFromFile()
    {

        vector <sTransferLog> _vTransferLogData;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                sTransferLog sTransferLogData = _ConvertLineToTransferLog(Line);

                _vTransferLogData.push_back(sTransferLogData);
            }

            MyFile.close();

        }

        return _vTransferLogData;

    }


	static clsBankClient _GetEmptyClientObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}

    static vector<clsBankClient> _ReadClientsFromFile(string FileName = "Clients.txt") {
        vector<clsBankClient> vClients;
        fstream File;
        string Line = "";
        File.open(FileName, ios::in);
        if (File.is_open())
        {
            while (getline(File, Line))
            {

                clsBankClient Client = _ConvertLineToClientObject(Line);

                vClients.push_back(Client);
            }

            File.close();

        }

        return vClients;

    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients, string FileName = "Clients.txt")
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C._MarkedForDelete == false)
                {
                    DataLine = _ConvertClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();

        }
    }

    void _AddDataLineToFile(string  stDataLine, string FileName = "Clients.txt")
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _ReadClientsFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveClientsDataToFile(_vClients);

    }

    void _AddNew() {

        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
        string AccountNumber, string PinCode, float AccountBalance)
        :clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool isEmpty() {
        return (_Mode == enMode::EmptyMode);
    }
    string AccountNumber()
    {
        return _AccountNumber;
    }

    void Deposit(double Amount) {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }

    }
    bool checkAmount(double Amount) {
        if (_AccountBalance >= Amount)
        {
            return true;
        }
        return false;
    }

    bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
    {
        sTransferLog T;
       
        if (Amount > _AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);

        T.SourceAccountNumber = AccountNumber();
        T.DestinationAccountNumber = DestinationClient.AccountNumber();
        T.Amount = Amount;
        T.SourceAccountBalanceAfter = _AccountBalance;
        T.DestinationAccountBalanceAfter = DestinationClient.AccountBalance;
        T.UserName = UserName;
        TransferLog(T);
        return true;
    }


    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    void SetMarkedForDelete(bool MarkedForDelete) {
        _MarkedForDelete = MarkedForDelete;
    }
    bool GetMarkedForDelete()
    {
        return _MarkedForDelete;
    }
    __declspec(property(get = GetMarkedForDelete, put = SetMarkedForDelete)) bool MarkedForDelete;

    static clsBankClient Find(string AccountNumber) {
        vector<clsBankClient> vClient;
        vClient = _ReadClientsFromFile();
        for (clsBankClient& C : vClient)
        {
            if (C.AccountNumber() == AccountNumber)
            {
                return C;
            }
        }
        return _GetEmptyClientObject();
    }
    static clsBankClient Find(string AccountNumber, string PinCode) {
        vector<clsBankClient> vClient;
        vClient = _ReadClientsFromFile();
        for (clsBankClient& C : vClient)
        {
            if (C.AccountNumber() == AccountNumber && C.PinCode == PinCode)
            {
                return C;
            }
        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, 
        svFaildAccountNumberExists = 2};

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }
        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
      }
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _ReadClientsFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveClientsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsBankClient CreateNewClient(string AccountNumber) {
        return clsBankClient(enMode::AddNewMode,"","","","", AccountNumber, "", 0);
    }

    static bool IsClientExist(string AccountNumber) {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.isEmpty());
    }

    static vector<clsBankClient> GetClientsList() {
        return  _ReadClientsFromFile();
    }

    static double TotalBalances() {
        vector <clsBankClient> _vClients;
        _vClients = _ReadClientsFromFile();
        double TotalBalances = 0;
        for (clsBankClient C : _vClients)
        {
            TotalBalances += C.AccountBalance;
        }
        return TotalBalances;
    }

    void TransferLog(sTransferLog T)
    {

        string stDataLine = _PrepareTransferRecord(T);
      

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    static vector <sTransferLog> GetTransferLogList()
    {
        return _LoadTransferLogDataFromFile();
    }
};
