//
//  main.cpp
//  task remainder
//
//  Created by Nipuna Lakruwan on 2023-11-12.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>//
#include <ctime>
#include <algorithm>

using namespace std;

struct Task {
    string description;
    time_t dueDate;
};

const string TASKS_FILE = "tasks.txt";

void saveTasks(const vector<Task>& tasks) {
    ofstream outFile(TASKS_FILE);

    if (!outFile.is_open()) {
        cerr << "Error opening tasks file for writing." << endl;
        return;
    }

    for (const auto& task : tasks) {
        outFile << task.description << "," << task.dueDate << endl;
    }

    outFile.close();
}

vector<Task> loadTasks() {
    vector<Task> tasks;
    ifstream inFile(TASKS_FILE);

    if (!inFile.is_open()) {
        cerr << "No existing tasks file found." << endl;
        return tasks;
    }

    while (!inFile.eof()) {
        Task task;
        getline(inFile, task.description, ',');
        inFile >> task.dueDate;

        // Ignore empty lines
        if (!task.description.empty()) {
            tasks.push_back(task);
        }

        // Consume newline character
        inFile.ignore();
    }

    inFile.close();
    return tasks;
}

void printTask(const Task& task) {
    tm* timeInfo = localtime(&task.dueDate);
    cout << "Description: " << task.description << endl;
    cout << "Due Date: " << put_time(timeInfo, "%Y/%m/%d %H:%M:%S") << endl;
    cout << "-----------------------------------" << endl;
}

void displayTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No task to Display, Please add task first to display! " << endl;
    }
            cout << "Tasks: " << endl;
        for (const auto& task : tasks) {
                printTask(task);
        }
    }

void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    

    cout << "Enter due date and time (YYYY/MM/DD HH:MM:SS): ";
    string dueDateString;
    getline(cin, dueDateString);

    struct tm dueDate = {};
    if (strptime(dueDateString.c_str(), "%Y/%m/%d %H:%M:%S", &dueDate) == nullptr) {
        cerr << "Invalid date and time format. Task not added." << endl;
        return;
    }

    newTask.dueDate = mktime(&dueDate);

    tasks.push_back(newTask);
    saveTasks(tasks);

    cout << "Task added successfully." << endl;
}

void removeTask(vector<Task>& tasks) {
    displayTasks(tasks);

    if (tasks.empty()) {
        cout << "No tasks to remove." << endl;
        return;
    }

    cout << "Enter the index of the task to remove: ";
    int index;
    cin >> index;

    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
        saveTasks(tasks);
        cout << "Task removed successfully." << endl;
    } else {
        cout << "Invalid index. Task not removed." << endl;
    }
}

int main() {
    vector<Task> tasks = loadTasks();

    int choice;
    do {
        cout << "-----------------------------------" << endl;
        cout << "Task Scheduler Menu:" << endl;
        cout << "1. Display Tasks" << endl;
        cout << "2. Add Task" << endl;
        cout << "3. Remove Task" << endl;
        cout << "4. Exit" << endl;
        cout << "-----------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Consume newline

        switch (choice) {
            case 1:
                displayTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                break;
            case 3:
                removeTask(tasks);
                break;
            case 4:
                cout << "Exiting Task Scheduler." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

