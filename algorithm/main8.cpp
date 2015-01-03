#include <iostream>

#include "IndexMinPQ.h"
#include "queue.h"

void merge(queue<char>* myqueue) {
    int i;
    const int N = 3;
    IndexMinPQ<char> pq(N);
    for (i = 0; i < N; i++)
        if (!myqueue[i].isEmpty())
            pq.insert(i, myqueue[i].dequeue());
    while (!pq.isEmpty()) {
        std::cout << pq.minKey() << std::endl;
        i = pq.delMin();
        if (!myqueue[i].isEmpty())
            pq.insert(i, myqueue[i].dequeue());
    }
}

int main() {
    int i;
    char str1[] = {'A', 'B', 'C', 'F', 'G', 'I', 'I', 'Z'};
    char str2[] = {'B', 'D', 'H', 'P', 'Q', 'Q', 'W', 'Z'};
    char str3[] = {'A', 'B', 'E', 'F', 'J', 'N', 'X', 'Z'};

    queue<char> myqueue[3];
    for (i = 0; i < 8; i++)
        myqueue[0].enqueue(str1[i]);
    for (i = 0; i < 8; i++)
        myqueue[1].enqueue(str2[i]);
    for (i = 0; i < 8; i++)
        myqueue[2].enqueue(str3[i]);
    merge(myqueue);
}
