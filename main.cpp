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

    ListNode(T _data, std::shared_ptr<ListNode<T>> nextNode) : data(_data), next(nextNode)
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


std::shared_ptr<ListNode<int>> InvertList(std::shared_ptr<ListNode<int>>& inputList, int beginIndex, int endIndex)
{
    auto dummy_head = std::make_shared<ListNode<int>>(ListNode<int>{0, inputList});
    auto sublist_head = dummy_head;
    int k =1;

    while(k++ < beginIndex)
    {
        sublist_head = sublist_head->next;
    }

    // Reverses sublist
    auto sublist_iter = sublist_head->next;
    while(beginIndex++ < endIndex)
    {
        auto temp = sublist_iter->next;
        sublist_iter->next = temp->next;
        temp->next = sublist_head->next;
        sublist_head->next = temp;
    }

    return dummy_head->next;
}

/*{
    auto index = 1;
    auto justBeforefirstNode = inputList;
    auto firstNode = inputList->next;

    while(index != beginIndex)
    {
        justBeforefirstNode = firstNode;
        firstNode = firstNode->next;
        index++;
    }

    std::shared_ptr<ListNode<int>> endList(new ListNode<int>());

    while(index != endIndex)
    {



        index++;
    }
    auto secondNode = firstNode->next;

    justBeforefirstNode->next = secondNode;
    justBeforefirstNode->next->next = firstNode;
}*/

BOOST_AUTO_TEST_CASE(should_return_inverted_items_when_a_two_item_list_is_to_be_inverted)
{
    auto firstNode = std::make_shared<ListNode<int>>((5));
    auto secondNode = std::make_shared<ListNode<int>>((8));
    firstNode->next = secondNode;

    std::shared_ptr<ListNode<int>> resultList = InvertList(firstNode, 1, 2);

    BOOST_TEST(resultList->data == 8);
    BOOST_TEST(resultList->next->data == 5);
}

BOOST_AUTO_TEST_CASE(should_return_inverted_items_when_a_three_item_list_is_to_be_inverted)
{
    auto firstNode = std::make_shared<ListNode<int>>((5));
    auto secondNode = std::make_shared<ListNode<int>>((8));
    auto thirdNode = std::make_shared<ListNode<int>>((3));
    firstNode->next = secondNode;
    secondNode->next = thirdNode;

    std::shared_ptr<ListNode<int>> resultList = InvertList(firstNode, 2, 3);

    BOOST_TEST(resultList->data == 5);
    BOOST_TEST(resultList->next->data == 3);
    BOOST_TEST(resultList->next->next->data == 8);
}

BOOST_AUTO_TEST_CASE(should_return_inverted_items_when_a_five_item_list_is_to_be_inverted)
{
    auto firstNode = std::make_shared<ListNode<int>>((11));
    auto secondNode = std::make_shared<ListNode<int>>((3));
    auto thirdNode = std::make_shared<ListNode<int>>((5));
    auto fourthNode = std::make_shared<ListNode<int>>((7));
    auto fifthNode = std::make_shared<ListNode<int>>((2));
    firstNode->next = secondNode;
    secondNode->next = thirdNode;
    thirdNode->next = fourthNode;
    fourthNode->next = fifthNode;

    std::shared_ptr<ListNode<int>> resultList = InvertList(firstNode, 2, 4);

    BOOST_TEST(resultList->data == 11);
    BOOST_TEST(resultList->next->data == 7);
    BOOST_TEST(resultList->next->next->data == 5);
    BOOST_TEST(resultList->next->next->next->data == 3);
    BOOST_TEST(resultList->next->next->next->next->data == 2);
}

BOOST_AUTO_TEST_CASE(should_return_inverted_items_when_a_ten_item_list_is_to_be_inverted)
{
    auto firstNode = std::make_shared<ListNode<int>>((1));
    auto secondNode = std::make_shared<ListNode<int>>((2));
    auto thirdNode = std::make_shared<ListNode<int>>((3));
    auto fourthNode = std::make_shared<ListNode<int>>((4));
    auto fifthNode = std::make_shared<ListNode<int>>((5));
    auto sixthNode = std::make_shared<ListNode<int>>((6));
    auto seventhNode = std::make_shared<ListNode<int>>((7));
    auto eigthNode = std::make_shared<ListNode<int>>((8));
    auto ninthNode = std::make_shared<ListNode<int>>((9));
    auto tenthNode = std::make_shared<ListNode<int>>((10));
    firstNode->next = secondNode;
    secondNode->next = thirdNode;
    thirdNode->next = fourthNode;
    fourthNode->next = fifthNode;
    fifthNode->next = sixthNode;
    sixthNode->next = seventhNode;
    seventhNode->next = eigthNode;
    eigthNode->next = ninthNode;
    ninthNode->next = tenthNode;

    std::shared_ptr<ListNode<int>> resultList = InvertList(firstNode, 2, 9);

    BOOST_TEST(resultList->data == 1);
    BOOST_TEST(resultList->next->data == 9);
    BOOST_TEST(resultList->next->next->data == 8);
    BOOST_TEST(resultList->next->next->next->data == 7);
    BOOST_TEST(resultList->next->next->next->next->data == 6);
    BOOST_TEST(resultList->next->next->next->next->next->data == 5);
    BOOST_TEST(resultList->next->next->next->next->next->next->data == 4);
    BOOST_TEST(resultList->next->next->next->next->next->next->next->data == 3);
    BOOST_TEST(resultList->next->next->next->next->next->next->next->next->data == 2);
    BOOST_TEST(resultList->next->next->next->next->next->next->next->next->next->data == 10);
}

void RemoveKthLatestNode(std::shared_ptr<ListNode<int>> inputList, int kthLastElementToRemove)
{
    auto TailDetector(inputList->next);

    int index = 1;
    while(index < kthLastElementToRemove)
    {
        TailDetector = TailDetector->next;
        index++;
    }

    auto KthLastNodePredessor(inputList);

    while(TailDetector->next != nullptr)
    {
        TailDetector = TailDetector->next;
        KthLastNodePredessor = KthLastNodePredessor->next;
    }

    KthLastNodePredessor->next = KthLastNodePredessor->next->next;
}

BOOST_AUTO_TEST_CASE(should_erase_kth_latest_items_when_a_three_item_list_is_processed)
{
    auto DummyHead = std::make_shared<ListNode<int>>(0);
    auto firstNode = std::make_shared<ListNode<int>>((1));
    auto secondNode = std::make_shared<ListNode<int>>((2));
    auto thirdNode = std::make_shared<ListNode<int>>((3));

    DummyHead->next = firstNode;
    firstNode->next = secondNode;
    secondNode->next = thirdNode;

    RemoveKthLatestNode(DummyHead, 2);

    BOOST_TEST(DummyHead->next->data == 1);
    BOOST_TEST(DummyHead->next->next->data == 3);
    BOOST_TEST(DummyHead->next->next->next == nullptr);
}

BOOST_AUTO_TEST_CASE(should_erase_kth_latest_items_when_a_ten_item_list_is_processed)
{
    auto DummyHead = std::make_shared<ListNode<int>>(0);
    auto firstNode = std::make_shared<ListNode<int>>((1));
    auto secondNode = std::make_shared<ListNode<int>>((2));
    auto thirdNode = std::make_shared<ListNode<int>>((3));
    auto fourthNode = std::make_shared<ListNode<int>>((4));
    auto fifthNode = std::make_shared<ListNode<int>>((5));
    auto sixthNode = std::make_shared<ListNode<int>>((6));
    auto seventhNode = std::make_shared<ListNode<int>>((7));
    auto eigthNode = std::make_shared<ListNode<int>>((8));
    auto ninthNode = std::make_shared<ListNode<int>>((9));
    auto tenthNode = std::make_shared<ListNode<int>>((10));
    DummyHead->next = firstNode;
    firstNode->next = secondNode;
    secondNode->next = thirdNode;
    thirdNode->next = fourthNode;
    fourthNode->next = fifthNode;
    fifthNode->next = sixthNode;
    sixthNode->next = seventhNode;
    seventhNode->next = eigthNode;
    eigthNode->next = ninthNode;
    ninthNode->next = tenthNode;

    RemoveKthLatestNode(DummyHead, 3);

    BOOST_TEST(DummyHead->next->data == 1);
    BOOST_TEST(DummyHead->next->next->data == 2);
    BOOST_TEST(DummyHead->next->next->next->data == 3);
    BOOST_TEST(DummyHead->next->next->next->next->data == 4);
    BOOST_TEST(DummyHead->next->next->next->next->next->data == 5);
    BOOST_TEST(DummyHead->next->next->next->next->next->next->data == 6);
    BOOST_TEST(DummyHead->next->next->next->next->next->next->next->data == 7);
    BOOST_TEST(DummyHead->next->next->next->next->next->next->next->next->data == 9);
    BOOST_TEST(DummyHead->next->next->next->next->next->next->next->next->next->data == 10);
}

