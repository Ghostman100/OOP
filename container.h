#pragma once

template <class T>
class MyElement
{
public:
    MyElement(T const& value, MyElement<T> *next): m_element(value), m_next(next)
    {

    }
    ~MyElement(){
        delete &m_element;
    }

    T m_element;
    MyElement<T>* m_next;
};

template <class T>
class Container
{
public:
    Container(): m_size(0), m_first(NULL), m_last(NULL)
    {

    }

    ~Container(){
        clearContainer();
    }

    void addFirstElement(T const &value){
        MyElement<T>* new_element = new MyElement<T>(value, m_first);
        if (m_first == NULL){
            m_last = new_element;
        }
        m_first = new_element;
        m_size++;
    }

    void addLastElement(T const &value){
        MyElement<T>* new_element = new MyElement<T>(value, NULL);
        if (m_size == 0){
            m_first = m_last = new_element;
        } else{
        m_last->m_next = new_element;
        m_last = new_element;
        if (m_last == NULL){
            m_first = new_element;
        }
        }
        m_size++;
    }

    void removeFirstElement(){
        if (m_size == 0){
            throw std::logic_error("Container is empty");
        }
        MyElement<T>* temp = m_first->m_next;
        delete m_first;
        m_first = temp;
        m_size--;
    }

    void removeLastElement(){
        if (m_size == 0){
            throw std::logic_error("Container is empty");
        }
        MyElement<T>* temp = m_first;
        while(temp->m_next != m_last){
            temp = temp->m_next;
        }
        delete m_last;
        m_last = temp;
        m_last->m_next = NULL;
        m_size--;
    }

    T getFirst() const {
        if (m_size == 0){
            throw std::logic_error("Container is empty!");
        }
        return m_first->m_element;
    }

    T getLast() const {
        if (m_size == 0){
            throw std::logic_error("Container is empty");
        }
        return m_last->m_element;
    }

    MyElement<T>* startIterate() const {
        return m_first;
    }

    MyElement<T>* finishIterate() const {
        return m_last;
    }

    int getSize(){
        return m_size;
    }

    bool isEmpty(){
        return m_size == 0;
    }

    void clearContainer(){
//        MyElement<T>* i = m_first;
//        while(i != m_last){
//            MyElement<T>* temp = i->m_next;
//            delete i->m_element;
//            i = temp;
//        }
//        delete i->m_element;
//        m_size=0;
        MyElement<T>* temp;
        while(m_first != NULL)
        {
            temp = m_first->m_next;
            delete m_first;
            m_first = temp;
        }
        m_size=0;
    }

    class Iterator
    {
    public:
        MyElement<T>* k;
        Iterator &next()
        {
            this->k = this->k->m_next;
            return *this;
        }
        Iterator getNext()
        {
            Iterator j;
            j.k = this->k->m_next;
            return j;
        }
        bool operator!=(Iterator t)
        {
            if (t.k == this->k)
                return false;
            return true;

        }

        Iterator()
        {
            this->k = NULL;
        }
    private:
    };
    friend Iterator;

    Iterator& begin()
    {
        Iterator *i = new Iterator();
        i->k = m_first;
        return *i;
    }

    Iterator& end()
    {
        Iterator *i = new Iterator();
        i->k = NULL;
        return *i;
    }

    T& operator[](Iterator& i)
    {
        return i.k->m_element;
    }

private:
    int m_size;
    MyElement<T>* m_first;
    MyElement<T>* m_last;
};
