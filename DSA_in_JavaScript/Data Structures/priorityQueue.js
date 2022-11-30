/**
 * Heap based priority queue implementation
 * @funcions top(), pop(), push(), size(), empty(), clear()
 * @constructor PriorityQueue(comparator)
 * Acknowledgement: https://stackoverflow.com/questions/42919469/efficient-way-to-implement-priority-queue-in-javascript
 */

class PriorityQueue {
    constructor(comparator = (a, b) => a < b) {
        this._heap = [];
        this._comparator = comparator;
    }

    _left (i) {
        return (i << 1) + 1;
    }

    _right (i) {
        return (i << 1) + 2;
    }

    _parent (i) {
        return ((i + 1) >>> 1) - 1;
    }

    // greater priority
    _greater (i, j) {
        return this._comparator(this._heap[i], this._heap[j]);
    }

    _swap (i, j) {
        [this._heap[i], this._heap[j]] = [this._heap[j], this._heap[i]];
    }

    _heapifyUp () {
        let curIndex = this._heap.length - 1;
        while (
            curIndex > 0 &&
            this._greater(curIndex, this._parent(curIndex))
        ) {
            this._swap(curIndex, this._parent(curIndex));
            curIndex = this._parent(curIndex);
        }
    }

    _heapifyDown () {
        let curIndex = 0;
        while (
            (this._left(curIndex) < this._heap.length &&
                this._greater(this._left(curIndex), curIndex)) ||
            (this._right(curIndex) < this._heap.length &&
                this._greater(this._right(curIndex), curIndex))
        ) {
            let greaterChildIndex =
                this._right(curIndex) < this._heap.length &&
                this._greater(this._right(curIndex), this._left(curIndex))
                    ? this._right(curIndex)
                    : this._left(curIndex);
            this._swap(curIndex, greaterChildIndex);
            curIndex = greaterChildIndex;
        }
    };

    top () {
        return this._heap[0];
    }

    size () {
        return this._heap.length;
    }

    empty () {
        return this._heap.length === 0;
    }

    clear () {
        this._heap = [];
    }

    push (...values) {
        values.forEach(value => {
            this._heap.push(value);
            this._heapifyUp();
        });
    }

    pop () {
        let poppedValue = this.top();
        this._swap(0, this._heap.length - 1);
        this._heap.pop();
        this._heapifyDown();
        return poppedValue;
    }
};

/**
let pq = new PriorityQueue(); // default comparator is min heap
console.log(pq.pop()); // undefined
pq.push(1, -1, 2, 0);
console.log(pq.top(), pq.size(), pq.empty()); //-1 4 false
console.log(pq.pop(), pq.top(), pq.size(), pq.empty()); //-1 0 3 false
console.log(pq.pop(), pq.top(), pq.size(), pq.empty()); //0 1 2 false
pq.push(-100);
console.log(pq.top(), pq.size(), pq.empty()); //-100 3 false
while (!pq.empty()) { // -100 1 2
    console.log(pq.pop());
}
*/