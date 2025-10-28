$(document).ready(function() {
    loadNurseryPlants();
});

function loadNurseryPlants() {
    $.get("http://localhost:8080/nursery", function(data) {
        console.log("Nursery plants loaded:", data);

        // Clear existing content
        $('#cardBoxes').empty();

        // Create plant cards
        data.forEach(function(plant, index) {
            const plantId = index + 1;
            const plantCard = `
                <div class="cardItem" id="plant${plantId}">
                    <img src="media/Plant${plantId}.png" class="plantImg"/>
                    <h2 class="plantName">${plant.name}</h2>
                    <p class="plantStatus">Status: ${plant.status}</p>
                    <p class="plantCount">In Stock: <span class="countLoc">${plant.nurseryStock || plant.quantity || 0}</span></p>
                    <div class="buttonGroup">
                        <button onclick="waterPlant('${plant.name}')">Water</button>
                        <button onclick="checkPlant('${plant.name}')">Check-up</button>
                        <button onclick="moveToShop('${plant.name}')">Add to Store</button>
                    </div>
                </div>
            `;
            $('#cardBoxes').append(plantCard);
        });
    }).fail(function(error) {
        console.error("Error loading nursery plants:", error);
        $('#cardBoxes').html('<p>Error loading plants. Make sure the backend is running.</p>');
    });
}

function waterPlant(plantName) {
    $.post(`http://localhost:8080/waterPlant/${plantName}`)
        .then(function(response) {
            alert(`Watered ${plantName}: ${response}`);
            loadNurseryPlants(); // Refresh the display
        })
        .fail(function(error) {
            console.error("Error watering plant:", error);
            alert("Error watering plant");
        });
}

function moveToShop(plantName) {
    $.post(`http://localhost:8080/movePlantOut/${plantName}`)
        .then(function(response) {
            alert(`Moved ${plantName} to shop: ${response}`);
            loadNurseryPlants(); // Refresh the display
        })
        .fail(function(error) {
            console.error("Error moving plant:", error);
            alert("Error moving plant to shop");
        });
}

function checkPlant(plantName) {
    alert(`Checking health of ${plantName}...`);
    // This could call a health check endpoint if implemented
}