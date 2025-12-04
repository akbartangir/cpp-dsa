#include "../include/Vector.h"
#include <gtest/gtest.h>
#include <string>

// Construction Tests
TEST(VectorTest, DefaultConstruction)
{
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, ConstructionWithInitialCapacity)
{
    Vector<int> vec(10);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, ConstructionWithCountAndValue)
{
    Vector<int> vec(5, 42);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_FALSE(vec.empty());

    for (size_t i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], 42);
    }
}

TEST(VectorTest, CopyConstructor)
{
    Vector<int> original(3, 10);
    Vector<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.capacity(), original.capacity());

    for (size_t i = 0; i < original.size(); ++i)
    {
        EXPECT_EQ(copy[i], original[i]);
    }

    // Verify deep copy
    copy[0] = 99;
    EXPECT_NE(copy[0], original[0]);
}

TEST(VectorTest, CopyAssignment)
{
    Vector<int> original(3, 10);
    Vector<int> copy;

    copy = original;

    EXPECT_EQ(copy.size(), original.size());
    for (size_t i = 0; i < original.size(); ++i)
    {
        EXPECT_EQ(copy[i], original[i]);
    }

    // Verify deep copy
    copy[1] = 88;
    EXPECT_NE(copy[1], original[1]);
}

TEST(VectorTest, MoveConstructor)
{
    Vector<int> original(3, 10);
    size_t originalSize = original.size();

    Vector<int> moved(std::move(original));

    EXPECT_EQ(moved.size(), originalSize);
    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.capacity(), 0);
}

TEST(VectorTest, MoveAssignment)
{
    Vector<int> original(3, 10);
    size_t originalSize = original.size();

    Vector<int> moved;
    moved = std::move(original);

    EXPECT_EQ(moved.size(), originalSize);
    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.capacity(), 0);
}

// Element Access Tests
TEST(VectorTest, OperatorBracket)
{
    Vector<int> vec(3, 0);
    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;

    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
}

TEST(VectorTest, OperatorBracketConst)
{
    const Vector<int> vec(3, 42);
    EXPECT_EQ(vec[0], 42);
    EXPECT_EQ(vec[2], 42);
}

TEST(VectorTest, AtWithValidIndex)
{
    Vector<int> vec(3, 0);
    vec.at(0) = 10;
    vec.at(1) = 20;

    EXPECT_EQ(vec.at(0), 10);
    EXPECT_EQ(vec.at(1), 20);
}

TEST(VectorTest, AtWithInvalidIndexThrows)
{
    Vector<int> vec(3, 0);
    EXPECT_THROW(vec.at(3), std::out_of_range);
    EXPECT_THROW(vec.at(100), std::out_of_range);
}

TEST(VectorTest, Front)
{
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);

    EXPECT_EQ(vec.front(), 10);
    vec.front() = 99;
    EXPECT_EQ(vec.front(), 99);
}

TEST(VectorTest, FrontOnEmptyVectorThrows)
{
    Vector<int> vec;
    EXPECT_THROW(vec.front(), std::out_of_range);
}

TEST(VectorTest, Back)
{
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);

    EXPECT_EQ(vec.back(), 20);
    vec.back() = 99;
    EXPECT_EQ(vec.back(), 99);
}

TEST(VectorTest, BackOnEmptyVectorThrows)
{
    Vector<int> vec;
    EXPECT_THROW(vec.back(), std::out_of_range);
}

TEST(VectorTest, Data)
{
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);

    int* ptr = vec.data();
    EXPECT_EQ(ptr[0], 10);
    EXPECT_EQ(ptr[1], 20);
}

// Iterator Tests
TEST(VectorTest, Iterators)
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    int sum = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(VectorTest, ConstIterators)
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    int sum = 0;
    for (auto it = vec.cbegin(); it != vec.cend(); ++it)
    {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(VectorTest, RangeBasedForLoop)
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    int sum = 0;
    for (int val : vec)
    {
        sum += val;
    }
    EXPECT_EQ(sum, 6);
}

// Capacity Tests
TEST(VectorTest, Empty)
{
    Vector<int> vec;
    EXPECT_TRUE(vec.empty());

    vec.push_back(1);
    EXPECT_FALSE(vec.empty());

    vec.pop_back();
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, Size)
{
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);

    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);

    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
}

TEST(VectorTest, Reserve)
{
    Vector<int> vec;
    vec.reserve(100);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_GE(vec.capacity(), 100);
}

TEST(VectorTest, ReserveDoesNotShrink)
{
    Vector<int> vec;
    vec.reserve(100);
    size_t cap = vec.capacity();

    vec.reserve(50);
    EXPECT_EQ(vec.capacity(), cap);
}

TEST(VectorTest, ShrinkToFit)
{
    Vector<int> vec;
    vec.reserve(100);
    vec.push_back(1);
    vec.push_back(2);

    vec.shrink_to_fit();
    EXPECT_EQ(vec.capacity(), vec.size());
}

// Modifier Tests
TEST(VectorTest, PushBackCopy)
{
    Vector<int> vec;
    int value = 42;

    vec.push_back(value);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 42);
}

TEST(VectorTest, PushBackMove)
{
    Vector<std::string> vec;
    std::string str = "hello";

    vec.push_back(std::move(str));
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "hello");
}

TEST(VectorTest, PushBackMultiple)
{
    Vector<int> vec;
    for (int i = 0; i < 100; ++i)
    {
        vec.push_back(i);
    }

    EXPECT_EQ(vec.size(), 100);
    for (int i = 0; i < 100; ++i)
    {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(VectorTest, PopBack)
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, PopBackOnEmptyThrows)
{
    Vector<int> vec;
    EXPECT_THROW(vec.pop_back(), std::out_of_range);
}

TEST(VectorTest, Clear)
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    size_t cap = vec.capacity();

    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), cap);
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, ResizeGrow)
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    vec.resize(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 0);
}

TEST(VectorTest, ResizeShrink)
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec.resize(1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, Swap)
{
    Vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    Vector<int> vec2;
    vec2.push_back(10);
    vec2.push_back(20);
    vec2.push_back(30);

    vec1.swap(vec2);

    EXPECT_EQ(vec1.size(), 3);
    EXPECT_EQ(vec1[0], 10);

    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
}

// Edge Cases
TEST(VectorTest, LargeVector)
{
    Vector<int> vec;
    const size_t largeSize = 10000;

    for (size_t i = 0; i < largeSize; ++i)
    {
        vec.push_back(static_cast<int>(i));
    }

    EXPECT_EQ(vec.size(), largeSize);
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec[largeSize - 1], static_cast<int>(largeSize - 1));
}

TEST(VectorTest, WithComplexType)
{
    Vector<std::string> vec;
    vec.push_back("hello");
    vec.push_back("world");

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], "hello");
    EXPECT_EQ(vec[1], "world");
}
