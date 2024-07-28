#include "ABLog.h"

void UABLog::Log(FString String, int32 Line, FString FunctionName)
{
    int32 Key = rand() % 4294967295 - 2147483648;
    GEngine->AddOnScreenDebugMessage(Key, 3, FColor::Cyan, String);
    FString ToPrintLogger = FunctionName + " (Line " + FString::FromInt(Line) + "): " + String;
    UE_LOG(LogTemp, Warning, TEXT("%s"), *ToPrintLogger);
}

void UABLog::Log(const char* String, int32 Line, FString FunctionName)
{
    Log(FString(String), Line, FunctionName);
}

void UABLog::Log(int32 Value, int32 Line, FString FunctionName)
{
    Log(FString::FromInt(Value), Line, FunctionName);
}

void UABLog::Log(float Value, int32 Line, FString FunctionName)
{
    Log(FString::SanitizeFloat(Value), Line, FunctionName);
}

void UABLog::Log(bool bValue, int32 Line, FString FunctionName)
{
    Log(bValue ? FString("true") : FString("false"), Line, FunctionName);
}
