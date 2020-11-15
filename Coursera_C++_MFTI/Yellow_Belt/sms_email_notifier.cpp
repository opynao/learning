#include <string>
#include <iostream>


using Message_t = std::string;
using TelephoneNumber_t = std::string;
using Email_t = std::string;

/*
void SendSms(const TelephoneNumber_t& telephoneNumber, const Message_t& message)
{
	std::cout << "Send '" << message << "' to number " << telephoneNumber << std::endl;
}

void SendEmail(const Email_t& email, const Message_t& message)
{
	std::cout << "Send '" << message << "' to e-mail " << email << std::endl;
}
*/
class INotifier
{
public:
	virtual void Notify(const Message_t&) = 0;
};

/*
void Notify(INotifier& notifier, const Message_t& message) 
{
	notifier.Notify(message);
}
*/

class SmsNotifier : public INotifier
{
public:
	SmsNotifier(const TelephoneNumber_t&);
	virtual ~SmsNotifier();
	void Notify(const Message_t&) override;
private: 
	const TelephoneNumber_t telephoneNumber_;
};

SmsNotifier::SmsNotifier(const TelephoneNumber_t& telephoneNumber)
	: telephoneNumber_ (telephoneNumber)
{
}

SmsNotifier::~SmsNotifier()
{
}

void SmsNotifier::Notify(const Message_t& message) 
{
	SendSms(telephoneNumber_, message);
}

class EmailNotifier : public INotifier
{
public:
	EmailNotifier(const Email_t&);
	virtual ~EmailNotifier();
	void Notify(const Message_t&) override;
private:
	const Email_t email_;
};

EmailNotifier::EmailNotifier(const Email_t& email)
	: email_ (email)
{
}

EmailNotifier::~EmailNotifier()
{
}
 
void EmailNotifier::Notify(const Message_t& message)
{
	SendEmail(email_, message);
}

int main() 
{
  SmsNotifier sms{"+7-495-777-77-77"};
  EmailNotifier email{"na-derevnyu@dedushke.ru"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}
