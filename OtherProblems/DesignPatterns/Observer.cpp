#include <iterator>
#include <set>
#include <iostream>
#include <algorithm>
#include <vector>
#define LOGF std::cerr<<__FUNCTION__<<" " << this  << std::endl
class Subject;

class Observer
{
public:
	virtual void Update(Subject*) = 0;
};

class Subject
{
public:
	virtual void Attach(Observer*) = 0;
	virtual void Detach(Observer*) = 0;
	virtual void Notify() = 0;
};

class ConcreteSubject : public Subject
{
public:
	ConcreteSubject() { LOGF << "\b::CS CONSTRUCTED" << std::endl; };
	virtual ~ConcreteSubject() { LOGF << "\b::CS DESTRUCTED" << std::endl; }
public:	
	void Attach(Observer*) final;
	void Detach(Observer*) final;
	void Notify() final;
private:
	std::set<Observer*> m_Observers;
};

class ConcreteObserver : public Observer
{
public:
	ConcreteObserver() { LOGF << "\b::CO CONSTRUCTED" << std::endl; }
	virtual ~ConcreteObserver() { LOGF << "\b::CO CONSTRUCTED" << std::endl; }

public:
	void Update(Subject*) final;
};

void ConcreteSubject::Attach (Observer* obs)
{
	LOGF << "Observer: " << obs << std::endl;
	m_Observers.insert(obs);
}

void ConcreteSubject::Detach (Observer* obs)
{
	LOGF << "Observer: " << obs << std::endl;
	m_Observers.erase(obs);
}

void ConcreteSubject::Notify()
{
	LOGF;
	std::for_each(m_Observers.begin(),m_Observers.end(),[this](Observer* obs) {obs->Update(this);});
}

void ConcreteObserver::Update(Subject* sbj)
{
	LOGF << " Subject: " << sbj << std::endl;
}

int main()
{
	std::vector<Observer*> vObservers (5);
	std::generate(vObservers.begin(),vObservers.end(),[]()->Observer*{return new ConcreteObserver;});
	ConcreteSubject subject;
	std::for_each(vObservers.begin(),vObservers.end(),[&subject](Observer* obs){subject.Attach(obs);});
	subject.Notify();
	return 0;
}
