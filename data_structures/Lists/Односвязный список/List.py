class Node:

    def __init__(self, data):
        self.data = data
        self.next = None


class List:

    def __init__(self):
        self.__first = None
        self.__last = None

    def add_first(self, data):
        new_node = Node(data)

        if self.__first != None:
            new_node.next = self.__first
            self.__last = self.__first
        self.__first = new_node

    def add_last(self, data):
        new_node = Node(data)

        if self.__first == Node:
            self.__first = new_node
            self.__last = new_node
            return
        else:
            self.__last.next = new_node
            self.__last = new_node

    def del_first(self):
        if self.__first == None:
            return
        else:
            self.__first = self.__first.next

    def del_last(self):
        if self.__last == None:
            return
        else:
            temp = self.__first
            if temp == self.__last:
                self.__last = None
                self.__first = None
                return
            while temp.next != self.__last:
                temp = temp.next
            self.__last = temp
            self.__last.next = None

    def print(self):
        temp = self.__first
        print("list: ", end="")
        while temp != None:
            print(temp.data, end=" ")
            temp = temp.next


if __name__ == '__main__':
    list = List()
    list.add_first(3)
    list.add_first(4)
    list.add_last(6)
    list.add_last(5)
    list.del_first()
    list.add_last(2)
    list.del_last()
    list.print()