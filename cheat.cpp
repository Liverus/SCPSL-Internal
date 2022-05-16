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

typedef void(*Camera_Render_t)(Camera* this_);
Camera_Render_t Camera_Render;

void Camera_Render_hk(Camera* this_) {
	Camera_Render(this_);
	EventManager::Call("OnGUI");
}

typedef void(*OnGUI_t)(OBJECT* this_);
OnGUI_t OnGUI;

void OnGUI_hk(OBJECT* this_) {

	std::cout << "alled" << std::endl;

	OnGUI(this_);

	// EventManager::Call("OnGUI");
}

// Cheat

namespace Cheat {
	bool Initialized = false;
}

bool Cheat::Initialize() {

	Features::Initialize();

	auto camera_render = Method("UnityEngine.CoreModule", "UnityEngine", "Camera", "Render", 0)->Hook<Camera_Render_t>(Camera_Render_hk, &Camera_Render);

	LOG("Cheeto Loaded!");

	Initialized = true;

	return true;
}

bool Cheat::Shutdown() {

	LOG("Cheat Unloaded!");

	return true;
}