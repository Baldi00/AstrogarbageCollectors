// Copyright Epic Games, Inc. All Rights Reserved.

#include "ABEditorUtilsStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FABEditorUtilsStyle::StyleInstance = nullptr;

void FABEditorUtilsStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FABEditorUtilsStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FABEditorUtilsStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ABEditorUtilsStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FABEditorUtilsStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("ABEditorUtilsStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("ABEditorUtils")->GetBaseDir() / TEXT("Resources"));

	Style->Set("ABEditorUtils.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FABEditorUtilsStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FABEditorUtilsStyle::Get()
{
	return *StyleInstance;
}
