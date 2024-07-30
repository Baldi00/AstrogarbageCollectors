#include "ABLog.h"
#include "Kismet/KismetSystemLibrary.h"

void UABLog::Log(UObject* WorldContexObject, FString String, int32 Line, FString FunctionName)
{
    UKismetSystemLibrary::PrintString(WorldContexObject, String, true, false);
    FString ToPrintLogger = FunctionName + "(" + FString::FromInt(Line) + "): " + String;
    UE_LOG(LogTemp, Warning, TEXT("%s"), *ToPrintLogger);
}

void UABLog::Log(UObject* WorldContexObject, const char* String, int32 Line, FString FunctionName)
{
    Log(WorldContexObject, FString(String), Line, FunctionName);
}

void UABLog::Log(UObject* WorldContexObject, int32 Value, int32 Line, FString FunctionName)
{
    Log(WorldContexObject, FString::FromInt(Value), Line, FunctionName);
}

void UABLog::Log(UObject* WorldContexObject, float Value, int32 Line, FString FunctionName)
{
    Log(WorldContexObject, FString::SanitizeFloat(Value), Line, FunctionName);
}

void UABLog::Log(UObject* WorldContexObject, bool bValue, int32 Line, FString FunctionName)
{
    Log(WorldContexObject, bValue ? FString("true") : FString("false"), Line, FunctionName);
}
