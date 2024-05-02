#include "../RingBuffer.hpp"
#include <cassert>
#include <iostream>

void test_empty_buffer()
{
    RingBuffer<int> buffer(5);

    // Assert that the buffer is empty initially
    assert(buffer.isEmpty() == true);
};

void test_push_one_element()
{
    RingBuffer<int> buffer(5);
    int value = 10;

    buffer.push(value);

    // Assert that the buffer is no longer empty
    assert(buffer.isEmpty() == false);

    // Pop the element and check its value
    int popped_value;
    assert(buffer.pop(popped_value) == true);
    assert(popped_value == value);
};

void test_push_multiple_elements()
{
    RingBuffer<int> buffer(3);
    int values[] = {1, 2, 3};

    for (int value : values)
    {
        buffer.push(value);
    }

    // Assert that the buffer is full after pushing all elements
    assert(buffer.isFull() == true);

    // Pop elements and check their values
    for (int value : values)
    {
        int popped_value;
        assert(buffer.pop(popped_value) == true);
        assert(popped_value == value);
    }
};

void test_pop_from_empty_buffer()
{
    RingBuffer<int> buffer(5);

    // Assert that pop fails from an empty buffer
    int value;
    assert(buffer.pop(value) == false);
};

void test_push_to_full_buffer()
{
    RingBuffer<int> buffer(3);
    int values[] = {1, 2, 3};

    // Push two elements to fill the buffer
    for (int value : values)
    {
        buffer.push(value);
    }

    // Assert that the buffer is full (assuming no overflow handling)
    assert(buffer.isFull() == true);

    // Push another element, effectively overwriting the oldest element
    int overflow_value = 4;
    buffer.push(overflow_value);

    int popped_value;
    assert(buffer.pop(popped_value) == true);
    assert(popped_value == values[1]);
    assert(buffer.pop(popped_value) == true);
    assert(popped_value == values[2]);

    int popped_value2;
    assert(buffer.pop(popped_value2) == true);
    assert(popped_value2 == overflow_value); // Overflow value should be popped second
}

void test_overflow_after_pop()
{
    RingBuffer<int> buffer(3);
    int values[] = {1, 2, 3};

    // Push and then pop two elements
    for (int i = 0; i < 2; ++i)
    {
        buffer.push(values[i]);
    }
    int popped_value;
    buffer.pop(popped_value);
    buffer.pop(popped_value);

    // Assert buffer is not full after pops (assuming no overflow handling)
    assert(buffer.isFull() == false);

    // Push one element, then overflow with another. Overwritten element is lost.
    buffer.push(values[2]);
    int overflow_value = 4;
    buffer.push(overflow_value);

    // Pop elements and check their values, ensuring the middle element is lost
    int popped_value1;
    assert(buffer.pop(popped_value1) == true);

    assert(popped_value1 == values[2]); // First element should be popped first

    int popped_value2;
    assert(buffer.pop(popped_value2) == true);
    assert(popped_value2 == overflow_value); // Overflow value should be popped second
}

int main()
{
    std::cout << "test_empty_buffer" << std::endl;
    test_empty_buffer();
    std::cout << "test_push_one_element" << std::endl;
    test_push_one_element();
    std::cout << "test_push_multiple_elements" << std::endl;
    test_push_multiple_elements();
    std::cout << "test_pop_from_empty_buffer" << std::endl;
    test_pop_from_empty_buffer();
    std::cout << "test_push_to_full_buffer" << std::endl;
    test_push_to_full_buffer();
    std::cout << "test_overflow_after_pop" << std::endl;
    test_overflow_after_pop();
    std::cout << "All tests passed!" << std::endl;
    return 0;
};
