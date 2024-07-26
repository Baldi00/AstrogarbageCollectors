// Copyright Epic Games, Inc. All Rights Reserved.

#include "ABEditorUtils.h"
#include "ABEditorUtilsStyle.h"
#include "ABEditorUtilsCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName ABEditorUtilsTabName("ABEditorUtils");

#define LOCTEXT_NAMESPACE "FABEditorUtilsModule"

void FABEditorUtilsModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

    FABEditorUtilsStyle::Initialize();
    FABEditorUtilsStyle::ReloadTextures();

    FABEditorUtilsCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    PluginCommands->MapAction(
        FABEditorUtilsCommands::Get().OpenPluginWindow,
        FExecuteAction::CreateRaw(this, &FABEditorUtilsModule::PluginButtonClicked),
        FCanExecuteAction());

    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FABEditorUtilsModule::RegisterMenus));

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ABEditorUtilsTabName, FOnSpawnTab::CreateRaw(this, &FABEditorUtilsModule::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("FABEditorUtilsTabTitle", "ABEditorUtils"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FABEditorUtilsModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.

    UToolMenus::UnRegisterStartupCallback(this);

    UToolMenus::UnregisterOwner(this);

    FABEditorUtilsStyle::Shutdown();

    FABEditorUtilsCommands::Unregister();

    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ABEditorUtilsTabName);
}

TSharedRef<SDockTab> FABEditorUtilsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    FText ButtonText = FText::FromString("Add module");

    AccessibleText = FText::FromString("Module name");

    FOnClicked OnClickedDelegate;
    OnClickedDelegate.BindLambda([this]()->FReply
        {
            GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, AccessibleText.ToString());
            return FReply::Handled();
        });

    return SNew(SDockTab).TabRole(ETabRole::NomadTab)
        [
            SNew(SOverlay)
                + SOverlay::Slot().HAlign(HAlign_Left)
                [
                    SNew(STextBlock).Text(AccessibleText).AccessibleText(AccessibleText)
                ]
                + SOverlay::Slot().HAlign(HAlign_Right)
                [
                    SNew(SButton).Text(ButtonText).OnClicked(OnClickedDelegate)
                ]
        ];
}

void FABEditorUtilsModule::PluginButtonClicked()
{
    FGlobalTabmanager::Get()->TryInvokeTab(ABEditorUtilsTabName);
}

void FABEditorUtilsModule::RegisterMenus()
{
    // Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
    FToolMenuOwnerScoped OwnerScoped(this);

    {
        UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
        {
            FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
            Section.AddMenuEntryWithCommandList(FABEditorUtilsCommands::Get().OpenPluginWindow, PluginCommands);
        }
    }

    {
        UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
        {
            FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
            {
                FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FABEditorUtilsCommands::Get().OpenPluginWindow));
                Entry.SetCommandList(PluginCommands);
            }
        }
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FABEditorUtilsModule, ABEditorUtils)