#include "Challenge.hpp"
#include <iostream>
using namespace std;

Challenge::Challenge(const char* name, const char* challenger, const char* challenged1, const char* challenged2, const char* challenged3, const char* status, const bool completion,const int times, const int grade, const int id)
{
	setName(name);
	setChallenger(challenger);
	setChallenged1(challenged1);
	setChallenged2(challenged2);
	setChallenged3(challenged3);
	setStatus(status);
	setCompletion(completion);
	setTimes(times);
	setGrade(grade);
	setId(id);

}

Challenge::Challenge() :Challenge("Mandatory", "Mandatory","Unknown","Unknown", "Mandatory","new",false,0,0, 0) {};

char* Challenge::getName()
{
	return name;
}

void Challenge::setName(const char* name)
{
	strcpy(this->name, name);
}

char* Challenge::getChallenger()
{
	return challenger;
}
void Challenge::setChallenger(const char* challenger)
{
	strcpy(this->challenger, challenger);
}

char* Challenge::getChallenged1()
{
	return challenged1;
}

void Challenge::setChallenged1(const char* callenged1)
{
	strcpy(this->challenged1, challenged1);
}

char* Challenge::getChallenged1()
{
	return challenged2;
}

void Challenge::setChallenged1(const char* callenged2)
{
	strcpy(this->challenged1, challenged2);
}

char* Challenge::getChallenged3()
{
	return challenged3;
}

void Challenge::setChallenged3(const char* callenged3)
{
	strcpy(this->challenged1, challenged3);
}


char* Challenge::getStatus()
{
	return status;
}

void Challenge::setStatus(const char* Status)
{
	strcpy(this->status, status);
}

bool Challenge::getCompletion()
{
	return completion;
}

void Challenge::setCompletion(bool completion)
{
	completion = true;
	this->completion = completion;
}

int Challenge::getTimes()
{
	return times;
}
int Challenge::setTimes(const int times)
{
	this->times=times;
}

int Challenge::getGrade()
{
	return grade;
}
void Challenge::setGrade(const int grade)
{
	this->grade = grade;
}

int Challenge::getId()
{
	return id;
}
void Challenge::setId(const int id)
{
	this->id = id;
}

//void User::getInfo()
//{
//	cout << "Profile name is:" << name << endl;
//	cout << "Profile age is:" << age << endl;
//	cout << "Profile email is:" << email << endl;
//	cout << "Profile id is:" << id << endl;
//}