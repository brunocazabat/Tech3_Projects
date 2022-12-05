const youtubeAPI = require("./youtubeAPI.js");
const ytb = new youtubeAPI();
const express = require("express");
const router = express.Router();

router.post('/authorize', async (req, res) => {
    await ytb.authorize(req, res);
});

router.get('/getSearchList', async (req, res) => {
    await ytb.getSearchList(req, res);
});

router.get('/getChannelStat', async (req, res) => {
    await ytb.getChannelStat(req, res);
});

router.post('/sendThumbnailToImgur', async (req, res) => {
    await ytb.sendThumbnailToImgur(req, res);
});

module.exports = router