const express = require("express");
const path = require("path");
const app = express();
const PORT = 3000;

const CROW_API = "http://localhost:8080";

app.use(express.json());

app.use(express.static(path.join(__dirname, "website"))); 

/* general function for get routes */
async function proxyGet(res, endpoint) {
    try{
        const response = await fetch(`${CROW_API}${endpoint}`);
        const data = await response.json();
        res.json(data);
    }catch (err) {
        console.error(`Error fetching ${endpoint}:`, err);
        res.status(500).json({ error: `Failed to fetch ${endpoint}` });
    }
}

/* General function for post routes */
async function proxyPost(res, endpoint, body = {}) {
    try{
        const response = await fetch(`${CROW_API}${endpoint}`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(body)
        });

        const text = await response.text();
        let data;
        try{
            data = JSON.parse(text);
        } catch {
            data = { message: text };
        }

        res.status(response.status).json(data);
    }catch (err) {
        console.error(`Error posting to ${endpoint}:`, err);
        res.status(500).json({ error: `Failed to post to ${endpoint}` });
    }
}

app.get("/shop", (req, res) => proxyGet(res, "/shop"));
app.get("/randomShop", (req, res) => proxyGet(res, "/randomShop"));
app.get("/nursery", (req, res) => proxyGet(res, "/nursery"));
app.get("/staff", (req, res) => proxyGet(res, "/staff"));
app.get("/notifications", (req, res) => proxyGet(res, "/notifications"));
app.get("/bundle", (req, res) => proxyGet(res, "/bundle"));

app.post("/waterPlant/:id", (req, res) => {
    proxyPost(res, `/waterPlant/${req.params.id}`, req.body);
});

app.post("/movePlantOut/:id", (req, res) => {
    proxyPost(res, `/movePlantOut/${req.params.id}`, req.body);
});

app.post("/finishTask/:id", (req, res) => {
    proxyPost(res, `/finishTask/${req.params.id}`, req.body);
});

app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});