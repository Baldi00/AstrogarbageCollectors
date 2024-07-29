#pragma once

#define STRF(...) FString::Printf(L ## __VA_ARGS__)
#define LOG(ToLog) UABLog::Log(ToLog, __LINE__, FString(__FUNCTION__))
#define LOGF(...) LOG(STRF(__VA_ARGS__))

class ABUTILS_API UABLog
{
public:
	static void Log(FString String, int32 Line, FString FunctionName);
	static void Log(const char* String, int32 Line, FString FunctionName);
	static void Log(int32 Value, int32 Line, FString FunctionName);
	static void Log(float Value, int32 Line, FString FunctionName);
	static void Log(bool bValue, int32 Line, FString FunctionName);
};
