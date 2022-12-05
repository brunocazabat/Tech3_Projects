const express = require("express");
const router = express.Router();
const passport = require("passport");
const AutomatedObject = require('./AutomatedObject.js');
const automation = new AutomatedObject();

router.post('/create', async (req, res) => {
    automation.create(req, res)
});

router.get('/getInfo', async (req, res) => {
    automation.getItemBP(req, res)
});

module.exports = router