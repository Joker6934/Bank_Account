#pragma once
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include"date.h"
#include<string>

//Savings Account类的定义
class SavingsAccount {
private:
	std::string id;//账号
	double balance;//余额
	double rate;//存款的年利率
	Date lastDate;//上次变更余额的时期
	double accumulation;//余额按日累加之和
	static double total;//所有账户的总金额
	void record(const Date& date, double amount, const std::string& desc);//记录一笔账，date为日期，amount为金额，取钱和存钱都是要调用这个函数
	//来改变余额，利息增长也用这个来记录并输出。
	void error(const std::string& msg)const;
	double accumulate(const Date& date) const {//获得到指定日期为止的存款金额按日期积累的总和····常成员函数
		return accumulation + balance * date.distance(lastDate);//这里直接余额乘以日期是因为
		//在settle函数里面计算年利息时直接除以365，这样这里的意思就变成一年中的比例了。
	}
public:
	SavingsAccount(const Date& date, const std::string& id, double rate);//构造函数
	const std::string& getId() const { return id; }//获得用户的id
	double getBalance() const { return balance; }//获得账户余额
	double getRate() const { return rate; }//计算年利率
	static double getTotal() { return total; }//计算总共的金额
	void show() const;//显示账户信息
	void deposit(const Date& date, double amount, const std::string& desc);//存入现金
	void withdraw(const Date& date, double amount, const std::string& desc);//取出现金
	void settle(const Date& date);//计算利息，每年1月1日调用一次
};


#endif