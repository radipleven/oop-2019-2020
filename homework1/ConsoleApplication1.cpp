#include <iostream>
#include "User.hpp"
#include "Challenge.hpp"
using namespace std;

User* users = new User[1024];
int id = 0;
Challenge* challenges = new Challenge[1024];
int challengeId = 0;

void userFunction(char input[])
{
	char* pch;
	pch = strtok(input, " ");
	int counter = 0;

	while (pch != NULL)
	{
		counter++;
		//cout << "counter =" << counter << endl;
		//cout << "pch = " << pch << endl;
		if (counter ==2)
		{
			//cout << "tuk chekvame za counter 2" << endl;
			if (pch[0] >= '0' && pch[0] <= '9')
			{
				cout << "Invalid or missing name";
				return;
			}
			users[id].setName(pch);
		}

		if (counter==3)
		{
			//cout << "tuk chekvame za counter 3" << endl;
			if (strlen(pch)>2)
			{
				
				users[id].setEmail(pch);
			}
			else  users[id].setAge(pch);

		}

		if (counter==4)
		{
			//cout << "tuk chekvame za counter 4" << endl;
			users[id].setEmail(pch);
		}
		pch = strtok(NULL, " ");
	}
	users[id].setId(id); 
	//cout << "id =" << id << "i e prisvoeno na users[" << id << "]" << endl;
	id++;// cout << "uvelichihme id s 1 i veche id= " << id << endl;
	cout << "Registration complete" << endl;
	return;
}
void challengeFunction(char challengeInput[])
{
	char* pch;
	pch = strtok(challengeInput, " ");
	int counter = -1;
	while (pch != NULL)
	{
		counter++;
		if (counter == 1)
		{
			if (pch!="challenge")
			{
				cout << "Invalid input gresheno napisano challenge";
				return;
			}
		}
		
		if (counter == 2)
		{
			
			if (pch[0] >= '0' && pch[0] <= '9')
			{
				cout << "Invalid or missing name";//chekvame dali imeto e ok

				return;
			}
			for (int i = 0; i < sizeof(users); i++)
			{
				if (users[i].getName == pch) {
					//chekvame dali predizvkikvashtiq e registriran ako vleze v ifa nqma da vleze v elsa
					challenges[challengeId].setChallenger = pch;
				}
				else
				{
					cout << "Challenging user is not registered";
						return;
				}
			}
		}

		if (counter == 3)
		{
			//chekvame dali challenga go ima
			if (pch[0] != '#')
			{
				cout << "Invalid challenge";
				return;
			}
			bool added = true;
			for (int i = 0; i <sizeof(challenges); i++)
			{
				if (challenges[i].getName == pch)
				{
					int a= challenges[i].getTimes ;
					challenges[i].setTimes = a + 1;
					added = false;
				} 
			}
			if (added)
			{
				challenges[challengeId].setName = pch;
				challenges[challengeId].setTimes = 1;
			}

		}

		if (counter == 4)
		{
			//tuk chekvame dali predizvikanite sa registrirani
			for (int i = 0; i < sizeof(users); i++)
			{
				if (users[i].getName == pch) {
					
					challenges[challengeId].setChallenged1 = pch;
				}
				else
				{
					cout << "One or more challenged users are not registered";
					return;
				}
			}
			
		}

		if (counter == 5)
		{
			//tuk chekvame dali predizvikanite sa registrirani
			for (int i = 0; i < sizeof(users); i++)
			{
				if (users[i].getName == pch) {

					challenges[challengeId].setChallenged2 = pch;
				}
				else
				{
					cout << "One or more challenged users are not registered";
					return;
				}
			}

		}
		if (counter == 6)
		{
			//tuk chekvame dali predizvikanite sa registrirani
			for (int i = 0; i < sizeof(users); i++)
			{
				if (users[i].getName == pch) {

					challenges[challengeId].setChallenged3 = pch;
				}
				else
				{
					cout << "One or more challenged users are not registered";
					return;
				}
			}

		}


		if (challenges[challengeId].getTimes <= 2)
		{
			challenges[challengeId].setStatus = "new";
		}
		else if (challenges[challengeId].getTimes >= 2 && challenges[challengeId].getTimes <= 11)
		{
			challenges[challengeId].setStatus = "quite recently";
		}else if (challenges[challengeId].getTimes >= 11)
		{
			challenges[challengeId].setStatus = "old";
		}

		pch = strtok(NULL, " "); challengeId++;
	}
}

void finishFunction (char finishInput[])
	{

	}
int main() {
	//User nqkoi = { "nqkogo", "23", "ahhaha", 25 };
	
	char input[1024];
	cin.getline(input,1024);
	userFunction(input);
	users[id-1].getInfo();
	
	char challengeInput[1024];
	cin.getline(challengeInput, 1024);
	challengeFunction(challengeInput);

	char finishInput[1024];
	finishFunction(finishInput);
	return 0;
}
