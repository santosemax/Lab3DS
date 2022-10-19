// IGNORE THISE
// #include <iostream>

// using namespace std;

// template<class T>
// class Node
// {
//     T *data;
//     Node<T> *next;
// };

// template<class T>
// class Ordered_Link_List
// {
//     Node<T> *head;
//     int size;

// public:
//     // Default Constructor
//     Ordered_Link_List();

//     // Constructor
//     Ordered_Link_List(const Ordered_Link_List &new_l);

//     // Destructor
//     ~Ordered_Link_List();
    
//     // Reset List
//     void reset();
    
//     // Operator Overrides
//     // = Override
//     Ordered_Link_List<T>& operator=(const Ordered_Link_List &new_l);
//     // += Override to add items to list
//     Ordered_Link_List<T>& operator+=(T *data);
//     // -= Override to remove items from list
//     Ordered_Link_List<T>& operator-=(T *data);
//     // SeeAt - [] Override to see at index 'i'
//     T* operator[](int i);
//     // << Override to see TODO!!!!
//     friend ostream& operator<<(ostream &out,const Ordered_Link_List<T> &new_l){

//         for (int i = 0; i < new_l.size; i++)
//             out << "\n" << *(new_l[i]);

//         return out;
//     }

//     void SeeNext(int i); 
   

//     // Return if item is in list
//     bool IsInList(Node<T> input);

//     // Return if list is empty
//     bool IsEmpty(Ordered_Link_List<T> &new_l);
    
//     // Return size of list
//     int getSize()const;

// };