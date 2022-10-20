#include<iostream>
using namespace std;

template<typename T>
class Node{
public:
    T *data;
    Node<T> *next;
    Node<T> *prev;

};

template<typename T>
class LinkedList{
    private:
        Node<T>* head = new Node<T>;
        int size;

        // Two variables used to keep track of SeeAt
        // and SeeNext
        Node<T>* seePlace = new Node<T>;
        bool seePlaceSet;

    public:
        // Constructor
        LinkedList(){
            this->head = NULL;
            this->size = 0;
            this->seePlace = nullptr;
            this->seePlaceSet = false;
        }

        // Destructor
        ~LinkedList()
        {
            Node<T>* seePlace = head;
            while (seePlace)
            {
                head = head->next;
                delete seePlace;
                seePlace = head;
            }
        }

        // AddItem
        void AddItem(T* item){
            Node<T>* node = new Node<T>;
            node->data = item;
            if (head == NULL){
                head = node;
                head->prev = NULL;
                seePlace = head;
                
                cout << head->data->GetName() << endl;
                return;
            }
            Node<T>* temp = head;
            Node<T>* prev = head;
            while(temp->next != NULL){
                prev = temp;
                temp = temp->next;
            }
            temp->next = node;
            temp->next->prev = head;


            // DEBUG
            if (head->prev == NULL)
                cout << "Head prev == NULL";
            if (head->next == NULL)
                cout << "Head next == NULL";
            else
                cout << "Head next == " << head->next->data->GetName() << endl;

            if (head->next->prev == head)
                cout << "Marc prev == head" << endl;
            if (head->next->prev == NULL)
                cout << "Marc prev == NULL" << endl;
            if (head->next->next == NULL)
                cout << "Marc next == NULL" << endl;
        }

        // GetItem
        void GetItem(int index)
        {
            // Check if index is in bounds
            if (index > Size()-1 || index < 0)
            {
                cout << "Index out of bounds. (0-based indexing)" << endl;
                return;
            }
            
            // Check if list in empty
            if (Size() == 0)
            {
                cout << "No nodes in list" << endl;
                return;
            }

            // Get item
            Node<T>* temp = head;
            Node<T>* prev = head;
            int count = 0;
            while (temp->next != NULL && count <= index-1)
            {
                prev = temp;
                temp = temp->next;
                count++;
            }
            cout << temp->data->GetName() << endl;

            // Remove items
            if (temp == head && head->next != NULL)
            {
                head = head->next;
                head->prev = NULL;
            }
            else if (temp == head && head->next == NULL)
            {
                // RUN RESET?
            }
            else 
                prev->next = temp->next;

            
        }

        bool IsInList(int mNum)
        {
            // Check if head exists
            if (head == NULL)
            {
                cout << "List is empty" << endl;
                return false;
            }

            Node<T>* temp = head;
            // Check head
            if (head->data->GetMNum() == mNum)
            {
                return true;
            }
            // Check rest 
            while (temp != NULL)
            {
                if (temp->data->GetMNum() == mNum)
                {
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }

        bool IsEmpty()
        {
            if (Size() == 0)
                return true;
            return false;
        }

        int Size(){
            int len = 0;
            Node<T>* temp = head;
            while (temp != NULL)
            {
                len++;
                temp = temp->next;
            }
            return len;
        }

        void PrintList(){
            if (head == NULL)
            {
                cout << "The Linked List is Empty" << endl;
                return;
            }
            cout << endl << "**** Items *************************" << endl;
            Node<T>* temp = head;
            while (temp != NULL){
                cout << temp->data->GetName() << " * ";
                temp = temp->next;
            }
            cout << endl;
        }

        Node<T>* SeeAt(int index)
        {
            // Check if index is in bounds
            if (index > Size()-1 || index < 0)
            {
                cout << "Index out of bounds. (0-based indexing)" << endl;
            }
            
            // Check if list in empty
            if (Size() == 0)
            {
                cout << "Error: No nodes in list." << endl;
            }

            // get item
            Node<T>* temp = head;
            Node<T>* prev = head;
            int count = 0;
            while (temp->next != NULL && count <= index-1)
            {
                prev = temp;
                temp = temp->next;
                count++;
            }

            seePlace = temp;
            seePlaceSet = true;
            return seePlace;
        }

        Node<T>* SeeNext()
        {
            // Check if list in empty
            if (Size() == 0)
            {
                cout << "Error: No nodes in list." << endl;
            }

            // Check if SeeAt has been used
            if (!seePlaceSet)
            {
                seePlaceSet = true;
                seePlace = head;
                return seePlace;
            }

            // Get item using SeeAt()
            if (seePlace->next == NULL)
                return NULL;
            else
            {
                seePlace = seePlace->next;
                return seePlace;
            }
        }

        void Reset()
        {
            seePlaceSet = false;
            seePlace = head;
        }
};

class Student
{
    private: 
        string firstName;
        string lastName;
        int mNum;
        float gpa;
        int bDay;

    public: 
    // Default Constructor
    Student();

    // Constructor w/ optional gpa parameter
    Student(string fname, string lname, int mnum, int bday, int gpa = 0.0)
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
        return 2022 - bDay;
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

int main()
{

    LinkedList<Student> list;
    int choice, item, index;
    bool quit = false;

    do
    {
        cout << "************************************" << endl;
        cout << "Select an Option Below:" << endl;
        cout << "1: AddItem" << endl;
        cout << "2: GetItem" << endl;
        cout << "3: IsInList" << endl;
        cout << "4: IsEmpty" << endl;
        cout << "5: Size" << endl;
        cout << "6: PrintList" << endl;
        cout << "7: SeeAt" << endl;
        cout << "8: SeeNext" << endl;
        cout << "9: Reset" << endl;
        cout << "10: Quit (Destructor)" << endl;
        cin >> choice;
        cout << "************************************" << endl;

        string fName, lName;
        int index, mNum_search;
        Node<Student>* temp = new Node<Student>; // used in case 8

        switch (choice)
        {
        // AddItem Case
        case 1:
            // list.AddItem(test);
            // list.PrintList();

            int mNum, bDay;
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

            if (ans == 'y')
            {
                cin >> gpa; 
                Student* newStudent = new Student(fName, lName, mNum, bDay, gpa);
                list.AddItem(newStudent);
            }
            else if (ans == 'n') 
            {
                Student* newStudent = new Student(fName, lName, mNum, bDay);
                list.AddItem(newStudent);
            }
            else
            {
                cout << "Wrong Input for GPA (y/n) (lowercase)" << endl;
                return 1;
            }
            list.PrintList();
            break;
        // GetItem Case
        case 2:
            cout << "Please input index to get item at: ";
            cin >> index;

            list.GetItem(index);
            break;
        // IsInList Case
        case 3:
            cout << "Please input MNumber: ";
            cin >> mNum_search;
            
            if (list.IsInList(mNum_search))
                cout << "True" << endl;
            else
                cout << "False" << endl;
            break;
        // IsEmpty Case
        case 4:
            if (list.IsEmpty())
                cout << "True" << endl;
            else
                cout << "False" << endl;
            break;
        // Size Case
        case 5:
            cout << "Size: " << list.Size() << endl;
            break;
        // Printing (Just in case needed for testing)
        case 6:
            list.PrintList();
            break;
        // SeeAt Case
        case 7:
            cout << "Please input index to get item at: ";
            cin >> index;

            if (list.SeeAt(index) == NULL)
                cout << "NULL" << endl;
            else 
                cout << list.SeeAt(index)->data->GetName() << endl;
            break;
        // SeeNext Case
        case 8:
            temp = list.SeeNext();
            if (temp == NULL)
                cout << "NULL" << endl;
            else
                cout << temp->data->GetName() << endl;
            break;
        // Reset Case
        case 9:
            list.Reset();
            cout << "See location reset to head." << endl;
            break;
        case 10:
            delete temp;
            quit = true;
            break;
        default:
            cout << "invalid selection" << endl;
            break;
        }

    } while (!quit);
    return 0;
}