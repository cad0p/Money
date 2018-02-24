#pragma once
#ifndef ITEMS_H
#define ITEMS_H

template<typename T>
class Counter { // copied by http://www.drdobbs.com/cpp/counting-objects-in-c/184403484
public:
	Counter() { ++count; }
	Counter(const Counter&) { ++count; }
	~Counter() { --count; }

	static size_t howMany()
	{
		return count;
	}

private:
	static size_t count;
};

template<typename T>
size_t
Counter<T>::count = -1; // this now can go in header

class Bank
{
private:
	double balance;
public:
	Bank(double b = 0) { balance = b; }
	double get_balance() { return balance; }
	double grow_balance(double amount) { balance += amount; return balance; }
};

class CreditCard
{
private:
	string n;
	string exp;
	double b, in, out;
public:
	CreditCard(string number = random_cc(),
		string expire_date = random_expire(),
		double balance = 10000)
	{
		n = number; exp = expire_date;
		b = balance; in = out = 0;
	}
	string get_n() { return n; }
	string get_exp() { return exp; }
	double get_in() { return in; }
	double get_out() { return out; }
	void lower_in(int times = 1) { in -= BUFFER * times; }
	void lower_out(int times = 1) { out -= BUFFER * times; }
	double draw_b(double money = 0) { b -= money; out -= money; return b; } // reduce BUFFER
	double credit_b(double money = 0, double commissions = 0) 
	{ b += money - commissions; in -= money; return b; } // reduce BUFFER, t is made
	double vdraw_b(double money = 0) { out += money; return b; }
	double vcredit_b(double money = 0) { in += money; return b; }
};


class Buyer
{
private:
	int ID;
	CreditCard c;
	Counter<Buyer> counter;
	bool inlist;
public:
	Buyer() { ID = Counter<Buyer>::howMany(); inlist = false; }
	int get_id() { return ID; }
	void set_inlist(bool bo) { inlist = bo; }
	bool is_inlist() { return inlist; }
	CreditCard& get_cc() { return c; }
};
// used to order the priority list to pay
bool operator<(Buyer b1, Buyer b2) { return b1.get_cc().get_out() > b2.get_cc().get_out(); }
ostream& operator<<(ostream& os, Buyer b) { return os << b.get_id() << endl; }

class Seller
{
private:
	int ID;
	CreditCard c;
	Counter<Seller> counter;
	bool inlist;
public:
	Seller() { ID = Counter<Seller>::howMany(); inlist = false; }
	int get_id() { return ID; }
	void set_inlist(bool bo) { inlist = bo; }
	bool is_inlist() { return inlist; }
	CreditCard& get_cc() { return c; }
};
// used to order the priority list to be payed
bool operator<(Seller s1, Seller s2) { return s1.get_cc().get_in() > s2.get_cc().get_in();
}
ostream& operator<<(ostream& os, Seller b) { return os << b.get_id() << endl; }

template<typename T>
size_t count_ = 0;
class Transaction
{
private:
	int ID, b_ID, s_ID;
	double am, commissions;
public:
	Transaction() {}
	Transaction(Bank &bank, double amount, Buyer &buyer, Seller &seller)
	{
		ID = count_<Transaction>++;
		am = amount;
		Buyer& b = buyer; Seller& s = seller;
		b_ID = b.get_id(); s_ID = s.get_id();
		b.get_cc().draw_b(am);
		commissions = FIXED + am * VARIABLE;
		bank.grow_balance(commissions);
		s.get_cc().credit_b(am, commissions);
	}
	int get_id() { return ID; }
	int get_b_id() { return b_ID; }
	int get_s_id() { return s_ID; }
	double get_am() { return am; }
};
ostream& operator<<(ostream& os, Transaction t)
{
	return os << "ID:" << t.get_id() << "Amount:" << t.get_am()
		<< "b_ID:" << t.get_b_id() << "s_ID:" << t.get_s_id() << endl;
}

class vTransaction
{ // virtual Transaction
private:
	int ID, b_ID, s_ID;
	double am, commissions;
public:
	vTransaction() {}
	vTransaction(Bank &bank, double amount, Buyer &buyer, Seller &seller)
	{
		ID = count_<vTransaction>++;
		am = amount;
		Buyer& b = buyer; Seller& s = seller;
		b_ID = b.get_id(); s_ID = s.get_id();
		b.get_cc().vdraw_b(am);
		s.get_cc().vcredit_b(am);
	}
	int get_id() { return ID; }
	int get_b_id() { return b_ID; }
	int get_s_id() { return s_ID; }
	double get_am() { return am; }
};
ostream& operator<<(ostream& os, vTransaction t)
{
	return os << "ID:" << t.get_id() << "Amount:" << t.get_am() 
		<< "b_ID:" << t.get_b_id()  << "s_ID:" << t.get_s_id() << endl;
}

#endif // !ITEMS_H
