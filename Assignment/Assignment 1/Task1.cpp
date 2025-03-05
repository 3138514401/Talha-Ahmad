#include <iostream>
#include <string>
using namespace std;

// Define the Task structure
struct Task {
    int id;
    string description;
    int priority;
    Task* next;
};

// Define the TaskManager class
class TaskManager {
private:
    Task* head; // Pointer to the first task in the list

public:
    // Constructor
    TaskManager() : head(nullptr) {}

    // Function to add a new task
    void addTask(int id, string description, int priority) {
        Task* newTask = new Task{id, description, priority, nullptr};

        // If the list is empty or the new task has higher priority than the head
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            // Traverse the list to find the correct position
            Task* current = head;
            while (current->next && current->next->priority >= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
        cout << "Task added successfully!\n";
    }

    // Function to remove the highest priority task
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        delete temp;
        cout << "Highest priority task removed.\n";
    }

    // Function to remove a task by ID
    void removeTaskById(int id) {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        // If the task to be removed is the head
        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task with ID " << id << " removed.\n";
            return;
        }
        // Traverse the list to find the task with the given ID
        Task* current = head;
        while (current->next && current->next->id != id) {
            current = current->next;
        }
        if (current->next) {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Task with ID " << id << " removed.\n";
        } else {
            cout << "Task with ID " << id << " not found.\n";
        }
    }

    // Function to view all tasks
    void viewTasks() {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        Task* current = head;
        while (current) {
            cout << "ID: " << current->id << ", Description: " << current->description
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }
};

// Main function
int main() {
    TaskManager tm;
    int choice, id, priority;
    string description;

    do {
        // Display the menu
        cout << "\nTask Management System\n";
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task ID: ";
                cin >> id;
                cin.ignore(); // Ignore the newline character
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                tm.addTask(id, description, priority);
                break;
            case 2:
                tm.viewTasks();
                break;
            case 3:
                tm.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter task ID to remove: ";
                cin >> id;
                tm.removeTaskById(id);
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
