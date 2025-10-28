// StaffCoordinator.cpp
#include "StaffCoordinator.h"
#include "WebAPIAdapter.h"
#include <iostream>
#include <sstream>
#include <map>

StaffCoordinator::StaffCoordinator(WebAPIAdapter* adapter) : apiAdapter(adapter) {
    std::cout << "Staff Coordinator initialized" << std::endl;
}

StaffCoordinator::~StaffCoordinator() {
    std::cout << "Staff Coordinator destroyed" << std::endl;
}

std::string StaffCoordinator::handleCustomerQuestion(int customerId, const std::string& question) {
    std::cout << "StaffCoordinator: Handling question from customer " << customerId
              << ": " << question << std::endl;

    // Analyze question to determine which staff member should handle it
    std::string assignedRole = determineStaffRoleForTask(question);
    int staffId = findAvailableStaff(assignedRole);

    std::stringstream response;
    response << "{\"action\": \"handle_question\", "
             << "\"customer_id\": " << customerId << ", "
             << "\"question\": \"" << question << "\", "
             << "\"assigned_staff_id\": " << staffId << ", "
             << "\"assigned_role\": \"" << assignedRole << "\", "
             << "\"status\": \"assigned\"}";

    return response.str();
}

std::string StaffCoordinator::handleCustomerRequest(int customerId, const std::string& request) {
    std::cout << "StaffCoordinator: Handling request from customer " << customerId
              << ": " << request << std::endl;

    // Get staff information from API
    std::string staffInfo = apiAdapter->getStaff();

    std::stringstream response;
    response << "{\"action\": \"handle_request\", "
             << "\"customer_id\": " << customerId << ", "
             << "\"request\": \"" << request << "\", "
             << "\"staff_assigned\": " << staffInfo << ", "
             << "\"status\": \"processing\"}";

    return response.str();
}

std::string StaffCoordinator::providePlantAdvice(int customerId, const std::string& plantType) {
    std::cout << "StaffCoordinator: Providing plant advice to customer " << customerId
              << " for plant type: " << plantType << std::endl;

    // Simulate plant advice based on type
    std::string advice;
    if (plantType == "Rose" || plantType == "rose") {
        advice = "Roses need full sunlight (6+ hours daily) and well-drained soil. Water deeply 2-3 times per week.";
    } else if (plantType == "Cactus" || plantType == "cactus") {
        advice = "Cacti prefer bright light and minimal water. Water every 2-3 weeks and ensure excellent drainage.";
    } else if (plantType == "Fern" || plantType == "fern") {
        advice = "Ferns thrive in indirect light and high humidity. Keep soil consistently moist but not soggy.";
    } else {
        advice = "This plant requires moderate care. Provide indirect sunlight and water when the top soil feels dry.";
    }

    return "{\"customer_id\": " + std::to_string(customerId) +
           ", \"plant_type\": \"" + plantType +
           "\", \"advice\": \"" + advice + "\"}";
}

std::string StaffCoordinator::assignTask(int staffId, const std::string& task) {
    std::cout << "StaffCoordinator: Assigning task to staff " << staffId
              << ": " << task << std::endl;

    std::string formattedTask = formatTaskDescription(task);

    return "{\"action\": \"assign_task\", "
           "\"staff_id\": " + std::to_string(staffId) +
           ", \"task\": \"" + formattedTask +
           "\", \"status\": \"assigned\", "
           "\"task_id\": " + std::to_string(rand() % 1000 + 1) + "}";
}

std::string StaffCoordinator::assignTaskByRole(const std::string& role, const std::string& task) {
    std::cout << "StaffCoordinator: Assigning task to role " << role
              << ": " << task << std::endl;

    int staffId = findAvailableStaff(role);

    if (staffId == -1) {
        return "{\"error\": \"No available staff for role: " + role + "\"}";
    }

    return assignTask(staffId, task);
}

std::string StaffCoordinator::completeTask(int taskId) {
    std::cout << "StaffCoordinator: Completing task ID: " << taskId << std::endl;

    // Use API to mark task as completed
    std::string apiResponse = apiAdapter->finishTask(taskId);

    return "{\"action\": \"complete_task\", "
           "\"task_id\": " + std::to_string(taskId) +
           ", \"api_response\": " + apiResponse + "}";
}

std::string StaffCoordinator::getPendingTasks() {
    std::cout << "StaffCoordinator: Retrieving pending tasks" << std::endl;

    // Get notifications from API (which represent tasks)
    std::string notifications = apiAdapter->getNotifications();

    return "{\"pending_tasks\": " + notifications + "}";
}

std::string StaffCoordinator::getStaffTasks(int staffId) {
    std::cout << "StaffCoordinator: Getting tasks for staff ID: " << staffId << std::endl;

    // Simulate staff-specific tasks
    return "{\"staff_id\": " + std::to_string(staffId) +
           ", \"tasks\": ["
           "{\"task_id\": 101, \"description\": \"Water plants in greenhouse A\", \"status\": \"in_progress\"}, "
           "{\"task_id\": 102, \"description\": \"Restock rose inventory\", \"status\": \"pending\"}, "
           "{\"task_id\": 103, \"description\": \"Assist customers in shop\", \"status\": \"completed\"}"
           "]}";
}

std::string StaffCoordinator::getAllStaff() {
    std::cout << "StaffCoordinator: Retrieving all staff information" << std::endl;

    std::string staffInfo = apiAdapter->getStaff();
    return "{\"staff_list\": " + staffInfo + "}";
}

std::string StaffCoordinator::getStaffByRole(const std::string& role) {
    std::cout << "StaffCoordinator: Retrieving staff by role: " << role << std::endl;

    std::string allStaff = apiAdapter->getStaff();

    // In real implementation, filter by role from API response
    return "{\"role\": \"" + role +
           "\", \"staff\": [{\"id\": 1, \"name\": \"Mr. Green\", \"role\": \"Gardener\"}]}";
}

std::string StaffCoordinator::getStaffPerformance() {
    std::cout << "StaffCoordinator: Generating staff performance report" << std::endl;

    return "{\"performance_report\": {"
           "\"period\": \"November 2024\", "
           "\"metrics\": {"
           "\"tasks_completed\": 45, "
           "\"customer_satisfaction\": 4.8, "
           "\"plants_cared_for\": 123, "
           "\"efficiency_rating\": 92"
           "}}}";
}

std::string StaffCoordinator::assignStaffToNurseryArea(int staffId, const std::string& area) {
    std::cout << "StaffCoordinator: Assigning staff " << staffId
              << " to nursery area: " << area << std::endl;

    return "{\"action\": \"assign_area\", "
           "\"staff_id\": " + std::to_string(staffId) +
           ", \"area\": \"" + area +
           "\", \"status\": \"assigned\"}";
}

std::string StaffCoordinator::escalateTask(int taskId) {
    std::cout << "StaffCoordinator: Escalating task ID: " << taskId << std::endl;

    // Simulate escalation logic
    return "{\"action\": \"escalate_task\", "
           "\"task_id\": " + std::to_string(taskId) +
           ", \"new_priority\": \"high\", "
           "\"assigned_to\": \"senior_staff\", "
           "\"status\": \"escalated\"}";
}

std::string StaffCoordinator::reassignTask(int taskId, int newStaffId) {
    std::cout << "StaffCoordinator: Reassigning task " << taskId
              << " to staff " << newStaffId << std::endl;

    return "{\"action\": \"reassign_task\", "
           "\"task_id\": " + std::to_string(taskId) +
           ", \"new_staff_id\": " + std::to_string(newStaffId) +
           ", \"status\": \"reassigned\"}";
}

std::string StaffCoordinator::coordinateStaffMeeting(const std::string& agenda) {
    std::cout << "StaffCoordinator: Coordinating staff meeting with agenda: " << agenda << std::endl;

    return "{\"action\": \"schedule_meeting\", "
           "\"agenda\": \"" + agenda +
           "\", \"scheduled_time\": \"2024-11-15 10:00\", "
           "\"participants\": \"all_staff\", "
           "\"status\": \"scheduled\"}";
}

std::string StaffCoordinator::getStaffNotifications() {
    std::cout << "StaffCoordinator: Retrieving staff notifications" << std::endl;

    std::string notifications = apiAdapter->getNotifications();
    return "{\"staff_notifications\": " + notifications + "}";
}

std::string StaffCoordinator::markNotificationCompleted(int notificationId) {
    std::cout << "StaffCoordinator: Marking notification as completed: " << notificationId << std::endl;

    std::string apiResponse = apiAdapter->finishTask(notificationId);
    return "{\"action\": \"complete_notification\", "
           "\"notification_id\": " + std::to_string(notificationId) +
           ", \"api_response\": " + apiResponse + "}";
}

std::string StaffCoordinator::createStaffNotification(const std::string& message, const std::string& priority) {
    std::cout << "StaffCoordinator: Creating staff notification: " << message
              << " (priority: " << priority << ")" << std::endl;

    return "{\"action\": \"create_notification\", "
           "\"message\": \"" + message +
           "\", \"priority\": \"" + priority +
           "\", \"status\": \"created\", "
           "\"notification_id\": " + std::to_string(rand() % 1000 + 100) + "}";
}

std::string StaffCoordinator::createWorkSchedule(const std::string& period) {
    std::cout << "StaffCoordinator: Creating work schedule for period: " << period << std::endl;

    return "{\"schedule\": {"
           "\"period\": \"" + period + "\", "
           "\"shifts\": ["
           "{\"staff_id\": 1, \"name\": \"Mr. Green\", \"monday\": \"9-5\", \"tuesday\": \"9-5\", \"wednesday\": \"off\", \"thursday\": \"9-5\", \"friday\": \"9-5\"}, "
           "{\"staff_id\": 2, \"name\": \"Mr. Cash\", \"monday\": \"12-8\", \"tuesday\": \"12-8\", \"wednesday\": \"9-5\", \"thursday\": \"12-8\", \"friday\": \"9-5\"}"
           "]}}";
}

std::string StaffCoordinator::getStaffSchedule(int staffId) {
    std::cout << "StaffCoordinator: Getting schedule for staff ID: " << staffId << std::endl;

    return "{\"staff_id\": " + std::to_string(staffId) +
           ", \"schedule\": {"
           "\"week\": \"2024-11-11 to 2024-11-15\", "
           "\"shifts\": [\"Mon: 9AM-5PM\", \"Tue: 9AM-5PM\", \"Wed: OFF\", \"Thu: 9AM-5PM\", \"Fri: 9AM-5PM\"]"
           "}}";
}

std::string StaffCoordinator::updateStaffAvailability(int staffId, const std::string& availability) {
    std::cout << "StaffCoordinator: Updating availability for staff " << staffId
              << ": " << availability << std::endl;

    return "{\"action\": \"update_availability\", "
           "\"staff_id\": " + std::to_string(staffId) +
           ", \"availability\": \"" + availability +
           "\", \"status\": \"updated\"}";
}

// Private helper methods
std::string StaffCoordinator::determineStaffRoleForTask(const std::string& task) {
    std::string lowerTask = task;
    // Convert to lowercase for comparison (simplified)
    for (char &c : lowerTask) {
        c = tolower(c);
    }

    if (lowerTask.find("water") != std::string::npos ||
        lowerTask.find("plant") != std::string::npos ||
        lowerTask.find("grow") != std::string::npos) {
        return "gardener";
    } else if (lowerTask.find("sale") != std::string::npos ||
               lowerTask.find("buy") != std::string::npos ||
               lowerTask.find("price") != std::string::npos) {
        return "sales";
    } else if (lowerTask.find("care") != std::string::npos ||
               lowerTask.find("advice") != std::string::npos) {
        return "consultant";
    }

    return "general";
}

int StaffCoordinator::findAvailableStaff(const std::string& role) {
    // Simple staff assignment logic
    std::map<std::string, int> roleToStaffId = {
        {"gardener", 1},
        {"sales", 2},
        {"consultant", 1}, // Mr. Green can also consult
        {"general", 2}
    };

    if (roleToStaffId.find(role) != roleToStaffId.end()) {
        return roleToStaffId[role];
    }

    return 1; // Default to Mr. Green
}

std::string StaffCoordinator::formatTaskDescription(const std::string& task) {
    // Add timestamp and format task description
    return "[Task] " + task + " (assigned: 2024-11-10)";
}