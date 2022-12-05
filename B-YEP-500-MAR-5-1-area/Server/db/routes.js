const dbHandler = require('./dbHandler.js')
const db = new dbHandler()
const express = require("express");
const router = express.Router();

router.post('/createUser', async (req, res) => {
    await db.registerUser(req, res, db.createUser);
});

router.delete('/deleteUser', async (req, res) => {
    await db.deleteUser(req, res);
});

router.post('/loginUser', async (req, res) => {
    await db.loginUser(req, res);
});

router.get('/getUser', async (req, res) => {
    await db.getUser(req, res);
});

router.put('/updateYoutubeUser', async (req, res) => {
    await db.updateYoutubeToken(req, res);
})

router.get('/getYoutubeCredentials', async (req, res) => {
    await db.getYoutubeCredentials(req, res);
})

module.exports = router