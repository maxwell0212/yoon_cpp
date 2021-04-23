/*
 * Banking System Ver 0.1
 * �ۼ���: ������
 * ��  ��: OOP �ܰ躰 ������Ʈ�� �⺻ Ʋ ����
 */

#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN=20;

void ShowMenu(void);       // �޴����
void MakeAccount(void);    // ���°����� ���� �Լ�
void DepositMoney(void);       // ��    ��
void WithdrawMoney(void);      // ��    ��
void ShowAllAccInfo(void);     // �ܾ���ȸ

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

class Account
{
private:
	int accID;      // ���¹�ȣ
	int balance;    // ��    ��
	char * cusName;   // ���̸�

public:
    Account(int accid, int bal, char * name)
    {
        this->accID = accid;
        this->balance = bal;
        cusName = new char[strlen(name)+1];
        strcpy(cusName, name);
    }
    // Ver0.3 ��������� �߰�.
    Account(const Account& copy): accID(copy.accID), balance(copy.balance)
    {
        cusName = new char[strlen(copy.cusName)+1];
        strcpy(cusName, copy.cusName);
    }
    ~Account()
    {
        cout << "~Account()....." << endl;
        delete [] cusName;
    }
    int GetAccID() const
    {
        return this->accID;
    }
    void SetAccID(int id)
    {
        this->accID = id;
    }
    int GetBalance() const
    {
        return this->balance;
    }
    void SetBalance(int bal)
    {
        this->balance = bal;
    }
    char * GetName() const
    {
        return cusName;
    }
    void ShowAccountInfo() const
    {
        cout << "�� ��ȣ :" << GetAccID() << endl;
        cout << "���� �ܾ� :" << GetBalance() << endl;
        cout << "�� ���� :" << GetName() << endl << endl;
    }
};

class AccountHandler
{
private:
    Account * accArr[100];   // Account ������ ���� �迭
    int accNum=0;        // ����� Account ��
public:
    AccountHandler();
    void ShowMenu() const;
    void MakeAccount();
    void DepositMoney();
    void WithdrawMoney();
    void ShowAllAccInfo() const;
    ~AccountHandler();
};

AccountHandler::AccountHandler(): accNum(0)
{

}
void AccountHandler::ShowMenu(void) const
{
	cout<<"-----Menu------"<<endl;
	cout<<"1. ���°���"<<endl;
	cout<<"2. ��    ��"<<endl;
	cout<<"3. ��    ��"<<endl;
	cout<<"4. �������� ��ü ���"<<endl;
	cout<<"5. ���α׷� ����"<<endl;
}

void AccountHandler::MakeAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout<<"[���°���]"<<endl;
	cout<<"����ID: ";	cin>>id;
	cout<<"��  ��: ";	cin>>name;
	cout<<"�Աݾ�: ";	cin>>balance;
	cout<<endl;

	//accArr[accNum].accID=id;
	//accArr[accNum].balance=balance;
	//strcpy(accArr[accNum].cusName, name);
	accArr[accNum] = new Account(id, balance, name);
	accNum++;
}

void AccountHandler::DepositMoney(void)
{
	int money;
	int id;
	cout<<"[��    ��]"<<endl;
	cout<<"����ID: ";	cin>>id;
	cout<<"�Աݾ�: ";	cin>>money;

	for(int i=0; i<accNum; i++)
	{
		//if(accArr[i].accID==id)
		if( accArr[i]->GetAccID() == id )
		{
			//accArr[i].balance+=money;
			accArr[i]->SetBalance( accArr[i]->GetBalance()+money );
			cout<<"�ԱݿϷ�"<<endl<<endl;
			return;
		}
	}
	cout<<"��ȿ���� ���� ID �Դϴ�."<<endl<<endl;
}

void AccountHandler::WithdrawMoney(void)
{
	int money;
	int id;
	cout<<"[��    ��]"<<endl;
	cout<<"����ID: ";	cin>>id;
	cout<<"��ݾ�: ";	cin>>money;

	for(int i=0; i<accNum; i++)
	{
		//if(accArr[i].accID==id)
		if( accArr[i]->GetAccID() == id )
		{
			//if(accArr[i].balance<money)
			if( accArr[i]->GetBalance() < money )
			{
				cout<<"�ܾ׺���"<<endl<<endl;
				return;
			}

			//accArr[i].balance-=money;
			accArr[i]->SetBalance( accArr[i]->GetBalance() - money );
			cout<<"��ݿϷ�"<<endl<<endl;
			return;
		}
	}
	cout<<"��ȿ���� ���� ID �Դϴ�."<<endl<<endl;
}

void AccountHandler::ShowAllAccInfo(void) const
{
	for(int i=0; i<accNum; i++)
	{
		//cout<<"����ID: "<<accArr[i]->GetAccID()<<endl;
		//cout<<"��  ��: "<<accArr[i]->GetName()<<endl;
		//cout<<"��  ��: "<<accArr[i]->GetBalance()<<endl<<endl;

		accArr[i]->ShowAccountInfo();
	}
}
AccountHandler::~AccountHandler()
{
    for(int i=0; i<accNum; i++)
        delete accArr[i];
}

int main(void)
{
	int choice;
    AccountHandler mgr;

	while(1)
	{
		mgr.ShowMenu();
		cout<<"����: ";
		cin>>choice;
		cout<<endl;

		switch(choice)
		{
		case MAKE:
			mgr.MakeAccount();
			break;
		case DEPOSIT:
			mgr.DepositMoney();
			break;
		case WITHDRAW:
			mgr.WithdrawMoney();
			break;
		case INQUIRE:
			mgr.ShowAllAccInfo();
			break;
		case EXIT:
			return 0;
		default:
			cout<<"Illegal selection.."<<endl;
		}
	}
	return 0;
}

