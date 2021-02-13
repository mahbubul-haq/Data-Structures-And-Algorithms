class Node:

    def __init__(self, data=None, next=None, prev=None):
        self.data = data
        self.next = next
        self.prev = prev


class DoublyLinkedList:
    """Doubly Linked List Class
    
    attributes: head, tail, length
    methods: insertFirst, searchNode, printForward
    insertLast, deleteLast, deleteFast, printBackward,
    deleteNode, deleteValue, front, back
    """

    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0
    
    def insertFirst(self, data):

        """Insert a value at the beginning
        
        returns: None
        """

        newNode = Node(data=data)

        if self.length == 0:
            self.head = newNode
            self.tail = newNode
        else:
            newNode.next = self.head
            self.head.prev = newNode
            self.head = newNode

        self.length += 1

    def searchNode(self, data):

        """Search the node of the data
        
        returns: Node, None
        """

        left = self.head
        right = self.tail

        i, maxi = 1, (self.length + 1) // 2

        while i <= maxi:

            if left.data == data:
                return left
            elif right.data == data:
                return right

            i += 1
            left = left.next
            right = right.prev

        return None

    def printForward(self):

        temp = self.head

        print("Length: {0}".format(self.length))
        print("List:", end=' ')
        while temp:
            print(temp.data, end=' ')
            temp = temp.next
        print()

    
    def insertLast(self, data):

        """insert a node at the back
        
        returns: None
        """

        if self.tail:
            temp = Node(data)
            temp.prev = self.tail
            self.tail.next = temp
            self.tail = temp

        else:
            self.tail = Node(data)
            self.head = self.tail

        self.length += 1


    def deleteLast(self):
        """Delete the last Node
        
        returns: None
        """

        if self.tail:
            temp = self.tail

            if self.length > 1:
                self.tail = self.tail.prev
                self.tail.next = None

            else:
                self.tail = None
                self.head = None

            del temp
            self.length -= 1

    def deleteFast(self):
        """Delete the first Node
        
        returns: None
        """

        if self.head:
            temp = self.head

            if self.length > 1:
                self.head = self.head.next
                self.head.prev = None
            else:
                self.tail = None
                self.head = None
        
        self.length -= 1
        del temp

    
    def printBackward(self):

        temp = self.tail

        print("Length: {0}".format(self.length))
        print("List:", end=' ')

        while temp:
            print(temp.data, end=' ')
            temp = temp.prev
        
        print()


    def deleteNode(self, node):
        """Delete a given Node
        
        returns: None
        """
        
        if node == self.head:
            self.deleteFast()
        elif node == self.tail:
            self.deleteLast()
        else:
            node.prev.next = node.next
            node.next.prev = node.prev
            self.length -= 1
            del node


    def deleteValue(self, data):
        """Delete the node of a given value
        
        returns: None
        """

        node = self.searchNode(data=data)

        if node:
            self.deleteNode(node)

    def front(self):
        if self.head:
            return self.head.data
        else:
            return None
    
    def back(self):
        if self.tail:
            return self.tail.data
        else:
            return None




dll = DoublyLinkedList()
dll.printBackward()
dll.printForward()
dll.insertFirst(1)
dll.printForward()
dll.insertFirst(3)
dll.insertLast(101)
dll.insertLast(102)
dll.insertLast(103)
dll.insertLast(105)
dll.printForward()
dll.insertLast(100)
dll.printBackward()
dll.printForward()
dll.deleteValue(1)
dll.printForward()
dll.printBackward()
dll.deleteValue(100)
dll.printBackward()
dll.printForward()
dll.deleteValue(3)
dll.printForward()
dll.printForward()
dll.deleteValue(1000)
dll.printForward()
dll.printBackward()

print(dll.front())
print(dll.back())
node = dll.searchNode(103)
print(node.data)
node = node.next
print(node.data)
dll.deleteNode(node)
dll.printForward()
