$(document).ready(function() {
    loadStaffInfo();
    loadNotifications();
});

function loadStaffInfo() {
    $.get("http://localhost:8080/staff", function(data) {
        console.log("Staff info loaded:", data);
        $('#profile h3').text(data.name || "Staff Member");
        $('#role').text(`Role: ${data.role || "Employee"}`);
        $('#since').text(`Since: ${data.since || "2024"}`);
    }).fail(function(error) {
        console.error("Error loading staff info:", error);
    });
}

function loadNotifications() {
    $.get("http://localhost:8080/notifications", function(data) {
        console.log("Notifications loaded:", data);

        // Clear existing content
        $('#notifList').empty();

        // Create notification items
        data.forEach(function(notification, index) {
            const notifItem = `
                <li>
                    <h3>${notification.type} : ${notification.status}</h3>
                    <p>${notification.description}</p>
                    <button onclick="completeTask(${notification.id})">Mark Complete</button>
                </li>
            `;
            $('#notifList').append(notifItem);
        });
    }).fail(function(error) {
        console.error("Error loading notifications:", error);
    });
}

function completeTask(taskId) {
    $.post(`http://localhost:8080/finishTask/${taskId}`)
        .then(function(response) {
            alert(`Task ${taskId} completed: ${response}`);
            loadNotifications(); // Refresh the list
        })
        .fail(function(error) {
            console.error("Error completing task:", error);
            alert("Error completing task");
        });
}