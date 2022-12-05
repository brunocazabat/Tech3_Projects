const express = require("express");
const router = express.Router();
const MeteoServices = require("./Meteo.js")
const meteo = new MeteoServices();

router.get('/getCurrentMeteo', async (req, res) => {
    await meteo.getCurrentMeteo(req, res);
});

router.post('/sendCurrentMeteoMail', async (req, res) => {
    await meteo.sendCurrentMeteoMail(req, res);
});

router.post('/sendMeteoToImgur', async (req, res) => {
    await meteo.sendMeteoToImgur(req, res);
});
module.exports = router