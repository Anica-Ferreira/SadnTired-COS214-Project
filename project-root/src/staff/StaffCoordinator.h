// StaffCoordinator.h
#ifndef STAFF_COORDINATOR_H
#define STAFF_COORDINATOR_H

#include <string>
#include <iostream>
#include <vector>
#include "../core/WebAPIAdapter.h"

class WebAPIAdapter;

class StaffCoordinator {
private:
    WebAPIAdapter* apiAdapter;
    
public:
    StaffCoordinator(WebAPIAdapter* adapter);
    ~StaffCoordinator();
    
    // Customer interaction
    string handleCustomerQuestion(int customerId, const string& question);
    string handleCustomerRequest(int customerId, const string& request);
    string providePlantAdvice(int customerId, const string& plantType);
    
    // Task management
    string assignTask(int staffId, const string& task);
    string assignTaskByRole(const string& role, const string& task);
    string completeTask(int taskId);
    string getPendingTasks();
    string getStaffTasks(int staffId);
    
    // Staff management
    string getAllStaff();
    string getStaffByRole(const string& role);
    string getStaffPerformance();
    string assignStaffToNurseryArea(int staffId, const string& area);
    
    // Escalation and coordination
    string escalateTask(int taskId);
    string reassignTask(int taskId, int newStaffId);
    string coordinateStaffMeeting(const string& agenda);
    
    // Notification management
    string getStaffNotifications();
    string markNotificationCompleted(int notificationId);
    string createStaffNotification(const string& message, const string& priority);
    
    // Work scheduling
    string createWorkSchedule(const string& period);
    string getStaffSchedule(int staffId);
    string updateStaffAvailability(int staffId, const string& availability);
    
private:
    string determineStaffRoleForTask(const string& task);
    int findAvailableStaff(const string& role);
    string formatTaskDescription(const string& task);
};

#endif