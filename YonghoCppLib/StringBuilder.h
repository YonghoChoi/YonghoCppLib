#pragma once
#include <stdlib.h>
#include <stdarg.h>

class StringBuilder
{
	const static int MAX_CHAR_LENGTH = 1024;
	char msg[MAX_CHAR_LENGTH];

public:
	StringBuilder()
	{
		Init();
	}

	void Init()
	{
		memset(msg, 0x00, MAX_CHAR_LENGTH);
	}

	void Append(char* format, ...)
	{
		char msgPiece[MAX_CHAR_LENGTH] = { 0, };

		va_list args;
		va_start(args, format);
		vsprintf_s(msgPiece, MAX_CHAR_LENGTH, format, args);
		sprintf_s(msg, MAX_CHAR_LENGTH, "%s%s\n", msg, msgPiece);

		va_end(args);
	}

	void AppendNoLine(char* format, ...)
	{
		char msgPiece[MAX_CHAR_LENGTH] = { 0, };

		va_list args;
		va_start(args, format);
		vsprintf_s(msgPiece, MAX_CHAR_LENGTH, format, args);
		sprintf_s(msg, MAX_CHAR_LENGTH, "%s%s", msg, msgPiece);

		va_end(args);
	}

	char* ToString()
	{
		return msg;
	}
};