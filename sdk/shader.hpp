
class Shader : public OBJECT {
public:

	static Shader* Find(const char* name) {

		auto il2cpp_name = (STRING*)API::il2cpp_string_new_len(name, strlen(name));

		typedef Shader*(*Shader_Find_t)(STRING* name);
		return Function<Shader_Find_t>("UnityEngine.CoreModule", "UnityEngine", "Shader", "Find", 1)(il2cpp_name);
	}

	static Shader* SetInt(const char* name) {

		auto il2cpp_name = (STRING*)API::il2cpp_string_new_len(name, strlen(name));

		typedef Shader* (*Shader_Find_t)(STRING* name);
		return Function<Shader_Find_t>("UnityEngine.CoreModule", "UnityEngine", "Shader", "Find", 1)(il2cpp_name);
	}
};

