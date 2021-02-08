#include <stdio.h>
#include <stdlib.h>
#include <new>

template <class Type>
struct queue_t {

    typedef struct {
        Type* array;
        int size;
        int max_size;
    }stack_t;

    stack_t first;
    stack_t second;

    queue_t() {

        first.array = nullptr;
        second.array = nullptr;

        first.size = 0;
        second.size = 0;

        first.max_size = 0;
        second.max_size = 0;

        printf("OK\n");
    }

    ~queue_t() {
        while (first.size > 0) {
            first.array[--first.size].~Type();
        }
        while (second.size > 0) {
            second.array[--second.size].~Type();
        }
        free(first.array);
        free(second.array);

        printf("GOOD BYE\n");
    }

    void push_stack(stack_t* a, Type elem) {
        if (a->size == a->max_size) {
            a->max_size += (a->max_size == 0);
            a->max_size *= 2;
            a->array = (Type*) realloc((void*) a->array, a->max_size * sizeof(Type));
            //Type* new_a = (Type*) malloc(a->max_size * sizeof(Type));
            //a->array = new_a;
        }
        new(a->array + a->size) Type(elem);
        a->size++;
    }

    Type top_stack(stack_t* a) {
        return a->array[a->size - 1];
    }

    void pop_stack(stack_t* a) {
        a->array[--a->size].~Type();
    }

    void push(Type elem) {
        push_stack(&first, elem);
    }

    Type top() {
        if (second.size == 0) {
            int len = first.size;
            for (int i = 0; i < len; i++) {
                Type elem = top_stack(&first);
                pop_stack(&first);
                push_stack(&second, elem);
            }
        }
        return top_stack(&second);
    }

    void pop() {
        if (second.size == 0) {
            int len = first.size;
            for (int i = 0; i < len; i++) {
                Type elem = top_stack(&first);
                pop_stack(&first);
                push_stack(&second, elem);
            }
        }
        pop_stack(&second);
    }
};

int main() {
    {
        queue_t<int> q;
        q.push(42);
        q.push(777);
        q.push(123456789);
        printf("%d\n", q.top()); //should be 42
        printf("%d\n", q.top()); //should be 42
        q.pop();
        printf("%d\n", q.top()); //should be 777
        q.pop();
        printf("%d\n", q.top()); //should be 123456789
    }

    {
        queue_t<char> q;
        q.push('A');
        printf("%c\n", q.top()); //should be A
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
        printf("%s\n", q.top()); //should be "What"
        q.pop();
        printf("%s\n", q.top()); //should be "are"
        q.pop();
        printf("%s\n", q.top()); //should be "you"
        q.pop();
        printf("%s\n", q.top()); //should be "doing?"
        q.pop();
    }

    return 0;
}
