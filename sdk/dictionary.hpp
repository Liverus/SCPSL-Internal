template <class TKey, class TValue>
class Dictionary : public Object {
public:
	template <class TKey, class TValue>
	struct Entry {
		int hashCode;
		int next;
		TKey key;
		TValue value;
	};

	int Count() {
		return this->GetValue<int>("count");
	}

	Array<Entry<TKey, TValue>>* GetEntries() {
		return this->GetValue<Array<Entry<TKey, TValue>>*>("entries");
	}
};