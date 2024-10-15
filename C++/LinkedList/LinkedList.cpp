#include "LinkedList.h"


void LinkedList::insert(std::size_t index)
{
    Node* current = this->head;
    for(std::size_t i = 0; i < index && current != nullptr; ++i)
    {
        current = current->next;
    }
}
