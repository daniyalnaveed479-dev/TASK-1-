#include <iostream>
#include <string>
using namespace std;

struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;

public:

    PriorityQueue()
    {
        front = NULL;
        rear = NULL;
    }

    void Add(BookRequestNode* request)
    {
        request->next = NULL;

        if (front == NULL)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* temp = front;

            while (temp->next != NULL &&
                   temp->next->priority <= request->priority)
            {
                temp = temp->next;
            }

            request->next = temp->next;
            temp->next = request;

            if (request->next == NULL)
            {
                rear = request;
            }
        }
    }

    BookRequestNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        BookRequestNode* temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        temp->next = NULL;
        return temp;
    }

    bool IsEmpty()
    {
        return front == NULL;
    }

    void PrintQueue()
    {
        if (front == NULL)
        {
            cout << "Queue is empty." << endl;
            return;
        }

        BookRequestNode* temp = front;

        while (temp != NULL)
        {
            cout << "\nStudent ID: " << temp->studentID;
            cout << "\nStudent Name: " << temp->studentName;
            cout << "\nBook ID: " << temp->bookID;
            cout << "\nBook Title: " << temp->bookTitle;
            cout << "\nPriority: " << temp->priority;
            cout << "\n------------------------";

            temp = temp->next;
        }

        cout << endl;
    }

    ~PriorityQueue()
    {
        while (front != NULL)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main()
{
    PriorityQueue q;
    int choice;

    do
    {
        cout << "\n===== Library Book Request System =====";
        cout << "\n1. Add Book Request";
        cout << "\n2. Process Highest Priority Request";
        cout << "\n3. Display All Requests";
        cout << "\n4. Check Queue Status";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            BookRequestNode* request = new BookRequestNode;

            cout << "Enter Student ID: ";
            cin >> request->studentID;

            cout << "Enter Student Name: ";
            cin >> request->studentName;

            cout << "Enter Book ID: ";
            cin >> request->bookID;

            cout << "Enter Book Title: ";
            cin >> request->bookTitle;

            cout << "Enter Priority (1-3): ";
            cin >> request->priority;

            q.Add(request);

            cout << "Request added successfully!" << endl;
        }

        else if (choice == 2)
        {
            BookRequestNode* request = q.Remove();

            if (request == NULL)
            {
                cout << "Queue is empty." << endl;
            }
            else
            {
                cout << "\nProcessing Request";
                cout << "\nStudent: " << request->studentName;
                cout << "\nBook: " << request->bookTitle;
                cout << "\nPriority: " << request->priority << endl;

                delete request;
            }
        }

        else if (choice == 3)
        {
            q.PrintQueue();
        }

        else if (choice == 4)
        {
            if (q.IsEmpty())
                cout << "Queue is empty." << endl;
            else
                cout << "Queue is not empty." << endl;
        }

        else if (choice == 5)
        {
            cout << "Program ended." << endl;
        }

        else
        {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}
