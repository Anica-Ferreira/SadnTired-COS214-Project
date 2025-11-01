$(document).ready(function() {
    loadCartItems();
});

function loadCartItems() {
    // For demo purposes, show some sample items
    // In a real app, you'd get this from the backend
    const sampleItems = [
        { name: "Rose", count: 2 },
        { name: "Cactus", count: 1 },
        { name: "Sunflower", count: 3 }
    ];

    $('#shopList').empty();
    sampleItems.forEach(function(item, index) {
        const listItem = `
            <li>
                <img src="media/Plant${index + 1}.png" />
                <div class="details">
                    <h2>${item.name}</h2>
                    <p>Count: <span>${item.count}</span></p>
                </div>
            </li>
        `;
        $('#shopList').append(listItem);
    });
}

function addBundle() {
    $.get("http://localhost:8080/bundle", function(data) {
        console.log("Bundle data:", data);
        alert(`Added bundle: ${data.name} with ${data.count} plants`);

        // Add bundle to cart UI
        const bundleItem = `
            <li>
                <img src="media/bundle.png" />
                <div class="details">
                    <h2>${data.name} Bundle</h2>
                    <p>Count: <span>${data.count} plants</span></p>
                </div>
            </li>
        `;
        $('#shopList').append(bundleItem);
    }).fail(function(error) {
        console.error("Error loading bundle:", error);
        alert("Error adding bundle");
    });
}

// Handle form submission
$('form').on('submit', function(e) {
    e.preventDefault();

    const name = $('#payName').val();
    const surname = $('#paySurname').val();
    const confirmed = $('#payConfirm').is(':checked');

    if (!name || !surname) {
        alert("Please fill in required fields");
        return;
    }

    if (!confirmed) {
        alert("Please confirm payment");
        return;
    }

    // Set customer information
    const customerData = {
        name: name,
        surname: surname,
        email: $('#payCont1').val() || "customer@example.com"
    };

    $.post({
        url: "http://localhost:8080/customer",
        contentType: "application/json",
        data: JSON.stringify(customerData)
    }).then(function() {
        alert("Purchase confirmed! Thank you for your order.");
        // Redirect or clear cart
        window.location.href = "shop.html";
    }).fail(function(error) {
        console.error("Error processing purchase:", error);
        alert("Error processing purchase");
    });
});