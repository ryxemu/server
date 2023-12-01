#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class MyQueue;

template <class T>
class MyQueueNode {
   public:
	MyQueueNode(T* data) {
		next = 0;
		this->data = data;
	}

	friend class MyQueue<T>;

   private:
	T* data;
	MyQueueNode<T>* next;
};

template <class T>
class MyQueue {
   public:
	MyQueue() {
		head = tail = 0;
	}
	~MyQueue() {
		clear();
	}

	void push(T* data) {
		if (head == 0) {
			tail = head = new MyQueueNode<T>(data);
		} else {
			tail->next = new MyQueueNode<T>(data);
			tail = tail->next;
		}
	}

	T* pop() {
		if (head == 0) {
			return 0;
		}

		T* data = head->data;
		MyQueueNode<T>* next_node = head->next;
		delete head;
		head = next_node;

		return data;
	}

	T* top() {
		if (head == 0) {
			return 0;
		}

		return head->data;
	}

	bool empty() {
		if (head == 0) {
			return true;
		}

		return false;
	}

	void clear() {
		T* d = 0;
		while ((d = pop())) {
			delete d;
		}
		return;
	}

	int count() {
		int count = 0;
		MyQueueNode<T>* d = head;
		while (d != 0) {
			count++;
			d = d->next;
		}
		return (count);
	}

   private:
	MyQueueNode<T>* head;
	MyQueueNode<T>* tail;
};

#endif
