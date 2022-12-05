const express = require("express");
const router = express.Router();
const MarketApi = require("./MarketApi");
const market = new MarketApi();

router.get('/tickers/:symbols/eod', async (req, res) => {
    market.getTickersEod(req, res);
});


module.exports = router