#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int score;
};

int main() {
    std::cout << "Hello from C++!\n";

    std::vector<Student> students = {
        {"Alice", 92},
        {"Bob", 78},
        {"Carol", 85},
    };

    int total = 0;
    for (const auto &s : students) {
        std::cout << s.name << "\t" << s.score << "\n";
        total += s.score;
    }

    std::cout << "avg = " << static_cast<double>(total) / students.size() << "\n";
    return 0;
}
