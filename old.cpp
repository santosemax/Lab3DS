#include <iostream>

using namespace std;

// TASK 1 CLASSES - ***********************************
template<class S>
class Node
{
    S *data;
    Node *next;

public:
    // setter for data
    void setData(T* item)
    {
        this->data = item;
    }

    // getter for data
    void getData(T item)
    {
        return this->data;
    }
};

template<class T>
class Ordered_Link_List
{
    Node<T> *head;
    int size;

public:
    // Default Constructor
    Ordered_Link_List();

    // Constructor
    Ordered_Link_List(const Ordered_Link_List &new_l);

    // Destructor
    ~Ordered_Link_List();
    
    // Operator Overrides
    // = Override
    Ordered_Link_List<T>& operator=(const Ordered_Link_List &new_l);
    // += Override to add items to list
    Ordered_Link_List<T>& operator+=(T *data);
    // -= Override to remove items from list
    Ordered_Link_List<T>& operator-=(T *data);
    // SeeAt - [] Override to see at index 'i'
    T* operator[](int i);
    // << Override to see TODO!!!!
    friend ostream& operator<<(ostream &out,const Ordered_Link_List<T> &new_l){

        for (int i = 0; i < new_l.size; i++)
            out << "\n" << *(new_l[i]);

        return out;
    }

    T* SeeNext(int i); 
   
    // Return if item is in list
    bool IsInList(Node<T> input);

    // Return if list is empty
    bool IsEmpty(Ordered_Link_List<T> &new_l);
    
    // Return size of list
    int getSize()const;

    // Reset List
    void reset();

};

// TASK 2 CLASSES - ***********************************
class Student
{
private: 
    string firstName;
    string lastName;
    int mNum;
    float gpa;
    string bDay;

public: 
// Default Constructor
Student();

// Constructor w/ optional gpa parameter
Student(string fname, string lname, int mnum, string bday, int gpa = 0.0)
{
    firstName = fname;
    lastName = lname;
    mNum = mnum;
    bDay = bday;
    gpa = gpa;
}

string GetName()
{
    return (firstName + " " + lastName);
}

int GetMNum()
{
    return mNum;
}

int GetAge()
{ 
    int curryear;
    int year;

    cout << "Enter year of birth";
    cin >> year;
    cout << "Enter current year";
    cin >> curryear;

    int Age = curryear - year;

    return Age;
}

// Operator Overrides
// < Override to compare two Students MNumbers
bool operator <(const Student& input_student) 
{
    if(mNum < input_student.mNum)
        return true;
    else
        return false;
}
// > Override to compare two Students MNumbers
bool operator >(const Student& input_student) 
{
    if (mNum > input_student.mNum)
        return true;
    else
        return false;
}
// < Override to compare two Students MNumbers equivalency
bool operator ==(const Student& input_student) 
{
    if(mNum == input_student.mNum)
        return true;
    else
        return false;
}
};

// TASK 1 IMPLEMENTATION - ************************************
// Default Constructor
template<class T>
Ordered_Link_List<T>::Ordered_Link_List()
{
    head = NULL;
    size = 0;
}

// Constructor
template<class T>
Ordered_Link_List<T>::Ordered_Link_List(const Ordered_Link_List<T> &new_l)
{
    *this = new_l;
}

// Set list equal to new list
template<class T>
Ordered_Link_List<T>& Ordered_Link_List<T>::operator=(const Ordered_Link_List<T> &new_l)
{
    if (this == &new_l)
        return *this;
    
    this->size = new_l.size;

    reset();

    for (int i = 0; i < size; i++)
    {
        (*this)[i] = new_l[i];
    }

    return *this;
}

// Destructor - Resets list
template<class T>
Ordered_Link_List<T>::~Ordered_Link_List()
{
    reset();
}

// Reset - Empties list only if list isn't already empty and has 
// items in it
template<class T>
void Ordered_Link_List<T>::reset()
{
    while (size != 0){
        (*this) -= (*this)[0];
    }
}

// Add Item - Adds item to list using operator '+='
template<class T>
Ordered_Link_List<T>& Ordered_Link_List<T>::operator+=(T *data)
{
    Node<T> *temp = new Node<T>;

    temp->data = data;
    temp->next = head;
    head = temp;
    size++;

    return *this;
}

// GetItem - Searches for item and removes it if found and 
// returns it using operator '-='
template<class T>
Ordered_Link_List<T>& Ordered_Link_List<T>::operator-=(T *data)
{
    // check if size of list is 0
    if (size == 0){
        return *this;
    }

    // Set temp head and prev for traversal
    Node<T> *temp = head;
    Node<T> *prev = NULL;

    // update temp as I traverse the list. Check if data is found
    // and replace it if so. Return out
    while (temp != NULL)
    {
        if (data == temp->data)
        {
            if (prev == NULL)
            {
                head = head->next;
                size--;

                delete temp;

                return *this;
            }

            prev->next = temp->next;
            delete temp;
            size--;

            return *this;
        }
        prev = temp;
        temp = temp->next;
    }

    return *this;
}

// SeeAt - Returns if item is in list at index i
template<class T>
T* Ordered_Link_List<T>::operator[](int i){

    // Locate item and store in tmp using SeeNext
    T* foundItem = Ordered_Link_List<T>::SeeNext(i);

    return foundItem;
}

template<class T>
T* Ordered_Link_List<T>::SeeNext(int i)
{
    // Check if list is empty
    // if (IsEmpty(head))
    // {
    //     cout << "ERROR: List is empty." << endl;
    //     return NULL;
    //     // return;
    // }

    // Throw error and return NULL if item is 
    // outside of list size or negative
    if (i < 0 && i >= size)
    {
        cout << "ERROR: Index is not in range of list." << endl;
        return NULL;
        // return;
    }

    T *tmp = NULL;
    Node<T> *temp = head;

    // Return node at position next of index 'i'
    for (int j = 0; j <= i; j++)
    {
        if (temp->next == NULL)
        {
            return NULL;
            // return;
        }
        temp = temp->next;
    }
    tmp = temp->data;

    // return found item
    return tmp;
    // cout << tmp;
}

// IsInList - Return true if node is in list (by checking data)
template<class T>
bool Ordered_Link_List<T>::IsInList(Node<T> input)
{
    Node<T> *temp = head;
    Node<T> *prev = NULL;

    while (temp != NULL)
    {
        if (input->data == temp->data)
            return true;
        if (input->next == NULL)
            return false;
    }
    // just in case return out false
    return false;
}

// IsEmpty - Return if list is empty
template<class T>
bool IsEmpty(Ordered_Link_List<T> &new_l)
{
    if (new_l.getSize() == 0)
        return true;
    return false;
}

// Return size of list - Used in IsEmpty()
template<class T>
int Ordered_Link_List<T>::getSize()const{
    return size;
}

// TASK 3 (TEST PROGRAM) - **************************************
int main(void)
{

    Ordered_Link_List<Student> testList;

    // Present choice of public member functions of linked list class
    // and ask user which to try?
    cout << "Which public member function of the linked list class";
    cout << " would you like to try?";
    cout << "- AddItem" << endl << "- GetItem" << endl << "- IsInlist" << endl;
    cout << "- IsEmpty" << "- Size" << endl << "- SeeNext" << endl << "- SeeAt";
    cout << endl << "- Reset" << endl << "Destructor" << endl;

    string input;
    cin >> input;

    // AddItem
    if (input == "AddItem")
    {
        Student newStudent;
        string fName, lName, bDay;
        int mNum;
        float gpa;
        // Get info
        cout << "Input first name: ";
        cin >> fName;
        cout << "Input last name: ";
        cin >> lName;
        cout << "Input MNumber: ";
        cin >> mNum;
        cout << "Input Birthday: ";
        cin >> bDay;

        // GPA
        char ans;
        cout << "Would you like to input a GPA? (y/n): ";
        cin >> ans;

        if (ans == 'Y')
        {
            cin >> gpa; 
            Student newStudent(fName, lName, mNum, bDay, gpa);
            testList.
        }
        else if (ans == 'N') 
        {
            Student newStudent(fName, lName, mNum, bDay);
        }
        else
        {
            cout << "Wrong Input for GPA (y/n) (lowercase)" << endl;
            return 1;
        }

        // Add to Linked List
        // testList += newStudent;

    }

    

    return 0;
}