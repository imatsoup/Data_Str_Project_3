#include "Sequence.h"

Sequence::Sequence(size_type sz)
{
    numElts = sz;
    for(int i = 0; i < numElts; i++){
        SequenceNode *newNode = new SequenceNode();
        if(i <= 0){
            head = newNode;
        }
        else if(i == 1){
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
        if(i == 0){
            head = newNode;
        }
        else if(i == 1){
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
    Sequence *newSeq = new Sequence(s.numElts);
    SequenceNode *replacement = newSeq->head;
    SequenceNode *oldNode = s.head;
    for(int i = 0; i < numElts; i++){
        replacement = oldNode;
        replacement = replacement->next;
        if(i == numElts){
            newSeq->tail = replacement;
        }
        delete oldNode;
    }
    delete &s;
    return *newSeq;
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
    if(tail == NULL){
        head = placeHolder;
        tail = placeHolder;
    }
    else{
    placeHolder->prev = tail;
    tail->next = placeHolder;
    tail = placeHolder;
    }
    numElts++;
}

void Sequence::pop_back()
{
    SequenceNode * placeHolder = NULL;
    if(numElts > 0){
        if(numElts == 1){
        delete head;
        numElts--;
    }
    
    else{
        placeHolder = tail->prev;
        delete tail;
        tail = placeHolder;
        tail->next = NULL;
        numElts--;
    }
    }
    else{
        throw exception();
    }
}

void Sequence::insert(size_type position, value_type value)
{
    if(position > numElts || position < 0){
    throw exception();
    }
    if(position == numElts){
        push_back(value);
    }
    else if(position == 0){
        SequenceNode *tempPtr = new SequenceNode;
        tempPtr-> elt = value;
        tempPtr-> prev = NULL;
        tempPtr-> next = head;
        head = tempPtr;
    }
    else{
        SequenceNode *tempPtr = head;
        for(int i = 0; i < position; i++){
            tempPtr = tempPtr->next;
        }
        SequenceNode *oldPtr = tempPtr;
        oldPtr->next = tempPtr;
        tempPtr->prev = oldPtr;
        tempPtr->elt = value;

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
     if(numElts <= 0){
    throw exception();
    }
    SequenceNode * deleteTarget = NULL;
    SequenceNode *placeHolder = head;
    for(int i = 0; i < numElts; i++){
        deleteTarget = placeHolder;
        placeHolder = placeHolder->next;
        delete deleteTarget;
    }
   
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

string Sequence::toString(){
    string rtString = "<";
    SequenceNode*placeHolder = head;
    for(int i = 0; i < numElts; i++){
        rtString += to_string(placeHolder->elt);
        rtString += " ";
        placeHolder = placeHolder->next;
    }
    rtString += ">";
    return rtString;
}

ostream& operator<<(ostream& os, const Sequence& s)
{
    Sequence target = s;
    os << " " << target.toString() << endl;
    return os;
}