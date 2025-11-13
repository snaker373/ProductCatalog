#include <iostream>
#include <string>
#include <limits> // чтобы использовать син игнор
using namespace std;

struct Task {
    string title; // Назва файла або завдання (використовуємо нижній регістр)
    bool isDone; // Чи виконанно завдання?
};

struct Project {
    string name; //Назва проєкту
    Task* tasks; // Дін. Масив (використовуємо tasks)
    int taskCount; //Кількість завдань
    int capacity; // Макс кількість завдань яку вміщаемо в масив
};

void addProject (Project *p) {
    if (p == nullptr) return;

    cout << "enter the project name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,p->name);

    p->capacity = 5; // начальный размер масива
    p->taskCount = 0;
    p->tasks = new Task[p->capacity];

    cout << "project '" << p->name << "' successfully created with cob space " << p->capacity << endl;
}

void addTask(Project *p, const string& title) {
    if (p == nullptr) return;

    if (p->taskCount >= p->capacity) {
        int newCapacity = p->capacity * 2;
        Task* newTasks = new Task[newCapacity];

        for (int i = 0; i < p->taskCount; i++) {
            newTasks[i] = p->tasks[i];
        }

        delete[] p->tasks;
        p->tasks = newTasks;
        p->capacity = newCapacity;
        cout << " An array of extensions, a new capacity for now:" << p->capacity << endl;
    }

    p->tasks[p->taskCount].title = title;
    p->tasks[p->taskCount].isDone = false;
    p->taskCount++;

    cout << "Task" << title << " added to the project" << p->name << endl;
}

void markDone(Project* p, int index) {
    if (p == nullptr || index < 1 || index > p->taskCount) {
        cout << "\n Reminder: Invalid order number (" << index << ")" << endl;
        return;
    }
    p->tasks[index - 1].isDone = true;
    cout << "\n Task #" << index << " ('" << p->tasks[index - 1].title << "designated as **Wikonan**!') " << endl;
}

void show(const Project* p) {
    if (p == nullptr) return;

    cout << "\n---  Project Task: **" << p->name << "** ---\n";

    if (p->taskCount == 0) {
        cout << "   (There is no need for thirst.)" << endl;
    } else {
        for (int i = 0; i < p->taskCount; i++) {
            string status = p->tasks[i].isDone ? "[V]" : "[ ]";
            cout << i + 1 << ". " << status << " " << p->tasks[i].title << endl;
        }
    }
    cout << "--------------------------------------\n";
    cout << " That's all:" << p->taskCount << ". completed tasks: " << p->capacity << endl;
}

void freeMemory(Project* p) {
    if (p == nullptr) return;
    delete[] p->tasks;
    p->tasks = nullptr; // нуль чтобы не было ощибок

    cout << "\n Memory allocated for project tasks '" << p->name << "', successfully released." << endl;
}
int main() {
    Project myProject = {};
    addProject(&myProject);
    cout << "\n--- START OF THE DEMONSTRATION ---\n";
    addTask(&myProject, "Create Task and Project structures");
    addTask(&myProject, "Implement the addProject function");
    addTask(&myProject, "Implement the addTask function");
    addTask(&myProject, "Add array expansion logic");
    addTask(&myProject, "Test functions");
    addTask(&myProject, "Write the main function (main)");
    markDone(&myProject, 1);
    markDone(&myProject, 3);
    show(&myProject);

    freeMemory(&myProject); // освобождаем память

    cout << "\n Program completed." << endl;

    return 0;
}