#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

namespace linear {
	enum class State {
		UNUSE,
		USING,
		DEL
	};

	struct Bucket {
		Bucket(int key = 0, State state = State::UNUSE)
			:key_(key)
			, state_(state)
		{}

		int key_;
		State state_;
	};

	class HashTable {
	public:
		HashTable(int size = primes_[0], double loadFactor = 0.75);
		~HashTable();
	public:
		bool insert(int key);
		bool erase(int key);
		bool find(int key) const;
	private:
		void expand();
	private:
		Bucket* table_;
		int tableSize_;
		int useBucketNum_;
		double loadFactor_;

		static const int PRIME_SIZE = 10;
		static int primes_[PRIME_SIZE];
		int primeIdx_;
	};

	void testHashTable();
}

namespace linked {
	class HashTable {
	public:
		HashTable(int size = primes_[0], double loadFactor = 0.75);
	public:
		void insert(int key);

		void erase(int key);

		bool find(int key) const;
	private:
		void expand();
	private:
		std::vector<std::list<int>> table_;
		int useBucketNum_;
		double loadFactor_;

		static const int PRIME_SIZE = 10;
		static int primes_[PRIME_SIZE];
		int primeIdx_;
	};

	void testHashTable();
}