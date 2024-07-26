#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ABLog.generated.h"

#define LOG(ToLog) UABLog::Log(ToLog, __LINE__, FString(__FUNCSIG__));
#define LOGF(...) LOG(FString::Printf(L ## __VA_ARGS__))

UCLASS()
class ABUTILS_API UABLog : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void Log(FString String, int32 Line, FString FunctionName);
	static void Log(const char* String, int32 Line, FString FunctionName);
	static void Log(int32 Value, int32 Line, FString FunctionName);
	static void Log(float Value, int32 Line, FString FunctionName);
	static void Log(bool bValue, int32 Line, FString FunctionName);
};
