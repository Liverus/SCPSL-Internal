template <class T>
class List : public Object {
public:
	int Count() {
		return this->GetValue<int>("_size");
	}

	Array<T>* GetValues() {
		return this->GetValue<Array<T>*>("_items");
	}
};