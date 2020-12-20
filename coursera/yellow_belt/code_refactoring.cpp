#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using Name_t = std::string;
using Destination_t = std::string;
using FavouriteSong_t = std::string;
using Subject_t = std::string;
using Role_t = std::string;

class SongListener
{
public:
	SongListener( const FavoriteSong_t& song )
		: favoriteSong { song }
	{}
	}
private:
	const FavoriteSong_t favoriteSong;
};

class WalkingPerson
{
public:
	explicit WalkingPerson(const Name_t&, const Role_t& role);
	void Walk(const Destination_t&) const;
	Name_t GetName() const;
	Role_t GetRole() const;
private:
	const Name_t name_;
	const Role_t role_;
};

class Student : public WalkingPerson
	      , public SongListener 
{
public:
	explicit Student(const Name_t&, const FavouriteSong_t&);
	void Learn() const;
	void SingSong() const;
};

class Teacher : public WalkingPerson
{
public:
	explicit Teacher(const Name_t&, const Subject_t&);
	void Teach() const;
	Subject_t GetSubject() const;
private:
	Subject_t subject_;
};

class Policeman : public WalkingPerson
{
public:
	explicit Policeman(const Name_t&);
	void Check(const WalkingPerson&) const;
};

class Notifier
{
public:
	static void Walk(const Student&, const Destination_t&);
	static void Walk(const WalkingPerson&, const Destination_t&);
	static void Learn(const Student&);
	static void SingSong(const Name_t&. const Role_t&, const FavoriteSong_t&);
	static void Teach(const Teacher&);
	static void Check(const Policeman&, const WalkingPerson&);
};

WalkingPerson::WalkingPerson(const Name_t& name, const Role_t& role)
	: name_ {name}
	, role_{ role }
{
}

Name_t WalkingPerson::GetName() const
{
	return name_;
}

Role_t WalkingPerson::GetRole() const
{
	return role_;
}

void WalkingPerson::Walk( const Destination_t& rDestination) const
{
	Notifier::Walk(*this, rDestination);
}

Student::Student(const Name_t& name, const FavouriteSong_t& favouriteSong)
	: WalkingPerson(name, "Student")
	, SongListener (favouriteSong)
{
}

void Student::Learn() const 
{
	Notifier::Learn(*this);
}

void Student::SingSong() const
{
	Notifier::SingSong(name_, role_, favoriteSong_);
}


Teacher::Teacher(const Name_t& name, const Subject_t& subject)
	: WalkingPerson(name, "Teacher")
	, subject_ {subject}
{
}

Subject_t Teacher::GetSubject() const
{
	return subject_;
}

void Teacher::Teach() const
{
	Notifier::Teach(*this);
}

Policeman::Policeman(const Name_t& name)
	: WalkingPerson(name, "Policeman")
{
}

void Policeman::Check(const WalkingPerson& wp) const
{
	Notifier::Check(*this, wp);
}

void Notifier::Walk(const Student& s, const Destination_t& destination)
{
	Walk(static_cast<const WalkingPerson&>(s), destination);
	std::cout << s.GetRole() << ": " << s.GetName() << " sings a song: " << s.GetFavouriteSong() << std::endl;
}

void Notifier::Walk(const WalkingPerson& wp, const Destination_t& destination)
{
	std::cout << wp.GetRole() << ": " << wp.GetName() << " walks to: " << destination << std::endl;
}

void Notifier::Learn(const Student& s)
{
	std::cout << s.GetRole() << ": " << s.GetName() << " learns" << std::endl;
}

void Notifier::SingSong(const Name_t& name, const Role_t& role, const FavoriteSong& favoriteSong)
{
	std::cout << role << ": " << name << " sings a song: " << favoriteSong << std::endl;
}

void Notifier::Teach(const Teacher& t)
{
	std::cout << t.GetName() << " teaches: " << t.GetSubject() << std::endl;
}

void Notifier::Check(const Policeman& p, const WalkingPerson& wp)
{
	const auto& role = wp.GetRole();
	std::cout << p.GetRole() << ": " << p.GetName() << " checks " << role << ". " << role << "'s name is: " << wp.GetName() << std::endl;
}

void VisitPlaces(const WalkingPerson& p, const std::vector<std::string>& places) 
{
	std::for_each(std::cbegin( places ), std::cend( places ), [&p] ( const std::string& place) { p.Walk( place ); } );	
}

int main() 
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
    
