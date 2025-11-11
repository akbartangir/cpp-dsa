#include "../include/LList.h"
#include <gtest/gtest.h>

TEST(LListTest, DefaultConstruction)
{
    LList<int> list;
    EXPECT_EQ(list.length(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(LListTest, InsertSingleElement)
{
    LList<int> list;
    list.insert(42);
    EXPECT_EQ(list.length(), 1);
    EXPECT_EQ(list.getValue(), 42);
}

TEST(LListTest, InsertMultipleElements)
{
    LList<int> list;
    list.insert(3);
    list.insert(2);
    list.insert(1);

    EXPECT_EQ(list.length(), 3);

    list.moveToStart();
    EXPECT_EQ(list.getValue(), 1);

    list.next();
    EXPECT_EQ(list.getValue(), 2);

    list.next();
    EXPECT_EQ(list.getValue(), 3);
}

TEST(LListTest, AppendElements)
{
    LList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    EXPECT_EQ(list.length(), 3);

    list.moveToStart();
    EXPECT_EQ(list.getValue(), 1);

    list.next();
    EXPECT_EQ(list.getValue(), 2);

    list.next();
    EXPECT_EQ(list.getValue(), 3);
}

TEST(LListTest, RemoveSingleElement)
{
    LList<int> list;
    list.insert(42);
    int removed = list.remove();
    EXPECT_EQ(removed, 42);
    EXPECT_EQ(list.length(), 0);
}

TEST(LListTest, RemoveFromEmptyListThrows)
{
    LList<int> list;
    EXPECT_THROW(list.remove(), std::out_of_range);
}

TEST(LListTest, MoveToPos)
{
    LList<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.append(i);
    }

    list.moveToPos(2);
    EXPECT_EQ(list.getValue(), 2);
    EXPECT_EQ(list.currPos(), 2);

    list.moveToPos(0);
    EXPECT_EQ(list.getValue(), 0);

    list.moveToPos(4);
    EXPECT_EQ(list.getValue(), 4);
}

TEST(LListTest, PrevAndNext)
{
    LList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    list.moveToStart();
    EXPECT_EQ(list.getValue(), 1);

    list.next();
    EXPECT_EQ(list.getValue(), 2);

    list.prev();
    EXPECT_EQ(list.getValue(), 1);

    // Should not go before start
    list.prev();
    EXPECT_EQ(list.currPos(), 0);
}

TEST(LListTest, CopyConstructor)
{
    LList<int> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);

    LList<int> list2(list1);

    EXPECT_EQ(list2.length(), 3);
    list2.moveToStart();
    EXPECT_EQ(list2.getValue(), 1);
    list2.next();
    EXPECT_EQ(list2.getValue(), 2);
    list2.next();
    EXPECT_EQ(list2.getValue(), 3);
}

TEST(LListTest, MoveConstructor)
{
    LList<int> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);

    LList<int> list2(std::move(list1));

    EXPECT_EQ(list2.length(), 3);
    EXPECT_EQ(list1.length(), 0); // Moved-from list should be empty

    list2.moveToStart();
    EXPECT_EQ(list2.getValue(), 1);
}

TEST(LListTest, CopyAssignment)
{
    LList<int> list1;
    list1.append(1);
    list1.append(2);

    LList<int> list2;
    list2.append(9);

    list2 = list1;

    EXPECT_EQ(list2.length(), 2);
    list2.moveToStart();
    EXPECT_EQ(list2.getValue(), 1);
    list2.next();
    EXPECT_EQ(list2.getValue(), 2);
}

TEST(LListTest, MoveAssignment)
{
    LList<int> list1;
    list1.append(1);
    list1.append(2);

    LList<int> list2;
    list2.append(9);

    list2 = std::move(list1);

    EXPECT_EQ(list2.length(), 2);
    EXPECT_EQ(list1.length(), 0); // Moved-from list should be empty

    list2.moveToStart();
    EXPECT_EQ(list2.getValue(), 1);
}

TEST(LListTest, Clear)
{
    LList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    EXPECT_EQ(list.length(), 3);

    list.clear();

    EXPECT_EQ(list.length(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(LListTest, MoveToEnd)
{
    LList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    list.moveToEnd();
    EXPECT_EQ(list.currPos(), 3);

    // At end, getValue should throw
    EXPECT_THROW(list.getValue(), std::out_of_range);
}

TEST(LListTest, InvalidPositionThrows)
{
    LList<int> list;
    list.append(1);
    list.append(2);

    EXPECT_THROW(list.moveToPos(5), std::out_of_range);
}
