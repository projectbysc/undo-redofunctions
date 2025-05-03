#include <iostream>
#include <string>

using namespace std;

struct Node {
    string text;
    Node* prev;
    Node* next;

    Node(string t) : text(t), prev(nullptr), next(nullptr) {}
};

class TextEditor {
private:
    Node* head;
    Node* current;

public:
    TextEditor() {
        head = new Node("");
        current = head;
    }

    void typeText(const string& newText) {
        while (current->next != nullptr) {
            Node* temp = current->next;
            current->next = temp->next;
            if (temp->next) temp->next->prev = current;
            delete temp;
        }

        Node* newNode = new Node(current->text + newText);
        newNode->prev = current;
        current->next = newNode;
        current = newNode;
        cout << "Text added.\n";
    }

    void undo() {
        if (current->prev) {
            current = current->prev;
            cout << "Undo performed.\n";
        } else {
            cout << "Nothing to undo.\n";
        }
    }

    void redo() {
        if (current->next) {
            current = current->next;
            cout << "Redo performed.\n";
        } else {
            cout << "Nothing to redo.\n";
        }
    }

    void showText() {
        cout << "Current Text: " << current->text << "\n";
    }

    ~TextEditor() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TextEditor editor;
    int choice;
    string input;

    do {
        cout << "\n--- Text Editor Menu ---\n";
        cout << "1. Type Text\n";
        cout << "2. Undo\n";
        cout << "3. Redo\n";
        cout << "4. Show Current Text\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter text to add: ";
                getline(cin, input);
                editor.typeText(input);
                break;
            case 2:
                editor.undo();
                break;
            case 3:
                editor.redo();
                break;
            case 4:
                editor.showText();
                break;
            case 5:
                cout << "Exiting editor.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
