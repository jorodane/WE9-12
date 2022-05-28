#pragma once
void* CommandThread(void* data)
{
	string input;
	while (isRunning)
	{
		cin >> input;
		for (int i = 0; i < input.size(); i++)
		{
			//소문자를 찾아서
			if (input[i] >= 'a' || input[i] <= 'z')
			{
				//소문자를 대문자로 만들어줍시다!
				input[i] -= 'A' - 'a';
			};
		};

		switch (input.c_str())
		{
		case "QUIT":
		case "END":
		case "EXIT":
			isRunning = false;
			break;
		};
	};
}