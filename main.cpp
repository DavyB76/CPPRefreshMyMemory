#include <iostream>

#define BOOST_TEST_MODULE My Test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(first_test)
{
    int i = 5;
    BOOST_TEST(i);
    BOOST_TEST(i == 5);
}

BOOST_AUTO_TEST_CASE(second_test)
{
    int i = 2;
    BOOST_TEST(i);
    BOOST_TEST(i == 2);
}

template <typename T>
struct ListNode
{
    T data;

    std::shared_ptr<ListNode<T>> next;

    ListNode() : next(nullptr)
    {}

    ListNode(T _data) : data(_data), next(nullptr)
    {}
};

BOOST_AUTO_TEST_CASE(first_list_test)
{
    auto firstNode = std::make_shared<ListNode<int>>(5);

    BOOST_TEST(firstNode->data == 5);
}

BOOST_AUTO_TEST_CASE(should_insert_second_item_when_second_item_is_inserted)
{
    auto headNode = std::make_shared<ListNode<int>>((1));
    auto secondNode = std::make_shared<ListNode<int>>((1));

    headNode->next = secondNode;
}

std::shared_ptr<ListNode<int>>
MergeTwoLists(std::shared_ptr<ListNode<int>> firstList, std::shared_ptr<ListNode<int>> secondList) {

    std::shared_ptr<ListNode<int>> dummyHeadNode(new ListNode<int>());
    auto tail = dummyHeadNode;

    auto currentFirstListNode = firstList;
    auto currentSecondListNode = secondList;

    while(currentFirstListNode != nullptr && currentSecondListNode != nullptr)
    {
        if(currentFirstListNode->data <= currentSecondListNode->data)
        {
            tail->next = currentFirstListNode;
            currentFirstListNode = currentFirstListNode->next;
            tail = tail->next;
        } else
        {
            tail->next = currentSecondListNode;
            currentSecondListNode = currentSecondListNode->next;
            tail = tail->next;
        }
    }

    if(currentFirstListNode != nullptr)
    {
        tail->next = currentFirstListNode;
    }

    if(currentSecondListNode != nullptr)
    {
        tail->next = currentSecondListNode;
    }

    return dummyHeadNode->next;
}

BOOST_AUTO_TEST_CASE(should_return_sorted_two_element_list_when_two_one_onde_list_are_merged)
{
    auto firstList = std::make_shared<ListNode<int>>((5));
    auto secondList = std::make_shared<ListNode<int>>((8));

    auto mergedList = MergeTwoLists(firstList, secondList);

    BOOST_TEST(mergedList->data == 5);
    BOOST_TEST(mergedList->next->data == 8);
}

BOOST_AUTO_TEST_CASE(should_return_sorted_list_when_first_list_contains_two_elements_and_second_list_contains_one_element_in_the_middle)
{
    auto firstList = std::make_shared<ListNode<int>>((5));
    firstList->next = std::make_shared<ListNode<int>>((10));
    auto secondList = std::make_shared<ListNode<int>>((8));

    auto mergedList = MergeTwoLists(firstList, secondList);

    BOOST_TEST(mergedList->data == 5);
    BOOST_TEST(mergedList->next->data == 8);
    BOOST_TEST(mergedList->next->next->data == 10);
}

BOOST_AUTO_TEST_CASE(should_return_sorted_list_when_first_list_contains_two_elements_and_second_list_contains_two_elements_in_the_middle)
{
    auto firstList = std::make_shared<ListNode<int>>((5));
    firstList->next = std::make_shared<ListNode<int>>((10));
    auto secondList = std::make_shared<ListNode<int>>((8));
    secondList->next = std::make_shared<ListNode<int>>((12));

    auto mergedList = MergeTwoLists(firstList, secondList);

    BOOST_TEST(mergedList->data == 5);
    BOOST_TEST(mergedList->next->data == 8);
    BOOST_TEST(mergedList->next->next->data == 10);
    BOOST_TEST(mergedList->next->next->next->data == 12);
}
