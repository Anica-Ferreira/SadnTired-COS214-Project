$(document).ready(function() {
    loadCartItems();
    loadCartSummary();
});

function loadCartItems() {
    const cart = JSON.parse(localStorage.getItem('cart') || '[]');

    $('#shopList').empty();

    if (cart.length > 0) {
        cart.forEach(function(item, index) {
            const listItem = `
                <li>
                    <img src="media/Plant${item.id}.png" alt="${item.name}" />
                    <div class="details">
                        <h2>${item.name}</h2>
                        <p>Quantity: <span>${item.quantity}</span></p>
                        <button onclick="removeFromCart(${item.id})">Remove</button>
                    </div>
                </li>
            `;
            $('#shopList').append(listItem);
        });
    } else {
        $('#shopList').html('<li>Your cart is empty</li>');
    }
}

function loadCartSummary() {
    const cart = JSON.parse(localStorage.getItem('cart') || '[]');
    const itemCount = cart.reduce((sum, item) => sum + item.quantity, 0);
    const total = cart.reduce((sum, item) => sum + (item.price * item.quantity), 0);

    $('#totalAmount').text(`$${total.toFixed(2)}`);
    $('#itemCount').text(itemCount);
}

function addBundle() {
    $.ajax({
        url: "http://localhost:8080/bundles",
        type: "GET",
        success: function(data) {
            console.log("Bundle data:", data);
            // Add first bundle to cart
            if (data && data.length > 0) {
                const bundle = data[0];
                let cart = JSON.parse(localStorage.getItem('cart') || '[]');
                cart.push({
                    id: 99,
                    name: bundle.name || "Plant Bundle",
                    quantity: 1,
                    price: bundle.price || 29.99
                });
                localStorage.setItem('cart', JSON.stringify(cart));
                alert(`Added ${bundle.name} to cart!`);
                loadCartItems();
                loadCartSummary();
            }
        },
        error: function(error) {
            console.error("Error loading bundle:", error);
            // Fallback bundle
            let cart = JSON.parse(localStorage.getItem('cart') || '[]');
            cart.push({
                id: 99,
                name: "Starter Plant Bundle",
                quantity: 1,
                price: 29.99
            });
            localStorage.setItem('cart', JSON.stringify(cart));
            alert('Added Starter Plant Bundle to cart!');
            loadCartItems();
            loadCartSummary();
        }
    });
}

function removeFromCart(itemId) {
    let cart = JSON.parse(localStorage.getItem('cart') || '[]');
    cart = cart.filter(item => item.id !== itemId);
    localStorage.setItem('cart', JSON.stringify(cart));
    loadCartItems();
    loadCartSummary();
}

// Handle form submission
$('form').on('submit', function(e) {
    e.preventDefault();

    const name = $('#payName').val();
    const surname = $('#paySurname').val();
    const email = $('#payCont1').val();
    const confirmed = $('#payConfirm').is(':checked');

    if (!name || !surname || !email) {
        alert("Please fill in all required fields");
        return;
    }

    if (!confirmed) {
        alert("Please confirm payment");
        return;
    }

    // Process checkout
    alert("Purchase confirmed! Thank you for your order.");

    // Clear cart
    localStorage.removeItem('cart');

    // Redirect to shop
    setTimeout(() => {
        window.location.href = "shop.html";
    }, 2000);
});