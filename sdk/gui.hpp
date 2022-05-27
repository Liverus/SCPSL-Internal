class GUI : public Object {
public:

	static void SetColor(Color clr) {
		typedef void (*GUI_set_color_t)(Color clr);
		return Function<GUI_set_color_t>("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "set_color", 1)(clr);
	}

	static void Label(Rect pos, const char* str) {

		auto il2cpp_str = (String*)API::il2cpp_string_new_len(str, strlen(str));

		typedef void (*GUI_Label_t)(Rect pos, String* str);
		return Function<GUI_Label_t>("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "Label", 2)(pos, il2cpp_str);
	}
};