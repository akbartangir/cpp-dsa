
#include <gtest/gtest.h>
#include "../include/linked_list.h"

TEST(LinkedListTest, PushFrontAndBack)
{
    LinkedList list;
    EXPECT_TRUE(list.empty());
    list.push_front(1);
    EXPECT_FALSE(list.empty());
    list.push_back(2);
    list.push_front(0);
    EXPECT_FALSE(list.empty());
}

TEST(LinkedListTest, PopFrontAndBack)
{
    LinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.pop_front(); // removes 1
    list.pop_back();  // removes 3
    list.pop_back();  // removes 2
    EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, PrintDoesNotCrash)
{
    LinkedList list;
    list.push_back(42);
    // Capture stdout to ensure print outputs as expected
    testing::internal::CaptureStdout();
    list.print(); // Should print "42\n"
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "42 \n");
}

TEST(LinkedListTest, PrintEmptyList)
{
    LinkedList list;
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\n");
}

TEST(LinkedListTest, OrderAfterPushes)
{
    LinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    list.push_back(3);
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "0 1 2 3 \n");
}

TEST(LinkedListTest, PopOnEmptyDoesNotCrash)
{
    LinkedList list;
    EXPECT_TRUE(list.empty());
    // Should be no crash and still empty
    list.pop_front();
    EXPECT_TRUE(list.empty());
    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, InterleavedOperationsMaintainCorrectEnds)
{
    LinkedList list;
    // Build: [1]
    list.push_back(1);
    // [0, 1]
    list.push_front(0);
    // [0, 1, 2]
    list.push_back(2);
    // pop_front -> [1, 2]
    list.pop_front();
    // push_front -> [0, 1, 2]
    list.push_front(0);
    // pop_back -> [0, 1]
    list.pop_back();

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "0 1 \n");
}

// No custom main(): we link with GTest::gtest_main provided by CMake
