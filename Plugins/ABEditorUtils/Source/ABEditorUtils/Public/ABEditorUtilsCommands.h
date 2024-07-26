// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ABEditorUtilsStyle.h"

class FABEditorUtilsCommands : public TCommands<FABEditorUtilsCommands>
{
public:

	FABEditorUtilsCommands()
		: TCommands<FABEditorUtilsCommands>(TEXT("ABEditorUtils"), NSLOCTEXT("Contexts", "ABEditorUtils", "ABEditorUtils Plugin"), NAME_None, FABEditorUtilsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};