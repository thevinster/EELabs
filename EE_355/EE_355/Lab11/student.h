#ifndef STUDENT_H
#define STUDENT_H
#include <vector>
#include <string>

class Student { 
 public: 
  Student() { }
  Student(std::string myname)       { name_ = myname; }
  std::string get_name()   		{ return name_; } 
  void add_grade(int score)     { grades_.push_back(score); }
  void update_grade(int index, int score) { grades_[index] = score; }
  int get_grade(int index)     { return grades_[index]; }
  std::vector<int> &get_grades()  { return grades_; }
 private: 
  std::string name_; 
  std::vector<int> grades_; 
}; 
#endif
