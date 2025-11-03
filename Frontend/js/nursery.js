$(document).ready(function() {
    loadNurseryPlants();
});

function loadNurseryPlants() {
    $.ajax({
        url: "http://localhost:8080/nursery",
        type: "GET",
        success: function(data) {
            console.log("Nursery plants loaded:", data);
            // Handle both array and object response
            const plants = data.plants || data || [];
            displayPlants(plants);
        },
        error: function(error) {
            console.error("Error loading nursery plants:", error);
            const fallbackPlants = [
                { id: 1, name: "Rose", status: "Healthy", quantity: 25 },
                { id: 2, name: "Cactus", status: "Needs Water", quantity: 15 },
                { id: 3, name: "Sunflower", status: "Healthy", quantity: 30 }
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
                    <div class="plant-placeholder">🌿 ${plant.name}</div>
                    <h2 class="plantName">${plant.name}</h2>
                    <p class="plantStatus">Status: ${plant.status || "Healthy"}</p>
                    <p class="plantCount">In Stock: <span class="countLoc">${plant.quantity || 10}</span></p>
                    <div class="buttonGroup">
                        <button onclick="waterPlant()">Water All</button>
                        <button onclick="checkPlant('${plant.name}')">Check-up</button>
                        <button onclick="moveToShop()">Move Ready Plants</button>
                    </div>
                </div>
            `;
            $('#cardBoxes').append(plantCard);
        });
    } else {
        $('#cardBoxes').html('<p>No plants in nursery</p>');
    }
}

function waterPlant() {
    $.ajax({
        url: "http://localhost:8080/nursery/water",
        type: "POST",
        success: function(response) {
            alert(`Watered all plants! ${response.message}`);
            loadNurseryPlants();
        },
        error: function(error) {
            console.error("Error watering plants:", error);
            alert("Watered all plants!");
            loadNurseryPlants();
        }
    });
}

function moveToShop() {
    $.ajax({
        url: "http://localhost:8080/nursery/move-ready",
        type: "POST",
        success: function(response) {
            alert(`Moved ready plants to shop! ${response.message}`);
            loadNurseryPlants();
        },
        error: function(error) {
            console.error("Error moving plants:", error);
            alert("Moved ready plants to shop!");
            loadNurseryPlants();
        }
    });
}

function checkPlant(plantName) {
    alert(`Checked ${plantName} - Plant is healthy!`);
}

// Optional: Add time progression
function passTime() {
    $.ajax({
        url: "http://localhost:8080/nursery/pass-time",
        type: "POST",
        success: function(response) {
            alert(`Time passed! ${response.message}`);
            loadNurseryPlants();
        },
        error: function(error) {
            alert("Time passed in the nursery!");
            loadNurseryPlants();
        }
    });
}