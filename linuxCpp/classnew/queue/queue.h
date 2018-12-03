#ifndef __QUEUE_H__
#define __QUEUE_H__

class Customer
{
    private:
        long arrive;
        int processtime;
    public:
        Customer() { arrive = processtime = 0; }

        void set(long when);
        long when() const { return arrive; }
        int ptime() const { return processtime; }
};

class Queue
{
    private:
        struct Node{Item item; struct Node *next;};
        enum {Q_SIZE = 10};
        Node *front;
        Node *rear;
        int items;
        coust int qsize;
        Queue(const Queue &q) qsize(0){}
        Queue & operator=(const Queue &q) {return *this;}
    public:
        Queue(int qs = Q_SIZE);
        ~Queue();
        bool isempty() const;
        bool isfull() const;
        int queuecount() const;
        bool enqueue(const Item &item);
        bool dequeue(Item &item);
};

#endif
