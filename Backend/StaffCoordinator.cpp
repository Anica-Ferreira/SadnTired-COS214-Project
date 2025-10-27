#include "StaffCoordinator.h"
#include "WebAPIAdapter.h"
#include <iostream>
#include <sstream>
#include <map>
#include <cstdlib> // for rand()

using namespace std;

StaffCoordinator::StaffCoordinator(string name, WebAPIAdapter* adapter)
    : StaffMember(name, "Coordinator"), apiAdapter(adapter) {
}

StaffCoordinator::~StaffCoordinator() {
    cout << "Staff Coordinator " << name_ << " destroyed" << endl;
}

// Override StaffMember pure virtual functions
string StaffCoordinator::processRequest(string request) {
    cout << name_ << " processing request: " << request << endl;

    // Simple request routing logic
    if (request.find("question") != string::npos) {
        return handleCustomerQuestion(1, request);
    } else if (request.find("advice") != string::npos) {
        return providePlantAdvice(1, "general");
    } else if (request.find("assign") != string::npos) {
        return assignTaskByRole("general", request);
    } else {
        return "Coordinator handling: " + request;
    }
}

void StaffCoordinator::mainDuty() {
    cout << "  [Main] " << name_ << ": Coordinating staff activities" << endl;
}

void StaffCoordinator::workDuty() {
    cout << "  [Work] " << name_ << ": Assigning tasks and managing workflow" << endl;
}

void StaffCoordinator::subDuty() {
    cout << "  [Sub] " << name_ << ": Monitoring staff performance" << endl;
}

// Coordinator-specific methods (keep your existing implementations)
string StaffCoordinator::handleCustomerQuestion(int customerId, const string& question) {
    cout << "StaffCoordinator: Handling question from customer " << customerId
              << ": " << question << endl;

    string assignedRole = determineStaffRoleForTask(question);
    int staffId = findAvailableStaff(assignedRole);

    stringstream response;
    response << "{\"action\": \"handle_question\", "
             << "\"customer_id\": " << customerId << ", "
             << "\"question\": \"" << question << "\", "
             << "\"assigned_staff_id\": " << staffId << ", "
             << "\"assigned_role\": \"" << assignedRole << "\", "
             << "\"status\": \"assigned\"}";

    return response.str();
}

string StaffCoordinator::handleCustomerRequest(int customerId, const string& request) {
    cout << "StaffCoordinator: Handling request from customer " << customerId
              << ": " << request << endl;

    string staffInfo = apiAdapter->getStaff();

    stringstream response;
    response << "{\"action\": \"handle_request\", "
             << "\"customer_id\": " << customerId << ", "
             << "\"request\": \"" << request << "\", "
             << "\"staff_assigned\": " << staffInfo << ", "
             << "\"status\": \"processing\"}";

    return response.str();
}

string StaffCoordinator::providePlantAdvice(int customerId, const string& plantType) {
    cout << "StaffCoordinator: Providing plant advice to customer " << customerId
              << " for plant type: " << plantType << endl;

    string advice;
    if (plantType == "Rose" || plantType == "rose") {
        advice = "Roses need full sunlight (6+ hours daily) and well-drained soil. Water deeply 2-3 times per week.";
    } else if (plantType == "Cactus" || plantType == "cactus") {
        advice = "Cacti prefer bright light and minimal water. Water every 2-3 weeks and ensure excellent drainage.";
    } else if (plantType == "Fern" || plantType == "fern") {
        advice = "Ferns thrive in indirect light and high humidity. Keep soil consistently moist but not soggy.";
    } else {
        advice = "This plant requires moderate care. Provide indirect sunlight and water when the top soil feels dry.";
    }

    return "{\"customer_id\": " + to_string(customerId) +
           ", \"plant_type\": \"" + plantType +
           "\", \"advice\": \"" + advice + "\"}";
}

string StaffCoordinator::assignTask(int staffId, const string& task) {
    cout << "StaffCoordinator: Assigning task to staff " << staffId
              << ": " << task << endl;

    string formattedTask = formatTaskDescription(task);

    return "{\"action\": \"assign_task\", "
           "\"staff_id\": " + to_string(staffId) +
           ", \"task\": \"" + formattedTask +
           "\", \"status\": \"assigned\", "
           "\"task_id\": " + to_string(rand() % 1000 + 1) + "}";
}

string StaffCoordinator::assignTaskByRole(const string& role, const string& task) {
    cout << "StaffCoordinator: Assigning task to role " << role
              << ": " << task << endl;

    int staffId = findAvailableStaff(role);

    if (staffId == -1) {
        return "{\"error\": \"No available staff for role: " + role + "\"}";
    }

    return assignTask(staffId, task);
}

string StaffCoordinator::completeTask(int taskId) {
    cout << "StaffCoordinator: Completing task ID: " << taskId << endl;

    string apiResponse = apiAdapter->finishTask(taskId);

    return "{\"action\": \"complete_task\", "
           "\"task_id\": " + to_string(taskId) +
           ", \"api_response\": " + apiResponse + "}";
}

string StaffCoordinator::getPendingTasks() {
    cout << "StaffCoordinator: Retrieving pending tasks" << endl;

    string notifications = apiAdapter->getNotifications();

    return "{\"pending_tasks\": " + notifications + "}";
}

string StaffCoordinator::getStaffTasks(int staffId) {
    cout << "StaffCoordinator: Getting tasks for staff ID: " << staffId << endl;

    return "{\"staff_id\": " + to_string(staffId) +
           ", \"tasks\": ["
           "{\"task_id\": 101, \"description\": \"Water plants in greenhouse A\", \"status\": \"in_progress\"}, "
           "{\"task_id\": 102, \"description\": \"Restock rose inventory\", \"status\": \"pending\"}, "
           "{\"task_id\": 103, \"description\": \"Assist customers in shop\", \"status\": \"completed\"}"
           "]}";
}

string StaffCoordinator::getAllStaff() {
    cout << "StaffCoordinator: Retrieving all staff information" << endl;

    string staffInfo = apiAdapter->getStaff();
    return "{\"staff_list\": " + staffInfo + "}";
}

string StaffCoordinator::getStaffByRole(const string& role) {
    cout << "StaffCoordinator: Retrieving staff by role: " << role << endl;

    string allStaff = apiAdapter->getStaff();

    return "{\"role\": \"" + role +
           "\", \"staff\": [{\"id\": 1, \"name\": \"Mr. Green\", \"role\": \"Gardener\"}]}";
}

string StaffCoordinator::escalateTask(int taskId) {
    cout << "StaffCoordinator: Escalating task ID: " << taskId << endl;

    return "{\"action\": \"escalate_task\", "
           "\"task_id\": " + to_string(taskId) +
           ", \"new_priority\": \"high\", "
           "\"assigned_to\": \"senior_staff\", "
           "\"status\": \"escalated\"}";
}

string StaffCoordinator::reassignTask(int taskId, int newStaffId) {
    cout << "StaffCoordinator: Reassigning task " << taskId
              << " to staff " << newStaffId << endl;

    return "{\"action\": \"reassign_task\", "
           "\"task_id\": " + to_string(taskId) +
           ", \"new_staff_id\": " + to_string(newStaffId) +
           ", \"status\": \"reassigned\"}";
}

string StaffCoordinator::coordinateStaffMeeting(const string& agenda) {
    cout << "StaffCoordinator: Coordinating staff meeting with agenda: " << agenda << endl;

    return "{\"action\": \"schedule_meeting\", "
           "\"agenda\": \"" + agenda +
           "\", \"scheduled_time\": \"2024-11-15 10:00\", "
           "\"participants\": \"all_staff\", "
           "\"status\": \"scheduled\"}";
}

string StaffCoordinator::getStaffNotifications() {
    cout << "StaffCoordinator: Retrieving staff notifications" << endl;

    string notifications = apiAdapter->getNotifications();
    return "{\"staff_notifications\": " + notifications + "}";
}

string StaffCoordinator::markNotificationCompleted(int notificationId) {
    cout << "StaffCoordinator: Marking notification as completed: " << notificationId << endl;

    string apiResponse = apiAdapter->finishTask(notificationId);
    return "{\"action\": \"complete_notification\", "
           "\"notification_id\": " + to_string(notificationId) +
           ", \"api_response\": " + apiResponse + "}";
}

string StaffCoordinator::createStaffNotification(const string& message, const string& priority) {
    cout << "StaffCoordinator: Creating staff notification: " << message
              << " (priority: " << priority << ")" << endl;

    return "{\"action\": \"create_notification\", "
           "\"message\": \"" + message +
           "\", \"priority\": \"" + priority +
           "\", \"status\": \"created\", "
           "\"notification_id\": " + to_string(rand() % 1000 + 100) + "}";
}

// Private helper methods
string StaffCoordinator::determineStaffRoleForTask(const string& task) {
    string lowerTask = task;
    for (char &c : lowerTask) {
        c = tolower(c);
    }

    if (lowerTask.find("water") != string::npos ||
        lowerTask.find("plant") != string::npos ||
        lowerTask.find("grow") != string::npos) {
        return "gardener";
    } else if (lowerTask.find("sale") != string::npos ||
               lowerTask.find("buy") != string::npos ||
               lowerTask.find("price") != string::npos) {
        return "sales";
    } else if (lowerTask.find("care") != string::npos ||
               lowerTask.find("advice") != string::npos) {
        return "consultant";
    }

    return "general";
}

int StaffCoordinator::findAvailableStaff(const string& role) {
    map<string, int> roleToStaffId = {
        {"gardener", 1},
        {"sales", 2},
        {"consultant", 1},
        {"general", 2}
    };

    if (roleToStaffId.find(role) != roleToStaffId.end()) {
        return roleToStaffId[role];
    }

    return 1;
}

string StaffCoordinator::formatTaskDescription(const string& task) {
    // Simple formatting - capitalize first letter
    if (task.empty()) return task;
    string formatted = task;
    formatted[0] = toupper(formatted[0]);
    return formatted;
}