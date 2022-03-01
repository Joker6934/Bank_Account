#pragma once
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include"date.h"
#include<string>

//Savings Account��Ķ���
class SavingsAccount {
private:
	std::string id;//�˺�
	double balance;//���
	double rate;//����������
	Date lastDate;//�ϴα������ʱ��
	double accumulation;//�����ۼ�֮��
	static double total;//�����˻����ܽ��
	void record(const Date& date, double amount, const std::string& desc);//��¼һ���ˣ�dateΪ���ڣ�amountΪ��ȡǮ�ʹ�Ǯ����Ҫ�����������
	//���ı�����Ϣ����Ҳ���������¼�������
	void error(const std::string& msg)const;
	double accumulate(const Date& date) const {//��õ�ָ������Ϊֹ�Ĵ������ڻ��۵��ܺ͡�����������Ա����
		return accumulation + balance * date.distance(lastDate);//����ֱ����������������Ϊ
		//��settle���������������Ϣʱֱ�ӳ���365�������������˼�ͱ��һ���еı����ˡ�
	}
public:
	SavingsAccount(const Date& date, const std::string& id, double rate);//���캯��
	const std::string& getId() const { return id; }//����û���id
	double getBalance() const { return balance; }//����˻����
	double getRate() const { return rate; }//����������
	static double getTotal() { return total; }//�����ܹ��Ľ��
	void show() const;//��ʾ�˻���Ϣ
	void deposit(const Date& date, double amount, const std::string& desc);//�����ֽ�
	void withdraw(const Date& date, double amount, const std::string& desc);//ȡ���ֽ�
	void settle(const Date& date);//������Ϣ��ÿ��1��1�յ���һ��
};


#endif