#include "User.hpp"
#include <iostream>
using namespace std;

User::User(const char* name, const char* age, const char* email, const int id)
{
	setName(name);
	setAge(age);
	setEmail(email);
	setId(id);

}

User::User() :User("Mandatory", "Unknown", "Unknown", 0) {};

char* User::getName()
{
	return name;
}

void User::setName(const char* name)
{
	strcpy(this->name, name);
}

char* User::getAge()
{
	return age;
}
void User::setAge(const char* age)
{
	strcpy(this->age, age);
}

char* User::getEmail()
{
	return email;
}

void User::setEmail(const char* email)
{
	strcpy(this->email, email);
}

int User::getId()
{
	return id;
}
void User::setId(const int id)
{
	this->id = id;
}

void User::getInfo()
{
	cout << "Profile name is:" << name << endl;
	cout << "Profile age is:" << age << endl;
	cout << "Profile email is:" << email << endl;
	cout << "Profile id is:" << id << endl;
}