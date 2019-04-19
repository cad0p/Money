// ConsoleApplication1.cpp: definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"


static const int N_b = 100; //Number of buyers
static const int N_s = 10;  // Number of sellers
static const int N_t = 5000;  // Number of transactions a day
static const int DAYS = INFINITY; // Number of days
static const int BUFFER = 80; // Buffer for every transaction
static const int from = 0;
static const int to = 10;

static const double FIXED = 0.1;    // Fixed cost in real money per transaction
static const double VARIABLE = 0.02; // Variable cost of transaction (in percentage)

string random_expire()
{
	return to_string((rand() % 12) + 1) + '/' + to_string((rand() % (100 - 18)) + 18);
}

string random_cc()
{
	string s;
	for (int i = 0; i < 16; i++)
	{
		if (i % 4 == 0 && i != 0) s += ' ';
		s += rand() % 9 + '0';
	}
	return s;
}

string random_name(int len = rand() % 3 + 3)
{
	if (len == 0) return "";
	char c = rand() % 26 + 'a';
	return c + random_name(len - 1);
}

#include "Item.h"

bool criteria_b(Buyer* first, Buyer* second)
{
	return first->get_cc().get_out() > second->get_cc().get_out();
}

bool criteria_s(Seller* first, Seller* second)
{
	return first->get_cc().get_in() > second->get_cc().get_in();
}

int main()
{
	int i;

	Bank bleech;
	
	Buyer*buyers = new Buyer[N_b];
/*	cout << "Buyers:" << endl;
	for (i = 0; i < N_b; i++)
	{
		cout << buyers[i];
	}*/
	Seller*sellers = new Seller[N_s];
/*	cout << "Sellers:" << endl;
	for (i = 0; i < N_s; i++)
	{
		cout << sellers[i];
	}*/
	vTransaction* vtransactions = new vTransaction[N_t];
	Transaction* transactions = new Transaction[N_t];
	// Now let's try doing transactions and checking the balance
	double amount, total_amount = 0, total_real_amount = 0;
	int ID = 0, real_ID = 0;
	list<Buyer*>ready_b; list<Seller*>ready_s;
	while (total_amount <= 10000)
	{
		amount = (rand() % ((to - from)*100)  + from * 100) / 100.0;
		int b = rand() % N_b, s = rand() % N_s;
		//Transaction t(bleech, amount, buyers[b], sellers[s]); // traditional model
		//transactions[ID] = t;
		vTransaction vt(bleech, amount, buyers[b], sellers[s]);
		vtransactions[vt.get_id()] = vt;
		total_amount += amount;
		//cout << "Virtual t" << vt;
		//cout << "Buyer" << b << "out" << buyers[b].get_cc().get_out() << endl;
		//cout << "Seller" << s << "in" << sellers[s].get_cc().get_in() << endl;
		if (!buyers[b].is_inlist() && buyers[b].get_cc().get_out() >= BUFFER)
		{ // add it!
			ready_b.push_back(&buyers[b]);
			buyers[b].set_inlist(true);
		}
		if (!sellers[s].is_inlist() && sellers[s].get_cc().get_in() >= BUFFER)
		{
			ready_s.push_back(&sellers[s]);
			sellers[s].set_inlist(true);
		}
		ready_b.sort(criteria_b); ready_s.sort(criteria_s);

		if (ready_s.size() > 0 && ready_b.size() > 0)
		{
			amount = min<double>(ready_b.front()->get_cc().get_out(),
				ready_s.front()->get_cc().get_in());
			Transaction t(bleech, amount, *ready_b.front(), *ready_s.front());
			transactions[t.get_id()] = t;
			real_ID++;
			//cout << "Transaction made" << endl;
			total_real_amount += amount;
			if (ready_b.front()->get_cc().get_out() < BUFFER || ready_b.front()->get_cc().get_out() == 0)
			{ // if buffer == 0, item doesn't get removed
				ready_b.front()->set_inlist(false);
				ready_b.pop_front();
			}
			if (ready_s.front()->get_cc().get_in() < BUFFER || ready_s.front()->get_cc().get_in() == 0)
			{
				ready_s.front()->set_inlist(false);
				ready_s.pop_front();
			}
		}
		ID++;
	}
	/*
	double rem_s_in = 0, rem_b_out = 0; // remaining
	cout << "Sellers waiting income" << endl;
	for (int s = 0; s < N_s; s++)
	{
		cout << sellers[s].get_cc().get_in() << endl; rem_s_in += sellers[s].get_cc().get_in();
	}
	cout << "Buyers waiting outcome" << endl;
	for (int b = 0; b < N_b; b++)
	{
		cout << buyers[b].get_cc().get_out() << endl; rem_b_out += buyers[b].get_cc().get_out();
	}
	cout << rem_b_out << rem_s_in << endl;
	*/
	/*
	// optional: finish with the last cents (could be a big percentage if BUFFER too big!)
	for (int b = 0; b < N_b; b++)
	{ // add all the buyers not yet done to list
		if (!buyers[b].is_inlist() && buyers[b].get_cc().get_out() > 0)
		{
			ready_b.push_back(&buyers[b]);
			buyers[b].set_inlist(true);
		}
	}
	ready_b.sort(criteria_b); ready_s.sort(criteria_s);
	//while (total_amount - total_real_amount > 0.1)
	while(ready_s.size() > 0 && ready_b.size() > 0)
	{
		amount = min<double>(ready_b.front()->get_cc().get_out(),
			ready_s.front()->get_cc().get_in());
		Transaction t(bleech, amount, *ready_b.front(), *ready_s.front());
		transactions[t.get_id()] = t;
		cout << t;
		real_ID++;
		//cout << "Transaction made" << endl;
		total_real_amount += amount;
		if (ready_b.front()->get_cc().get_out() == 0)
		{
			ready_b.front()->set_inlist(false);
			ready_b.pop_front();
		}
		if (ready_s.front()->get_cc().get_in() == 0)
		{
			ready_s.front()->set_inlist(false);
			ready_s.pop_front();
		}
		ready_b.sort(criteria_b); ready_s.sort(criteria_s);
	}*/
	cout << "vTransactions: " << ID << endl;
	cout << "Transactions: " << real_ID << endl;
	cout << "Total amount: " << total_amount << endl;
	cout << "Total real amount" << total_real_amount << endl;
	cout << "Advantage over system" << (1 - real_ID / (ID * 1.0))*100 << '%' <<  endl;
	cout << "Bank balance: " << bleech.get_balance() << endl;
	cout << "Interest rate: " << bleech.get_balance() / total_real_amount << endl;
	double max_spent = 0, spent;
	int max_spent_i = -1;
	for (i = 0; i < N_b; i++)
	{
		spent = 10000 - buyers[i].get_cc().credit_b(); // money spent
		if (spent > max_spent) { max_spent = spent; max_spent_i = i; }
	}
	cout << "max spent" << max_spent;

}

