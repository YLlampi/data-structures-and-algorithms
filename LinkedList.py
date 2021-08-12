class Node:
    def __init__(self, elem=None):
        self.__elem = elem
        self.__next = None

    @property
    def elem(self):
        return self.__elem

    @elem.setter
    def elem(self, elem):
        self.__elem = elem

    @property
    def next(self):
        return self.__next

    @next.setter
    def next(self, next):
        self.__next = next

    def __str__(self):
        return f'{self.__elem}'


class LinkedList:
    def __init__(self):
        self.__head = None
        self.__size = 0

    def push_back(self, elem):
        temp_node = Node(elem)
        if self.__head == None:
            self.__head = temp_node
        else:
            aux = self.__head
            while aux.next:
                aux = aux.next
            aux.next = temp_node
        self.__size += 1

    def pop_back(self):
        aux = self.__head;
        q = None
        if self.__head != None:
            while aux.next:
                q = aux
                aux = aux.next
            if self.__head == aux:
                self.__head == None
            else:
                q.next = None
            self.__size -= 1

    @property
    def size(self):
        return self.__size

    def impresion(self):
        aux = self.__head
        while aux:
            print(aux.elem, end=' ')
            aux = aux.next

    def __str__(self):
        aux = self.__head
        list = []
        while aux:
            list.append(aux.elem)
            aux = aux.next
        return f'{list}'


if __name__ == '__main__':
    list = LinkedList()

    list.push_back(7)
    list.push_back(4)
    list.push_back(6)
    list.push_back(2)
    list.push_back(9)

    print(list.impresion())
    print(list)
    print(list.size)

    list.pop_back()

    print(list.impresion())
    print(list)
    print(list.size)
