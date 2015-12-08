// YonghoCppLib.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "YonghoCppLib.h"
#include "StringBuilder.h"
using namespace std;

void test_datetime(YonghoCppLib& lib)
{
	printf("%lld\n", lib.GetNowToTime_t());
	printf("%s\n", lib.GetNowToStr());
	printf("%d\n", lib.GetNowToTmStruct().tm_year);
	printf("%s\n", lib.ConvertFromTmToString(lib.GetNowToTmStruct()));
}

void test_enum_to_string(YonghoCppLib& lib)
{
	printf("%s\n", lib.GetEnumToString());
	printf("%s\n", lib.GetEnumToStringByVariable());
}

void test_string_builder(YonghoCppLib& lib)
{
	StringBuilder strBuilder;
	strBuilder.Append("Name : Yongho Choi");
	strBuilder.Append("Age : 30");
	strBuilder.Append("Address : %s", "Suwon");
	printf("%s\n", strBuilder.ToString());
}

void test_json(YonghoCppLib& lib)
{
	string jsonStr = lib.WriteJson();
	cout << jsonStr << endl;

	lib.ReadJson(jsonStr);
}

void test_get_local_ip(YonghoCppLib& lib)
{
	cout << lib.GetLocalIp() << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	YonghoCppLib lib;
	test_get_local_ip(lib);
	getchar();
	return 0;
}

