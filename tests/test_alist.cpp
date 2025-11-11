#include "../include/AList.h"
#include <gtest/gtest.h>

TEST(AListTest, DefaultConstruction)
{
    AList<int> list;
    EXPECT_EQ(list.length(), 0);
}

TEST(AListTest, InsertSingleElement)
{
    AList<int> list;
    list.insert(42);
    EXPECT_EQ(list.length(), 1);
    EXPECT_EQ(list.getValue(), 42);
}

TEST(AListTest, InsertMultipleElements)
{
    AList<int> list;
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

TEST(AListTest, RemoveSingleElement)
{
    AList<int> list;
    list.insert(42);
    int removed = list.remove();
    EXPECT_EQ(removed, 42);
    EXPECT_EQ(list.length(), 0);
}

TEST(AListTest, RemoveFromEmptyListThrows)
{
    AList<int> list;
    EXPECT_THROW(list.remove(), std::out_of_range);
}
