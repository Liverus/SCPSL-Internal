enum TextAnchor
{
	UpperLeft = 0,
	UpperCenter,
	UpperRight,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	LowerLeft,
	LowerCenter,
	LowerRight
};

class GUISkin : public Object {
public:
	static GUISkin* GetCurrent() {
		return Field::Resolve("UnityEngine.IMGUIModule", "UnityEngine", "GUISkin", "current")->GetStaticValue<GUISkin*>();
	}
};

class Font : public Object {
public:
	void SetSize(int size) {/*
		typedef void (*Font_set_fontSize_t)(int size);
		return Function<Font_set_fontSize_t>("UnityEngine.TextRenderingModule", "UnityEngine", "Font", "set_fontSize", 1)(size);*/
	}
};

class GUIStyle : public Object {
public:
	static GUIStyle* GetLabelStyle() {
		return GUISkin::GetCurrent()->GetValue<GUIStyle*>("m_label");
	}

	Font* GetFont() {
		typedef Font* (*GUIStyle_get_font_t)(Object* this_);
		return Function<GUIStyle_get_font_t>("UnityEngine.IMGUIModule", "UnityEngine", "GUIStyle", "get_font", 0)(this);
	}

	void SetFontSize(int size) {
		this->GetFont()->SetSize(size);
	}

	void SetAlignment(TextAnchor alignment) {
		typedef void (*GUIStyle_set_alignment_t)(Object* this_, TextAnchor alignment);
		return Function<GUIStyle_set_alignment_t>("UnityEngine.IMGUIModule", "UnityEngine", "GUIStyle", "set_alignment", 1)(this, alignment);
	}
};

class GUI : public Object {
public:

	static void SetColor(Color clr) {
		typedef void (*GUI_set_color_t)(Color clr);
		return Function<GUI_set_color_t>("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "set_color", 1)(clr);
	}

	static void DrawTexture(Rect pos, Object* texture) {
		typedef void (*GUI_DrawTexture_t)(Rect pos, Object* texture);
		return Function<GUI_DrawTexture_t>("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "DrawTexture", 2)(pos, texture);
	}

	static void Label(Rect pos, const char* str) {
		auto il2cpp_str = (String*)API::il2cpp_string_new_len(str, strlen(str));

		return Label(pos, il2cpp_str);
	}

	static void Label(Rect pos, String* str) {
		typedef void (*GUI_Label_t)(Rect pos, String* str);
		return Function<GUI_Label_t>("UnityEngine.IMGUIModule", "UnityEngine", "GUI", "Label", 2)(pos, str);
	}
};