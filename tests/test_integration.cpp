#include <cassert>
#include <iostream>
#include "Booking.h"
#include "Resource.h"
#include "ServiceRequest.h"
#include "Emergency.h"
int main(){
 Resource roomResource(5,"G-101 Classroom","Classroom","Room",12,"ACTIVE");
 assert(roomResource.getResourceId()==5); assert(roomResource.getLocationId()==12); assert(roomResource.isBookable());
 roomResource.setStatus("INACTIVE"); assert(!roomResource.isBookable());
 Booking booking("B-1",12345,"Student",5,"G-101 Classroom","2026-10-22","10:00","11:00","PENDING","2026-10-21 10:00");
 assert(booking.getRequesterId()==12345); assert(booking.isPending()); booking.setStatus("APPROVED"); assert(booking.isApproved());
 ServiceRequest req("SR-1",12345,"Student","Maintenance","B. Tech Block","Projector not working","2026-10-21 10:00");
 assert(req.getStatus()=="PENDING"); assert(req.updateStatus("IN_PROGRESS")); assert(req.getStatus()=="IN_PROGRESS"); assert(req.updateStatus("RESOLVED"));
 Emergency e("E-1",12345,"Student","Fire","B. Tech Block","Test report","2026-10-21 10:00");
 assert(e.getReporterId()==12345); assert(e.isActive()); e.setStatus("RESOLVED"); assert(!e.isActive());
 std::cout << "PASS: Core model integration tests\n";
}
