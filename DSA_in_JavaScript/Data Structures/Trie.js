/**
 * Trie trie = new Trie();
 * trie.insert("apple");    // insert "apple" into trie
 * trie.search("apple");   // returns true
 * trie.search("app");     // returns false
 */

class TrieNode {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
    }
}

class Trie {
    constructor() {
        this.root = new TrieNode();
    }

    insert(word) {
        let current = this.root;

        for (let x of word) {
            if (!current.children[x]) {
                current.children[x] = new TrieNode();
            }
            current = current.children[x];
        }
        current.isEndOfWord = true;
    }

    search(word) {
        let current = this.root, len = word.length;
        for (let i = 0; i < len; i++) {
            if (!current.children[word[i]]) {
                return false;
            }
            current = current.children[word[i]];
        }
        return current.isEndOfWord;
    }
}

// tests
// const trie = new Trie();
// trie.insert("apple");
// console.log(trie.search("apple")); // true
// console.log(trie.search("app")); // false
// trie.insert("app");
// console.log(trie.search("app")); // true
// console.log(trie.search("appl")); // false