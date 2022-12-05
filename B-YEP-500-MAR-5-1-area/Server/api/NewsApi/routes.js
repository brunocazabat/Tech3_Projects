const express = require("express");
const router = express.Router();
const NewsServices = require("./NewsApi");
const newsServices = new NewsServices();

router.get('/getlastnews', async (req, res) => {
    newsServices.getLastNews(req, res);
});

router.get('/getnewsfromsubject/:keyword', async (req, res) => {
    newsServices.getNewsFromSubject(req, res);
});

router.get('/getnewsfromcategory/:category', async (req, res) => {
    newsServices.getNewsFromCategory(req, res);
});

router.get('/getrandomnews', async (req, res) => {
    newsServices.getRandomNews(req, res);
});

router.post('/sendRandomNewsToImgur', async (req, res) => {
    newsServices.sendRandomNewsToImgur(req, res);
});

router.post('/sendMailFromNewsCategory/:category', async (req, res) => {
    newsServices.sendMailFromNewsCategory(req, res);
});

router.post('/sendMailFromNewsSubject/:keyword', async (req, res) => {
    newsServices.sendMailFromNewsSubject(req, res);
});

module.exports = router