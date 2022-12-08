/**
 * Heap based priority queue implementation
 * @funcions top(), pop(), push(), size(), empty(), clear()
 * @constructor PriorityQueue(comparator)
 * Acknowledgement: https://stackoverflow.com/questions/42919469/efficient-way-to-implement-priority-queue-in-javascript
 */

class MyPriorityQueue {
    constructor(comparator = (a, b) => a[0] < b[0]) {
        this._heap = [];
        this._comparator = comparator;
    }

    _left(i) {
        return (i << 1) + 1;
    }

    _right(i) {
        return (i << 1) + 2;
    }

    _parent(i) {
        return ((i + 1) >>> 1) - 1;
    }

    // greater priority
    _greater(i, j) {
        return this._comparator(this._heap[i], this._heap[j]);
    }

    _swap(i, j) {
        [this._heap[i], this._heap[j]] = [this._heap[j], this._heap[i]];
    }

    _heapifyUp() {
        let curIndex = this._heap.length - 1;
        while (
            curIndex > 0 &&
            this._greater(curIndex, this._parent(curIndex))
        ) {
            this._swap(curIndex, this._parent(curIndex));
            curIndex = this._parent(curIndex);
        }
    }

    _heapifyDown() {
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
    }

    top() {
        return this._heap[0];
    }

    size() {
        return this._heap.length;
    }

    empty() {
        return this._heap.length === 0;
    }

    clear() {
        this._heap = [];
    }

    push(...values) {
        values.forEach((value) => {
            this._heap.push(value);
            this._heapifyUp();
        });
    }

    pop() {
        let poppedValue = this.top();
        this._swap(0, this._heap.length - 1);
        this._heap.pop();
        this._heapifyDown();
        return poppedValue;
    }
}

/**
 * @param {number[][]} edges
 * @param {number} N
 * @param {number} source
 * @return {number[]}
 *
 * @description: nodes are numbered from 0 to N-1, returns shortest path from node source to all other nodes
 * @edges is a list of directed edges, where each edge is represented as a triplet: [source, destination, weight]
 * @timeComplexity: O(ElogV)
 * @spaceComplexity: O(V)
 */
var dijsourcestraSSSP = function (edges, N, source) {
    let distance = new Array(N).fill(Infinity),
        graph = new Array(N).fill(0).map(() => []);
    let pq = new MyPriorityQueue(),
        visited = new Array(N).fill(false);

    edges.forEach(([u, v, weight]) => {
        graph[u].push([v, weight]);
    });

    distance[source] = 0;
    pq.push([0, source]);

    while (!pq.empty()) {
        let [distu, u] = pq.pop();
        if (!visited[u] && distu === distance[u]) {
            visited[u] = true;
            for (let [v, weightUtoV] of graph[u]) {
                if (distance[v] > distu + weightUtoV) {
                    pq.push([distu + weightUtoV, v]);
                    distance[v] = distu + weightUtoV;
                }
            }
        }
    }

    return distance;
};

// test
console.log(
    dijsourcestraSSSP(
        [
            [0, 1, 1],
            [0, 2, 4],
            [1, 2, 2],
            [1, 3, 7],
            [2, 3, 3],
        ],
        4,
        0
    )
); // [0, 1, 3, 6]
// more test
console.log(
    dijsourcestraSSSP(
        [
            [0, 1, 1],
            [0, 2, 4],
            [1, 2, 2],
            [1, 3, 7],
            [2, 3, 3],
            [3, 4, 1],
            [4, 5, 1],
            [5, 6, 1],
            [6, 7, 1],
            [7, 8, 1],
            [8, 9, 1],
            [9, 1, 4],
        ],
        10,
        4
    )
); // [Infinity, 5, 7, 4, 0, 1, 2, 3, 4, 5]
