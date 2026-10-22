#include <cassert>
#include <iostream>
#include "Building.h"
#include "Room.h"
#include "Resource.h"
#include "Booking.h"
#include "ServiceRequest.h"
#include "InputValidator.h"
int main(){
 assert(!InputValidator::isValidStudentName("")); assert(!InputValidator::isValidEmail("")); assert(!InputValidator::isValidPhone(""));
 Building b; assert(b.getBuildingId()==0); b.setNumberOfFloors(0); assert(b.getNumberOfFloors()==0);
 Room r; assert(r.getRoomId()==0); r.setCapacity(0); assert(r.getCapacity()==0);
 Resource resource; assert(resource.getResourceId()==0); assert(resource.isBookable());
 Booking booking; assert(booking.isPending()); assert(!booking.isApproved());
 ServiceRequest req; assert(req.cancelPendingRequest());
 assert(InputValidator::isValidPhone("9999999999")); assert(!InputValidator::isValidPhone("99999999999"));
 std::cout << "PASS: Edge case tests\n";
}
