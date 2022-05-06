class Dictionary : public OBJECT {
public:
	int Count() {
		return this->GetValue<int>("count");
	}

	ARRAY<OBJECT*>* Entries() {
		return this->GetValue<ARRAY<OBJECT*>*>("entries");
	}
};