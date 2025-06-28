#include "pch.h"
#include "DisablecrateAnim.h"

BAKKESMOD_PLUGIN(DisableCrateAnim, "Disables that annoying crate animation ", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void DisableCrateAnim::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->registerCvar("DisableCrateAnim_ShowHint", "1");

	gameWrapper->HookEventWithCallerPost<ActorWrapper>(
		"Function TAGame.GFxData_UIConfig_TA.HandleUIConfig",
		[this](ActorWrapper caller, void* params, ...)
	{
		// if you're reading this, you owe me money
		// also did you know that you're is the same amount of characters as 'you are' just 1 has a space.
		// you are saving 1 key press, 1 tap on the screen, 1 motion, to make yourself look fancier.
		pHandleUiConfig* p = (pHandleUiConfig*)params;
		if(!p || !p->config) return;
		// 3rd bit is bCrateRouletteEnabled;
		p->config->flag |= (1u << 3);

		Set = true;
	});

	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas)
	{
		CVarWrapper c_ShowHint = cvarManager->getCvar("DisableCrateAnim_ShowHint");
		if (!c_ShowHint) return;
		if(!c_ShowHint.getBoolValue()) return;
		MenuStackWrapper msw = gameWrapper->GetMenuStack();
		if(!msw) return;
		if (msw.GetTopMenu() == "PreviewListMenuMovie")
		{
			canvas.SetPosition(Vector2(0,0));
			canvas.SetColor(LinearColor(255, 255, 255, 255));
			canvas.DrawString(Set ? "Will skip drop animation" : "Will not skip drop animation. Re-enter the main menu from a gamestate (An example being join and leave freeplay)", 1, 1);
		}
	});
}
void DisableCrateAnim::RenderSettings()
{
	CVarWrapper c_ShowHint = cvarManager->getCvar("DisableCrateAnim_ShowHint");
	if (!c_ShowHint)
	{
		ImGui::Text("Could not find cvar 'DisableCrateAnim_ShowHint'");
		return;
	}
	bool b_ShowHint = c_ShowHint.getBoolValue();
	if (ImGui::Checkbox("Show hint in drop menu", &b_ShowHint))
	{
		c_ShowHint.setValue(b_ShowHint);
	}
}
