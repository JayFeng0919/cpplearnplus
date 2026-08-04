#include"hashtable.h"

namespace linear {
	HashTable::HashTable(int size, double loadFactor)
		:useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		if (size != primes_[0]) {
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++) {
				if (primes_[primeIdx_] >= size) break;
			}
			if (primeIdx_ == PRIME_SIZE) {
				primeIdx_--;
			}
		}
		tableSize_ = primes_[primeIdx_];
		table_ = new Bucket[tableSize_];
	}

	HashTable::~HashTable() {
		delete[]table_;
		table_ = nullptr;
	}

	bool HashTable::insert(int key) {
		double factor = useBucketNum_ * 1.0 / tableSize_;
		std::cout << "factor: " << factor << std::endl;
		if (factor > loadFactor_) {
			expand();
		}

		int idx = key % tableSize_;
		if (idx < 0) idx += tableSize_;
		int i = idx;
		int insertPos = -1; // 用来记录遇到的第一个空闲位置（DEL 或 UNUSE）

		do {
			if (table_[i].state_ == State::USING) {
				if (table_[i].key_ == key)
					return false;
			}
			else {
				if (insertPos == -1)
					insertPos = i;
				if (table_[i].state_ == State::UNUSE)
					break;
			}
			i = (i + 1) % tableSize_;
		} while (i != idx);

		if (insertPos != -1) {
			table_[insertPos].key_ = key;
			table_[insertPos].state_ = State::USING;
			useBucketNum_++;
			return true;
		}
		return false; // 理论上扩容机制保证了这里不会发生，除非表全满了且全是 USING
	}

	bool HashTable::erase(int key) {
		int idx = key % tableSize_;
		if (idx < 0) idx += tableSize_;
		int i = idx;
		do {
			if (table_[i].state_ == State::USING && table_[i].key_ == key) {
				table_[i].state_ = State::DEL;
				useBucketNum_--;
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (table_[i].state_ != State::UNUSE && i != idx);
		return false;
	}

	bool HashTable::find(int key) const {
		int idx = key % tableSize_;
		if (idx < 0) idx += tableSize_;
		int i = idx;
		do {
			if (table_[i].state_ == State::USING && table_[i].key_ == key) {
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (table_[i].state_ != State::UNUSE && i != idx);

		return false;
	}

	void HashTable::expand() {
		if (primeIdx_ + 1 == PRIME_SIZE) {
			throw "HashTable is too large to be expanded anymore";
		}

		++primeIdx_;
		Bucket* newTable = new Bucket[primes_[primeIdx_]];
		for (int i = 0; i < tableSize_; i++) {
			if (table_[i].state_ == State::USING) {
				int idx = table_[i].key_ % primes_[primeIdx_];
				if (idx < 0) idx += primes_[primeIdx_];
				int k = idx;
				do {
					if (newTable[k].state_ != State::USING) {
						newTable[k].key_ = table_[i].key_;
						newTable[k].state_ = State::USING;
						break;
					}
					k = (k + 1) % primes_[primeIdx_];
				} while (k != idx);
			}
		}
		delete[]table_;
		table_ = newTable;
		tableSize_ = primes_[primeIdx_];
	}

	int HashTable::primes_[PRIME_SIZE] = { 3,7,23,47,97,251,443,911,1471,42773 };

	void testHashTable() {
		HashTable htable;
		htable.insert(21);
		htable.insert(32);
		htable.insert(14);
		htable.insert(15);
		htable.insert(22);

		std::cout << htable.find(21) << std::endl;
		htable.erase(21);
		std::cout << htable.find(21) << std::endl;
	}
}

namespace linked {
	HashTable::HashTable(int size, double loadFactor)
		:useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		if (size != primes_[0]) {
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++) {
				if (primes_[primeIdx_] >= size) break;
			}
			if (primeIdx_ == PRIME_SIZE) {
				primeIdx_--;
			}
		}
		table_.resize(primes_[primeIdx_]);
	}

	void HashTable::insert(int key) {
		double factor = useBucketNum_ * 1.0 / table_.size();
		std::cout << "factor：" << factor << std::endl;
		if (factor > loadFactor_)
			expand();

		int idx = key % table_.size();
		if (idx < 0) idx += table_.size();
		if (table_[idx].empty()) {
			useBucketNum_++;
			table_[idx].emplace_front(key);
		}
		else {
			auto it = std::find(table_[idx].begin(), table_[idx].end(), key);
			if (it == table_[idx].end())
				table_[idx].emplace_front(key);
		}
	}

	void HashTable::erase(int key) {
		int idx = key % table_.size();
		if (idx < 0) idx += table_.size();
		auto it = std::find(table_[idx].begin(), table_[idx].end(), key);
		if (it != table_[idx].end()) {
			table_[idx].erase(it);
			if (table_[idx].empty())
				useBucketNum_--;
		}
	}

	bool HashTable::find(int key) const {
		int idx = key % table_.size();
		if (idx < 0) idx += table_.size();
		auto it = std::find(table_[idx].begin(), table_[idx].end(), key);
		return it != table_[idx].end();
	}

	void HashTable::expand() {
		if (primeIdx_ + 1 == PRIME_SIZE)
			throw "HashTable is too large to be expanded anymore";

		++primeIdx_;
		useBucketNum_ = 0;
		std::vector<std::list<int>> newtable;
		newtable.resize(primes_[primeIdx_]);
		for (const auto& list : table_) {
			for (const auto& key : list) {
				int idx = key % newtable.size();
				if (idx < 0) idx += newtable.size();
				if (newtable[idx].empty()) {
					useBucketNum_++;
				}
				newtable[idx].emplace_front(key);
			}
		}
		table_.swap(newtable);
	}

	int HashTable::primes_[PRIME_SIZE] = { 3,7,23,47,97,251,443,911,1471,42773 };

	void testHashTable() {
		HashTable htable;
		htable.insert(21);
		htable.insert(32);
		htable.insert(14);
		htable.insert(15);
		htable.insert(22);
		htable.insert(67);

		std::cout << htable.find(21) << std::endl;
		htable.erase(21);
		std::cout << htable.find(21) << std::endl;
	}
}