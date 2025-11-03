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
    //cout << "Staff Coordinator initialized" << endl;
}

/**
 * @brief [Destroys the StaffCoordinator object]
 */
StaffCoordinator::~StaffCoordinator() {
    //cout << "Staff Coordinator destroyed" << endl;
}

/**
 * @brief [Handles customer questions and assigns appropriate staff]
 * @param[in,out] customerId [The ID of the customer asking the question]
 * @param[in,out] question [The customer's question]
 * @return [JSON string with assignment information]
 */
string StaffCoordinator::handleCustomerQuestion(int customerId, const string& plantName) {
    cout << "\033[1;32m\nStaffCoordinator: Handling question from customer " 
         << customerId << ": " << plantName << "\033[0m" << endl;

    return providePlantAdvice(customerId, plantName);
}

/**
 * @brief [Handles general customer requests]
 * @param[in,out] customerId [The ID of the customer making the request]
 * @param[in,out] request [The customer's request]
 * @return [JSON string with request handling information]
 */
string StaffCoordinator::handleCustomerRequest(int customerId, const string& request) {
    cout << "StaffCoordinator: Handling request from customer " << customerId
              << ": " << request << endl;

    // Get staff information from API
    string staffInfo = apiAdapter->getStaff();

    stringstream response;
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
string StaffCoordinator::providePlantAdvice(int customerId, const string& plantType) {
    // Define advice based on known plant options
    string advice;

    if (plantType == "Rose" || plantType == "rose") {
        advice = "Roses need full sunlight (6+ hours daily) and well-drained soil. Water deeply 2-3 times per week.";
    } 
    else if (plantType == "Tulip" || plantType == "tulip") {
        advice = "Tulips prefer cool climates and well-drained soil. Water moderately and avoid waterlogging.";
    } 
    else if (plantType == "Lavender" || plantType == "lavender") {
        advice = "Lavender thrives in full sun and dry, sandy soil. Water sparingly once established.";
    } 
    else if (plantType == "Cactus" || plantType == "cactus") {
        advice = "Cacti prefer bright light and minimal water. Water every 2-3 weeks and ensure excellent drainage.";
    } 
    else if (plantType == "Aloe Vera" || plantType == "aloe vera") {
        advice = "Aloe Vera needs bright, indirect sunlight and well-draining soil. Water only when soil is dry.";
    } 
    else if (plantType == "Bonsai" || plantType == "bonsai") {
        advice = "Bonsai require filtered light and regular watering. Keep soil slightly moist and prune as needed.";
    } 
    else if (plantType == "Maple Tree" || plantType == "maple tree") {
        advice = "Maple trees need full sun to partial shade and well-drained soil. Water young trees regularly.";
    } 
    else if (plantType == "Sunflower" || plantType == "sunflower") {
        advice = "Sunflowers need full sun and fertile soil. Water moderately and support tall stems if needed.";
    } 
    else if (plantType == "Snake Plant" || plantType == "snake plant") {
        advice = "Snake Plants tolerate low light and infrequent watering. Perfect for indoor settings.";
    } 
    else if (plantType == "Oak" || plantType == "oak") {
        advice = "Oak trees need full sun and deep, well-drained soil. Water young trees until established.";
    } 
    else {
        advice = "This plant requires moderate care. Provide indirect sunlight and water when the top soil feels dry.";
    }

    // Return plain advice string
    return advice;
}

/**
 * @brief [Assigns a task to a specific staff member]
 * @param[in,out] staffId [The ID of the staff member to assign the task to]
 * @param[in,out] task [The task description to assign]
 * @return [JSON string with assignment confirmation]
 */
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

/**
 * @brief [Assigns a task to any available staff member of a specific role]
 * @param[in,out] role [The role type to assign the task to]
 * @param[in,out] task [The task description to assign]
 * @return [JSON string with assignment information]
 */
string StaffCoordinator::assignTaskByRole(const string& role, const string& task) {
    cout << "StaffCoordinator: Assigning task to role " << role
              << ": " << task << endl;

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
string StaffCoordinator::completeTask(int taskId) {
    cout << "StaffCoordinator: Completing task ID: " << taskId << endl;

    // Use API to mark task as completed
    string apiResponse = apiAdapter->finishTask(taskId);

    return "{\"action\": \"complete_task\", "
           "\"task_id\": " + to_string(taskId) +
           ", \"api_response\": " + apiResponse + "}";
}

/**
 * @brief [Retrieves all pending tasks]
 * @return [JSON string with pending tasks information]
 */
string StaffCoordinator::getPendingTasks() {
    cout << "StaffCoordinator: Retrieving pending tasks" << endl;

    // Get notifications from API (which represent tasks)
    string notifications = apiAdapter->getNotifications();

    return "{\"pending_tasks\": " + notifications + "}";
}

/**
 * @brief [Gets tasks assigned to a specific staff member]
 * @param[in,out] staffId [The ID of the staff member]
 * @return [JSON string with staff task information]
 */
string StaffCoordinator::getStaffTasks(int staffId) {
    cout << "StaffCoordinator: Getting tasks for staff ID: " << staffId << endl;

    // Simulate staff-specific tasks
    return "{\"staff_id\": " + to_string(staffId) +
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
string StaffCoordinator::getAllStaff() {
    cout << "StaffCoordinator: Retrieving all staff information" << endl;

    string staffInfo = apiAdapter->getStaff();
    return "{\"staff_list\": " + staffInfo + "}";
}

/**
 * @brief [Retrieves staff members by specific role]
 * @param[in,out] role [The role to filter staff by]
 * @return [JSON string with filtered staff information]
 */
string StaffCoordinator::getStaffByRole(const string& role) {
    cout << "StaffCoordinator: Retrieving staff by role: " << role << endl;

    string allStaff = apiAdapter->getStaff();

    // In real implementation, filter by role from API response
    return "{\"role\": \"" + role +
           "\", \"staff\": [{\"id\": 1, \"name\": \"Mr. Green\", \"role\": \"Gardener\"}]}";
}

/**
 * @brief [Generates a performance report for staff members]
 * @return [JSON string with performance report]
 */
string StaffCoordinator::getStaffPerformance() {
    cout << "StaffCoordinator: Generating staff performance report" << endl;

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
string StaffCoordinator::assignStaffToNurseryArea(int staffId, const string& area) {
    cout << "StaffCoordinator: Assigning staff " << staffId
              << " to nursery area: " << area << endl;

    return "{\"action\": \"assign_area\", "
           "\"staff_id\": " + to_string(staffId) +
           ", \"area\": \"" + area +
           "\", \"status\": \"assigned\"}";
}

/**
 * @brief [Escalates a task to higher priority]
 * @param[in,out] taskId [The ID of the task to escalate]
 * @return [JSON string with escalation information]
 */
string StaffCoordinator::escalateTask(int taskId) {
    cout << "StaffCoordinator: Escalating task ID: " << taskId << endl;

    // Simulate escalation logic
    return "{\"action\": \"escalate_task\", "
           "\"task_id\": " + to_string(taskId) +
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
string StaffCoordinator::reassignTask(int taskId, int newStaffId) {
    cout << "StaffCoordinator: Reassigning task " << taskId
              << " to staff " << newStaffId << endl;

    return "{\"action\": \"reassign_task\", "
           "\"task_id\": " + to_string(taskId) +
           ", \"new_staff_id\": " + to_string(newStaffId) +
           ", \"status\": \"reassigned\"}";
}

/**
 * @brief [Coordinates staff meetings with specified agenda]
 * @param[in,out] agenda [The meeting agenda]
 * @return [JSON string with meeting scheduling information]
 */
string StaffCoordinator::coordinateStaffMeeting(const string& agenda) {
    cout << "StaffCoordinator: Coordinating staff meeting with agenda: " << agenda << endl;

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
string StaffCoordinator::getStaffNotifications() {
    cout << "StaffCoordinator: Retrieving staff notifications" << endl;

    string notifications = apiAdapter->getNotifications();
    return "{\"staff_notifications\": " + notifications + "}";
}

/**
 * @brief [Marks a notification as completed]
 * @param[in,out] notificationId [The ID of the notification to complete]
 * @return [JSON string with completion confirmation]
 */
string StaffCoordinator::markNotificationCompleted(int notificationId) {
    cout << "StaffCoordinator: Marking notification as completed: " << notificationId << endl;

    string apiResponse = apiAdapter->finishTask(notificationId);
    return "{\"action\": \"complete_notification\", "
           "\"notification_id\": " + to_string(notificationId) +
           ", \"api_response\": " + apiResponse + "}";
}

/**
 * @brief [Creates a new staff notification]
 * @param[in,out] message [The notification message]
 * @param[in,out] priority [The priority level of the notification]
 * @return [JSON string with notification creation information]
 */
string StaffCoordinator::createStaffNotification(const string& message, const string& priority) {
    cout << "StaffCoordinator: Creating staff notification: " << message
              << " (priority: " << priority << ")" << endl;

    return "{\"action\": \"create_notification\", "
           "\"message\": \"" + message +
           "\", \"priority\": \"" + priority +
           "\", \"status\": \"created\", "
           "\"notification_id\": " + to_string(rand() % 1000 + 100) + "}";
}

/**
 * @brief [Creates a work schedule for staff members]
 * @param[in,out] period [The scheduling period]
 * @return [JSON string with work schedule information]
 */
string StaffCoordinator::createWorkSchedule(const string& period) {
    cout << "StaffCoordinator: Creating work schedule for period: " << period << endl;

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
string StaffCoordinator::getStaffSchedule(int staffId) {
    cout << "StaffCoordinator: Getting schedule for staff ID: " << staffId << endl;

    return "{\"staff_id\": " + to_string(staffId) +
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
string StaffCoordinator::updateStaffAvailability(int staffId, const string& availability) {
    cout << "StaffCoordinator: Updating availability for staff " << staffId
              << ": " << availability << endl;

    return "{\"action\": \"update_availability\", "
           "\"staff_id\": " + to_string(staffId) +
           ", \"availability\": \"" + availability +
           "\", \"status\": \"updated\"}";
}

// Private helper methods

/**
 * @brief [Determines the appropriate staff role for a given task]
 * @param[in] task [The task description to analyze]
 * @return [The determined staff role for the task]
 */
string StaffCoordinator::determineStaffRoleForTask(const string& task) {
    string lowerTask = task;
    // Convert to lowercase for comparison (simplified)
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

/**
 * @brief [Finds available staff for a specific role]
 * @param[in] role [The role to find staff for]
 * @return [The ID of available staff member, or -1 if none found]
 */
int StaffCoordinator::findAvailableStaff(const string& role) {
    // Simple staff assignment logic
    map<string, int> roleToStaffId = {
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
string StaffCoordinator::formatTaskDescription(const string& task) {
    // Add timestamp and format task description
    return "[Task] " + task + " (assigned: 2024-11-10)";
}