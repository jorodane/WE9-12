#pragma once
#include "/usr/include/mysql/mysql.h"

#define SQL_ADDRESS "localhost"
#define SQL_ID		"root"
#define SQL_PW		"password"

//���� ����� SQL�Դϴ�!
MYSQL* SQLConnection;

//SQL���� "����"�� �մϴ�! SQL�� �������� "���"������!
MYSQL_RES* SQLResponse;

//�˻��� �ؼ� ����� ���� ���� ���⿡�ٰ� �ӽô�!
MYSQL_ROW resultRow;

//MYSQL�� ������ �����ϴ� �Լ��� �ʿ��� �ſ���!
int SQLConnect()
{
	//���� ���� ���� �ؾ��ϴ� ���� mySQL�� �����ϱ� ���� "�ʱ�ȭ"�� �õ��մϴ�!
	if (!(SQLConnection = mysql_init((MYSQL*)NULL)))
	{
		cout << "MYSQL Initiate Failed" << endl;
		return -1;
	};

	//�ʱ�ȭ�� �����ϱ� �� ��ġ���ٰ� "���� ����"�� ��Ű�� �̴ϴ�!
	if (!(mysql_real_connect(SQLConnection, SQL_ADDRESS,  SQL_ID, SQL_PW, NULL, 3306, NULL, 0)))
	{                    //   ��� ������   �ּ�(�� ��ǻ��) ���̵�   ���          ��Ʈ
		cout << "MYSQL Connection Failed" << endl;
		return -1;
	};

	cout << "MYSQL Connection Succeed" << endl;

	cout << mysql_query(SQLConnection, "use loginfo") << endl;

	return 0;
}