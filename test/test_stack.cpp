#include "stack.h"

#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> v(5));
}

TEST(Stack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(Stack<int> v(MAX_VECTOR_SIZE+1));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> v(-1));
}
 
TEST(Stack, can_return_top) {
	Stack<int> v(2);
	EXPECT_EQ(0,v.top());
}

TEST(Stack, can_push_element) {
	Stack<int> v(2);
	v.push(1);
	EXPECT_EQ(1, v.top());
}

TEST(Stack, push_change_size) {
	Stack<int> v(2);
	v.push(1);
	EXPECT_NE(2,v.GetSize());
}

TEST(Stack, can_do_pop) {
	Stack<int> v(1);
	v.pop();
	ASSERT_ANY_THROW(v[0]);
}

TEST(Stack, pop_change_size) {
	Stack<int> v(2);
	v.pop();
	EXPECT_NE(2, v.GetSize());
}

TEST(Stack, cant_do_pop_when_stack_is_empty) {
	Stack<int> v;
	ASSERT_ANY_THROW(v.pop());
}

TEST(Stack, return_true_when_stack_is_empty) {
	Stack<int> v;
	EXPECT_EQ(true,v.empty());
}

TEST(Stack, return_false_when_stack_isnt_empty) {
	Stack<int> v(1);
	EXPECT_EQ(false, v.empty());
}

TEST(Stack, return_true_when_stack_is_full) {
	Stack<int> v;
	EXPECT_EQ(true, v.full());
}

TEST(Stack, return_false_when_stack_isnt_full) {
	Stack<int> v(10);
	v.push(1);
	EXPECT_EQ(false, v.full());
}

 