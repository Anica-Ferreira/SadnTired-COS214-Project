/*const arr = [
    {
        "name" : "Plant 01",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 02",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 03",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 04",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 05",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 06",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 07",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 08",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 09",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 10",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 11",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    },
    {
        "name" : "Plant 12",
        "description" : "Yeah This A Plant",
        "shopStock" : 10
    }
]*/

window.addEventListener("load", generate);

async function generate() {
    const arr = await getShop();
    var itemList = "";
    var itemID;

    for (var i = 0; i < arr.length; i++) {
        if (i < 9) itemID = "0" + (i + 1)
        else itemID = i + 1;

        itemList = itemList + `<div class="cardItem" id="`+ itemID +`">`;
        itemList = itemList + `<img src="media/Plant` + itemID + `.png" class="plantImg"/>`;
        itemList = itemList + `<h2 class="plantName">` + arr[i].name + `</h2>`;
        itemList = itemList + `<p class="plantDesc">` + arr[i].description + `</p>`;
        itemList = itemList + `<p class="plantCount">In Stock: <span class="countLoc">` + arr[i].shopStock + `</span></p>`;
        itemList = itemList + `<button id="button` + itemID + `" onClick="addToCart(` + itemID + `)">Add To Cart</button>`
        itemList = itemList + `</div>`;
    }

    $('#cardBoxes').html(itemList);
}

async function getShop() {
    try{
        const response = await fetch("/shop"); //call from the express server from now on yay
        if (!response.ok) throw new Error("Cannot GET notifications");
        const data = await response.json();
        return data;
    }catch (err) {
        console.error("Fetch error:", err);
        return [];
    }
}

async function addToCart(id) {
    console.log(id);
    //POST AddToCart/id
}