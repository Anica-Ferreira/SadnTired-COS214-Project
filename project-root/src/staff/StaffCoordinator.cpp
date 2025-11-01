/**
 * @class [StaffCoordinator]
 * @brief [Implementation of the StaffCoordinator class for staff coordination]
 * @details [Handles staff task assignment, coordination, and workflow management]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "StaffCoordinator.h"
#include <iostream>
#include <sstream>
#include <map>

/**
 * @brief [Constructs a new StaffCoordinator object]
 * @param[in] name [The name of the staff coordinator]
 * @param[in] adapter [Pointer to the WebAPIAdapter for system communication]
 */
StaffCoordinator::StaffCoordinator(WebAPIAdapter* adapter) : apiAdapter(adapter) {
    std::cout << "Staff Coordinator initialized" << std::endl;
}

/**
 * @brief [Destroys the StaffCoordinator object]
 */
StaffCoordinator::~StaffCoordinator() {
    std::cout << "Staff Coordinator destroyed" << std::endl;
}

/**
 * @brief [Handles customer questions and assigns appropriate staff]
 * @param[in,out] customerId [The ID of the customer asking the question]
 * @param[in,out] question [The customer's question]
 * @return [JSON string with assignment information]
 */
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

/**
 * @brief [Handles general customer requests]
 * @param[in,out] customerId [The ID of the customer making the request]
 * @param[in,out] request [The customer's request]
 * @return [JSON string with request handling information]
 */
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

/**
 * @brief [Provides plant care advice to customers]
 * @param[in,out] customerId [The ID of the customer requesting advice]
 * @param[in,out] plantType [The type of plant for advice]
 * @return [JSON string with plant care advice]
 */
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

/**
 * @brief [Assigns a task to a specific staff member]
 * @param[in,out] staffId [The ID of the staff member to assign the task to]
 * @param[in,out] task [The task description to assign]
 * @return [JSON string with assignment confirmation]
 */
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

/**
 * @brief [Assigns a task to any available staff member of a specific role]
 * @param[in,out] role [The role type to assign the task to]
 * @param[in,out] task [The task description to assign]
 * @return [JSON string with assignment information]
 */
std::string StaffCoordinator::assignTaskByRole(const std::string& role, const std::string& task) {
    std::cout << "StaffCoordinator: Assigning task to role " << role
              << ": " << task << std::endl;

    int staffId = findAvailableStaff(role);

    if (staffId == -1) {
        return "{\"error\": \"No available staff for role: " + role + "\"}";
    }

    return assignTask(staffId, task);
}

/**
 * @brief [Marks a task as completed]
 * @param[in,out] taskId [The ID of the task to complete]
 * @return [JSON string with completion confirmation]
 */
std::string StaffCoordinator::completeTask(int taskId) {
    std::cout << "StaffCoordinator: Completing task ID: " << taskId << std::endl;

    // Use API to mark task as completed
    std::string apiResponse = apiAdapter->finishTask(taskId);

    return "{\"action\": \"complete_task\", "
           "\"task_id\": " + std::to_string(taskId) +
           ", \"api_response\": " + apiResponse + "}";
}

/**
 * @brief [Retrieves all pending tasks]
 * @return [JSON string with pending tasks information]
 */
std::string StaffCoordinator::getPendingTasks() {
    std::cout << "StaffCoordinator: Retrieving pending tasks" << std::endl;

    // Get notifications from API (which represent tasks)
    std::string notifications = apiAdapter->getNotifications();

    return "{\"pending_tasks\": " + notifications + "}";
}

/**
 * @brief [Gets tasks assigned to a specific staff member]
 * @param[in,out] staffId [The ID of the staff member]
 * @return [JSON string with staff task information]
 */
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

/**
 * @brief [Retrieves information about all staff members]
 * @return [JSON string with staff list information]
 */
std::string StaffCoordinator::getAllStaff() {
    std::cout << "StaffCoordinator: Retrieving all staff information" << std::endl;

    std::string staffInfo = apiAdapter->getStaff();
    return "{\"staff_list\": " + staffInfo + "}";
}

/**
 * @brief [Retrieves staff members by specific role]
 * @param[in,out] role [The role to filter staff by]
 * @return [JSON string with filtered staff information]
 */
std::string StaffCoordinator::getStaffByRole(const std::string& role) {
    std::cout << "StaffCoordinator: Retrieving staff by role: " << role << std::endl;

    std::string allStaff = apiAdapter->getStaff();

    // In real implementation, filter by role from API response
    return "{\"role\": \"" + role +
           "\", \"staff\": [{\"id\": 1, \"name\": \"Mr. Green\", \"role\": \"Gardener\"}]}";
}

/**
 * @brief [Generates a performance report for staff members]
 * @return [JSON string with performance report]
 */
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

/**
 * @brief [Assigns a staff member to a specific nursery area]
 * @param[in,out] staffId [The ID of the staff member]
 * @param[in,out] area [The nursery area to assign the staff member to]
 * @return [JSON string with assignment confirmation]
 */
std::string StaffCoordinator::assignStaffToNurseryArea(int staffId, const std::string& area) {
    std::cout << "StaffCoordinator: Assigning staff " << staffId
              << " to nursery area: " << area << std::endl;

    return "{\"action\": \"assign_area\", "
           "\"staff_id\": " + std::to_string(staffId) +
           ", \"area\": \"" + area +
           "\", \"status\": \"assigned\"}";
}

/**
 * @brief [Escalates a task to higher priority]
 * @param[in,out] taskId [The ID of the task to escalate]
 * @return [JSON string with escalation information]
 */
std::string StaffCoordinator::escalateTask(int taskId) {
    std::cout << "StaffCoordinator: Escalating task ID: " << taskId << std::endl;

    // Simulate escalation logic
    return "{\"action\": \"escalate_task\", "
           "\"task_id\": " + std::to_string(taskId) +
           ", \"new_priority\": \"high\", "
           "\"assigned_to\": \"senior_staff\", "
           "\"status\": \"escalated\"}";
}

/**
 * @brief [Reassigns a task to a different staff member]
 * @param[in,out] taskId [The ID of the task to reassign]
 * @param[in,out] newStaffId [The ID of the new staff member]
 * @return [JSON string with reassignment confirmation]
 */
std::string StaffCoordinator::reassignTask(int taskId, int newStaffId) {
    std::cout << "StaffCoordinator: Reassigning task " << taskId
              << " to staff " << newStaffId << std::endl;

    return "{\"action\": \"reassign_task\", "
           "\"task_id\": " + std::to_string(taskId) +
           ", \"new_staff_id\": " + std::to_string(newStaffId) +
           ", \"status\": \"reassigned\"}";
}

/**
 * @brief [Coordinates staff meetings with specified agenda]
 * @param[in,out] agenda [The meeting agenda]
 * @return [JSON string with meeting scheduling information]
 */
std::string StaffCoordinator::coordinateStaffMeeting(const std::string& agenda) {
    std::cout << "StaffCoordinator: Coordinating staff meeting with agenda: " << agenda << std::endl;

    return "{\"action\": \"schedule_meeting\", "
           "\"agenda\": \"" + agenda +
           "\", \"scheduled_time\": \"2024-11-15 10:00\", "
           "\"participants\": \"all_staff\", "
           "\"status\": \"scheduled\"}";
}

/**
 * @brief [Retrieves staff notifications]
 * @return [JSON string with staff notifications]
 */
std::string StaffCoordinator::getStaffNotifications() {
    std::cout << "StaffCoordinator: Retrieving staff notifications" << std::endl;

    std::string notifications = apiAdapter->getNotifications();
    return "{\"staff_notifications\": " + notifications + "}";
}

/**
 * @brief [Marks a notification as completed]
 * @param[in,out] notificationId [The ID of the notification to complete]
 * @return [JSON string with completion confirmation]
 */
std::string StaffCoordinator::markNotificationCompleted(int notificationId) {
    std::cout << "StaffCoordinator: Marking notification as completed: " << notificationId << std::endl;

    std::string apiResponse = apiAdapter->finishTask(notificationId);
    return "{\"action\": \"complete_notification\", "
           "\"notification_id\": " + std::to_string(notificationId) +
           ", \"api_response\": " + apiResponse + "}";
}

/**
 * @brief [Creates a new staff notification]
 * @param[in,out] message [The notification message]
 * @param[in,out] priority [The priority level of the notification]
 * @return [JSON string with notification creation information]
 */
std::string StaffCoordinator::createStaffNotification(const std::string& message, const std::string& priority) {
    std::cout << "StaffCoordinator: Creating staff notification: " << message
              << " (priority: " << priority << ")" << std::endl;

    return "{\"action\": \"create_notification\", "
           "\"message\": \"" + message +
           "\", \"priority\": \"" + priority +
           "\", \"status\": \"created\", "
           "\"notification_id\": " + std::to_string(rand() % 1000 + 100) + "}";
}

/**
 * @brief [Creates a work schedule for staff members]
 * @param[in,out] period [The scheduling period]
 * @return [JSON string with work schedule information]
 */
std::string StaffCoordinator::createWorkSchedule(const std::string& period) {
    std::cout << "StaffCoordinator: Creating work schedule for period: " << period << std::endl;

    return "{\"schedule\": {"
           "\"period\": \"" + period + "\", "
           "\"shifts\": ["
           "{\"staff_id\": 1, \"name\": \"Mr. Green\", \"monday\": \"9-5\", \"tuesday\": \"9-5\", \"wednesday\": \"off\", \"thursday\": \"9-5\", \"friday\": \"9-5\"}, "
           "{\"staff_id\": 2, \"name\": \"Mr. Cash\", \"monday\": \"12-8\", \"tuesday\": \"12-8\", \"wednesday\": \"9-5\", \"thursday\": \"12-8\", \"friday\": \"9-5\"}"
           "]}}";
}

/**
 * @brief [Retrieves the schedule for a specific staff member]
 * @param[in,out] staffId [The ID of the staff member]
 * @return [JSON string with staff schedule information]
 */
std::string StaffCoordinator::getStaffSchedule(int staffId) {
    std::cout << "StaffCoordinator: Getting schedule for staff ID: " << staffId << std::endl;

    return "{\"staff_id\": " + std::to_string(staffId) +
           ", \"schedule\": {"
           "\"week\": \"2024-11-11 to 2024-11-15\", "
           "\"shifts\": [\"Mon: 9AM-5PM\", \"Tue: 9AM-5PM\", \"Wed: OFF\", \"Thu: 9AM-5PM\", \"Fri: 9AM-5PM\"]"
           "}}";
}

/**
 * @brief [Updates the availability status of a staff member]
 * @param[in,out] staffId [The ID of the staff member]
 * @param[in,out] availability [The new availability status]
 * @return [JSON string with availability update confirmation]
 */
std::string StaffCoordinator::updateStaffAvailability(int staffId, const std::string& availability) {
    std::cout << "StaffCoordinator: Updating availability for staff " << staffId
              << ": " << availability << std::endl;

    return "{\"action\": \"update_availability\", "
           "\"staff_id\": " + std::to_string(staffId) +
           ", \"availability\": \"" + availability +
           "\", \"status\": \"updated\"}";
}

// Private helper methods

/**
 * @brief [Determines the appropriate staff role for a given task]
 * @param[in] task [The task description to analyze]
 * @return [The determined staff role for the task]
 */
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

/**
 * @brief [Finds available staff for a specific role]
 * @param[in] role [The role to find staff for]
 * @return [The ID of available staff member, or -1 if none found]
 */
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

/**
 * @brief [Formats task descriptions for consistency]
 * @param[in] task [The task description to format]
 * @return [The formatted task description]
 */
std::string StaffCoordinator::formatTaskDescription(const std::string& task) {
    // Add timestamp and format task description
    return "[Task] " + task + " (assigned: 2024-11-10)";
}