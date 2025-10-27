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

const staffObj = {
    "name" : "Curt Curious",
    "role" : "Emotional Support",
    "since" : 2024
}

window.addEventListener("load", generateNotifs);
window.addEventListener("load", generateStaff);

function generateNotifs() {
    var itemList = "";
    var itemID;
    //const arr = getNotifs();

    for (var i = 0; i < arr.length; i++) {
        if (i < 9) itemID = "0" + (i + 1)
        else itemID = i + 1;

        itemList = itemList + `<li>`;
        itemList = itemList + `<h3>` + arr[i].type + ` : ` + arr[i].status + `</h3>`;
        itemList = itemList + `<p>` + arr[i].description + `</p>`;
        itemList = itemList + `<button id="` + arr[i].id + `" onClick="finishTask(` + itemID + `)">Mark Complete</button>`;
        itemList = itemList + `</li>`;
    }

    $('#notifList').html(itemList);
}

function generateStaff() {
    var itemList = "";
    var itemID;

    itemList = itemList + `<h3>` + staffObj.name + `</h3>`;
    itemList = itemList + `<img id="personalIcon" src="media/tempIcon.png" />`;
    itemList = itemList + `<p id="role">` + staffObj.role + `</p>`;
    itemList = itemList + `<p id="since">` + staffObj.since + `</p>`;

    $('#profile').html(itemList);
}

async function getNotifs() {
    try {
        var request = new XMLHttpRequest();
        request.open("GET", 'http://localhost:8080/notifications', true);
        request.send();
        console.log(request.response);

        /*const response = await fetch('http://localhost:8080/notifications');
        if (!response.ok) throw new Error('Cannot GET notifications');
        const data = await response.json();
        return data;*/
    } catch (err) {
        console.error('Fetch error: ', err);
    }
}

function getStaff() {
    //GET Staff
}

function finishTask(id) {
    //POST FinishTask/id
}