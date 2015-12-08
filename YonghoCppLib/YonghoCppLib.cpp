#include "stdafx.h"
#include "YonghoCppLib.h"
#include <ctime>
#include <json/json.h>
#include <WinSock2.h>

using namespace std;

/// Date Time
time_t YonghoCppLib::GetNowToTime_t()
{
	return time(0);
}

std::shared_ptr<char> YonghoCppLib::GetNowToStr()
{
	time_t now = time(0);		// current date/time based on current system

	// dt는 최소한 26개의 문자를 저장하기에 충분해야한다.
	// 마지막에 asctime_s를 통해 컨버팅될 것을 대비해서 여유 있게 56으로 잡음
	std::shared_ptr<char> dt(new char[56]);
	ctime_s(dt.get(), 56, &now);		// convert now to string form
	return dt;
}

tm YonghoCppLib::GetNowToTmStruct()
{
	time_t now = time(0);

	char dt[56];
	ctime_s(dt, 56, &now);
	tm gmtm;
	gmtime_s(&gmtm, &now);		// convert now to tm struct for UTC
	return gmtm;
}

std::shared_ptr<char> YonghoCppLib::ConvertFromTmToString(tm& gmtm)
{
	std::shared_ptr<char> dt(new char[56]);
	asctime_s(dt.get(), 56, &gmtm);
	return dt;
}


/// Enum To String
#define ENUM_TO_STRING(e)	#e
std::shared_ptr<char> YonghoCppLib::GetEnumToString()
{
	enum eTEST
	{
		TEST_STRING
	};
	std::shared_ptr<char> str(new char[56]);
	strcpy_s(str.get(), 56, ENUM_TO_STRING(TEST_STRING));
	return str;
}

std::shared_ptr<char> YonghoCppLib::GetEnumToStringByVariable()
{
	enum eTEST
	{
		TEST_STRING
	};

	eTEST e = TEST_STRING;
	std::shared_ptr<char> str(new char[56]);
	strcpy_s(str.get(), 56, ENUM_TO_STRING(e));
	return str;
}

/// Json
/*
	lib 연결 시 이미 정의되어 있다는 에러가 발생할 경우
	json lib 프로젝트 빌드 시 속성(C/C++ 코드 생성)이 현재 프로젝트와 동일한지 체크
*/
string YonghoCppLib::WriteJson()
{
	Json::Value root;
	Json::Value encoding;
	root["encoding"] = "UTF-8";
	Json::Value plugins;
	plugins.append("python");
	plugins.append("c++");
	plugins.append("c#");
	root["plug-ins"] = plugins;
	Json::Value indent;
	indent["length"] = 3;
	indent["use_space"] = true;
	root["indent"] = indent;
	Json::StyledWriter writer;
	return writer.write(root);
}

void YonghoCppLib::ReadJson(string jsonStr)
{
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonStr, root);
	if (!parsingSuccessful)
	{
		cout << "json parsing error. json string : " << jsonStr << endl;
		return;
	}

	string encoding = root.get("encoding", "").asString();
	cout << encoding << endl;
	Json::Value plugins = root["plug-ins"];
	for (int i = 0; i < (int)plugins.size(); ++i)
	{
		cout << plugins[i].asString() << endl;
	}

	cout << root["indent"].get("length", 0).asInt() << endl;
	cout << root["indent"]["use_space"].asBool() << endl;
}

string YonghoCppLib::GetLocalIp()
{
	char myaddr[256];
	PHOSTENT pHostInfo;
	struct sockaddr_in addr;

	WSADATA WsaData;
	if (WSAStartup(0x202, &WsaData) == SOCKET_ERROR)
		return "";

	gethostname(myaddr, sizeof(myaddr));
	pHostInfo = gethostbyname(myaddr);

	if (pHostInfo)
	{
		for (int i = 0; pHostInfo->h_addr_list[i] != NULL; ++i)
		{
			memcpy(&addr.sin_addr, pHostInfo->h_addr_list[i], pHostInfo->h_length);
			cout << inet_ntoa(addr.sin_addr) << endl;
		}

		memcpy(&addr.sin_addr, pHostInfo->h_addr_list[0], pHostInfo->h_length);
		return inet_ntoa(addr.sin_addr);
	}

	return "";
}