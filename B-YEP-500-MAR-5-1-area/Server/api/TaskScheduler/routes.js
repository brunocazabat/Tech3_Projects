const express = require("express");
const router = express.Router();
const passport = require("passport");
const TaskScheduler = require("./TaskScheduler.js");
const scheduler = new TaskScheduler();

router.post('/scheduler', async (req, res) => {
    scheduler.scheduler(req,res);
});


module.exports = router