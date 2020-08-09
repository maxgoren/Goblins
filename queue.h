namespace MaxCode {

template <class T>
class Queue {
private:
  struct node {
    T key;
    struct node* next;
  };
  struct node *head, *z;
public:
  void push(T v);
  T pop();
  T front();
  int empty();
  void clear();
  Queue();
  ~Queue();
};

template <class T>
Queue<T>::Queue()
{
  head = new node;
  z = new node;
  head->next = z;
  z->next = head;
}

template <class T>
Queue<T>::~Queue()
{
  struct node *t = head;
  while (t != z)
  {
   head = t;
   t = t->next;
   delete head;
  }
}

template <class T>
void Queue<T>::push(T v)
{
 struct node *t = new node;
 t->next = head->next;
 t->key = v;
 head->next = t;
}

template <class T>
T Queue<T>::pop()
{
 T x;
 struct node *t = head;
 while (t->next->next != z)
 {
   t=t->next;
 }
  x = t->next->key;
  t->next = z; 
  return x;
}

template <class T>
void Queue<T>::clear()
{
  while (!empty())
    pop();
}

template <class T>
T Queue<T>::front()
{
  struct node *t = head;
  while (t->next->next != z)
  {
    t = t->next;
  }
  return t->next->key;
}

template <class T>
int Queue<T>::empty()
{
 return head->next == z;
}

};
