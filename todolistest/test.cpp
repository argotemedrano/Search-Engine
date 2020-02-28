#include "../todolist.h"
#include "gtest/gtest.h"
#include <string>

class TodoListTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	TodoListTest() {
		// You can do set-up work for each test here.
	}

	virtual ~TodoListTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).

	}

	// Objects declared here can be used by all tests in the test case.
	DailyTodoList list;
};

TEST_F(TodoListTest, BasicConstructor) {
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(true, list.empty(0));
	EXPECT_EQ(0, list.numPriorityItems());

	for (size_t i = 0; i < list.numDays(); i++) {
		EXPECT_EQ(true, list.empty(i));
	}

	// Catch Exceptions
}
TEST_F(TodoListTest, InsertionNominal)   {
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(true, list.empty(0));
	EXPECT_EQ(0, list.numPriorityItems());
	for (size_t i = 0; i < list.numDays(); i++) {
		EXPECT_EQ(0, list.numItemsOnDay(i));
	}

	// Resize
	list.insert(6, 0, "6b", false);
    // 6b -> NULL
    // Priorty : NULL
	EXPECT_EQ(1, list.numItemsOnDay(6));
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(12, list.numDays());
	EXPECT_EQ("6b", list.getNormalVal(6, 0));
	EXPECT_EQ(false, list.empty(6));

	// Insert back
    list.push_back(6, "6c", false);
    // 6b -> 6c -> NULL
    // Priority: NULL 
	EXPECT_EQ(2, list.numItemsOnDay(6));
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(12, list.numDays());
	EXPECT_EQ("6b", list.getNormalVal(6, 0));
	EXPECT_EQ("6c", list.getNormalVal(6, 1));
	EXPECT_EQ(false, list.empty(6));


	// Insert Beginning
    list.insert(6, 0, "6a", false); 
    // 6a -> 6b -> 6c -> NULL
	// Priority: NULL
	EXPECT_EQ(3, list.numItemsOnDay(6));
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(12, list.numDays());
	EXPECT_EQ("6a", list.getNormalVal(6, 0));
	EXPECT_EQ("6b", list.getNormalVal(6, 1));
	EXPECT_EQ("6c", list.getNormalVal(6, 2));
	EXPECT_EQ(false, list.empty(6));

	// Insert End
    list.insert(6, 3, "6d", false); 
    // 6a -> 6b -> 6c -> 6d
    // Priority: NULL
	EXPECT_EQ(4, list.numItemsOnDay(6));
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(12, list.numDays());
	EXPECT_EQ("6a", list.getNormalVal(6, 0));
	EXPECT_EQ("6b", list.getNormalVal(6, 1));
	EXPECT_EQ("6c", list.getNormalVal(6, 2));
	EXPECT_EQ("6d", list.getNormalVal(6, 3));
	EXPECT_EQ(false, list.empty(6));

	// Insert middle
	list.insert(6, 2, "6e", false);
	// 6a -> 6b -> 6e -> 6c -> 6d
	// Priority: NULL
	EXPECT_EQ(5, list.numItemsOnDay(6));
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(12, list.numDays());
	EXPECT_EQ("6a", list.getNormalVal(6, 0));
	EXPECT_EQ("6b", list.getNormalVal(6, 1));
	EXPECT_EQ("6e", list.getNormalVal(6, 2));
	EXPECT_EQ("6c", list.getNormalVal(6, 3));
	EXPECT_EQ("6d", list.getNormalVal(6, 4));
	EXPECT_EQ(false, list.empty(6));
}

TEST_F(TodoListTest, RemovalNominal) {
	
	// Given Day 0: 1 -> 2 -> 3 -> 4 -> 5
	for (char i = '1'; i <= '5'; i++) {
		std::string s = std::string();
		s = i;
		list.push_back(0, s, false);
	}
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(5, list.numItemsOnDay(0));
	EXPECT_EQ(false, list.empty(0));
	for (int i = 0; i < 5; i++) {
		std::string s = std::string();
		s = ((char)('1' + i));
		EXPECT_EQ(s, list.getNormalVal(0, i));
	}

	// Remove front
	list.remove(0, 0);
	// 2 -> 3 -> 4 -> 5
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(4, list.numItemsOnDay(0));
	EXPECT_EQ(false, list.empty(0));
	for (int i = 0; i < 4; i++) {
		std::string s = std::string();
		s = ((char)('2' + i));
		EXPECT_EQ(s, list.getNormalVal(0, i));	
	}

	// Remove middle
	list.remove(0, 1);
	// 2 -> 4 -> 5
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(3, list.numItemsOnDay(0));
	EXPECT_EQ(false, list.empty(0));

	EXPECT_EQ("2", list.getNormalVal(0, 0));
	EXPECT_EQ("4", list.getNormalVal(0, 1));
	EXPECT_EQ("5", list.getNormalVal(0, 2));


	// Remove end
	list.remove(0, 2);
	// 2 -> 4
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(2, list.numItemsOnDay(0));
	EXPECT_EQ(false, list.empty(0));

	EXPECT_EQ("2", list.getNormalVal(0, 0));
	EXPECT_EQ("4", list.getNormalVal(0, 1));

	// Remove until empty
	list.remove(0, 1); // 2 -> NULL
	list.remove(0, 0); // NULL
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(0, list.numPriorityItems());
	EXPECT_EQ(0, list.numItemsOnDay(0));
	EXPECT_EQ(true, list.empty(0));
}

TEST_F(TodoListTest, PriorityAddition) {
	EXPECT_EQ(0, list.numPriorityItems());

	list.insert(6, 0, "6b", false);
    // 6b -> NULL (cout: 6b)
    // Priorty : NULL (cout:)
	EXPECT_EQ(0, list.numPriorityItems());

    list.push_back(6, "6c", true);
    // 6b -> 6c -> NULL (cout: 6b -> 6c)
    // Priority: 6c -> NULL (cout: 6c)
	EXPECT_EQ(1, list.numPriorityItems());
	EXPECT_EQ("6c", list.getPriorityVal(0));


    list.insert(6, 0, "6a", false); 
    // 6a -> 6b -> 6c -> NULL
	// Priority: 6c -> NULL
	EXPECT_EQ(1, list.numPriorityItems());
	EXPECT_EQ("6c", list.getPriorityVal(0));


    list.insert(6, 3, "6d", false); 
    // 6a -> 6b -> 6c -> 6d
    // Priority: 6c -> NULL
	EXPECT_EQ(1, list.numPriorityItems());
	EXPECT_EQ("6c", list.getPriorityVal(0));

    list.insert(2, 0, "2a", true); 
    // 2a -> NULL
    // Priority: 6c -> 2a -> NULL
	EXPECT_EQ(2, list.numPriorityItems());
	EXPECT_EQ("6c", list.getPriorityVal(0));
	EXPECT_EQ("2a", list.getPriorityVal(1));

    list.insert(14, 0, "14a", true); 
    // 14a -> NULL
    // Priority: 6c -> 2a -> 14a -> NULL
	EXPECT_EQ(3, list.numPriorityItems());
	EXPECT_EQ("6c", list.getPriorityVal(0));
	EXPECT_EQ("2a", list.getPriorityVal(1));
	EXPECT_EQ("14a", list.getPriorityVal(2));


    list.push_back(30, "30a", true); 
    // 30a -> NULL
    // Priority: 6c -> 2a -> 14a -> 30a -> NULL
	EXPECT_EQ(4, list.numPriorityItems());
	EXPECT_EQ("6c", list.getPriorityVal(0));
	EXPECT_EQ("2a", list.getPriorityVal(1));
	EXPECT_EQ("14a", list.getPriorityVal(2));
	EXPECT_EQ("30a", list.getPriorityVal(3));

}

TEST_F(TodoListTest, Resize) {
	// Given:
	// Day 0: 0a -> 0b -> NULL
	// Day 1: 1a -> NULL
	// Day 2: 2a -> 2b -> NULL
	// Day 3: 3a -> NULL
	// Day 4: 4a -> 4b -> 4c -> 4d -> NULL
	// Priority: 0a -> 1a -> 2b -> 0b -> 3a -> 4d -> NULL
	list.insert(0, 0, "0a", true); // 0a
	list.push_back(1, "1a", true); // 1a
	list.insert(2, 0, "2a", false); // 2a
	list.insert(2, 1, "2b", true); // 2a 2b
	list.push_back(0, "0b", true); // 0a 0b
	list.push_back(3, "3a", true); // 3a
	list.push_back(4, "4a", false); // 4a
	list.push_back(4, "4b", false); // 4a 4b
	list.push_back(4, "4c", false); // 4a 4b 4c
	list.push_back(4, "4d", true); // 4a 4b 4c 4d


	// Check normal todo
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(2, list.numItemsOnDay(0));
	EXPECT_EQ(1, list.numItemsOnDay(1));
	EXPECT_EQ(2, list.numItemsOnDay(2));
	EXPECT_EQ(1, list.numItemsOnDay(3));
	EXPECT_EQ(4, list.numItemsOnDay(4));

	// Check priority list
	EXPECT_EQ(6, list.numPriorityItems());
	EXPECT_EQ("0a", list.getPriorityVal(0));
	EXPECT_EQ("1a", list.getPriorityVal(1));
	EXPECT_EQ("2b", list.getPriorityVal(2));
	EXPECT_EQ("0b", list.getPriorityVal(3));
	EXPECT_EQ("3a", list.getPriorityVal(4));
	EXPECT_EQ("4d", list.getPriorityVal(5));

	list.push_back(9, "9a", true);
	// Given:
	// Day 0: 0a -> 0b -> NULL
	// Day 1: 1a -> NULL
	// Day 2: 2a -> 2b -> NULL
	// Day 3: 3a -> NULL
	// Day 4: 4a -> 4b -> 4c -> 4d -> NULL
	// Days 5-8: NULL
	// Day 9: 9a -> NULL
	// Priority: 0a -> 1a -> 2b -> 0b -> 3a -> 4d -> 9a -> NULL
	// Num Days: 2 * 9 = 18 (since 9 >= 5)

	// Check normal todo
	EXPECT_EQ(18, list.numDays());
	EXPECT_EQ(2, list.numItemsOnDay(0));
	EXPECT_EQ(1, list.numItemsOnDay(1));
	EXPECT_EQ(2, list.numItemsOnDay(2));
	EXPECT_EQ(1, list.numItemsOnDay(3));
	EXPECT_EQ(4, list.numItemsOnDay(4));
	EXPECT_EQ(1, list.numItemsOnDay(9));
	for (int i = 5; i <= 8; i++) {
		EXPECT_EQ(0, list.numItemsOnDay(i));
	}

	// Check priority list
	EXPECT_EQ(7, list.numPriorityItems());
	EXPECT_EQ("0a", list.getPriorityVal(0));
	EXPECT_EQ("1a", list.getPriorityVal(1));
	EXPECT_EQ("2b", list.getPriorityVal(2));
	EXPECT_EQ("0b", list.getPriorityVal(3));
	EXPECT_EQ("3a", list.getPriorityVal(4));
	EXPECT_EQ("4d", list.getPriorityVal(5));
	EXPECT_EQ("9a", list.getPriorityVal(6));

}

TEST_F(TodoListTest, PriorityRemoval) {
	// Given:
	// Day 0: 0a -> 0b -> NULL
	// Day 1: 1a -> NULL
	// Day 2: 2a -> 2b -> NULL
	// Day 3: 3a -> NULL
	// Day 4: 4a -> 4b -> 4c -> 4d -> NULL
	// Priority: 0a -> 1a -> 2b -> 0b -> 3a -> 4d -> NULL
	list.insert(0, 0, "0a", true); // 0a
	list.push_back(1, "1a", true); // 1a
	list.insert(2, 0, "2a", false); // 2a
	list.insert(2, 1, "2b", true); // 2a 2b
	list.push_back(0, "0b", true); // 0a 0b
	list.push_back(3, "3a", true); // 3a
	list.push_back(4, "4a", false); // 4a
	list.push_back(4, "4b", false); // 4a 4b
	list.push_back(4, "4c", false); // 4a 4b 4c
	list.push_back(4, "4d", true); // 4a 4b 4c 4d

	// Check normal todo
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(2, list.numItemsOnDay(0));
	EXPECT_EQ(1, list.numItemsOnDay(1));
	EXPECT_EQ(2, list.numItemsOnDay(2));
	EXPECT_EQ(1, list.numItemsOnDay(3));
	EXPECT_EQ(4, list.numItemsOnDay(4));

	// Check priority list
	EXPECT_EQ(6, list.numPriorityItems());
	EXPECT_EQ("0a", list.getPriorityVal(0));
	EXPECT_EQ("1a", list.getPriorityVal(1));
	EXPECT_EQ("2b", list.getPriorityVal(2));
	EXPECT_EQ("0b", list.getPriorityVal(3));
	EXPECT_EQ("3a", list.getPriorityVal(4));
	EXPECT_EQ("4d", list.getPriorityVal(5));
	
	// REMOVE OF MIDDLE OF PRIORITY LIST
	list.remove(2, 1); // 2a -> NULL
	// Check priority list:   0a -> 1a -> 0b -> 3a -> 4d -> NULL
	EXPECT_EQ(5, list.numPriorityItems());
	EXPECT_EQ("0a", list.getPriorityVal(0));
	EXPECT_EQ("1a", list.getPriorityVal(1));
	EXPECT_EQ("0b", list.getPriorityVal(2));
	EXPECT_EQ("3a", list.getPriorityVal(3));
	EXPECT_EQ("4d", list.getPriorityVal(4));

	// REMOVE FORM FRONT OF PRIORITY LIST
	list.remove(0, 0); // 0b -> NULL (Removed 0a)
	// Check priority list:   1a -> 0b -> 3a -> 4d -> NULL
	EXPECT_EQ(4, list.numPriorityItems());
	EXPECT_EQ("1a", list.getPriorityVal(0));
	EXPECT_EQ("0b", list.getPriorityVal(1));
	EXPECT_EQ("3a", list.getPriorityVal(2));
	EXPECT_EQ("4d", list.getPriorityVal(3));

	// REMOVE FROM END OF PRIORITY LIST
	list.remove(4, 3); // 4a -> 4b -> 4c -> NULL (removed 4d)
	// Check priority list:   1a -> 0b -> 3a -> NULL
	EXPECT_EQ(3, list.numPriorityItems());
	EXPECT_EQ("1a", list.getPriorityVal(0));
	EXPECT_EQ("0b", list.getPriorityVal(1));
	EXPECT_EQ("3a", list.getPriorityVal(2));

	// REMOVE FROM PRIORITY LIST UNTIL EMPTY
	list.remove(1, 0); // NULL (Day 1)
	list.remove(0, 0); // NULL (Day 0)
	list.remove(3, 0); // NULL (Day 3)
	EXPECT_EQ(0, list.numPriorityItems());
}	


/*
// bad_alloc
TEST_F(TodoListTest, PushBackExceptions) {
	// numDays: 5
	// 
} */


// bad_alloc, out_of_range
TEST_F(TodoListTest, InsertExceptions) {
	// numDays: 5

	// Invalid loc
	for (size_t i = 0; i < list.numDays(); i++) {
		EXPECT_THROW(list.insert(i, 1, "shoud fail", false), std::out_of_range); // Out of bounds
		EXPECT_THROW(list.insert(i, -1, "shoud fail", false), std::out_of_range); // Neg

	}

	// Nothing changed after exception thrown
	EXPECT_EQ(5, list.numDays());
	EXPECT_EQ(true, list.empty(0));
	EXPECT_EQ(0, list.numPriorityItems());

	// Invalid day: Neg value passed for day
	//EXPECT_THROW(list.insert(-1, 0), "should fail?", false), std::out_of_range);

	// Add a few days
	list.insert(12, 0, "a", false);
	list.remove(12, 0); // 24 days now: ALL LISTS ARE EMPTY
	EXPECT_EQ(24, list.numDays());
	EXPECT_EQ(true, list.empty(0));
	EXPECT_EQ(0, list.numPriorityItems());

	for (size_t i = 0; i <  list.numDays(); i++) {
		EXPECT_THROW(list.insert(i, 1, "shoud fail", false), std::out_of_range); // Out of bounds
		EXPECT_THROW(list.insert(i, -1, "shoud fail", false), std::out_of_range); // Neg

	}

	// Nothing changed after exception thrown
	EXPECT_EQ(24, list.numDays());
	EXPECT_EQ(true, list.empty(0));
	EXPECT_EQ(0, list.numPriorityItems());

	for (size_t i = 0; i < list.numDays(); i++) {
		EXPECT_EQ(true, list.empty(i));
	}

	// Invald day and 
	EXPECT_THROW(list.insert(100, 1, "should fail", false), std::out_of_range);

}


// out_of_range
TEST_F(TodoListTest, RemovalExceptions) {
	/* INVALID LOCATION */
	// Empty list
	EXPECT_THROW(try {
		list.remove(0, 0);
	} catch (std::exception& e) {
		EXPECT_STREQ("Cannot remove items on an empty list", e.what());
		throw;
	}, std::out_of_range);

	// Empty list: loc out of bounds
	EXPECT_THROW(try {
		list.remove(0, 1);
	} catch (std::exception& e) {
		EXPECT_STREQ("Cannot remove items on an empty list", e.what());
		throw;
	}, std::out_of_range);

	// Empty list: Negative loc
	EXPECT_THROW(try {
		list.remove(0, -1);
	} catch (std::exception& e) {
		EXPECT_STREQ("Cannot remove items on an empty list", e.what());
		throw;
	}, std::out_of_range);

	EXPECT_THROW(list.remove(0, 1), std::out_of_range); // Out of bounds
	EXPECT_THROW(list.remove(0, -1), std::out_of_range); // Neg

	// With Items
	list.push_back(0, "0a", false); // 0a -> NULL
	// With Items: out of bounds
	EXPECT_THROW(try { 
		list.remove(0, 1);
	} catch (std::exception& e) {
		EXPECT_STREQ("Invalid location", e.what());
		throw;
	}, std::out_of_range); 
	EXPECT_THROW(list.remove(0, 1), std::out_of_range); // Out of bounds

	// Negative loc
	EXPECT_THROW(try { 
		list.remove(0, -1);
	} catch (std::exception& e) {
		EXPECT_STREQ("Invalid location", e.what());
		throw;
	}, std::out_of_range); 
	EXPECT_THROW(list.remove(0, -1), std::out_of_range); // Neg

	// Invalid day: Day does not exist
	EXPECT_THROW(try { 
		list.remove(10, 0);
	} catch (std::exception& e) {
		EXPECT_STREQ("Invalid day index", e.what());
		throw;
	}, std::out_of_range); // Invalid day

	// INVALID DAY: Negative day
	EXPECT_THROW(try { 
		list.remove(-1, 0);
	} catch (std::exception& e) {
		EXPECT_STREQ("Invalid day index", e.what());
		throw;
	}, std::out_of_range); // Invalid day
}


// out_of_range
TEST_F(TodoListTest, numItemsOnDayExceptions) {
	// Days 0-4

	EXPECT_THROW(try {
		list.numItemsOnDay(5);
	} catch(std::exception& e) {
		EXPECT_STREQ("Invalid day index", e.what());
		throw;
	}, std::out_of_range);
}


// out_of_range
TEST_F(TodoListTest, EmptyExpctions) {
	// Days 0-4

	EXPECT_THROW(try {
		list.numItemsOnDay(5);
	} catch(std::exception& e) {
		EXPECT_STREQ("Invalid day index", e.what());
		throw;
	}, std::out_of_range);
}


// out_of_range
TEST_F(TodoListTest, getNormalValExpcetions) {
	// Valid day indexes: 0-4
	// Valid loc: NONE (all lists are empty)

	// Invalid: 5 >= index
	EXPECT_THROW(try {
		list.getNormalVal(5, 0);
	} catch(std::exception& e) {
		throw;
	}, std::out_of_range);

	// Invalid loc: 0
	// Invalid loc: positive (1)
	// Invald loc: negative (-1)
	for (size_t i = 0; i < list.numDays(); i++) {
		// 0
		EXPECT_THROW(try {
			list.getNormalVal(i, 0);
		} catch(std::exception& e) {
			throw;
		}, std::out_of_range);

		// 1
		EXPECT_THROW(try {
			list.getNormalVal(i, 1);
		} catch(std::exception& e) {
			throw;
		}, std::out_of_range);

		// -1
		EXPECT_THROW(try {
			list.getNormalVal(i, -1);
		} catch(std::exception& e) {
			throw;
		}, std::out_of_range);
	}

	// Valid days
	/* for (size_t i = 0; i < list.numDays(); i++) {
		EXPECT_NO_THROW();
	}*/
}


// out_of_range
TEST_F(TodoListTest, GetPriorityValExpcetions) {
	// Valid Priority Locs: NONE (no priority items)

	// Invalid: 0
	EXPECT_THROW(try {
			list.getPriorityVal(0);
		} catch(std::exception& e) {
			EXPECT_STREQ("Priority Location out of range", e.what());
			throw;
		}, std::out_of_range);

	// Invalid: Negative (-1)
	EXPECT_THROW(try {
			list.getPriorityVal(-1);
		} catch(std::exception& e) {
			EXPECT_STREQ("Priority Location out of range", e.what());
			throw;
		}, std::out_of_range);

	// Invalid: Out of Range (1)
	EXPECT_THROW(try {
			list.getPriorityVal(1);
		} catch(std::exception& e) {
			EXPECT_STREQ("Priority Location out of range", e.what());
			throw;
		}, std::out_of_range);
}