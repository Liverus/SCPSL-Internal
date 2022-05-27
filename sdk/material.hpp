
class Material : public Object {
public:

	//static Material* New(Shader* shader) {
	//	auto new_mat = IL2CPP::Class("UnityEngine.CoreModule", "UnityEngine", "Material")->New<Material*>();

	//	typedef Material*(*Material_ctor_t)(Material* this_, Shader* shader);
	//	return Function<Material_ctor_t>("UnityEngine.CoreModule", "UnityEngine", "Material", ".ctor", 1)(new_mat, shader);
	//}

	void SetInt(const char* name, int value) {
		auto name_str = String::NewLen(name);

		typedef void(*Material_SetInt_t)(Material* this_, String* name, int value);
		return Function<Material_SetInt_t>("UnityEngine.CoreModule", "UnityEngine", "Material", "SetInt", 2)(this, name_str, value);
	}

	void SetFloat(const char* name, float value) {
		auto name_str = String::NewLen(name);

		typedef void(*Material_SetFloat_t)(Material* this_, String* name, float value);
		return Function<Material_SetFloat_t>("UnityEngine.CoreModule", "UnityEngine", "Material", "SetFloat", 2)(this, name_str, value);
	}

	void SetColor(const char* name, Color clr) {
		auto name_str = String::NewLen(name);

		typedef void(*Material_SetColor_t)(Material* this_, String* name, Color clr);
		return Function<Material_SetColor_t>("UnityEngine.CoreModule", "UnityEngine", "Material", "SetColor", 2)(this, name_str, clr);
	}

	void SetColor(Color clr) {
		typedef void(*Material_SetColor_t)(Material* this_, Color clr);
		return Function<Material_SetColor_t>("UnityEngine.CoreModule", "UnityEngine", "Material", "set_color", 1)(this, clr);
	}

	void SetShader(Shader* shader) {
		typedef void(*Material_set_shader_t)(Material* this_, Shader* shader);
		return Function<Material_set_shader_t>("UnityEngine.CoreModule", "UnityEngine", "Material", "set_shader", 1)(this, shader);
	}
};