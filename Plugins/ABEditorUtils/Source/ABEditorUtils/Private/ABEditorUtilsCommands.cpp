// Copyright Epic Games, Inc. All Rights Reserved.

#include "ABEditorUtilsCommands.h"

#define LOCTEXT_NAMESPACE "FABEditorUtilsModule"

void FABEditorUtilsCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ABEditorUtils", "Bring up ABEditorUtils window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
