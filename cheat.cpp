#include "cheat.h"

namespace SDK {

	#include "color.hpp"
	#include "vec.hpp"
	#include "quaternion.hpp"
	#include "rect.hpp"
	#include "dictionary.hpp"
	#include "transform.hpp"
	#include "physics.hpp"
	#include "gui.hpp"
	#include "shader.hpp"
	#include "material.hpp"
	#include "renderer.hpp"
	#include "camera.hpp"
	#include "screen.hpp"
	#include "playermovementsync.hpp"
	#include "classmanager.hpp"
	#include "gameobject.hpp"
	#include "charactercontroller.hpp"
	#include "referencehub.hpp"
	#include "hitboxidentity.hpp"

}

using namespace SDK;


// Features
namespace Features {

	#include "esp.hpp"
	#include "aimbot.hpp"
	#include "fov.hpp"
	#include "chams.hpp"
	#include "norecoil.hpp"
	#include "antitesla.hpp"
	#include "noratelimit.hpp"
	#include "heareveryone.hpp"
	#include "speedhack.hpp"
	#include "fog.hpp"
	#include "noclip.hpp"
	#include "ambientlight.hpp"
	#include "silentstep.hpp"
	#include "fixcolors.hpp"

	void Initialize() {
		Esp::Initialize();
		FOV::Initialize();
		AntiTesla::Initialize();
		Noclip::Initialize();
		NoRecoil::Initialize();
		Chams::Initialize();
		NoRateLimit::Initialize();
		HearEveryone::Initialize();
		Aimbot::Initialize();
		Fog::Initialize();
		AmbientLight::Initialize();
		Speedhack::Initialize();
		SilentStep::Initialize();
		FixColors::Initialize();
	}
}

using namespace Features;

// Events

typedef void(*GUIConsole_OnGUI_t)(Object* this_);
GUIConsole_OnGUI_t GUIConsole_OnGUI;

void GUIConsole_OnGUI_hk(Object* this_) {
	//GUIConsole_OnGUI(this_);
	EventManager::Call("OnGUI");
}

typedef void(*RoundStart_Update_t)(Object* this_);
RoundStart_Update_t RoundStart_Update;

void RoundStart_Update_hk(Object* this_) {
	RoundStart_Update(this_);
	EventManager::Call("Update");
	std::cout << "update" << std::endl;
}

typedef void(*RoundStart_Start_t)(Object* this_);
RoundStart_Start_t RoundStart_Start;

void RoundStart_Start_hk(Object* this_) {
	RoundStart_Start(this_);
	EventManager::Call("Start");

	auto game_obj = Object::New<GameObject*>("UnityEngine.CoreModule", "UnityEngine", "GameObject");
	GameObject::Create(game_obj, "");
	game_obj->AddComponent<Object*>(Class::Resolve("Mirror.Components", "Mirror", "GUIConsole"));
	//game_obj->DontDestroyOnLoad();
}

// Cheat

namespace Cheat {
	bool Initialized = false;
}

bool Cheat::Initialize() {

	Features::Initialize();

	auto console_ongui = Method::Resolve("Mirror.Components", "Mirror", "GUIConsole", "OnGUI", 0)->Hook<GUIConsole_OnGUI_t>(GUIConsole_OnGUI_hk, &GUIConsole_OnGUI);
	auto roundstart_start = Method::Resolve("Assembly-CSharp", "GameCore", "RoundStart", "Start", 0)->Hook<RoundStart_Start_t>(RoundStart_Start_hk, &RoundStart_Start);
	auto roundstart_update = Method::Resolve("Assembly-CSharp", "GameCore", "RoundStart", "Update", 0)->Hook<RoundStart_Update_t>(RoundStart_Update_hk, &RoundStart_Update);

	LOG("Cheat Loaded!");

	Initialized = true;

	return true;
}

bool Cheat::Shutdown() {

	LOG("Cheat Unloaded!");

	return true;
}