const express = require("express");
const router = express.Router();
const NodeMailerServices = require("./nodemailer.js");
const mailer = new NodeMailerServices();

router.get('/login', async (req, res) => {
    
});

router.post('/send', async (req, res) => {
    mailer.send(req, res);
});

router.get('/connectListen', async (req, res) => {
    mailer.connectListen(req, res);
});

router.get('/disconnectListen', async (req, res) => {
    mailer.disconnectListen(req, res);
});


module.exports = router