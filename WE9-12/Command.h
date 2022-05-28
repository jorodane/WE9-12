#pragma once

enum class CommandType
{
	Error,
	Quit,
};

//���� ������� ��ɾ��� ����!
CommandType currentType;
//���� ��ɾ �� ĭ�̳� �о��°�?
int currentIndex;

void CalculateCommand(string word)
{
	cout << word << endl;
	//���� �ƹ��͵� �� �޾Ҿ��!
	//�� ���� �������� ���� ���� ��ɾ �� ������ ������ �ð��̶�� ���Դϴ�!
	if (currentIndex == 0)
	{
		if (word == "QUIT" || word == "EXIT" || word == "CLOSE" || word == "END")
		{
			currentType = CommandType::Quit;
		};
	};

	++currentIndex;
}

void ExecuteCommand()
{
	switch (currentType)
	{
	case CommandType::Quit:
		isRunning = false;
		break;
	};
}


void* CommandThread(void* data)
{
	string input;
	while (isRunning)
	{
		//�������� �Է��� ����
		cin >> input;

		//��ɾ �ʱ�ȭ�ϰ� ���Կ�!
		currentType = CommandType::Error;
		//���� ���� ���� �����ϱ� 0��°!
		currentIndex = 0;

		for (int i = 0; i < input.size(); i++)
		{
			//�ҹ��ڸ� ã�Ƽ�
			if (input[i] >= 'a' || input[i] <= 'z')
			{
				//�ҹ��ڸ� �빮�ڷ� ������ݽô�!
				input[i] += 'A' - 'a';
			};
		};

		string currentWord;
		currentWord.clear();
		for (int i = 0; i <= input.size(); i++)
		{
			//���ڰ� �����ų�, �����̽��� ������ �� �ڸ����� ����, ���ڸ� �о��!
			if (i == input.size() || input[i] == ' ')
			{
				CalculateCommand(currentWord);
				currentWord.clear();
			}
			else //�����̽��� �ƴ϶��! �ܾ�ٰ� ���ڸ� �߰��� �̴ϴ�!
			{
				currentWord += input[i];
			};
		};
		//���ڸ� ��� �ľ������� ������ Ŀ�ǵ带 �����մϴ�!
		ExecuteCommand();
	};

	return nullptr;
}