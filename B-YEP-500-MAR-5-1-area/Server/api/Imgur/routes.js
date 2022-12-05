const express = require("express");
const router = express.Router();
const ImgurServices = require("./Imgur.js");
const imgur = new ImgurServices();

router.get('/getDataToken', async (req, res) => {
    await imgur.getDataToken(req, res);
});

router.post('/access_token_via_code', async (req, res) => {
    await imgur.GenerateAccessTokenViaCode(req, res);
});

router.post('/access_token_via_pin', async (req, res) => {
    await imgur.GenerateAccessTokenViaPin(req, res);
});

router.post('/uploadImage', async (req, res) => {
    await imgur.uploadImage(req, res);
});

router.get('/getAccessToken', async (req, res) => {
    await imgur.getAccessToken(req, res);
});


module.exports = router