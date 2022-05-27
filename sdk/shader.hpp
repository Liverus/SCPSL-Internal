
class Shader : public Object {
public:

	static Shader* Find(const char* name) {

		auto il2cpp_name = (String*)API::il2cpp_string_new_len(name, strlen(name));

		typedef Shader*(*Shader_Find_t)(String* name);
		return Function<Shader_Find_t>("UnityEngine.CoreModule", "UnityEngine", "Shader", "Find", 1)(il2cpp_name);
	}

	static Shader* SetInt(const char* name) {

		auto il2cpp_name = (String*)API::il2cpp_string_new_len(name, strlen(name));

		typedef Shader* (*Shader_Find_t)(String* name);
		return Function<Shader_Find_t>("UnityEngine.CoreModule", "UnityEngine", "Shader", "Find", 1)(il2cpp_name);
	}
};

