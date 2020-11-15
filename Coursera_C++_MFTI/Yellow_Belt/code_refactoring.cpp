#include <iostream>
#include <string>
#include <vector>


template <typename T>
void Notify(T person, void action, )



class WalkingPerson
{
public:
	using Name_t = std::string;
	using Destination_t = std::string
	using Type_t = std::string;
public:
	explicit WalkingPerson(const Name_t&);
	virtual void Walk(const Destination_t&) const = 0;
	virtual ~WalkingPerson();
protected:
	Name_t name_;
	Type_t personType_;
};


WalkingPerson::WalkingPerson(const Name_t& name)
	: name_ {name}
	, personType_ {WalkingPerson}
{
}


WalkingPerson::~WalkingPerson()
{
}


class Student : public WalkingPerson 
{
	using FavouriteSong_t = std::string;
public:
	Student(const Name_t&, const FavouriteSong_t&);
	void NotifyLearn() const;
	void NotifyWalk(Destination_t&) const final;
	void NotifySingSong() const;
	type_t GetType();
private:
	const type_t personType {Student}; 
	FavouriteSong_t favouriteSong_;
};

Student::Student(const Name_t& name, const FavouriteSong_t& favouriteSong)
	: WalkingPerson {name}
	, favouriteSong_ {favouriteSong}
{
}


void Student::NotifyLearn() const 
{
	Learn(name_);
}

void Learn(Name_t name)
{
	std::cout << "Student: " << name << " learns" << std::endl;
}

void Student::NotifyWalk(const Destination_t& destination) const
{
	Walk(name_, destination, favouriteSong_);
}

void Walk(const Name_t& name_, const Destination_t& destination, const FavouriteSong_& favouriteSong)
{
	std::cout << "Student: " << name_ << " walks to: " << destination << std::endl;
	SingSong(name_, favouriteSong);
}

void Student::SingSong() const
{
	std::cout << "Student: " << name_ << " sings a song: " << favouriteSong_ << std::endl;
}


class Teacher : public WalkingPerson
{
public:
	using Subject_t = std::string;
public:
	Teacher(const Name_t&, const std::string&);
	void Teach() const;
	void Walk(const std::string&) const;
private:
	Subject_t subject_;
};

Teacher::Teacher(const std::string& name, const std::string& subject):
	name_ {name},
	subject_ {subject}
}

void Teacher::Teach() const
{
	std::cout << " teaches: " << subject_ << std::endl;
}

void Teacher::Walk(const std::string& destination) 
{
	PrintTeachersName();
	std::cout << " walks to: " << destination << endl;
}

class Policeman {
public:
    Policeman(string name) {
        Name = name;
    }

    void Check(Teacher t) {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student s) {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman p) {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(string destination) {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};


template<typename T>
void Policeman::Check(T subject)
{
	PrintPolicemansName();
	std::cout << " checks";
	switch(T)
	{
		case Teacher:
			std::cout << "Teacher. Teacher's";
			break;	
		case Student:
			std::cout << "Student. Student's";
			break;	
		case Policeman:
			std::cout << "Policeman. Policeman's";
			break;
	}
	std::cout << " name is: " << subject.name_ << std::endl;	

}

void VisitPlaces(Teacher t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places) {
    for (auto p : places) {
        pol.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}

