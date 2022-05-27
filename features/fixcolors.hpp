
namespace FixColors {

	Memory::Hook* is_supported;

	typedef bool(*ColorGrading_IsSupported_t)(Object* this_, Object* a);

	bool IsSupported_hk(Object* this_, Object* a) {
		return !Config::fix_colors;
	}

	void Initialize() {
		is_supported = Method::Resolve("Unity.Postprocessing.Runtime", "UnityEngine.Rendering.PostProcessing", "ColorGrading", "IsEnabledAndSupported", 1)->Hook<ColorGrading_IsSupported_t>(IsSupported_hk);
	}

	void Enable() {
		is_supported->Load();
	}

	void Disable() {
		is_supported->Unload();
	}
}