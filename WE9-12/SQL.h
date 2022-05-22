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

//지금 연결된 SQL입니다!
MYSQL* SQLConnection;

//SQL한테 "질문"을 합니다! SQL은 저희한테 "대답"해주죠!
MYSQL_RES* SQLResponse;

//검색을 해서 결과로 나온 줄을 여기에다가 둡시다!
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

		//뒷 칸이 더 남았다 싶을 때에만 쉼표를 넣기!
		if (i < columnAmount - 1) queryString += ", ";
	};

	queryString += ") VALUES(";

	//                 열의 개수만큼은 돌아야하니까!
	for (int i = 0; i < columnAmount; i++)
	{
		if (i < valueAmount)	queryString += values[i];	//값이 있으면 그 값으로 넣기!
		else					queryString += "\"\"";		//값이 없으면 그냥 "" 넣어주기!
		//뒷 칸이 더 남았다 싶을 때에만 쉼표를 넣기!
		if (i < columnAmount - 1) queryString += ", ";
	};

	queryString += ");";

	cout << queryString.c_str() << endl;
	//그래서 실제로 쿼리를 해봅니다!
	if (mysql_query(SQLConnection, queryString.c_str()) != 0)
	{
		cout << "Query Error Occured: " << mysql_error(SQLConnection);
	};

	//쿼리를 해서 나온 결과의 상태!
	SQLResponse = mysql_store_result(SQLConnection);

	//아.. 못가져왔구나..
	if (SQLResponse == nullptr) return false;

	//저희가 하나의 줄로 받아오도록 하면 됩니다!
	resultRow = mysql_fetch_row(SQLResponse);
	return true;
}

//MYSQL에 실제로 연결하는 함수가 필요할 거에요!
int SQLConnect()
{
	//제일 먼저 저희가 해야하는 것은 mySQL에 연결하기 전에 "초기화"를 시도합니다!
	if (!(SQLConnection = mysql_init((MYSQL*)NULL)))
	{
		cout << "MYSQL Initiate Failed" << endl;
		return -1;
	};

	//초기화를 했으니까 그 위치에다가 "실제 연결"을 시키는 겁니다!
	if (!(mysql_real_connect(SQLConnection, SQL_ADDRESS,  SQL_ID, SQL_PW, NULL, 3306, NULL, 0)))
	{                    //   대상 포인터   주소(내 컴퓨터) 아이디   비번          포트
		cout << "MYSQL Connection Failed" << endl;
		return -1;
	};

	cout << "MYSQL Connection Succeed" << endl;

	//어..? login_info가 없네요?
	if (mysql_query(SQLConnection, "USE Project9") != 0)
	{
		//없으면 만들면 되지!
		mysql_query(SQLConnection, "CREATE DATABASE Project9");
		mysql_query(SQLConnection, "USE Project9");
		mysql_query(SQLConnection, "CREATE TABLE UserData(ID VARCHAR(24) PRIMARY KEY, PW VARCHAR(24), NAME VARCHAR(24))");

		cout << "Table Created" << endl;
	};

	return 0;
}