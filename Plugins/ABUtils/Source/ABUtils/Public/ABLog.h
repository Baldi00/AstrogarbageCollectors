#pragma once

#define STRF(...) FString::Printf(L ## __VA_ARGS__)
#define LOG(ToLog) UABLog::Log(this, ToLog, __LINE__, FString(__FUNCTION__))
#define LOGF(...) LOG(STRF(__VA_ARGS__))

class ABUTILS_API UABLog
{
public:
	static void Log(UObject* WorldContexObject, FString String, int32 Line, FString FunctionName);
	static void Log(UObject* WorldContexObject, const char* String, int32 Line, FString FunctionName);
	static void Log(UObject* WorldContexObject, int32 Value, int32 Line, FString FunctionName);
	static void Log(UObject* WorldContexObject, float Value, int32 Line, FString FunctionName);
	static void Log(UObject* WorldContexObject, bool bValue, int32 Line, FString FunctionName);
};
