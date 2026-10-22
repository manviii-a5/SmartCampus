#include <cassert>
#include <iostream>
#include "InputValidator.h"
int main(){
 using namespace InputValidator;
 assert(isValidStudentName("Ashish Kumar")); assert(isValidStudentName("O'Neil"));
 assert(!isValidStudentName("")); assert(!isValidStudentName("Aman123"));
 assert(isValidEmail("student@example.com")); assert(!isValidEmail("student.example.com"));
 assert(!isValidEmail("a@@example.com")); assert(!isValidEmail("a b@example.com"));
 assert(isValidPhone("9876543210")); assert(isValidPhone("6123456789"));
 assert(!isValidPhone("5123456789")); assert(!isValidPhone("987654321")); assert(!isValidPhone("98765abc10"));
 assert(isValidPassword("Campus@123")); assert(!isValidPassword("password"));
 std::cout << "PASS: InputValidator tests\n";
}
