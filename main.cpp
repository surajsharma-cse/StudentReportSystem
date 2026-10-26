
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <limits>
#include <cstdio>
#include <windows.h>

using namespace std;

// ==========================================
// SECTION 1: STUDENT STRUCTURE
// ==========================================

struct Student {
    string name;
    int rollNo;
    map<string, int> marks;
    int total = 0;
    float percentage = 0.0f;
    char grade = 'F';
};

vector<Student> students;

// ==========================================
// SECTION 2: CALCULATE TOTAL, PERCENTAGE, GRADE
// ==========================================

void calculateGrade(Student &s) {
    s.total = 0;

    for (const auto &m : s.marks) {
        s.total += m.second;
    }

    if (s.marks.empty()) {
        s.percentage = 0.0f;
        s.grade = 'F';
        return;
    }

    s.percentage =
        static_cast<float>(s.total) / s.marks.size();

    if (s.percentage >= 90)
        s.grade = 'A';
    else if (s.percentage >= 80)
        s.grade = 'B';
    else if (s.percentage >= 70)
        s.grade = 'C';
    else if (s.percentage >= 60)
        s.grade = 'D';
    else
        s.grade = 'F';
}

// ==========================================
// SECTION 3: ADD STUDENT
// ==========================================

void addStudent() {
    Student s;
    int subjects;

    cout << "\nEnter student name: ";
    getline(cin >> ws, s.name);

    cout << "Enter roll number: ";
    if (!(cin >> s.rollNo)) {
        cout << "Invalid roll number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (s.rollNo <= 0) {
    cout << "Roll number must be a positive integer!\n";
    return;
}

    for (const auto &existing : students) {
        if (existing.rollNo == s.rollNo) {
            cout << "Roll number already exists!\n";
            return;
        }
    }

    cout << "Enter number of subjects: ";
    if (!(cin >> subjects) || subjects <= 0) {
        cout << "Invalid number of subjects!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    
for (int i = 0; i < subjects;) {
    string subject;
    int mark;

    cout << "Enter subject name: ";
    getline(cin >> ws, subject);

    if (subject.empty()) {
        cout << "Subject name cannot be empty. Try again.\n";
        continue;
    }

    if (s.marks.count(subject)) {
        cout << "Subject already entered. Try again.\n";
        continue;
    }

    cout << "Enter marks (0-100): ";

    if (!(cin >> mark)) {
        cout << "Invalid marks! Enter a number from 0 to 100.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }

    if (mark < 0 || mark > 100) {
        cout << "Invalid marks! Enter a number from 0 to 100.\n";
        continue;
    }

    s.marks[subject] = mark;
    i++;
}

    calculateGrade(s);
    students.push_back(s);

    cout << "\nStudent added successfully!\n";
    cout << "Total: " << s.total << '\n';
    cout << fixed << setprecision(2);
    cout << "Percentage: " << s.percentage << "%\n";
    cout << "Grade: " << s.grade << '\n';
}

// ==========================================
// SECTION 4: DISPLAY ALL STUDENTS
// ==========================================

void displayStudents() {
    if (students.empty()) {
        cout << "\nNo student records available.\n";
        return;
    }

    cout << "\n"
         << left << setw(10) << "Roll No"
         << setw(25) << "Name"
         << setw(10) << "Total"
         << setw(15) << "Percentage"
         << setw(8) << "Grade"
         << "Subject Marks\n";

    cout << string(85, '-') << '\n';

    for (const auto &s : students) {
        cout << left << setw(10) << s.rollNo
             << setw(25) << s.name
             << setw(10) << s.total
             << fixed << setprecision(2)
             << setw(15) << s.percentage
             << setw(8) << s.grade;

        for (const auto &m : s.marks) {
            cout << m.first << ":" << m.second << "  ";
        }

        cout << '\n';
    }
}

// ==========================================
// SECTION 5: BINARY SEARCH BY ROLL NUMBER
// ==========================================

void searchStudent() {
    if (students.empty()) {
        cout << "\nNo student records available.\n";
        return;
    }

    int roll;
    cout << "\nEnter roll number to search: ";

    if (!(cin >> roll)) {
        cout << "Invalid roll number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    sort(students.begin(), students.end(),
         [](const Student &a, const Student &b) {
             return a.rollNo < b.rollNo;
         });

    auto it = lower_bound(
        students.begin(), students.end(), roll,
        [](const Student &s, int r) {
            return s.rollNo < r;
        });

    if (it != students.end() && it->rollNo == roll) {
        cout << "\nStudent found!\n";
        cout << "Name: " << it->name << '\n';
        cout << "Roll Number: " << it->rollNo << '\n';
        cout << "Total: " << it->total << '\n';
        cout << fixed << setprecision(2);
        cout << "Percentage: " << it->percentage << "%\n";
        cout << "Grade: " << it->grade << '\n';
    } else {
        cout << "Student not found!\n";
    }
}

// ==========================================
// SECTION 6: UPDATE STUDENT
// ==========================================

void updateStudent() {
    int roll;

    cout << "\nEnter roll number to update: ";
    if (!(cin >> roll)) {
        cout << "Invalid roll number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    for (auto &s : students) {
        if (s.rollNo == roll) {
            cout << "Current name: " << s.name << '\n';
            cout << "Enter new name: ";

            string newName;
            getline(cin >> ws, newName);

            if (newName.empty()) {
                cout << "Name cannot be empty. Update cancelled.\n";
                return;
            }

            int subjects;
            cout << "Enter number of subjects: ";

            if (!(cin >> subjects) || subjects <= 0) {
                cout << "Invalid number of subjects. Update cancelled.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }

            map<string, int> newMarks;

            for (int i = 0; i < subjects;) {
                string subject;
                int mark;

                cout << "Enter subject " << i + 1 << " name: ";
                getline(cin >> ws, subject);

                if (subject.empty()) {
                    cout << "Subject name cannot be empty. Try again.\n";
                    continue;
                }

                if (newMarks.count(subject)) {
                    cout << "Subject already entered. Try again.\n";
                    continue;
                }

                cout << "Enter marks for " << subject << " (0-100): ";

                if (!(cin >> mark)) {
                    cout << "Invalid marks. Update cancelled.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                }

                if (mark < 0 || mark > 100) {
                    cout << "Marks must be between 0 and 100. Update cancelled.\n";
                    return;
                }

                newMarks[subject] = mark;
                i++;
            }

            // Apply changes only after all new data is valid.
            s.name = newName;
            s.marks = newMarks;
            calculateGrade(s);

            cout << "Student updated successfully!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}


// ==========================================
// SECTION 7: DELETE STUDENT
// ==========================================

void deleteStudent() {
    int roll;

    cout << "\nEnter roll number to delete: ";
    if (!(cin >> roll)) {
        cout << "Invalid roll number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto it = find_if(
        students.begin(), students.end(),
        [roll](const Student &s) {
            return s.rollNo == roll;
        });

    if (it != students.end()) {
        students.erase(it);
        cout << "Student deleted successfully!\n";
    } else {
        cout << "Student not found!\n";
    }
}

// ==========================================
// SECTION 8: FIND TOPPER
// ==========================================

void findTopper() {
    if (students.empty()) {
        cout << "\nNo student records available.\n";
        return;
    }

    auto topper = max_element(
        students.begin(), students.end(),
        [](const Student &a, const Student &b) {
            return a.percentage < b.percentage;
        });

    cout << "\n===== Class Topper =====\n";
    cout << "Name: " << topper->name << '\n';
    cout << "Roll Number: " << topper->rollNo << '\n';
    cout << fixed << setprecision(2);
    cout << "Percentage: " << topper->percentage << "%\n";
    cout << "Grade: " << topper->grade << '\n';
}

// ==========================================
// SECTION 9: SAVE DATA TO FILE
// ==========================================
void saveToFile() {
    const string tempFile = "students.tmp";
    ofstream fout(tempFile);

    if (!fout.is_open()) {
        cout << "Error: Could not open temporary file for saving!\n";
        return;
    }

    for (const auto &s : students) {
        fout << quoted(s.name) << ' '
             << s.rollNo << ' '
             << s.marks.size();

        for (const auto &m : s.marks) {
            fout << ' ' << quoted(m.first) << ' ' << m.second;
        }

        fout << '\n';

        if (!fout) {
            cout << "Error: Failed while writing student records!\n";
            fout.close();
            remove(tempFile.c_str());
            return;
        }
    }

    fout.close();

    if (!fout) {
        cout << "Error: Failed to finish writing the file!\n";
        remove(tempFile.c_str());
        return;
    }

   if (!MoveFileExA(
        tempFile.c_str(),
        "students.txt",
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
    cout << "Error: Could not replace students.txt. Windows error: "
         << GetLastError() << '\n';
    return;
}
    cout << "Data saved to students.txt successfully!\n";
}
// ==========================================
// SECTION 10: LOAD DATA FROM FILE
// ==========================================

void loadFromFile() {
    ifstream fin("students.txt");

    if (!fin.is_open()) {
        cout << "No saved file found. Starting fresh.\n";
        return;
    }

    vector<Student> loaded;
    Student s;
    size_t subjectCount;

    while (fin >> quoted(s.name) >> s.rollNo >> subjectCount) {
        // Reject invalid or duplicate roll numbers.
        if (s.rollNo <= 0 ||
            subjectCount > 100 ||
            any_of(loaded.begin(), loaded.end(),
                   [&s](const Student &existing) {
                       return existing.rollNo == s.rollNo;
                   })) {
            cout << "Warning: Invalid student record in file. Loading cancelled.\n";
            return;
        }

        s.marks.clear();
        bool valid = true;

        for (size_t i = 0; i < subjectCount; ++i) {
            string subject;
            int mark;

            if (!(fin >> quoted(subject) >> mark) ||
                subject.empty() ||
                mark < 0 || mark > 100 ||
                s.marks.count(subject)) {
                valid = false;
                break;
            }

            s.marks[subject] = mark;
        }

        if (!valid) {
            cout << "Warning: Invalid student record in file. Loading cancelled.\n";
            return;
        }

        calculateGrade(s);
        loaded.push_back(s);
    }

    // Distinguish a normal end-of-file from malformed trailing data.
    if (!fin.eof()) {
        cout << "Error: Invalid or incomplete data in students.txt. Loading cancelled.\n";
        return;
    }

    students = loaded;
    cout << students.size() << " student record(s) loaded.\n";
}

// ==========================================
// SECTION 11: MAIN MENU
// ==========================================

int main() {
    loadFromFile();

    int choice;

    do {
        cout << "\n========== STUDENT REPORT SYSTEM ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Find Topper\n";
        cout << "7. Save Records to File\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                findTopper();
                break;

            case 7:
                saveToFile();
                break;

            case 8:
                saveToFile();
                cout << "Exiting Student Report System...\n";
                break;

            default:
                cout << "Invalid choice! Select 1-8.\n";
        }

    } while (choice != 8);

    return 0;
}
