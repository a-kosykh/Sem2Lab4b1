#include <iostream>
#include <string>
#include <thread>
#include <mutex>
using namespace std;
mutex m;

class Worker {
protected:
	string name_;
	string sur_;
	unsigned int year_;
public:
	Worker(string n, string s, unsigned int year);
	virtual void print() = 0;
	~Worker() {}
};

Worker::Worker(string n, string s, unsigned int year)

{
	this->name_ = n;
	this->sur_ = s;
	this->year_ = year;
}

class Salary : public Worker {
protected:
	double monthSalary_;
	double daySalary_;
public:
	Salary(string n,
		string s,
		unsigned int year,
		double monthSalary_);
	void print();
};

Salary::Salary(string n, string s, unsigned int year, double monthSalary_)
	:
	Worker(n, s, year)
{
	this->monthSalary_ = monthSalary_;
	daySalary_ = monthSalary_ / 30;
}

void Salary::print()
{
	cout << name_ << endl;
	cout << sur_ << endl;
	cout << year_ << endl;
	cout << monthSalary_ << endl;
	cout << daySalary_ << endl;
	cout << endl;
}
Worker *pF[2];
void threadfoo(unsigned int n) {
	m.lock();
	pF[n]->print();
	m.unlock();
	
}



int main() {
	pF[0] = new Salary("Alex", "Kosykh", 1999, 100000);
	pF[1] = new Salary("domi", "asdas", 1998, 100022);
	thread th[2];
	
	th[0] = thread(threadfoo, 0);
	th[1] = thread(threadfoo, 1);
	
	th[0].join();
	th[1].join();


	system("pause");
	return 0;
}