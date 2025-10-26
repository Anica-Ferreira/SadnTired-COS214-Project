const arr = [
    {
        "type" : "Warning",
        "status" : "Active",
        "description" : "My neighbor's knocking and I open carefully",
        "id" : "id001"
    },
    {
        "type" : "Warning",
        "status" : "Waiting",
        "description" : "He looks a bit like ron jeremy",
        "id" : "id002"
    },
    {
        "type" : "Customer",
        "status" : "Waiting",
        "description" : "He's screaming at me ''damn you little albatraoz!''",
        "id" : "id003"
    },
    {
        "type" : "Customer",
        "status" : "Active",
        "description" : "While he smells like chips and calvadaoz",
        "id" : "id004"
    }
]

window.addEventListener("load", generate);

function generate() {
    var itemList = "";
    var itemID;

    for (var i = 0; i < arr.length; i++) {
        if (i < 9) itemID = "0" + (i + 1)
        else itemID = i + 1;

        itemList = itemList + `<li>`;
        itemList = itemList + `<h3>` + arr[i].type + ` : ` + arr[i].status + `</h3>`;
        itemList = itemList + `<p>` + arr[i].description + `</p>`;
        itemList = itemList + `<button id="` + arr[i].itemID + `">Mark Complete</button>`;
        itemList = itemList + `</li>`;
    }

    $('#notifList').html(itemList);
}