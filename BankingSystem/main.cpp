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
    ~Account()
    {
        cout << "~Account()....." << endl;
        delete [] cusName;
    }
    int GetAccID()
    {
        return this->accID;
    }
    void SetAccID(int id)
    {
        this->accID = id;
    }
    int GetBalance()
    {
        return this->balance;
    }
    void SetBalance(int bal)
    {
        this->balance = bal;
    }
    char * GetName()
    {
        return cusName;
    }
    void ShowAccountInfo()
    {
        cout << "�� ��ȣ :" << GetAccID() << endl;
        cout << "���� �ܾ� :" << GetBalance() << endl;
        cout << "�� ���� :" << GetName() << endl << endl;
    }
};

Account * accArr[100];   // Account ������ ���� �迭
int accNum=0;        // ����� Account ��

int main(void)
{
	int choice;

	while(1)
	{
		ShowMenu();
		cout<<"����: ";
		cin>>choice;
		cout<<endl;

		switch(choice)
		{
		case MAKE:
			MakeAccount();
			break;
		case DEPOSIT:
			DepositMoney();
			break;
		case WITHDRAW:
			WithdrawMoney();
			break;
		case INQUIRE:
			ShowAllAccInfo();
			break;
		case EXIT:
		    for(int i=0; i<accNum; i++)
                delete accArr[i];
			return 0;
		default:
			cout<<"Illegal selection.."<<endl;
		}
	}
	return 0;
}

void ShowMenu(void)
{
	cout<<"-----Menu------"<<endl;
	cout<<"1. ���°���"<<endl;
	cout<<"2. ��    ��"<<endl;
	cout<<"3. ��    ��"<<endl;
	cout<<"4. �������� ��ü ���"<<endl;
	cout<<"5. ���α׷� ����"<<endl;
}

void MakeAccount(void)
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

void DepositMoney(void)
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

void WithdrawMoney(void)
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

void ShowAllAccInfo(void)
{
	for(int i=0; i<accNum; i++)
	{
		//cout<<"����ID: "<<accArr[i]->GetAccID()<<endl;
		//cout<<"��  ��: "<<accArr[i]->GetName()<<endl;
		//cout<<"��  ��: "<<accArr[i]->GetBalance()<<endl<<endl;

		accArr[i]->ShowAccountInfo();
	}
}
