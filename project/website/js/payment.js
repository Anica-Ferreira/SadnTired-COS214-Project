const arr = [
    {
        "name" : "Plant 01",
        "count" : 1
    },
    {
        "name" : "Plant 02",
        "count" : 2
    },
    {
        "name" : "Plant 03",
        "count" : 3
    },
    {
        "name" : "Plant 04",
        "count" : 4
    },
    {
        "name" : "Plant 05",
        "count" : 5
    }
]

const bundle = {
    "name" : "Existensial Crisis",
    "count" : 2000000
}

window.addEventListener("load", generate);

async function generate() {
    var itemList = "";
    var itemID;

    for (var i = 0; i < arr.length; i++) {
        if (i < 9) itemID = "0" + (i + 1)
        else itemID = i + 1;

        itemList = itemList + `<li>`;
        itemList = itemList + `<img src="media/Plant` + itemID + `.png" class="plantImg"/>`;
        itemList = itemList + `<div class="details">`;
        itemList = itemList + `<h2>` + arr[i].name + `</h2>`;
        itemList = itemList + `<p>Count: <span>` + arr[i].count + `</span></p>`;
        itemList = itemList + `</div>`;
        itemList = itemList + `</li>`;
    }

    $('#shopList').html(itemList);
}

function addBundle() {
    var itemList = $('#shopList').html();

    itemList = itemList + `<li>`;
    itemList = itemList + `<img src="media/TempBundle.png" class="plantImg"/>`;
    itemList = itemList + `<div class="details">`;
    itemList = itemList + `<h2>` + bundle.name + `</h2>`;
    itemList = itemList + `<p>Count: <span>` + bundle.count + `</span></p>`;
    itemList = itemList + `</div>`;
    itemList = itemList + `</li>`;

    $('#shopList').html(itemList);
}