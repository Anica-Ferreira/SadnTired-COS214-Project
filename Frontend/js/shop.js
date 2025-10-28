$(document).ready(function() {
    loadShopPlants();
});

function loadShopPlants() {
    $.get("http://localhost:8080/shop", function(data) {
        console.log("Shop plants loaded:", data);

        // Clear existing content
        $('#cardBoxes').empty();

        // Create plant cards
        data.forEach(function(plant, index) {
            const plantId = index + 1;
            const plantCard = `
                <div class="cardItem" id="plant${plantId}">
                    <img src="media/Plant${plantId}.png" class="plantImg"/>
                    <h2 class="plantName">${plant.name}</h2>
                    <p class="plantDesc">${plant.description || 'Beautiful plant'}</p>
                    <p class="plantCount">In Stock: <span class="countLoc">${plant.shopStock || plant.quantity || 0}</span></p>
                    <button onclick="addToCart('${plant.name}')">Add to Cart</button>
                </div>
            `;
            $('#cardBoxes').append(plantCard);
        });
    }).fail(function(error) {
        console.error("Error loading shop plants:", error);
        $('#cardBoxes').html('<p>Error loading plants. Make sure the backend is running.</p>');
    });
}

function addToCart(plantName) {
    // Set customer info (simplified - in real app, get from form)
    const customerData = {
        name: "Customer",
        email: "customer@example.com"
    };

    $.post({
        url: "http://localhost:8080/customer",
        contentType: "application/json",
        data: JSON.stringify(customerData)
    }).then(function() {
        alert(`Added ${plantName} to cart!`);
        // In a real app, you'd update the cart UI
    }).fail(function(error) {
        console.error("Error adding to cart:", error);
        alert("Error adding plant to cart");
    });
}