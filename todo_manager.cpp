#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string title;
    bool completed;
};

vector<Task> tasks;

void loadTasks() {
    ifstream file("tasks.txt");
    if (!file) return;

    Task t;
    while (getline(file, t.title)) {
        string status;
        getline(file, status);
        t.completed = (status == "1");
        tasks.push_back(t);
    }
    file.close();
}

void saveTasks() {
    ofstream file("tasks.txt");
    for (auto &t : tasks) {
        file << t.title << "\n" << (t.completed ? "1" : "0") << "\n";
    }
    file.close();
}

void addTask() {
    Task t;
    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, t.title);
    t.completed = false;
    tasks.push_back(t);
    saveTasks();
    cout << "\n✅ Task added successfully!\n";
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "\n⚠️  No tasks available.\n";
        return;
    }
    cout << "\n📋 To-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].completed ? "✔" : "✖") << "] " << tasks[i].title << "\n";
    }
}

void markCompleted() {
    int num;
    viewTasks();
    cout << "\nEnter task number to mark complete: ";
    cin >> num;

    if (num > 0 && num <= (int)tasks.size()) {
        tasks[num - 1].completed = true;
        saveTasks();
        cout << "✅ Task marked as completed!\n";
    } else {
        cout << "❌ Invalid task number!\n";
    }
}

void deleteTask() {
    int num;
    viewTasks();
    cout << "\nEnter task number to delete: ";
    cin >> num;

    if (num > 0 && num <= (int)tasks.size()) {
        tasks.erase(tasks.begin() + num - 1);
        saveTasks();
        cout << "🗑️  Task deleted successfully!\n";
    } else {
        cout << "❌ Invalid task number!\n";
    }
}

int main() {
    loadTasks();
    int choice;

    while (true) {
        cout << "\n========== TO-DO LIST MANAGER ==========\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Completed\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "=======================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(); break;
            case 4: deleteTask(); break;
            case 5:
                cout << "\n👋 Exiting... Have a productive day!\n";
                return 0;
            default:
                cout << "⚠️ Invalid choice! Try again.\n";
        }
    }
}
