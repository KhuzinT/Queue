#include <stdio.h>
#include <stdlib.h>
#include <new>

template <typename T>
struct stack_t {
    T* array;
    int size;
    int max_size;

    stack_t() {
        array = nullptr;
        size = 0;
        max_size = 0;
    }

    ~stack_t() {
        while (size > 0) {
            pop();
        }
        free(array);
    }

    void push(T elem) {
        if (size == max_size) {
            max_size += (max_size == 0);
            max_size *= 2;
            array = (T*) realloc((void*) array, max_size * sizeof(T));
        }
        new (array + size) T(elem);
        size++;
    }

    T top() {
        return array[size - 1];
    }

    void pop() {
        array[--size].~T();
    }
};

template <typename U>
struct queue_t {
    stack_t<U> first;
    stack_t<U> second;

    void push(U elem) {
        first.push(elem);
    }

    U top() {
        if (second.size == 0) {
            int len = first.size;
            for (int i = 0; i < len; i++) {
                U elem = first.top();
                first.pop();
                second.push(elem);
            }
        }
        return second.top();
    }

    void pop() {
        if (second.size == 0) {
            int len = first.size;
            for (int i = 0; i < len; i++) {
                U elem = first.top();
                first.pop();
                second.push(elem);
            }
        }
        second.pop();
    }
};

int main() {
    {
        queue_t<int> q;
        q.push(125);
        q.push(42);
        q.push(98);
        printf("%d\n", q.top()); //should be 125
        printf("%d\n", q.top()); //should be 125
        q.pop();
        printf("%d\n", q.top()); //should be 42
        q.pop();
        printf("%d\n", q.top()); //should be 98
    }

    {
        queue_t<char> q;
        q.push('T');
        printf("%c\n", q.top()); //should be T
        q.pop();
        q.push('L');
        q.push('O');
        q.push('L');
        printf("%c\n", q.top()); //should be L
        q.pop();
        printf("%c\n", q.top()); //should be O
        q.pop();
        printf("%c\n", q.top()); //should be L
        q.pop();
    }

    {
        queue_t<char*> q;
        q.push("What");
        q.push("are");
        q.push("you");
        q.push("doing?");
        printf("%s\n", q.top()); //should be L
        q.pop();
        printf("%s\n", q.top()); //should be L
        q.pop();
        printf("%s\n", q.top()); //should be L
        q.pop();
        printf("%s\n", q.top()); //should be L
        q.pop();
    }
    return 0;
}
