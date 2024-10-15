#ifndef LINKED_LIST
#define LINKED_LIST

template <typename K>
class LinkedList
{
    private:
    class Node 
    {
        public:
        K* data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {};
    };
    Node* head;
    std::size_t size;

    public:
    LinkedList() : head(nullptr), size(0);
    LinkedList();
    void insert(std::size_t index));
    void remove(std::size_t index);
    std::size_t getSize();
    Node::~Node();

};


#endif
