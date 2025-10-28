/*const arr = [
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
}*/

window.addEventListener("load", generateNotifs);
window.addEventListener("load", generateStaff);

async function generateNotifs() {
    const arr = await getNotifs();

    if (!arr || arr.length === 0) {
        document.getElementById("notifList").innerHTML = "<li>No notifications found</li>";
        return;
    }

    let itemList = "";
    let itemID;

    for (let i = 0; i < arr.length; i++) {
        itemID = i < 9 ? "0" + (i + 1) : (i + 1);
        itemList += `
        <li>
            <h3>${arr[i].type} : ${arr[i].status}</h3>
            <p>${arr[i].description}</p>
            <button id="${arr[i].id}" onClick="finishTask(${arr[i].id})">
            Mark Complete
            </button>
        </li>`;
    }

    $('#notifList').html(itemList);
}

async function generateStaff() {
    const staffObj = await getStaff();
    var itemList = "";

    itemList = itemList + `<h3>` + staffObj.name + `</h3>`;
    itemList = itemList + `<img id="personalIcon" src="media/tempIcon.png" />`;
    itemList = itemList + `<p id="role">` + staffObj.role + `</p>`;
    itemList = itemList + `<p id="since">` + staffObj.since + `</p>`;

    $('#profile').html(itemList);
}

async function getNotifs() {
    try{
        const response = await fetch("/notifications"); //call from the express server from now on yay
        if (!response.ok) throw new Error("Cannot GET notifications");
        const data = await response.json();
        return data;
    }catch (err) {
        console.error("Fetch error:", err);
        return [];
    }
}

async function getStaff() {
    try{
        const response = await fetch("/staff"); //call from the express server from now on yay
        if (!response.ok) throw new Error("Cannot GET staff profile");
        const data = await response.json();
        return data;
    }catch (err) {
        console.error("Fetch error:", err);
        return [];
    }
}

async function finishTask(id) {
    try{
        const response = await fetch(`/finishTask/${id}`, {
            method: "POST"
        })
        if (!response.ok) throw new Error("Cannot Complete Task");
        const data = await response.json();
        return data;
    }catch (err) {
        console.error("Fetch error:", err);
        return [];
    }
}