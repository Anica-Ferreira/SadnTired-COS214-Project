const arr = [
    {
        "name" : "Plant 01",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 02",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 03",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 04",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 05",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 06",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 07",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 08",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 09",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 10",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 11",
        "status" : "Healthy",
        "nurseryStock" : 10
    },
    {
        "name" : "Plant 12",
        "status" : "Healthy",
        "nurseryStock" : 10
    }
]

window.addEventListener("load", generate);

function generate() {
    var itemList = "";
    var itemID;

    for (var i = 0; i < arr.length; i++) {
        if (i < 9) itemID = "0" + (i + 1)
        else itemID = i + 1;

        itemList = itemList + `<div class="cardItem" id="`+ itemID +`">`;
        itemList = itemList + `<img src="media/Plant` + itemID + `.png" class="plantImg"/>`;
        itemList = itemList + `<h2 class="plantName">` + arr[i].name + `</h2>`;
        itemList = itemList + `<p class="plantStatus">` + arr[i].status + `</p>`;
        itemList = itemList + `<p class="plantCount">In Stock: <span class="countLoc">` + arr[i].nurseryStock + `</span></p>`;
        itemList = itemList + `<div class="buttonGroup">`;
        itemList = itemList + `<button id="water` + itemID + `" onClick="water(` + itemID + `)">Water</button>`;
        itemList = itemList + `<button id="store` + itemID + `" onClick="addToShop(` + itemID + `)">Add to Store</button>`;
        itemList = itemList + `</div>`;
        itemList = itemList + `</div>`;
    }

    $('#cardBoxes').html(itemList);
}

function water(id) {
    console.log(id);
    //POST WaterPlant/id
}

function addToShop(id) {
    console.log(id);
    //POST MovePlantOut/id
}