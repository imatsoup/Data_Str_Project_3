#include "Sequence.h"

Sequence::Sequence(size_type sz)
{
    numElts = sz;
    for(int i = 0; i < numElts; i++){
        SequenceNode *newNode = new SequenceNode();
        newNode -> elt = NULL;
        if(i = 0){
            head = newNode;
        }
        else if(i = 1){
            head ->next = newNode;
            tail = newNode;
            tail->prev = head;
        }
        else{
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;
        }
    }
}

Sequence::Sequence(const Sequence& s)
{
    numElts = s.numElts;
    SequenceNode *placeHolder = s.head;
    for(int i = 0; i < numElts; i++){
        SequenceNode *newNode = new SequenceNode(placeHolder->elt);
        if(i = 0){
            head = newNode;
        }
        else if(i = 1){
            tail = newNode;
            tail->prev = head;
            head->next = tail;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        placeHolder = placeHolder->next;
    }
}

Sequence::~Sequence()
{
}

Sequence& Sequence::operator=(const Sequence& s)
{
    Sequence newSeq = new Sequence(s.numElts);
    return *this;
}

Sequence::value_type& Sequence::operator[](size_type position)
{
    if(position > numElts || position < 0){
    throw exception();
    }
    SequenceNode *placeHolder = head;
    for(int i = 0; i < position; i ++){
        placeHolder = placeHolder->next;
    }
    return placeHolder->elt;
}

void Sequence::push_back(const value_type& value)
{
    SequenceNode * placeHolder = new SequenceNode(value);
    placeHolder->prev = tail;
    tail->next = placeHolder;
    tail = placeHolder;
}

void Sequence::pop_back()
{
    SequenceNode * placeHolder = NULL;
    if(numElts > 0){
    placeHolder = tail->prev;
    delete tail;
    tail = placeHolder;
    tail->next = NULL;
    numElts--;
    }
    else{
    throw exception();
    }
}

void Sequence::insert(size_type position, value_type value)
{
    if(position = numElts){
        SequenceNode *tempPtr = new SequenceNode;
        tempPtr-> elt = value;
        tempPtr-> prev = tail;
        tempPtr-> next = NULL;
        tail = tempPtr;
    }
    else if(position == 0){
        SequenceNode *tempPtr = new SequenceNode;
        tempPtr-> elt = value;
        tempPtr-> prev = NULL;
        tempPtr-> next = head;
        head = tempPtr;
    }
    if(position > numElts || position < 0){
    throw exception();
    }
    numElts++;
}

const Sequence::value_type& Sequence::front() const
{   
    if(numElts <= 0){
    throw exception();
    }
    return head->elt;
}

const Sequence::value_type& Sequence::back() const
{
    if(numElts <= 0){
    throw exception();
    }
    return tail->elt;
}

bool Sequence::empty() const
{
    if(numElts == 0){
        return true;
    }
    return false;
}

Sequence::size_type Sequence::size() const
{
    return numElts;
}

void Sequence::clear()
{
    throw exception();
}

void Sequence::erase(size_type position, size_type count)
{   
    SequenceNode *placeHolder = head;
    if(position >= 0 && position + count - 1 <= numElts){
        for(int i = 0; i < position+count; i++){
            if(i < position){
                placeHolder = placeHolder->next;
            }
            else{
                SequenceNode *destructible = placeHolder;
                placeHolder = placeHolder->next;
                delete destructible;
            }
        }
    }
    else{
    throw exception();
    }
}


ostream& operator<<(ostream& os, const Sequence& s)
{
    return os;
}