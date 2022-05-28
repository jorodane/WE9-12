#pragma once

enum class CommandType
{
	Error,
	Quit,
};

//현재 계산중인 명령어의 종류!
CommandType currentType;
//현재 명령어를 몇 칸이나 읽었는가?
int currentIndex;

void CalculateCommand(string word)
{
	cout << word << endl;
	//아직 아무것도 안 받았어요!
	//그 말은 이제부터 저희가 무슨 명령어를 쓸 것인지 선택할 시간이라는 것입니다!
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
		//관리자의 입력을 받음
		cin >> input;

		//명령어를 초기화하고 갈게요!
		currentType = CommandType::Error;
		//아직 받은 것이 없으니까 0번째!
		currentIndex = 0;

		for (int i = 0; i < input.size(); i++)
		{
			//소문자를 찾아서
			if (input[i] >= 'a' || input[i] <= 'z')
			{
				//소문자를 대문자로 만들어줍시다!
				input[i] -= 'A' - 'a';
			};
		};

		string currentWord;
		for (int i = 0; i <= input.size(); i++)
		{
			//글자가 끝나거나, 스페이스가 나오면 그 자리에서 끊고, 글자를 읽어보기!
			if (i == input.size() || input[i] == ' ')
			{
				CalculateCommand(currentWord);
				currentWord.clear();
			}
			else //스페이스가 아니라면! 단어에다가 글자를 추가할 겁니다!
			{
				currentWord += input[i];
			};
		};
		//글자를 모두 파악했으니 실제로 커맨드를 실행합니다!
		ExecuteCommand();
	};

	return nullptr;
}