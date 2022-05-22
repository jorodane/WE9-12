#pragma once
#include "/usr/include/mysql/mysql.h"

#define SQL_ADDRESS "localhost"
#define SQL_ID		"root"
#define SQL_PW		"password"

/*
create database login_info;
use login_info;
create table certification
(
	ID VARCHAR(24) PRIMARY KEY,
	PW VARCHAR(24),
	NAME VARCHAR(24)
);
insert into certification
	(ID, PW, NAME)
values  ("d","e","f");
select * from certification where ID = "a";
delete from certification where ID = "d";
*/

//���� ����� SQL�Դϴ�!
MYSQL* SQLConnection;

//SQL���� "����"�� �մϴ�! SQL�� �������� "���"������!
MYSQL_RES* SQLResponse;

//�˻��� �ؼ� ����� ���� ���� ���⿡�ٰ� �ӽô�!
MYSQL_ROW resultRow;

bool SQLInsert(string tableName, int columnAmount, string* columnNames, int valueAmount, string* values)
{
	if (columnAmount <= 0) return false;
	if (valueAmount <= 0) return false;

	//insert into certification(ID, PW, NAME) values("d", "e", "f");
	string queryString = "INSERT INTO " + tableName + "(";

	for (int i = 0; i < columnAmount; i++)
	{
		queryString += columnNames[i];

		//�� ĭ�� �� ���Ҵ� ���� ������ ��ǥ�� �ֱ�!
		if (i < columnAmount - 1) queryString += ", ";
	};

	queryString += ") VALUES(";

	//                 ���� ������ŭ�� ���ƾ��ϴϱ�!
	for (int i = 0; i < columnAmount; i++)
	{
		if (i < valueAmount)	queryString += values[i];	//���� ������ �� ������ �ֱ�!
		else					queryString += "\"\"";		//���� ������ �׳� "" �־��ֱ�!
		//�� ĭ�� �� ���Ҵ� ���� ������ ��ǥ�� �ֱ�!
		if (i < columnAmount - 1) queryString += ", ";
	};

	queryString += ");";

	cout << queryString.c_str() << endl;
	//�׷��� ������ ������ �غ��ϴ�!
	mysql_query(SQLConnection, queryString.c_str());

	//������ �ؼ� ���� ����� ����!
	SQLResponse = mysql_store_result(SQLConnection);

	//��.. �������Ա���..
	if (SQLResponse == nullptr) return false;

	//���� �ϳ��� �ٷ� �޾ƿ����� �ϸ� �˴ϴ�!
	//resultRow = mysql_fetch_row(SQLResponse);
	return true;
}

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

	//��..? login_info�� ���׿�?
	if (mysql_query(SQLConnection, "USE Project9") != 0)
	{
		//������ ����� ����!
		mysql_query(SQLConnection, "CREATE DATABASE Project9");
		mysql_query(SQLConnection, "USE Project9");
		mysql_query(SQLConnection, "CREATE TABLE UserData(ID VARCHAR(24) PRIMARY KEY, PW VARCHAR(24), NAME VARCHAR(24))");

		cout << "Table Created" << endl;
	};

	return 0;
}