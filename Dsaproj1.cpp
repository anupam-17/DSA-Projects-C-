#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    string description;
    bool completed;

    Task(const string& desc) : description(desc), completed(false) {}
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& description) {
        Task task(description);
        tasks.push_back(task);
        cout << "Task added successfully.\n";
    }

    void markTaskAsCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].completed = true;
            cout << "Task marked as completed.\n";
        } else {
            cout << "Invalid task index.\n";
        }
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks to display.\n";
            return;
        }

        cout << "To-Do List:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << "[" << i + 1 << "] " << (tasks[i].completed ? "[X] " : "[ ] ") << tasks[i].description << "\n";
        }
    }

    void removeCompletedTasks() {
        tasks.erase(remove_if(tasks.begin(), tasks.end(), [](const Task& task) {
            return task.completed;
        }), tasks.end());

        cout << "Completed tasks removed.\n";
    }
};

int main() {
    ToDoList toDoList;

    while (true) {
        cout << "\nTo-Do List Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Task as Completed\n";
        cout << "3. View Tasks\n";
        cout << "4. Remove Completed Tasks\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string description;
                cout << "Enter task description: ";
                cin.ignore(); // Ignore the newline character in the buffer
                getline(cin, description);
                toDoList.addTask(description);
                break;
            }

            case 2: {
                int index;
                cout << "Enter the index of the task to mark as completed: ";
                cin >> index;
                toDoList.markTaskAsCompleted(index - 1); // Adjust index to 0-based
                break;
            }

            case 3:
                toDoList.viewTasks();
                break;

            case 4:
                toDoList.removeCompletedTasks();
                break;

            case 5:
                cout << "Exiting To-Do List. Bye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
