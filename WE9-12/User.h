class User
{
	int fdNumber;
	string name = "<NULL>";

public:
	User(int targetFD)
	{
		fdNumber = targetFD;
	}

	void SetName(string wantName) { name = wantName; };
};