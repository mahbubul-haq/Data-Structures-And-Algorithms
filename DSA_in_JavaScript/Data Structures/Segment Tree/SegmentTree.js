class Node {
    constructor(value) {
        this.value = value;
        this.left = null;
        this.right = null;
    }
}

/// for sum, min, max, gcd, lcm, and other operations
/// only range query and point update are implemented

class SegmentTree {
    

    constructor(arr, cb) {
        this.cb = cb;
        this.root = this._buildTree(arr, 0, arr.length - 1);
        
    }

    _buildTree(arr, start, end) {
        if (start > end) {
            return null; 
        }
        if (start === end) {
            return new Node(arr[start]);
        }

        const mid = Math.floor((start + end) / 2);
        const leftChild = this._buildTree(arr, start, mid);
        const rightChild = this._buildTree(arr, mid + 1, end);

        if (leftChild === null) return rightChild;
        if (rightChild === null) return leftChild;
        const root = new Node(this.cb(leftChild.value, rightChild.value));
        root.left = leftChild;
        root.right = rightChild;

        return root;
    }
    _rangeQuery(node, start, end, from, to) {
        if (start > end || start > to || end < from || node === null) {
            return null; 
        }

        if (start >= from && end <= to) {
            return node.value;
        }
        const mid = Math.floor((start + end) / 2);

        const leftResult = this._rangeQuery(node.left, start, mid, from, to);
        const rightResult = this._rangeQuery(node.right, mid + 1, end, from, to);

        if (leftResult === null) return rightResult;
        if (rightResult === null) return leftResult;
        return this.cb(leftResult, rightResult);
    }

    _pointUpdate(node, start, end, index, value) {
        if (start > end || node === null) {
            return;
        }
        if (start === end) {
            node.value = value;
            return;
        }
        const mid = Math.floor((start + end) / 2);
        if (index <= mid) {
            this._pointUpdate(node.left, start, mid, index, value);
        } else {
            this._pointUpdate(node.right, mid + 1, end, index, value);
        }
        node.value = node.left? (node.right ? this.cb(node.left.value, node.right.value) : node.left.value) : (node.right ? node.right.value : 0);
    }

    pointUpdate(start, end, index, value) {
        this._pointUpdate(this.root, start, end, index, value);
    }

    rangeQuery(start, end, from, to) {
        return this._rangeQuery(this.root, start, end, from, to);
    }
    
}

// let arr = [1, 3, 5, 7, 9, 11];
// let st = new SegmentTree(arr, (a, b) => Math.min(a, b)); // Sum function

// console.log(st.rangeQuery(0, arr.length - 1, 1, 3)); // Output: 3 (minimum value in range [1, 3])
// console.log(st.rangeQuery(0, arr.length - 1, 0, 5)); // Output: 1 (minimum value in range [0, 5])
// console.log(st.rangeQuery(0, arr.length - 1, 2, 4)); // Output: 5 (minimum value in range [2, 4])
// console.log(st.rangeQuery(0, arr.length - 1, 3, 5)); // Output: 7 (minimum value in range [3, 5])
// console.log(st.rangeQuery(0, arr.length - 1, 0, 0)); // Output: 1 (minimum value in range [0, 0])
// console.log(st.rangeQuery(0, arr.length - 1, 5, 5)); // Output: 11 (minimum value in range [5, 5])
// console.log(st.rangeQuery(0, arr.length - 1, 4, 4)); // Output: 9 (minimum value in range [4, 4])
// console.log(st.rangeQuery(0, arr.length - 1, 1, 5)); // Output: 3 (minimum value in range [1, 5])
// console.log(st.rangeQuery(0, arr.length - 1, 0, 3)); // Output: 1 (minimum value in range [0, 3])

// // Update the value at index 2 to 0
// st.pointUpdate(0, arr.length - 1, 2, 0);
// console.log(st.rangeQuery(0, arr.length - 1, 1, 3)); // Output: 0 (minimum value in range [1, 3])
// console.log(st.rangeQuery(0, arr.length - 1, 0, 5)); // Output: 0 (minimum value in range [0, 5])
// console.log(st.rangeQuery(0, arr.length - 1, 2, 4)); // Output: 0 (minimum value in range [2, 4])   

