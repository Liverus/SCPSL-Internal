namespace Esp {

	void OnGUI() {
		GUI::Label(Rect(200, 200, 400, 400), "Hello World!");
	}

	void Initialize() {
		EventManager::Add("OnGUI", Esp::OnGUI);
	}

	void Enable() {}
	void Disable() {}
}