#pragma once
// if youre reading this you owe me 100 dallars USD straight to my paypal
#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = "1.0";

struct UUIConfig
{
	unsigned char pad[0x0078];
	uint32_t flag;
};
struct pHandleUiConfig
{
	UUIConfig* config;
};

class DisableCrateAnim: public BakkesMod::Plugin::BakkesModPlugin
	, public SettingsWindowBase
{
	void onLoad() override;
public:
	bool Set = false;
public:
	void RenderSettings() override;
};
