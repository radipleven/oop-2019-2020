const int max = 1024;
class User {
	char* name = new char[max];
	char* age = new char[2];
	char* email = new char[100];
	int id;

public:

	User(const char* name, const char* age, const char* email, const int id);

	User();

	char* getName();

	void setName(const char* name);

	char* getAge();

	void setAge(const char* age);

	char* getEmail();

	void setEmail(const char* email);

	int getId();

	void setId(const int id);

	void getInfo();


};