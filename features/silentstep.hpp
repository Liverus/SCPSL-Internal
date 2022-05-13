namespace SilentStep {

	Memory::Hook* cmd_scp939_noise;
	Memory::Hook* play_landing_footstep;
	Memory::Hook* play_foostep_sound;

	typedef void(*FootstepSync_CmdScp939Noise_t)(OBJECT* this_);
	void CmdScp939Noise_hk(OBJECT* this_, float vol) {}

	typedef void(*FootstepSync_PlayLandingFootstep_t)(OBJECT* this_);
	void PlayLandingFootstep_hk(OBJECT* this_, bool a) {}

	typedef void(*FootstepSync_PlayFootstepSound_t)(OBJECT* this_);
	void PlayFootstepSound_hk(OBJECT* this_, float vol, bool a, bool b) {}

	void Initialize() {
		cmd_scp939_noise = Method("Assembly-CSharp", "", "FootstepSync", "UserCode_CmdScp939Noise", 1)->Hook<FootstepSync_CmdScp939Noise_t>(CmdScp939Noise_hk);
		play_landing_footstep = Method("Assembly-CSharp", "", "FootstepSync", "PlayLandingFootstep", 1)->Hook<FootstepSync_PlayLandingFootstep_t>(PlayLandingFootstep_hk);
		play_foostep_sound = Method("Assembly-CSharp", "", "FootstepSync", "PlayFootstepSound", 3)->Hook<FootstepSync_PlayFootstepSound_t>(PlayFootstepSound_hk);
	}

	void Enable() {
		cmd_scp939_noise->Load();
		play_landing_footstep->Load();
		play_foostep_sound->Load();
	}

	void Disable() {
		cmd_scp939_noise->Unload();
		play_landing_footstep->Unload();
		play_foostep_sound->Unload();
	}
}