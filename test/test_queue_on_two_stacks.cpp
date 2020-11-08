#include "StackQueue.h"

#include <gtest.h>

TEST(QueueOnTwoStacks, can_create_queue_on_two_stacks_with_positive_length)
{
	ASSERT_NO_THROW(QueueOnTwoStacks<int> q(5));
}

TEST(QueueOnTwoStacks, can_return_front_element_from_queue_on_two_stacks) {
	QueueOnTwoStacks<int> q;
	q.push(1);
	EXPECT_EQ(1, q.Front());
}

TEST(QueueOnTwoStacks, can_return_back_element_from_queue_on_two_stacks) {
	QueueOnTwoStacks<int> q;
	q.push(2);
	ASSERT_NO_THROW(q.pop());
}

TEST(QueueOnTwoStacks, cant_do_pop_when_queue_is_empty) {
	QueueOnTwoStacks<int> q;
	ASSERT_ANY_THROW(q.pop());
}

TEST(QueueOnTwoStacks, return_true_when_queue_is_empty) {
	QueueOnTwoStacks<int> q;
	EXPECT_EQ(true, q.empty());
}

TEST(QueueOnTwoStacks, return_false_when_queue_isnt_empty) {
	QueueOnTwoStacks<int> q;
	q.push(1);
	EXPECT_EQ(false, q.empty());
}

TEST(QueueOnTwoStacks, return_true_when_queue_is_full) {
	QueueOnTwoStacks<int> q;
	EXPECT_EQ(true, q.full());
}

TEST(QueueOnTwoStacks, return_false_when_queue_isnt_full) {
	QueueOnTwoStacks<int> q(10);
	q.push(1);
	EXPECT_EQ(false, q.full());
}

TEST(QueueOnTwoStacks, return_size_of_stack) {
	QueueOnTwoStacks<int> q;
	q.push(1);
	EXPECT_EQ(1, q.GetSize());
}


 