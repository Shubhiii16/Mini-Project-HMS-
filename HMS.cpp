#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Student {
string name;
string UID;
string course;
int feeDeposited;
int roomNo;
char block;
char attendance;
map<string, char> monthlyAttendance; 
};

map<int, vector<Student>> studentsByRoom;
map<string, Student> studentsByUID;

void loadOldData() {
ifstream file("hostel_data.txt");
if (file.is_open()) {
string line;
while (getline(file, line)) {
string name, UID, course;
int feeDeposited, roomNo;
char block;
Student student;
student.name = name;
student.UID = UID;
student.course = course;
student.feeDeposited = feeDeposited;
student.roomNo = roomNo;
student.block = block;
studentsByRoom[roomNo].push_back(student);
studentsByUID[UID] = student;
}
file.close();
}
}

void saveOldData() {
ofstream file("hostel_data.txt");
if (file.is_open()) {
for (const auto& room : studentsByRoom) {
for (const auto& student : room.second) {
file << student.name << " " << student.UID << " " << student.course << " " << student.feeDeposited << " " << student.roomNo << " " << student.block;
for (const auto& attendance : student.monthlyAttendance) {
file << " " << attendance.first << " " << attendance.second;
}
file << "\n";
}
}
file.close();
}
}

void addStudent() {
Student student;
cout << "Enter student name: ";
cin >> student.name;
cout << "Enter student UID: ";
cin >> student.UID;
cout << "Enter student course: ";
cin >> student.course;
cout << "Enter fee deposited: ";
cin >> student.feeDeposited;
cout << "Enter room no: ";
cin >> student.roomNo;
cout << "Enter block (A/B/C/D): ";
cin >> student.block;
student.attendance = 'A'; 
studentsByRoom[student.roomNo].push_back(student);
studentsByUID[student.UID] = student;
saveOldData();
}

void displayStudentsByRoom() {
int roomNo;
cout << "Enter room no: ";
cin >> roomNo;
if (studentsByRoom.find(roomNo)!= studentsByRoom.end()) {
cout << "Students in room " << roomNo << ":\n";
for (const auto& student : studentsByRoom[roomNo]) {
cout << "Name: " << student.name << ", UID: " << student.UID << ", Course: " << student.course << ", Fee Deposited: " << student.feeDeposited << ", Block: " << student.block << "\n";
}
} else {
cout << "No students in room " << roomNo << "\n";
}
}

void markAttendance() {
int roomNo;
cout << "Enter room no: ";
cin >> roomNo;
if (studentsByRoom.find(roomNo)!= studentsByRoom.end()) {
cout << "Enter student UID to mark attendance: ";
string UID;
cin >> UID;
if (studentsByUID.find(UID)!= studentsByUID.end()) {
cout << "Enter attendance (P/A): ";
char attendance;
cin >> attendance;
cout << "Enter date (DD/MM/YYYY): ";
string date;
cin >> date;
studentsByUID[UID].monthlyAttendance[date] = attendance;
saveOldData();
} else {
cout << "Student not found\n";
}
} else {
cout << "No students in room " << roomNo << "\n";
}
}

void updateAttendance() {
string UID;
cout << "Enter student UID to update attendance: ";
cin >> UID;
if (studentsByUID.find(UID)!= studentsByUID.end()) {
cout << "Enter date (DD/MM/YYYY) to update attendance: ";
string date;
cin >> date;
if (studentsByUID[UID].monthlyAttendance.find(date)!= studentsByUID[UID].monthlyAttendance.end()) {
cout << "Enter new attendance (P/A): ";
char attendance;
cin >> attendance;
studentsByUID[UID].monthlyAttendance[date] = attendance;
saveOldData();
cout << "Attendance updated successfully.\n";
} else {
cout << "No attendance recorded for " << date << "\n";
}
} else {
cout << "Student not found\n";
}
}

void displayMenu() {
cout << "Weekly Menu:\n";
cout << "Monday: Breakfast - Poha, Lunch - Rice, Dinner - Chicken\n";
cout << "Tuesday: Breakfast - Omelette, Lunch - Roti, Dinner - Vegetable\n";
cout << "Wednesday: Breakfast - Idli, Lunch - Dal, Dinner - Fish\n";
cout << "Thursday: Breakfast - Dosa, Lunch - Rice, Dinner - Mutton\n";
cout << "Friday: Breakfast - Upma, Lunch - Roti, Dinner - Chicken\n";
cout << "Saturday: Breakfast- Puri, Lunch - Dal, Dinner - Vegetable\n";
cout << "Sunday: Breakfast - Bread, Lunch - Rice, Dinner - Fish\n";
}

void studentComplaint() {
string issue;
cout << "Enter your issue (room/housekeeping): ";
cin >> issue;
cout << "Your issue has been registered. Thank you for your feedback!\n";
}

void nocForm() {
string UID;
cout << "Enter your UID: ";
cin >> UID;
if (studentsByUID.find(UID)!= studentsByUID.end()) {
cout << "Enter reason for leaving: ";
string reason;
cin >> reason;
cout << "Enter date of leaving (DD/MM/YYYY): ";
string date;
cin >> date;
studentsByUID.erase(UID);
for (auto& room : studentsByRoom) {
for (auto it = room.second.begin(); it!= room.second.end(); ++it) {
if (it->UID == UID) {
room.second.erase(it);
break;
}
}
}
saveOldData();
cout << "NOC form submitted successfully. You will be removed from the hostel list.\n";
} else {
cout << "Student not found\n";
}
}

void displayNocList() {
cout << "Students who have submitted NOC form:\n";
for (const auto& student : studentsByUID) {
if (student.second.attendance == 'L') { 
cout << "Name: " << student.second.name << ", UID: " << student.second.UID << "\n";
}
}
}

void displayMonthlyAttendance() {
string UID;
cout << "Enter student UID: ";
cin >> UID;
if (studentsByUID.find(UID)!= studentsByUID.end()) {
cout << "Enter date (DD/MM/YYYY): ";
string date;
cin >> date;
if (studentsByUID[UID].monthlyAttendance.find(date)!= studentsByUID[UID].monthlyAttendance.end()) {
cout << "Attendance on " << date << ": " << studentsByUID[UID].monthlyAttendance[date] << "\n";
} else {
cout << "No attendance recorded for " << date << "\n";
}
} else {
cout << "Student not found\n";
}
}

int main() {
loadOldData();
int choice;
while (true) {
cout << "Hostel Management System\n";
cout << "1. Add student\n";
cout << "2. Display students by room\n";
cout << "3. Mark attendance\n";
cout << "4. Update attendance\n";
cout << "5. Display menu\n";
cout << "6. Student complaint form\n";
cout << "7. NOC form\n";
cout << "8. Display NOC list\n";
cout << "9. Display monthly attendance\n";
cout << "10. Exit\n";
cout << "Enter your choice: ";
cin >> choice;
switch (choice) {
case 1:
addStudent();
break;
case 2:
displayStudentsByRoom();
break;
case 3:
markAttendance();
break;
case 4:
updateAttendance();
break;
case 5:
displayMenu();
break;
case 6:
studentComplaint();
break;
case 7:
nocForm();
break;
case 8:
displayNocList();
break;
case 9:
displayMonthlyAttendance();
break;
case 10:
return 0;
default:
cout << "Invalid choice. Please try again.\n";
}
}
return 0;
}