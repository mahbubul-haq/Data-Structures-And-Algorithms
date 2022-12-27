const mod = [1e9 + 7, 1e9 + 9];
const prime = [257, 263];
let primePow = [];

const modulus = (a) => [a[0] % mod[0], a[1] % mod[1]];
const add = (a, b) => modulus([a[0] + b[0], a[1] + b[1]]);
const subtract = (a, b) => modulus([a[0] - b[0] + mod[0], a[1] - b[1] + mod[1]]);
const multiply = (a, b) => modulus([a[0] * b, a[1] * b]);
const multiply1 = (a, b) => modulus([a[0] * b[0], a[1] * b[1]]);
const isEqual = (a, b) => a[0] === b[0] && a[1] === b[1];

const calcPow = (maxLength) => {
    primePow = new Array(maxLength + 1).fill(0).map(val => new Array(2).fill(1));

    for (let i = 1; i <= maxLength; i++) {
        primePow[i] = multiply1(primePow[i - 1], prime);
    }
}

//double hashing
const computeHash = (text) => {
    let len = text.length, hashValue = [0, 0]; 
    for (let i = 0; i < len; i++) {
        hashValue = add(hashValue, multiply(primePow[i], text[i].charCodeAt(0)));
    }
    return hashValue;
}

//double hashing reverse: powers from top to bottom
const computeReverseHash = (text) => {
    let len = text.length, hashValue = [0, 0];
    for (let i = 0; i < len; i++) {
        hashValue = add(hashValue, multiply(primePow[len - 1 - i], text[i].charCodeAt(0)));
    }
    return hashValue;
}
/**
 * @param {string} text
 * @param {number[]} patternHash
 * @param {number} patternLength
 */
const findPattern = (text, patternHash, patternLength) => {
    let len = text.length, hashValue = [0, 0];
    
    if (len < patternLength) return false;

    for (let i = 0; i < patternLength; i++) {
        hashValue = add(hashValue, multiply(primePow[patternLength - 1 - i], text[i].charCodeAt(0)));
    }

    if (isEqual(hashValue, patternHash)) return true;

    for (let i = patternLength; i < len; i++) {
        hashValue = add(multiply1(subtract(hashValue, multiply(primePow[patternLength - 1], text[i - patternLength].charCodeAt(0))), prime), [text[i].charCodeAt(0), text[i].charCodeAt(0)]);
        if (isEqual(hashValue, patternHash)) return true;
    }
    return false;
} 

//test
calcPow(100);
const hashValue = computeReverseHash("gorilla");
console.log(hashValue);
console.log(findPattern("Hello goorilla", hashValue, 7));
console.log(findPattern("Hello gorilla", hashValue, 7));
console.log(findPattern("Gorilla", hashValue, 7));
console.log(findPattern("gorilla", hashValue, 7));