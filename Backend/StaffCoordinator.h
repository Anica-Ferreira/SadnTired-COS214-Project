#ifndef STAFFCOORDINATOR_H
#define STAFFCOORDINATOR_H

#include "StaffMember.h"
#include "WebAPIAdapter.h"
#include <string>
#include <map>

class StaffCoordinator : public StaffMember {
private:
    WebAPIAdapter* apiAdapter;
    
    // Private helper methods
    std::string determineStaffRoleForTask(const std::string& task);
    int findAvailableStaff(const std::string& role);
    std::string formatTaskDescription(const std::string& task);

public:
    StaffCoordinator(std::string name, WebAPIAdapter* adapter);
    ~StaffCoordinator();

    // Override pure virtual functions from StaffMember
    std::string processRequest(std::string request) override;
    void mainDuty() override;
    void workDuty() override;
    void subDuty() override;

    // Coordinator-specific methods
    std::string handleCustomerQuestion(int customerId, const std::string& question);
    std::string handleCustomerRequest(int customerId, const std::string& request);
    std::string providePlantAdvice(int customerId, const std::string& plantType);
    std::string assignTask(int staffId, const std::string& task);
    std::string assignTaskByRole(const std::string& role, const std::string& task);
    std::string completeTask(int taskId);
    std::string getPendingTasks();
    std::string getStaffTasks(int staffId);
    std::string getAllStaff();
    std::string getStaffByRole(const std::string& role);
    std::string escalateTask(int taskId);
    std::string reassignTask(int taskId, int newStaffId);
    std::string coordinateStaffMeeting(const std::string& agenda);
    std::string getStaffNotifications();
    std::string markNotificationCompleted(int notificationId);
    std::string createStaffNotification(const std::string& message, const std::string& priority);
};

#endif // STAFFCOORDINATOR_H