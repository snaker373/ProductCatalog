#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>
#include <sstream>

using namespace std;
struct Student {
    string name;
    int age;
    double grade;
};
void addStudent(vector<Student>& group);
void showAllStudents(const vector<Student>& group);
void findTopStudent(const vector<Student>& group);
void calculateGroupAverage(const vector<Student>& group);
void removeStudentByName(vector<Student>& group);
void saveToFile(const vector<Student>& group);
void loadFromFile(vector<Student>& group);
void displayMenu();
void clearInputBuffer();
void initializeDefaultStudents(vector<Student>& group);
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addStudent(vector<Student>& group) {
    Student s;
    cout << "\n--- ADDING A NEW STUDENT ---\n";
    clearInputBuffer();

    cout << "Enter student's full name: ";
    getline(cin, s.name);

    cout << "Enter student's age: ";
    while (!(cin >> s.age) || s.age < 15 || s.age > 100) {
        cout << "Invalid age. Try again: ";
        clearInputBuffer();
    }

    cout << "Enter student's average grade (0.0 - 5.0): ";
    while (!(cin >> s.grade) || s.grade < 0.0 || s.grade > 5.0) {
        cout << "Invalid grade. Try again: ";
        clearInputBuffer();
    }

    group.push_back(s);
    cout << "✅ Student '" << s.name << "' successfully added!\n";
}

void showAllStudents(const vector<Student>& group) {
    if (group.empty()) {
        cout << "\n The student list is empty.\n";
        return;
    }

    cout << "\n--- LIST OF ALL STUDENTS ---\n";
    cout << left << setw(30) << "Name"
         << setw(10) << "Age"
         << setw(10) << "Avg. Grade"
         << endl;
    cout << string(50, '-') << endl;

    for (const auto& s : group) {
        cout << left << setw(30) << s.name
             << setw(10) << s.age
             << fixed << setprecision(2) << setw(10) << s.grade
             << endl;
    }
    cout << string(50, '-') << endl;
}

void findTopStudent(const vector<Student>& group) {
    if (group.empty()) {
        cout << "\n Cannot find top student: the list is empty.\n";
        return;
    }

    const Student* topStudent = &group[0];

    for (const auto& s : group) {
        if (s.grade > topStudent->grade) {
            topStudent = &s;
        }
    }

    cout << "\n STUDENT WITH THE HIGHEST GRADE:\n";
    cout << "  Name: **" << topStudent->name << "**\n";
    cout << "  Age: " << topStudent->age << "\n";
    cout << "  Average Grade: " << fixed << setprecision(2) << topStudent->grade << "\n";
}

void calculateGroupAverage(const vector<Student>& group) {
    if (group.empty()) {
        cout << "\n Cannot calculate average: the list is empty.\n";
        return;
    }

    double totalGrade = 0.0;
    for (const auto& s : group) {
        totalGrade += s.grade;
    }

    double average = totalGrade / group.size();
    cout << "\n📊 GROUP AVERAGE GRADE:\n";
    cout << "  Total number of students: " << group.size() << "\n";
    cout << "  Group average grade: **" << fixed << setprecision(2) << average << "**\n";
}

void removeStudentByName(vector<Student>& group) {
    if (group.empty()) {
        cout << "\n The student list is empty. Nothing to remove.\n";
        return;
    }

    string nameToRemove;
    cout << "\n--- REMOVING A STUDENT ---\n";
    clearInputBuffer();
    cout << "Enter the full name of the student to remove: ";
    getline(cin, nameToRemove);

    auto it = find_if(group.begin(), group.end(),
                      [&](const Student& s) { return s.name == nameToRemove; });

    if (it != group.end()) {
        string removedName = it->name;
        group.erase(it);
        cout << "🗑 Student '" << removedName << "' successfully removed.\n";
    } else {
        cout << " Student with the name '" << nameToRemove << "' not found.\n";
    }
}

void saveToFile(const vector<Student>& group) {
    if (group.empty()) {
        cout << "\n The list is empty, nothing to save.\n";
        return;
    }

    ofstream file("students.txt");
    if (!file.is_open()) {
        cerr << "\n Error: Failed to open students.txt for writing.\n";
        return;
    }

    for (const auto& s : group) {
        file << s.name << ";" << s.age << ";" << fixed << setprecision(2) << s.grade << "\n";
    }

    file.close();
    cout << "\n Student list successfully saved to file **students.txt**.\n";
}

void loadFromFile(vector<Student>& group) {
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout << "\n Error: Failed to open students.txt. Maybe it does not exist.\n";
        return;
    }

    group.clear();
    string line;
    int loadedCount = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string segment;
        Student s;
        int fieldIndex = 0;

        while (getline(ss, segment, ';')) {
            try {
                switch (fieldIndex) {
                    case 0: s.name = segment; break;
                    case 1: s.age = stoi(segment); break;
                    case 2: s.grade = stod(segment); break;
                }
            } catch (const std::exception& e) {
                cerr << "Error parsing line: " << line << endl;
                continue;
            }
            fieldIndex++;
        }
        group.push_back(s);
        loadedCount++;
    }

    file.close();
    cout << "\n📥 Successfully loaded **" << loadedCount << "** students from file **students.txt**.\n";
}

void displayMenu() {
    cout << "\n====================================\n";
    cout << "        STUDENT MANAGER (C++)      \n";
    cout << "====================================\n";
    cout << "1. Add a new student\n";
    cout << "2. Show all students\n";
    cout << "3. Find student with the highest grade\n";
    cout << "4. Calculate group average grade\n";
    cout << "5. Remove student by name\n";
    cout << "6. Save list to file\n";
    cout << "7. Load list from file\n";
    cout << "0. Exit program\n";
    cout << "------------------------------------\n";
    cout << "Your choice: ";
}

// --- INITIALIZATION FUNCTION (Based on your screenshots) ---

void initializeDefaultStudents(vector<Student>& group) {
    group.push_back({"Danya Novikov", 20, 4.95});
    group.push_back({"Vlad Melnyk", 21, 4.10});
    group.push_back({"Nyxis O'Connell", 19, 3.85});
    group.push_back({"Quinn 'qq11qq' Jones", 20, 3.50});
    group.push_back({"Sofia Kopytse", 22, 4.60});
    group.push_back({"Alex Petrov", 20, 4.05});
    group.push_back({"Artem Guts", 19, 3.90});
    group.push_back({"J.S. Smith", 21, 4.25});
    group.push_back({"Damm Dmytro", 18, 4.88});
    group.push_back({"Glar1nzy K.", 20, 3.75});
    group.push_back({"Rina Lypko", 19, 4.55});
    group.push_back({"Kirill Koval", 22, 3.99});
    group.push_back({"Herman Ryndya", 20, 4.75});
    group.push_back({"Maksym Volkov", 21, 3.65});
    group.push_back({"Andrii Stus", 23, 4.20}); // Placeholder for the icon
    group.push_back({"Lesya Lysenko", 19, 4.45});
    group.push_back({"Valeriya Moskaluk", 20, 4.80});
    group.push_back({"Yaroslav Rudenko", 21, 3.90});
    group.push_back({"Maksym Postolaki", 20, 4.30});
    group.push_back({"Artem Hrytsai", 22, 3.70});
    group.push_back({"Sjkodidas Mykhailo", 19, 4.15});
    group.push_back({"Maxym Dybach", 20, 4.65});
    group.push_back({"Vladislav Demchenko", 21, 3.80});
    group.push_back({"Ilona Savelieva", 19, 4.50});
    group.push_back({"Vladislav X (Zhovner)", 20, 4.35});
    group.push_back({"Boichuk Ivan", 21, 3.40});
    group.push_back({"Bogdan Sydorenko", 22, 4.00});
    group.push_back({"Ksenia Melnyk", 18, 4.90});
    group.push_back({"DEFL1 K.", 20, 3.60});
    group.push_back({"Daniil Kuzmenko", 21, 4.70});
    group.push_back({"IG Ivanenko", 24, 3.20});
}

// --- MAIN FUNCTION ---

int main() {
    vector<Student> studentGroup;
    initializeDefaultStudents(studentGroup); // Load students from screenshots
    int choice;

    do {
        displayMenu();

        if (!(cin >> choice)) {
            cout << "\n Invalid input. Please enter a number.\n";
            clearInputBuffer();
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(studentGroup);
                break;
            case 2:
                showAllStudents(studentGroup);
                break;
            case 3:
                findTopStudent(studentGroup);
                break;
            case 4:
                calculateGroupAverage(studentGroup);
                break;
            case 5:
                removeStudentByName(studentGroup);
                break;
            case 6:
                saveToFile(studentGroup);
                break;
            case 7:
                loadFromFile(studentGroup);
                break;
            case 0:
                cout << "\n Exiting program. Goodbye!\n";
                break;
            default:
                cout << "\n Invalid choice. Try again (0-7).\n";
        }
    } while (choice != 0);

    return 0;
}
