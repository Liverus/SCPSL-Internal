#include "menu.h"

namespace Menu {
	bool Opened = false;
}

typedef void(*Cursor_set_lockState_t)(int state);
Cursor_set_lockState_t Cursor_set_lockState;

void Cursor_set_lockState_hk(int state) {

	if (Menu::Opened) {
		state = 0;
	}

	return Cursor_set_lockState(state);
}

typedef void(*Cursor_set_visible_t)(bool state);
Cursor_set_visible_t Cursor_set_visible;

void Cursor_set_visible_hk(bool state) {

	if (Menu::Opened) {
		state = true;
	}

	return Cursor_set_visible(state);
}

bool Menu::Initialize() {
	D3D11_Hook::Initialize();
	
	 Method("UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_lockState", 1)->Hook<Cursor_set_lockState_t>(Cursor_set_lockState_hk, &Cursor_set_lockState);
	 Method("UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_visible", 1)->Hook<Cursor_set_visible_t>(Cursor_set_visible_hk, &Cursor_set_visible);

	return true;
}


void Menu::Render() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Populate();
	
	ImGui::EndFrame();
	ImGui::Render();
}

void Menu::Populate() {
	ImGui::Begin("Damithe");

	ImGui::Text("Aimbot");
	ImGui::Checkbox("Enabled##Aimbot", &Config::aimbot);
	ImGui::Checkbox("No Recoil##Aimbot", &Config::aimbot_norecoil);
	ImGui::Checkbox("Autoshoot##Aimbot", &Config::aimbot_autoshoot);
	ImGui::Checkbox("Friendly Fire##Aimbot", &Config::aimbot_friendlyfire);
	ImGui::Checkbox("Fov##Aimbot", &Config::aimbot_fov);
	ImGui::SliderFloat("Value##Aimbot", &Config::aimbot_fov_value, 0.0f, 1920.0f);

	ImGui::Text("Chams");
	ImGui::Checkbox("Enabled##Chams", &Config::chams);
	ImGui::Checkbox("Local##Chams", &Config::chams_local);
	ImGui::Checkbox("Rainbow##Chams", &Config::chams_rgb);
	ImGui::SliderFloat("Rainbow Speed##Chams", &Config::chams_rgb_speed, 0.0f, 1.0f);
	ImGui::SliderFloat("Transparency##Chams", &Config::chams_alpha, 0.0f, 1.0f);

	ImGui::Text("Rendering");
	ImGui::Checkbox("Fix Colors##Rendering", &Config::fix_colors);
	ImGui::Checkbox("No Fog##Rendering", &Config::no_fog);
	ImGui::Checkbox("No AmbientLight##Rendering", &Config::no_ambient_light);

	ImGui::Text("Speedhack");
	ImGui::Checkbox("Enabled##Rendering", &Config::speedhack);
	ImGui::SliderFloat("Multiplier##Speedhack", &Config::speedhack_multiplier, 0.0f, 1.0f);

	ImGui::Text("Misc");
	ImGui::Checkbox("Anti Tesla##Misc", &Config::anti_tesla);
	ImGui::Checkbox("Hear Everyone##Misc", &Config::hear_everyone);
	ImGui::Checkbox("Noclip##Misc", &Config::noclip);
	ImGui::SliderFloat("Fov##Misc", &Config::fov, 60.0f, 170.0f);

	ImGui::Separator();

	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

	ImGui::End();
}

void Menu::Style() {
	ImGuiStyle* style = &ImGui::GetStyle();

	// +
	style->WindowBorderSize = 0;
	style->WindowRounding = 0;

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/ARLRDBD.TTF", 16);

	style->WindowPadding = ImVec2(15, 15);
	//style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	//style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	//style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	//style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	//style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
}

bool Menu::Shutdown() {

	return true;
}