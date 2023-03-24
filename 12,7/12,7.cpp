#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Textbook {
    string author;
    string title;
    int approvals;
    Textbook* next;
};

Textbook* addTextbook(Textbook* head, string author, string title, int approvals) {
    Textbook* newBook = new Textbook;
    newBook->author = author;
    newBook->title = title;
    newBook->approvals = approvals;
    newBook->next = NULL;

    if (head == NULL) {
        head = newBook;
    }
    else {
        Textbook* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }

    return head;
}

void printTextbooks(Textbook* head) {
    cout << "List of textbooks:" << endl;
    Textbook* temp = head;
    while (temp != NULL) {
        cout << temp->title << " by " << temp->author << " (" << temp->approvals << " approvals)" << endl;
        temp = temp->next;
    }
}

Textbook* filterTextbooks(Textbook* head, int minApprovals) {
    Textbook* filteredHead = NULL;
    Textbook* temp = head;
    while (temp != NULL) {
        if (temp->approvals >= minApprovals) {
            filteredHead = addTextbook(filteredHead, temp->author, temp->title, temp->approvals);
        }
        temp = temp->next;
    }
    return filteredHead;
}

int main() {
    Textbook* head = NULL;

    // Ask user for input method
    int inputMethod;
    cout << "Enter 1 to input from keyboard or 2 to input from file: ";
    cin >> inputMethod;

    if (inputMethod == 1) {
        // Input from keyboard
        string author, title;
        int approvals;
        char continueInput;
        do {
            cout << "Enter author: ";
            cin >> author;
            cout << "Enter title: ";
            cin >> title;
            cout << "Enter number of approvals: ";
            cin >> approvals;

            head = addTextbook(head, author, title, approvals);

            cout << "Add another textbook? (y/n): ";
            cin >> continueInput;
        } while (continueInput == 'y');
    }
    else if (inputMethod == 2) {
        // Input from file
        string filename;
        cout << "Enter filename: ";
        cin >> filename;

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file" << endl;
            return 1;
        }

        string author, title, approvalsStr;
        int approvals;
        while (file >> author >> title >> approvalsStr) {
            try {
                approvals = stoi(approvalsStr);
            }
            catch (invalid_argument& e) {
                cerr << "Invalid number of approvals: " << approvalsStr << endl;
                continue;
            }

            head = addTextbook(head, author, title, approvals);
        }

        file.close();
    }
    else {
        cout << "Invalid input method" << endl;
        return 1;
    }

    printTextbooks(head);

    int minApprovals;
    cout << "Enter minimum number of approvals for filtering: ";
    cin >> minApprovals;

    Textbook* filteredHead = filterTextbooks(head, minApprovals);

    printTextbooks(filteredHead);

    return 0;
}
