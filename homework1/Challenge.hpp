const int max = 1024;
class Challenge {
	char* name = new char[max];
	char* challenger = new char[100];
	char* challenged1 = new char[100];
	char* challenged2 = new char[100];
	char* challenged3 = new char[100];
	char* status = new char[100];
	bool completion;
	int times;
	int grade;
	int id;

public:

	Challenge(const char* name, const char* challenger, const char* challenged1, const char* challenged2, const char* challenged3,const char* status,const int times, bool completion, const int grade, const int id);

	Challenge();

	char* getName();

	void setName(const char* name);

	char* getChallenger();

	void setChallenger(const char* challenger);

	char* getChallenged1();

	void setChallenged1(const char* challenged1);

	char* getChallenged2();

	void setChallenged2(const char* challenged2);

	char* getChallenged3();

	void setChallenged3(const char* challenged3);

	char* getStatus();

	void setStatus(const char* status);

	int getTimes();

	int setTimes(const int times);

	bool getCompletion();

	void setCompletion(bool completion);

	int getGrade();

	void setGrade(const int grade);

	int getId();

	void setId(const int id);

};