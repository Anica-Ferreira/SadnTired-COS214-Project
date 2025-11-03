$(document).ready(function() {
    loadShopPlants();
    updateCartCount();
});

function loadShopPlants() {
    $.ajax({
        url: "http://localhost:8080/shop",
        type: "GET",
        success: function(data) {
            console.log("Shop plants loaded:", data);
            // Handle both array and object response
            const plants = data.plants || data || [];
            displayPlants(plants);
        },
        error: function(error) {
            console.error("Error loading shop plants:", error);
            // Fallback data
            const fallbackPlants = [
                { id: 1, name: "Rose", description: "Beautiful red roses", price: 12.99, quantity: 15 },
                { id: 2, name: "Cactus", description: "Low maintenance desert plant", price: 8.99, quantity: 10 },
                { id: 3, name: "Sunflower", description: "Bright and cheerful flowers", price: 6.99, quantity: 20 }
            ];
            displayPlants(fallbackPlants);
        }
    });
}

function displayPlants(plants) {
    $('#cardBoxes').empty();

    if (Array.isArray(plants)) {
        plants.forEach(function(plant, index) {
            const plantId = plant.id || index + 1;

            const plantCard = `
                <div class="cardItem" id="plant${plantId}">
                    <img src="media/Plant` + plantId + `.png" class="plantImg"/>
                    <h2 class="plantName">${plant.name}</h2>
                    <p class="plantDesc">${plant.description || 'Beautiful plant'}</p>
                    <p class="plantPrice">Price: R ${plant.price || '9.99'}</p>
                    <p class="plantCount">In Stock: <span class="countLoc">${plant.quantity || plant.stockQuantity || 10}</span></p>
                    <button onclick="addToCart(${plantId}, '${plant.name}')">Add to Cart</button>
                </div>
            `;
            $('#cardBoxes').append(plantCard);
        });
    } else {
        $('#cardBoxes').html('<p>No plants available</p>');
    }
}

function addToCart(plantId, plantName) {
    let cart = JSON.parse(localStorage.getItem('cart') || '[]');
    const existingItem = cart.find(item => item.id === plantId);

    if (existingItem) {
        existingItem.quantity += 1;
    } else {
        cart.push({
            id: plantId,
            name: plantName,
            quantity: 1,
            price: 0
        });
    }

    localStorage.setItem('cart', JSON.stringify(cart));
    alert(`Added ${plantName} to cart!`);
    updateCartCount();
}

function updateCartCount() {
    const cart = JSON.parse(localStorage.getItem('cart') || '[]');
    const totalItems = cart.reduce((sum, item) => sum + item.quantity, 0);
    $('#cartCount').text(totalItems);
}