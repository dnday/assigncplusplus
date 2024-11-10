#include <iostream> //input output stream
#include <fstream> //membuka dan membaca file
#include <vector> //menyimpan data dalam bentuk array dinamis 
#include <sstream> //memisahkan data csv atau mengolah string stream
#include <iomanip> //untuk manipulasi format output

using namespace std;

struct studentType {
	string studentFName;
	string studentLName;
	int testScore;
	char grade;
};

void readFile(const string& filename, studentType students[], int size);
void assignGrades(studentType students[], int size);
int findHighestScore(const studentType students[], int size);
void printHighestScorers(const studentType students[], int size, int highestScore);
void printStudents(const studentType students[], int size);
void processStudents(const string& filename);

int main() {
	// Process the students from the given CSV file
	processStudents("student_scores.csv");
	return 0;
}

void processStudents(const string& filename) {
	const int size = 20;
	studentType students[size];
	
	// Read student data from file
	readFile(filename, students, size);
	
	// Assign grades based on test scores
	assignGrades(students, size);
	
	// Find the highest test score
	int highestScore = findHighestScore(students, size);
	
	// Print students with the highest score
	printHighestScorers(students, size, highestScore);
	
	// Print all students' information
	printStudents(students, size);
}

void readFile(const string& filename, studentType students[], int size) {
	ifstream file(filename);
	string line;

	// Check if the file was successfully opened
	if (!file.is_open()) {
		cerr << "Failed to open file " << filename << endl;
		return;
	}

	// Ignore the CSV file header
	getline(file, line);

	// Read each line in the CSV file
	int count = 0;
	while (getline(file, line) && count < size) {
		stringstream ss(line);
		string studentFName, studentLName, scoreStr;
		int testScore;

		// Read data from each column
		getline(ss, studentFName, ',');
		getline(ss, studentLName, ',');
		getline(ss, scoreStr, ',');

		// Convert score from string to integer
		testScore = stoi(scoreStr);

		// Validate the test score
		if (testScore < 0 || testScore > 100) {
			cerr << "Invalid score " << testScore << " for student " << studentFName << " " << studentLName << ". Skipping entry." << endl;
			continue;
		}

		// Add data to the array
		students[count] = {studentFName, studentLName, testScore, ' '};
		count++;
	}

	file.close();
}

void assignGrades(studentType students[], int size) {
	for (int i = 0; i < size; ++i) {
		if (students[i].testScore >= 90) {
			students[i].grade = 'A';
		} else if (students[i].testScore >= 80) {
			students[i].grade = 'B';
		} else if (students[i].testScore >= 70) {
			students[i].grade = 'C';
		} else if (students[i].testScore >= 60) {
			students[i].grade = 'D';
		} else {
			students[i].grade = 'E';
		}
	}
}

int findHighestScore(const studentType students[], int size) {
	int highestScore = 0;
	for (int i = 0; i < size; ++i) {
		if (students[i].testScore > highestScore) {
			highestScore = students[i].testScore;
		}
	}
	return highestScore;
}

void printHighestScorers(const studentType students[], int size, int highestScore) {
	cout << "\nStudents with the highest score (" << highestScore << "):\n";
	cout << "----------------------------------------\n";
	for (int i = 0; i < size; ++i) {
		if (students[i].testScore == highestScore) {
			cout << left << setw(20) << (students[i].studentLName + ", " + students[i].studentFName) 
				<< endl;
		}
	}
	cout << "----------------------------------------\n";
}

void printStudents(const studentType students[], int size) {
	cout << "\nAll Students Information:\n";
	cout << "----------------------------------------\n";
	for (int i = 0; i < size; ++i) {
		cout << left << setw(20) << (students[i].studentLName + ", " + students[i].studentFName) 
			 << " - Score: " << students[i].testScore << ", Grade: " << students[i].grade << endl;
	}
	cout << "----------------------------------------\n";
}
