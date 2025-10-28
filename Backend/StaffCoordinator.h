// StaffCoordinator.h
#ifndef STAFF_COORDINATOR_H
#define STAFF_COORDINATOR_H

#include <string>
#include <vector>

class WebAPIAdapter;

class StaffCoordinator {
private:
    WebAPIAdapter* apiAdapter;
    
public:
    StaffCoordinator(WebAPIAdapter* adapter);
    ~StaffCoordinator();
    
    // Customer interaction
    std::string handleCustomerQuestion(int customerId, const std::string& question);
    std::string handleCustomerRequest(int customerId, const std::string& request);
    std::string providePlantAdvice(int customerId, const std::string& plantType);
    
    // Task management
    std::string assignTask(int staffId, const std::string& task);
    std::string assignTaskByRole(const std::string& role, const std::string& task);
    std::string completeTask(int taskId);
    std::string getPendingTasks();
    std::string getStaffTasks(int staffId);
    
    // Staff management
    std::string getAllStaff();
    std::string getStaffByRole(const std::string& role);
    std::string getStaffPerformance();
    std::string assignStaffToNurseryArea(int staffId, const std::string& area);
    
    // Escalation and coordination
    std::string escalateTask(int taskId);
    std::string reassignTask(int taskId, int newStaffId);
    std::string coordinateStaffMeeting(const std::string& agenda);
    
    // Notification management
    std::string getStaffNotifications();
    std::string markNotificationCompleted(int notificationId);
    std::string createStaffNotification(const std::string& message, const std::string& priority);
    
    // Work scheduling
    std::string createWorkSchedule(const std::string& period);
    std::string getStaffSchedule(int staffId);
    std::string updateStaffAvailability(int staffId, const std::string& availability);
    
private:
    std::string determineStaffRoleForTask(const std::string& task);
    int findAvailableStaff(const std::string& role);
    std::string formatTaskDescription(const std::string& task);
};

#endif