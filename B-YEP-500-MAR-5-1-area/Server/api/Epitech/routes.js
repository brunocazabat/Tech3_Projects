const express = require("express");
const router = express.Router();
const EpitechServices = require('./EpitechAPI.js');
const epitech = new EpitechServices();
const request = require("request")

// router.get('/login', async (req, res) => {
//     epitech.login(req, res);
// });

// router.get('/redirect', async (req, res) => {
//     epitech.redirect(req, res);
// });

// router.get('/test', async (req, res) => {
//     request("https://login.microsoftonline.com/common/oauth2/authorize?response_type=code&client_id=e05d4149-1624-4627-a5ba-7472a39e43ab&redirect_uri=https%3A%2F%2Fintra.epitech.eu%2Fauth%2Foffice365&state=%2F%3Fformat%3Djson",
//     //request("https://intra.epitech.eu/?format=json#",
//     function (error, response, body) {
//         // console.error('error:', error); // Print the error if one occurred
//         res.json({response}); // Print the response status code if a response was received
//         // console.log('body:', body); // Print the HTML for the Google homepage.
//       });
// })

router.get('/binomes/:login', async (req, res) => {
    epitech.getBinomes(req, res);
});

router.get('/login/:autolog', async (req, res) => {
    epitech.login(req, res);
});

router.get('/notifications', async (req, res) => {
    // epitech.login(req, res);
});

router.get('/message', async (req, res) => {
    epitech.message(req, res);
});

router.get('/account', async (req, res) => {
    epitech.account(req, res);
});

router.post('/sendMessageMail', async (req, res) => {
    epitech.sendMessageMail(req, res);
});

router.get('/apointments', async (req, res) => {
    // epitech.login(req, res);
});

module.exports = router