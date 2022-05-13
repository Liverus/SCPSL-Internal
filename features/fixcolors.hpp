
namespace FixColors {

	Memory::Hook* is_supported;

	typedef bool(*ColorGrading_IsSupported_t)(OBJECT* this_, OBJECT* a);

	bool IsSupported_hk(OBJECT* this_, OBJECT* a) {
		return false;
	}

	void Initialize() {
		is_supported = Method("Unity.Postprocessing.Runtime", "UnityEngine.Rendering.PostProcessing", "ColorGrading", "IsEnabledAndSupported", 1)->Hook<ColorGrading_IsSupported_t>(IsSupported_hk);
	}

	void Enable() {
		is_supported->Load();
	}

	void Disable() {
		is_supported->Unload();
	}
}