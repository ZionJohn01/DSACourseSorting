// ProjectTwoDSA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

std::vector<Course> courseData;

void loadDataStructure(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Course course;
            size_t pos = line.find(',');
            course.courseNumber = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            course.courseTitle = line.substr(0, pos);
            line.erase(0, pos + 1);
            while (!line.empty()) {
                pos = line.find(',');
                std::string prereq = line.substr(0, pos);
                course.prerequisites.push_back(prereq);
                if (pos == std::string::npos)
                    break;
                line.erase(0, pos + 1);
            }
            courseData.push_back(course);

        }
        file.close();
    }
    else {
        std::cout << "Failed to open file." << std::endl;
    }
}

void printCourseList() {
    std::sort(courseData.begin(), courseData.end(), [](const Course& c1, const Course& c2) {
        return c1.courseNumber < c2.courseNumber;
        });

    for (const auto& course : courseData) {
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
    }
}

void printCourse(const std::string& courseNumber) {
    for (const auto& course : courseData) {
        if (course.courseNumber == courseNumber) {
            std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
            if (!course.prerequisites.empty()) {
                std::cout << "Prerequisites: ";
                for (const auto& prereq : course.prerequisites) {
                    std::cout << prereq << " ";
                }
                std::cout << std::endl;
            }
            return;
        }
    }
    std::cout << "course not found." << std::endl;
}

int main() {
    int choice;
    std::string filename;
    std::string courseNumber;

    do {
        std::cout << "welcome to the course planner." << std::endl;
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit." << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the filename: ";
            std::cin >> filename;
            loadDataStructure(filename);
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            std::cout << "What course do you want to know about? ";
            std::cin >> courseNumber;
            printCourse(courseNumber);
        case 9:
             std::cout << "Thank you. Goodbye." << std::endl;
             return 0;
        default:
            std::cout << "Invalid. Try again." << std::endl;
            break;
        }
    } while (true);
}