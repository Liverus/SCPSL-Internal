#include "cheat.h"

namespace SDK {
	#include "color.hpp"
	#include "vec.hpp"
	#include "rect.hpp"
	#include "dictionary.hpp"
	#include "gui.hpp"
	#include "shader.hpp"
	#include "material.hpp"
	#include "renderer.hpp"
	#include "camera.hpp"
	#include "screen.hpp"
	#include "classmanager.hpp"
	#include "gameobject.hpp"
	#include "charactercontroller.hpp"
	#include "referencehub.hpp"
}

using namespace SDK;


// Features
namespace Features {
	#include "aimbot.hpp"
	#include "chams.hpp"
	#include "norecoil.hpp"
	#include "antitesla.hpp"
	#include "noratelimit.hpp"
	#include "heareveryone.hpp"
	#include "spider.hpp"

	void Initialize() {
		AntiTesla::Initialize();
		NoRecoil::Initialize();
		Chams::Initialize();
		NoRateLimit::Initialize();
		HearEveryone::Initialize();
		Aimbot::Initialize();
		// Spider::Initialize();
	}
}

using namespace Features;



typedef void(*ClassManager_Update_t)(ClassManager* this_);
ClassManager_Update_t ClassManager_Update;

void ClassManager_Update_hk(ClassManager* this_) {
	ClassManager_Update(this_);

	ReferenceHub* hub = this_->GetValue<ReferenceHub*>("_hub");

	//if (hub && hub->Ready() && hub->IsLocalPlayer()) {
	//	CharacterController* controller = hub->GetValue<CharacterController*>("characterController");
	//	std::cout << controller << std::endl;
	//	if (controller) {
	//		controller->SetSlopeLimit(99999);
	//		controller->SetSkinWidth(0.1);
	//		//controller->SetHeight(-3000);
	//		//controller->SetCenter(Vector3(-3000, -3000, -3000));
	//		controller->SetStepOffset(100);

	//		std::cout << "sat" << std::endl;
	//	}
	//}
}


typedef void(*set_RealModelPosition_t)(OBJECT* this_, Vector3 pos);
typedef Vector3(*get_RealModelPosition_t)(OBJECT* this_);
typedef void(*SendPosition_t)(OBJECT* this_, bool idk, bool idk2);
SendPosition_t SendPosition;

bool lol = false;

void SendPosition_hk(OBJECT* this_, bool a, bool b) {


	if ((GetAsyncKeyState(0x46) & 0x8000)) {
		auto getpos = Function<get_RealModelPosition_t>("Assembly-CSharp", "", "PlayerMovementSync", "get_RealModelPosition", 0);
		auto setpos = Function<set_RealModelPosition_t>("Assembly-CSharp", "", "PlayerMovementSync", "set_RealModelPosition", 1);

		auto pos = getpos(this_);
		pos.y += 0.01;
		setpos(this_, pos);
	}


	SendPosition(this_, a, b);
}

typedef bool(*get_Fog_t)(OBJECT* this_);
bool get_Fog_hk(OBJECT* this_) {
	return false;
}

typedef bool(*get_Ambient_t)(OBJECT* this_);
Color get_Ambient_hk(OBJECT* this_) {
	return Color(0.0f, 0.0f, 0.0f, 0.0f);
}

typedef void(*OnEquipped_t)(OBJECT* this_);
OnEquipped_t OnEquipped;

struct FirearmBaseStats {
	float AdsInaccuracy;
	float BaseDamage;
	float BaseDrawTime;
	int BasePenetrationPercent;
	float BulletInaccuracy;
	float DamageFalloff;
	float FullDamageDistance;
	float HipInaccuracy;
};

void OnEquipped_hk(OBJECT* this_) {
	OnEquipped(this_);
	std::cout << "equipped" << std::endl;

	if (this_) {

		typedef FirearmBaseStats(*get_BaseStats_t)(OBJECT* this_);
		auto stats = Function<get_BaseStats_t>("Assembly-CSharp", "InventorySystem.Items.Firearms", "AutomaticFirearm", "get_BaseStats", 0)(this_);

		//auto stats = this_->GetValue<void*>("_stats");

		std::cout << &stats << std::endl;
	}

	//stats.AdsInaccuracy = 0;
	//stats.BaseDamage = 100;
	//stats.BaseDrawTime = 0;
	//stats.BasePenetrationPercent = 100;
	//stats.BulletInaccuracy = 0;
	//stats.DamageFalloff = 0;
	//stats.FullDamageDistance = 9999;
	//stats.HipInaccuracy = 0;

	//this_->SetValue<FirearmBaseStats>("_stats", &stats);

	//float new_value = 0.0f;
	//stats->SetValue<float>("HipInaccuracy", &new_value);
	//stats->SetValue<float>("AdsInaccuracy", &new_value);
}

typedef void(*CmdScp939Noise_t)(OBJECT* this_);
void CmdScp939Noise_hk(OBJECT* this_, float vol) {}

typedef void(*PlayLandingFootstep_t)(OBJECT* this_);
void PlayLandingFootstep_hk(OBJECT* this_, bool a) {}

typedef void(*PlayFootstepSound_t)(OBJECT* this_);
void PlayFootstepSound_hk(OBJECT* this_, float vol, bool a, bool b) {}

typedef void(*PRender_t)(OBJECT* this_, OBJECT* a);
void PRender_hk(OBJECT* this_) {}

typedef bool(*IsSupported_t)(OBJECT* this_, OBJECT* a);
bool IsSupported_hk(OBJECT* this_, OBJECT* a) {
	return false;
}

typedef bool(*CanNoclip_t)(OBJECT* this_);
CanNoclip_t CanNoclip;

bool CanNoclip_hk(OBJECT* this_) {
	std::cout << "PTSDFSDFSDFDSF" << std::endl;
	return true;
}

struct CoinMessage {
	bool tail;
	unsigned short serial;
};

typedef void(*ClientProcessMessage_t)(CoinMessage a);
ClientProcessMessage_t ClientProcessMessage;

void ClientProcessMessage_hk(CoinMessage a) {
	ClientProcessMessage(a);
	std::cout << "process client" << std::endl;
}

typedef void(*CoinInit_t)();
CoinInit_t CoinInit;

void CoinInit_hk() {
	std::cout << "coininit" << std::endl;
	return CoinInit();
}

typedef void(*CoinCtor_t)();
CoinCtor_t CoinCtor;

void CoinCtor_hk() {
	std::cout << "coinctor" << std::endl;
	return CoinCtor();
}

typedef void(*CoinSerialize_t)(OBJECT* net, CoinMessage msg);
CoinSerialize_t CoinSerialize;

void CoinSerialize_hk(OBJECT* net, CoinMessage msg) {

	std::cout << "coinserialize " << msg.serial << std::endl;

	for (size_t i = 0; i < 60; i++)
	{
		CoinSerialize(net, msg);
	}
}

typedef void (*GetSpeed_t)(OBJECT* this_, float* out, bool idk);
GetSpeed_t GetSpeed;

void GetSpeed_hk(OBJECT* this_, float* speed, bool idk) {
	GetSpeed(this_, speed, idk);

	auto hub = this_->GetValue<ReferenceHub*>("_hub");

	if (hub->IsLocalPlayer()) {
		auto class_manager = hub->GetClassManager();

		*speed = *speed * 1.3f;
	}

	bool noclip = false;

	if (GetKeyState(VK_UP)) {
		noclip = true;
	}

	this_->SetValue<bool>("NoclipEnabled", &noclip);
}

// Cheat

bool Cheat::Initialize() {

	Features::Initialize();

	//Method("Assembly-CSharp", "", "CharacterClassManager", "EnableFPC", 0)->Hook<ClassManager_Update_t>(ClassManager_Update_hk, &ClassManager_Update);
	//Method("Assembly-CSharp", "", "PlayerMovementSync", "SendPosition", 2)->Hook<SendPosition_t>(SendPosition_hk, &SendPosition);

	Method("UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_fog", 0)->Hook<get_Fog_t>(get_Fog_hk);
	Method("UnityEngine.CoreModule", "UnityEngine", "RenderSettings", "get_ambientLight", 0)->Hook<get_Ambient_t>(get_Ambient_hk);
	Method("Unity.Postprocessing.Runtime", "UnityEngine.Rendering.PostProcessing", "ColorGrading", "IsEnabledAndSupported", 1)->Hook<IsSupported_t>(IsSupported_hk);

	Method("Assembly-CSharp", "", "FirstPersonController", "GetSpeed", 2)->Hook<GetSpeed_t>(GetSpeed_hk, &GetSpeed);


	////Method("Assembly-CSharp", "InventorySystem.Items.Firearms", "AutomaticFirearm", "OnEquipped", 0)->Hook<OnEquipped_t>(OnEquipped_hk, &OnEquipped);

	Method("Assembly-CSharp", "", "FootstepSync", "UserCode_CmdScp939Noise", 1)->Hook<CmdScp939Noise_t>(CmdScp939Noise_hk);
	Method("Assembly-CSharp", "", "FootstepSync", "PlayLandingFootstep", 1)->Hook<PlayLandingFootstep_t>(PlayLandingFootstep_hk);
	Method("Assembly-CSharp", "", "FootstepSync", "PlayFootstepSound", 3)->Hook<PlayFootstepSound_t>(PlayFootstepSound_hk);

	//MessageBoxA(0, "a", "n", 0);
	//Method("Assembly-CSharp", "", "CharacterClassManager", "NoclipCmdsAllowed", 0)->Hook<CanNoclip_t>(CanNoclip_hk, &CanNoclip);


	//Method("Assembly-CSharp", "InventorySystem.Items.Coin", "CoinNetworkHandler", ".cctor", 0)->Hook<CoinCtor_t>(CoinCtor_hk, &CoinCtor);
	//Method("Assembly-CSharp", "InventorySystem.Items.Coin", "CoinNetworkHandler", "Init", 0)->Hook<CoinInit_t>(CoinInit_hk, &CoinInit);
	//Method("Assembly-CSharp", "InventorySystem.Items.Coin", "CoinNetworkHandler", "Serialize", 2)->Hook<CoinSerialize_t>(CoinSerialize_hk, &CoinSerialize);

	//Method("Assembly-CSharp", "", "CharacterClassManager", "SetPlayersClass", 4)->Hook<SetClass_t>(SetClass_hk, &SetClass);
	// Method("Assembly-CSharp", "", "CharacterClassManager", "LaterJoinPossible", 0)->Hook<laterjoin_t>(laterjoin_hk);

	// Method("UnityEngine.PhysicsModule", "UnityEngine", "CharacterController", "get_velocity", 0)->Hook<get_velocity_t>(get_velocity_hk, &get_velocity);

	//Method("Assembly-CSharp", "", "PlayerMovementSync", "SendPosition", 2)->Hook<SendPosition_t>(SendPosition_hk, &SendPosition);


	LOG("Cheat Loaded!");

	return true;
}

bool Cheat::Shutdown() {

	LOG("Cheat Unloaded!");

	return true;
}