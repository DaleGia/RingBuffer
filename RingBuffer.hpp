#ifndef RING_BUFFER_H
#define RING_BUFFER_H

template <typename T>
class RingBuffer
{
public:
    /* Constructor with user-specified capacity */
    RingBuffer(unsigned int capacity) : capacity(capacity), head(0), tail(0), full(false), empty(true)
    {
        data = new T[capacity];
    }

    /* Destructor, frees allocated memory */
    ~RingBuffer()
    {
        delete[] data;
    }

    /* Check if the buffer is empty */
    bool isEmpty() const
    {
        return empty;
    }

    /* Check if the buffer is full */
    bool isFull() const
    {
        return full;
    }

    /* Push data to the back of the buffer */
    void push(const T &item)
    {

        data[head] = item;

        if (isFull())
        {
            /* TODO: Handle overflow via user defined callback */
            tail++;
            if (tail == capacity)
            {
                tail = 0;
            }
        }

        head++;
        if ((head == capacity))
        {
            head = 0;
        }

        if (head == tail)
        {
            full = true;
        }

        empty = false;
    }

    /* Pop data from the front of the buffer */
    bool pop(T &buffer)
    {
        if (isEmpty())
        {
            return false;
        }
        buffer = data[tail];
        full = false;
        tail++;
        if ((tail == capacity))
        {
            tail = 0;
        }

        if (head == tail)
        {
            empty = true;
        }
        return true;
    }

    /* Clear the ring buffer */
    void clear()
    {
        head = 0;
        tail = 0;
        full = false;
        empty = true;
    }

private:
    T *data;               // Array to store data
    unsigned int capacity; // Maximum capacity of the buffer
    unsigned int head;     // Index of the head element
    unsigned int tail;     // Index of the tail element (points to the next empty slot)
    bool full;
    bool empty;
};

#endif