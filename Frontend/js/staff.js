$(document).ready(function() {
    loadStaffInfo();
    loadNotifications();
});

function loadStaffInfo() {
    $.ajax({
        url: "http://localhost:8080/staff",
        type: "GET",
        success: function(data) {
            console.log("Staff info loaded:", data);
            // Handle both array and object response
            const staff = data.staff ? data.staff[0] : data;
            $('#profile h3').text(staff.name || "Staff Member");
            $('#role').text(`Role: ${staff.role || "Employee"}`);
            $('#since').text(`Since: ${staff.since || "2024"}`);
        },
        error: function(error) {
            console.error("Error loading staff info:", error);
            // Fallback data
            $('#profile h3').text("John Doe");
            $('#role').text("Role: Nursery Manager");
            $('#since').text("Since: 2022");
        }
    });
}

function loadNotifications() {
    $.ajax({
        url: "http://localhost:8080/notifications",
        type: "GET",
        success: function(data) {
            console.log("Notifications loaded:", data);
            // Handle both array and object response
            const notifications = data.notifications || data || [];
            displayNotifications(notifications);
        },
        error: function(error) {
            console.error("Error loading notifications:", error);
            // Fallback notifications
            const fallbackNotifications = [
                { id: 1, type: "Watering", status: "Pending", description: "Water plants in section A" },
                { id: 2, type: "Inventory", status: "Urgent", description: "Restock roses in shop" }
            ];
            displayNotifications(fallbackNotifications);
        }
    });
}

function displayNotifications(notifications) {
    $('#notifList').empty();

    if (Array.isArray(notifications)) {
        notifications.forEach(function(notification) {
            const notifItem = `
                <li>
                    <h3>${notification.type} : ${notification.status}</h3>
                    <p>${notification.description}</p>
                    <button onclick="completeTask(${notification.id})">Mark Complete</button>
                </li>
            `;
            $('#notifList').append(notifItem);
        });
    } else {
        $('#notifList').html('<li>No notifications found</li>');
    }
}

function completeTask(taskId) {
    alert(`Task ${taskId} marked as complete!`);
    // Remove from UI
    $(`#notifList li:has(button[onclick="completeTask(${taskId})"])`).fadeOut();
}