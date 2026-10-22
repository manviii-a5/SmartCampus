#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "FileManager.h"
int main(){
 const std::string path="tests/test_records.tmp"; std::remove(path.c_str());
 assert(!FileManager::fileExists(path)); assert(FileManager::ensureFileExists(path)); assert(FileManager::fileExists(path));
 std::vector<std::string> in={"101|Ashish|CSE","102|Divya|CSE"};
 assert(FileManager::saveRecords(path,in)); std::vector<std::string> out;
 assert(FileManager::readRecords(path,out)); assert(out.size()==2); assert(out[0]==in[0]); assert(out[1]==in[1]);
 assert(FileManager::appendRecord(path,"103|Manvi|CSE")); out.clear(); assert(FileManager::readRecords(path,out)); assert(out.size()==3);
 assert(!FileManager::isValidRecord("")); assert(!FileManager::isValidRecord("bad\nrecord")); assert(FileManager::isValidRecord("ok|record"));
 auto fields=FileManager::splitRecord("a|b|c"); assert(fields.size()==3 && fields[1]=="b");
 assert(FileManager::joinRecord(fields)=="a|b|c"); std::remove(path.c_str());
 std::cout << "PASS: File persistence tests\n";
}
