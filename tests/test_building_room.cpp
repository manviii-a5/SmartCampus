#include <cassert>
#include <iostream>
#include "Building.h"
#include "Room.h"
int main(){
 Building b(7,"B. Tech Block","Academic",true,4,"ACTIVE","BTech");
 assert(b.getBuildingId()==7); assert(b.getName()=="B. Tech Block"); assert(b.getNumberOfFloors()==4); assert(b.getHasBasement()); assert(b.isActive());
 b.setName("Engineering Block"); b.setNumberOfFloors(5); b.setStatus("INACTIVE");
 assert(b.getName()=="Engineering Block"); assert(b.getNumberOfFloors()==5); assert(!b.isActive());
 Room r(12,7,"Ground Floor","G-101","Classroom",40,"AVAILABLE");
 assert(r.getRoomId()==12); assert(r.getBuildingId()==7); assert(r.getCapacity()==40); assert(r.isAvailable());
 r.setFloor("First Floor"); r.setRoomNumber("F-201"); r.setCapacity(55); r.setStatus("UNAVAILABLE");
 assert(r.getFloor()=="First Floor"); assert(r.getRoomNumber()=="F-201"); assert(r.getCapacity()==55); assert(!r.isAvailable());
 std::cout << "PASS: Building and Room tests\n";
}
