#include<iostream>
#include<cmath>
using namespace std;

//Savings Account类的定义
class SavingsAccount {
private:
	int id;//账号
	double balance;//余额
	double rate;//存款的年利率
	int lastDate;//上次变更余额的时期
	double accumulation;//余额按日累加之和
	void record(int date, double amount);//记录一笔账，date为日期，amount为金额，取钱和存钱都是要调用这个函数
	//来改变余额，利息增长也用这个来记录并输出。
	double accumulate(int date) const {//获得到指定日期为止的存款金额按日期积累的总和
		return accumulation + balance * (date - static_cast<unsigned __int64>(lastDate));//这里直接余额乘以日期是因为
		//在settle函数里面计算年利息时直接除以365，这样这里的意思就变成一年中的比例了。
	}
public:
	SavingsAccount(int date, int id, double rate);//构造函数
	int getId() { return id; }//获得用户的id
	double getBalance() { return balance; }//获得账户余额
	double getRate() { return rate; }//计算年利率
	void show();//显示账户信息
	void deposit(int date, double amount);//存入现金
	void withdraw(int date, double amount);//取出现金
	void settle(int date);//计算利息，每年1月1日调用一次
};

//类成员函数的实现
SavingsAccount::SavingsAccount(int date, int id, double rate)
	:id(id), balance(0), rate(rate), lastDate(date), accumulation(0) {
	cout << date << "\t# " << id << " is created" << endl;
}
void SavingsAccount::record(int date, double amount) {
	accumulation = accumulate(date);
	lastDate = date;
	amount = floor(amount * 100 + 0.5) / 100;//保留小数点后两位，4舍5入
	balance += amount;
	cout << date << "\t# " << id << "\t" << amount << "\t" << balance << endl;
}
void SavingsAccount::deposit(int date, double amount) {
	record(date, amount);
}
void SavingsAccount::withdraw(int date, double amount) {
	if (amount > getBalance()) {
		cout << "Error: not enough money" << endl;
	}
	else
		record(date, -amount);
}
void SavingsAccount::settle(int date) {
	double interest = accumulate(date) * rate / 365;//计算年利率
	if (interest != 0) {
		record(date, interest);
	}
	accumulation = 0;
}
void SavingsAccount::show() {
	cout << "# " << id << "\tBalance: " << balance;
}

int main() {
	//建立几个账户
	SavingsAccount sa0(1, 21325302, 0.015);
	SavingsAccount sa1(1, 58320212, 0.015);
	//几笔账目
	sa0.deposit(5, 5000);
	sa1.deposit(25, 10000);
	sa0.deposit(45, 5500);
	sa1.withdraw(60, 4000);
	//开户90天计算年息
	sa0.settle(90);
	sa1.settle(90);
	//输出各账户信息
	sa0.show(); cout << endl;
	sa1.show(); cout << endl;

	return 0;
}