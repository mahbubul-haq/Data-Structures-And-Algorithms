/**
 * Operations: add VALUE to range: LEFT to RIGHT, get sum of range left to right 
 * constructor: start = leftmost index, end = rightmost index
 */

class TreeNode {
    constructor(start, end) {
        this.start = start;
        this.end = end;
        this.left = null;
        this.right = null;
        this.sum = 0;
        this.propagate = 0;
    }
}

class SegmentTree {
    constructor(arrayLength) {
        this.root = new TreeNode(0, arrayLength - 1);
    }

    _propagate(node) {
        if (node.propagate !== 0) {
            if (node.left === null && node.start !== node.end) {
                node.left = new TreeNode(node.start, (node.start + node.end) >> 1);
                node.right = new TreeNode(((node.start + node.end) >> 1) + 1, node.end);
            }
            if (node.left !== null) {
                node.left.propagate += node.propagate;
                node.right.propagate += node.propagate;
                node.left.sum += node.propagate * (node.left.end - node.left.start + 1);
                node.right.sum += node.propagate * (node.right.end - node.right.start + 1);
            }
            node.propagate = 0;
        }
    }

    _buildTree(node, left, right, array) {
        if (left === right) {
            node.sum = array[left];
            return;
        }

        let mid = (left + right) >> 1;
        node.left = new TreeNode(left, mid);
        node.right = new TreeNode(mid + 1, right);

        this._buildTree(node.left, left, mid, array);
        this._buildTree(node.right, mid + 1, right, array);

        node.sum = node.left.sum + node.right.sum;
    }

    _addValue(node, left, right, value) {

        if (left > right) return;

        this._propagate(node);

        if (node.start === left && node.end === right) {
            node.propagate += value;
            node.sum += value * (node.end - node.start + 1);
        } else {
            let mid = (node.start + node.end) >> 1;
            if (!node.left) {
                node.left = new TreeNode(node.start, mid);
                node.right = new TreeNode(mid + 1, node.end);
            }

            this._addValue(node.left, left, Math.min(mid, right), value);
            this._addValue(node.right, Math.max(mid + 1, left), right, value);

            node.sum = node.left.sum + node.right.sum;
        }
    }

    _getSum(node, left, right) {
        if (left > right) return 0;
        this._propagate(node);

        if (node.start === left && node.end === right) {
            return node.sum;
        } else {
            let mid = (node.start + node.end) >> 1;
            let sum = 0;
            if (node.left) {
                sum += this._getSum(node.left, left, Math.min(mid, right));
            }
            if (node.right) {
                sum += this._getSum(node.right, Math.max(mid + 1, left), right);
            }
            return sum;
        }
    }

    // optional -> needed only if you want to build tree from array
    buildTree(array, arrayLength) {
        this._buildTree(this.root, 0, arrayLength - 1, array);
    }

    addValue(left, right, value) {
        this._addValue(this.root, left, right, value);
    }

    getSum(left, right) {
        return this._getSum(this.root, left, right);
    }
}

// test
let st = new SegmentTree(10);
st.addValue(0, 9, 1);
st.addValue(0, 4, 1);
console.log(st.getSum(0, 9));
st.addValue(0, 9, 1);
console.log(st.getSum(0, 9));
st.addValue(0, 9, 1);
console.log(st.getSum(0, 9));
st.addValue(0, 9, -5);
console.log(st.getSum(0, 9));
st.addValue(0, 2, 1);
console.log(st.getSum(0, 9));
console.log(st.getSum(0, 2));
console.log(st.getSum(3, 9));

