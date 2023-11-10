/**
 * Splay Tree implementation in JavaScript
 * Available methods: insert, find, findMin, findMax, delete, popMin, popMax, size, empty, has, clear, get
 * Complexity: O(log n) amortized time for all operations
 * Usage:can be used as a priority queue / sorted array / sorted set / sorted map
 */

class Node {
    constructor(key, ...values) {
        this.key = key;
        this.value = values;
        this.left = null;
        this.right = null;
        this.parent = null;
    }
}

class SplayTree {
    constructor() {
        this.root = null;
        this.size = 0;
    }

    rotateRight(node) {
        if (node === null) {
            return null;
        }
        if (node.left === null) {
            return node;
        }

        let leftRight = node.left.right;
        node.left.right = node;
        node.left.parent = node.parent;

        if (node.parent !== null) {
            if (node.parent.left === node) {
                node.parent.left = node.left;
            } else {
                node.parent.right = node.left;
            }
        }

        node.parent = node.left;
        node.left = leftRight;
        if (leftRight !== null) {
            leftRight.parent = node;
        }
        return node.parent;
    }

    rotateLeft(node) {
        if (node === null) {
            return null;
        }
        if (node.right === null) {
            return node;
        }
        let rightLeft = node.right.left;
        node.right.left = node;
        node.right.parent = node.parent;

        if (node.parent !== null) {
            if (node.parent.left === node) {
                node.parent.left = node.right;
            } else {
                node.parent.right = node.right;
            }
        }

        node.parent = node.right;
        node.right = rightLeft;
        if (rightLeft !== null) {
            rightLeft.parent = node;
        }
        return node.parent;
    }

    splay(node) {
        if (node === null) {
            return null;
        }
        while (node.parent !== null) {
            if (node.parent.parent === null) {
                if (node.parent.left === node) {
                    this.rotateRight(node.parent);
                } else {
                    this.rotateLeft(node.parent);
                }
            } else if (node.parent.left === node && node.parent.parent.left === node.parent) {
                this.rotateRight(node.parent.parent);
                this.rotateRight(node.parent);
            } else if (node.parent.right === node && node.parent.parent.right === node.parent) {
                this.rotateLeft(node.parent.parent);
                this.rotateLeft(node.parent);
            } else if (node.parent.left === node && node.parent.parent.right === node.parent) {
                this.rotateRight(node.parent);
                this.rotateLeft(node.parent);
            } else {
                this.rotateLeft(node.parent);
                this.rotateRight(node.parent);
            }
        }
        return node;
    }

    insert(key, ...values) {
        if (this.root === null) {
            this.root = new Node(key, ...values);
            this.size++;
            return this.root;
        }
        let node = this.root;
        while (node !== null) {
            if (node.key > key) {
                if (node.left === null) {
                    node.left = new Node(key, ...values);
                    node.left.parent = node;
                    this.root = this.splay(node.left);
                    this.size++;
                    return node.left;
                } else {
                    node = node.left;
                }
            } else {
                if (node.right === null) {
                    node.right = new Node(key, ...values);
                    node.right.parent = node;
                    this.root = this.splay(node.right);
                    this.size++;
                    return node.right;
                } else {
                    node = node.right;
                }
            }
        }
    }

    find(key) {
        let node = this.root;
        while (node !== null) {
            if (node.key > key) {
                node = node.left;
            } else if (node.key < key) {
                node = node.right;
            } else {
                this.root = this.splay(node);
                return node;
            }
        }
        return null;
    }
    
    findMin(node=null) {
        if (node === null) {
            node = this.root;
        }
        while (node.left !== null) {
            node = node.left;
        }
        this.root = this.splay(node);
        return node;
    }

    findMax(node=null) {
        if (node === null) {
            node = this.root;
        }
        while (node.right !== null) {
            node = node.right;
        }
        this.root = this.splay(node);
        return node;
    }

    delete(key) {
        let node = this.find(key);
        if (node === null) {
            return null;
        }
        this.size--;

        let left = node.left;
        let right = node.right;
        if (left === null && right === null) {
            this.root = null;
        } else if (left === null) {
            right.parent = null;
            this.root = right;
        } else if (right === null) {
            left.parent = null;
            this.root = left;
        } else {
            let min = this.findMin(right);
            this.splay(min);
            min.left = left;
            left.parent = min;
            this.root = min;
        }
        return node;
    }

    popMin() {
        let min = this.findMin();
        if (min === null) {
            return null;
        }
        this.delete(min.key);

        return min;
    }

    popMax() {
        let max = this.findMax();
        if (max === null) {
            return null;
        }
        this.delete(max.key);

        return max;
    }

    printInOrder(node=this.root) {
        if (node === null) {
            return;
        }
        this.printInOrder(node.left);
        console.log(node.key, node.value);
        this.printInOrder(node.right);
    }

    print() {
        console.log("SplayTree size:", this.size);
        this.printInOrder();
    }

    empty() {
        return this.size === 0;
    }

    has(key) {
        return this.find(key) !== null;
    }

    clear() {
        this.root = null;
        this.size = 0;
    }

    get(key) {
        let node = this.find(key);
        if (node === null) {
            return null;
        }
        return node.value;
    }

}

// //test SplayTree
// let tree = new SplayTree();
// tree.insert(5, 5, 0, 1, "abc");
// tree.insert(1, 1, 0, 1, "ab1");
// tree.insert(3, 3, 0, 1, "ab3");
// tree.insert(2, 2, 0, 1, "ab3");
// tree.insert(2, 2, 0, 1, "ab2");
// tree.printInOrder();
// console.log(tree.find(2).value);
// console.log(tree.findMax().value);
// console.log(tree.findMin().value);
// console.log(tree.popMin().value);
// console.log(tree.findMin().value);
// console.log(tree.popMax().value);
// console.log(tree.findMax().value);
// console.log(tree.find(2).value);
// tree.printInOrder();

// console.log(tree.has(2));
// console.log(tree.has(3));
// console.log(tree.has(4));
// console.log(tree.has(5));
// console.log(tree.get(3));
// console.log(tree.get(0));
// console.log(tree.size);
// console.log(tree.empty());
// tree.print();
// tree.clear();
// tree.print();
