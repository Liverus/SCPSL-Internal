template <class TKey, class TValue>
class Dictionary : public OBJECT {
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

	ARRAY<Entry<TKey, TValue>>* GetEntries() {
		return this->GetValue<ARRAY<Entry<TKey, TValue>>*>("entries");
	}
};