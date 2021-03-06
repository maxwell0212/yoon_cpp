/*
 * Banking System Ver 0.1
 * 작성자: 윤성우
 * 내  용: OOP 단계별 프로젝트의 기본 틀 구성
 */

#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN=20;

void ShowMenu(void);       // 메뉴출력
void MakeAccount(void);    // 계좌개설을 위한 함수
void DepositMoney(void);       // 입    금
void WithdrawMoney(void);      // 출    금
void ShowAllAccInfo(void);     // 잔액조회

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

class Account
{
private:
	int accID;      // 계좌번호
	int balance;    // 잔    액
	char * cusName;   // 고객이름

public:
    Account(int accid, int bal, char * name)
    {
        this->accID = accid;
        this->balance = bal;
        cusName = new char[strlen(name)+1];
        strcpy(cusName, name);
    }
    // Ver0.3 복사생성자 추가.
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
        cout << "고객 번호 :" << GetAccID() << endl;
        cout << "계좌 잔액 :" << GetBalance() << endl;
        cout << "고객 성명 :" << GetName() << endl << endl;
    }
};

class AccountHandler
{
private:
    Account * accArr[100];   // Account 저장을 위한 배열
    int accNum=0;        // 저장된 Account 수
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
	cout<<"1. 계좌개설"<<endl;
	cout<<"2. 입    금"<<endl;
	cout<<"3. 출    금"<<endl;
	cout<<"4. 계좌정보 전체 출력"<<endl;
	cout<<"5. 프로그램 종료"<<endl;
}

void AccountHandler::MakeAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;

	cout<<"[계좌개설]"<<endl;
	cout<<"계좌ID: ";	cin>>id;
	cout<<"이  름: ";	cin>>name;
	cout<<"입금액: ";	cin>>balance;
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
	cout<<"[입    금]"<<endl;
	cout<<"계좌ID: ";	cin>>id;
	cout<<"입금액: ";	cin>>money;

	for(int i=0; i<accNum; i++)
	{
		//if(accArr[i].accID==id)
		if( accArr[i]->GetAccID() == id )
		{
			//accArr[i].balance+=money;
			accArr[i]->SetBalance( accArr[i]->GetBalance()+money );
			cout<<"입금완료"<<endl<<endl;
			return;
		}
	}
	cout<<"유효하지 않은 ID 입니다."<<endl<<endl;
}

void AccountHandler::WithdrawMoney(void)
{
	int money;
	int id;
	cout<<"[출    금]"<<endl;
	cout<<"계좌ID: ";	cin>>id;
	cout<<"출금액: ";	cin>>money;

	for(int i=0; i<accNum; i++)
	{
		//if(accArr[i].accID==id)
		if( accArr[i]->GetAccID() == id )
		{
			//if(accArr[i].balance<money)
			if( accArr[i]->GetBalance() < money )
			{
				cout<<"잔액부족"<<endl<<endl;
				return;
			}

			//accArr[i].balance-=money;
			accArr[i]->SetBalance( accArr[i]->GetBalance() - money );
			cout<<"출금완료"<<endl<<endl;
			return;
		}
	}
	cout<<"유효하지 않은 ID 입니다."<<endl<<endl;
}

void AccountHandler::ShowAllAccInfo(void) const
{
	for(int i=0; i<accNum; i++)
	{
		//cout<<"계좌ID: "<<accArr[i]->GetAccID()<<endl;
		//cout<<"이  름: "<<accArr[i]->GetName()<<endl;
		//cout<<"잔  액: "<<accArr[i]->GetBalance()<<endl<<endl;

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
		cout<<"선택: ";
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

