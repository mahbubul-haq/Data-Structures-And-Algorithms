/**
 * Deque is a double ended queue. It is a list where you can add and remove elements from both ends.
 * Constructor: Deque()
 * Methods: pushFront(element), pushBack(element), popFront(), popBack(), front(), back(), empty(), size(), clear()
 */

class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
        this.prev = null;
    }
}

class Deque {
    constructor() {
        this._head = null;
        this._tail = null;
        this._size = 0;
    }

    pushFront (data) {
        const node = new Node(data);
        if (this._head) {
            node.next = this._head;
            this._head.prev = node;
            this._head = node;
        } else {
            this._head = node;
            this._tail = node;
        }
        this._size++;
    }

    pushBack (data) {
        const node = new Node(data);
        if (this._tail) {
            node.prev = this._tail;
            this._tail.next = node;
            this._tail = node;
        } else {
            this._head = node;
            this._tail = node;
        }
        this._size++;
    }

    popFront () {
        if (this._head) {
            const data = this._head.data;
            this._head = this._head.next;
            if (this._head) {
                this._head.prev = null;
            } else {
                this._tail = null;
            }
            this._size--;
            return data;
        }
        return null;
    }

    popBack () {
        if (this._tail) {
            const data = this._tail.data;
            this._tail = this._tail.prev;
            if (this._tail) {
                this._tail.next = null;
            } else {
                this._head = null;
            }
            this._size--;
            return data;
        }
        return null;
    }

    front () {
        return this._head ? this._head.data : null;
    }

    back () {
        return this._tail ? this._tail.data : null;
    }

    empty () {
        return this._size === 0;
    }

    size () {
        return this._size;
    }
}

// testing
/*
const deque = new Deque();
deque.pushFront(1);
deque.pushFront(2);
deque.pushBack(3);
deque.pushBack(4);
console.log(deque.front(), deque.back(), deque.size(), deque.empty()); // 2 4 4 false
console.log(deque.popFront(), deque.popBack(), deque.size(), deque.empty()); // 2 4 2 false
console.log(deque.popFront(), deque.popBack(), deque.size(), deque.empty()); // 1 3 0 true
console.log(deque.popFront(), deque.popBack(), deque.size(), deque.empty()); // null null 0 true
*/