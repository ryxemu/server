#ifndef __EQEMU_TESTS_FIXED_MEMORY_H
#define __EQEMU_TESTS_FIXED_MEMORY_H

#include "cppunit/cpptest.h"
#include "../common/fixed_memory_hash_set.h"
#include "../common/item_instance.h"

class FixedMemoryHashTest : public Test::Suite {
	typedef void (FixedMemoryHashTest::*TestFunction)(void);

   public:
	FixedMemoryHashTest() {
		size_ = EQ::FixedMemoryHashSet<EQ::ItemData>::estimated_size(72000, 190000);
		data_ = new uint8[size_];
		memset(data_, 0, size_);
		TEST_ADD(FixedMemoryHashTest::InitTest);
		TEST_ADD(FixedMemoryHashTest::LoadTest);
		TEST_ADD(FixedMemoryHashTest::InsertTest);
		TEST_ADD(FixedMemoryHashTest::RetrieveTest);
		TEST_ADD(FixedMemoryHashTest::OverwriteTest);
		TEST_ADD(FixedMemoryHashTest::OverwriteRetrieveTest);
		TEST_ADD(FixedMemoryHashTest::InsertAgainTest);
		TEST_ADD(FixedMemoryHashTest::RetrieveAgainTest);
		TEST_ADD(FixedMemoryHashTest::InsertBeginTest);
		TEST_ADD(FixedMemoryHashTest::RetrieveBeginTest);
		TEST_ADD(FixedMemoryHashTest::InsertEndTest);
		TEST_ADD(FixedMemoryHashTest::RetrieveEndTest);
	}
	~FixedMemoryHashTest() {
		delete[] data_;
	}

   private:
	void InitTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_, 72000, 190000);
		TEST_ASSERT(!hash.exists(1001));
		TEST_ASSERT(hash.size() == 0);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(hash.empty());
	}

	void LoadTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		TEST_ASSERT(!hash.exists(1001));
		TEST_ASSERT(hash.size() == 0);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(hash.empty());
	}

	void InsertTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		EQ::ItemData item;
		memset(&item, 0, sizeof(item));
		strcpy(item.Name, "Iron Sword");
		item.ID = 1001;
		hash.insert(1001, item);

		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.size() == 1);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());
	}

	void RetrieveTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.size() == 1);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());

		EQ::ItemData item = hash[1001];
		TEST_ASSERT(strcmp(item.Name, "Iron Sword") == 0);
		TEST_ASSERT(item.ID == 1001);
	}

	void OverwriteTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		EQ::ItemData item;
		memset(&item, 0, sizeof(item));
		strcpy(item.Name, "Steel Sword");
		item.ID = 1001;
		hash.insert(1001, item);

		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.size() == 1);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());
	}

	void OverwriteRetrieveTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.size() == 1);
		TEST_ASSERT((hash.max_size() == 72000));
		TEST_ASSERT(!hash.empty());

		EQ::ItemData item = hash[1001];
		TEST_ASSERT(strcmp(item.Name, "Steel Sword") == 0);
		TEST_ASSERT(item.ID == 1001);
	}

	void InsertAgainTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		EQ::ItemData item;
		memset(&item, 0, sizeof(item));
		strcpy(item.Name, "Iron Sword");
		item.ID = 1000;
		hash.insert(1000, item);

		TEST_ASSERT(hash.exists(1000));
		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.size() == 2);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());
	}

	void RetrieveAgainTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		TEST_ASSERT(hash.exists(1000));
		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.size() == 2);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());

		EQ::ItemData item = hash[1000];
		TEST_ASSERT(strcmp(item.Name, "Iron Sword") == 0);
		TEST_ASSERT(item.ID == 1000);

		item = hash[1001];
		TEST_ASSERT(strcmp(item.Name, "Steel Sword") == 0);
		TEST_ASSERT(item.ID == 1001);
	}

	void InsertBeginTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		EQ::ItemData item;
		memset(&item, 0, sizeof(item));
		strcpy(item.Name, "Bronze Sword");
		item.ID = 0;
		hash.insert(0, item);

		TEST_ASSERT(hash.exists(1000));
		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.exists(0));
		TEST_ASSERT(hash.size() == 3);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());
	}

	void RetrieveBeginTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		TEST_ASSERT(hash.exists(1000));
		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.exists(0));
		TEST_ASSERT(hash.size() == 3);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());

		EQ::ItemData item = hash[1000];
		TEST_ASSERT(strcmp(item.Name, "Iron Sword") == 0);
		TEST_ASSERT(item.ID == 1000);

		item = hash[1001];
		TEST_ASSERT(strcmp(item.Name, "Steel Sword") == 0);
		TEST_ASSERT(item.ID == 1001);

		item = hash[0];
		TEST_ASSERT(strcmp(item.Name, "Bronze Sword") == 0);
		TEST_ASSERT(item.ID == 0);
	}

	void InsertEndTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		EQ::ItemData item;
		memset(&item, 0, sizeof(item));
		strcpy(item.Name, "Jade Sword");
		item.ID = 190000;
		hash.insert(190000, item);

		TEST_ASSERT(hash.exists(1000));
		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.exists(0));
		TEST_ASSERT(hash.exists(190000));
		TEST_ASSERT(hash.size() == 4);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());
	}

	void RetrieveEndTest() {
		EQ::FixedMemoryHashSet<EQ::ItemData> hash(data_, size_);
		TEST_ASSERT(hash.exists(1000));
		TEST_ASSERT(hash.exists(1001));
		TEST_ASSERT(hash.exists(0));
		TEST_ASSERT(hash.exists(190000));
		TEST_ASSERT(hash.size() == 4);
		TEST_ASSERT(hash.max_size() == 72000);
		TEST_ASSERT(!hash.empty());

		EQ::ItemData item = hash[1000];
		TEST_ASSERT(strcmp(item.Name, "Iron Sword") == 0);
		TEST_ASSERT(item.ID == 1000);

		item = hash[1001];
		TEST_ASSERT(strcmp(item.Name, "Steel Sword") == 0);
		TEST_ASSERT(item.ID == 1001);

		item = hash[0];
		TEST_ASSERT(strcmp(item.Name, "Bronze Sword") == 0);
		TEST_ASSERT(item.ID == 0);

		item = hash[190000];
		TEST_ASSERT(strcmp(item.Name, "Jade Sword") == 0);
		TEST_ASSERT(item.ID == 190000);
	}

   private:
	uint8 *data_;
	size_t size_;
};

#endif
