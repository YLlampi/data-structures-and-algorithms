#include <iostream>
#include <memory>

template <class T>
class List;

template <class T>
class Node;

template <class T>
std::ostream& operator<<(std::ostream &os, const List<T> &list){
    Node<T> *temp = list.head.get();
    while(temp){
        os << temp->elem << ' ';
        temp = temp->next.get();
    }
    return os;
}

template <class T>
class Node{
private:
    T elem;
    std::unique_ptr<Node<T>> next;
public:
    Node(T elem) : elem{elem}, next{nullptr} {}
    friend class List<T>;
    friend std::ostream& operator<< <>(std::ostream &os, const List<T> &list);
};

template <class T>
class List{
private:
    int size;
    std::unique_ptr<Node<T>> head;
public:
    List() : size{0}, head{nullptr} {}

    List(const List &list) : size{0}{
        std::cout << "Copy Constructor" << '\n';
        Node<T> *tempList = list.head.get();
        while(tempList){
            insert(tempList->elem);
            tempList = tempList->next.get();
        }
    }

    List(List &&list){
        std::cout << "Move Constructor" << '\n';
        this->head = std::move(list.head);
    }

    void insert(T elem) {
        std::unique_ptr<Node<T>> temp{std::make_unique<Node<T>>(elem)};
        if(!this->head) this->head = std::move(temp);
        else {
            Node<T> *aux = this->head.get();
            while(aux->next.get())
                aux = aux->next.get();
            aux->next = std::move(temp);
        }
        this->size++;
    }

    void remove() {
        if(!this->head) return;
        std::unique_ptr<Node<T>> temp = std::move(this->head);
        this->head = std::move(temp->next);
        this->size--;
    }

    int getSize() const {
        return this->size;
    }

    class Iterator{
    private:
        const Node<T> *actual;
    public:
        Iterator() : actual{nullptr} {}

        Iterator(const Node<T> *other){
            this->actual = other;
        }

        Iterator &operator++(){
            if(this->actual)
                this->actual = this->actual->next.get();
            return *this;
        }
        Iterator operator++(int){
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
        bool operator!=(const Iterator &other){
            return this->actual != other.actual;
        }
        int operator*(){
            return this->actual->elem;
        }
    };

    Iterator begin(){
        return Iterator(this->head.get());
    }

    Iterator end(){
        return Iterator();
    }

    ~List(){
        while(this->head)
            this->head = std::move(head->next);
    }

    friend std::ostream& operator<< <>(std::ostream &os, const List<T> &list);
};


int main(){
    List<int> list;
    list.insert(2);
    list.insert(4);
    list.insert(9);
    list.insert(5);
    list.insert(0);

    for(List<int>::Iterator i = list.begin(); i != list.end(); ++i){
        std::cout << *i << ' ';
    }
    std::cout << '\n';

    std::cout << "list: " << list << '\n';

    List<int> list2 = list;
    std::cout << "list: " << list << '\n';
    std::cout << "list2: " << list2 << '\n';

    std::cout << "Remove first element of list2" << '\n';
    list2.remove();
    std::cout << "list: " << list << '\n';
    std::cout << "Size list: " << list.getSize() << '\n';
    std::cout << "list2: " << list2 << '\n';
    std::cout << "Size list2: " << list2.getSize() << '\n';

    List<int> list3 = std::move(list);
    std::cout << "list: " << list << '\n';
    std::cout << "list3: " << list3 << '\n';

    return 0;
}
