const { default: axios } = require("axios");
const request = require("axios");

class MarketApi {
  constructor() {}
  ApiKey = "8035b0122d992316947b922ac1209a9b";

  login = (req, res) => {};

  getTickersEod = (req, res) => {
    const symbols = req.params.symbols;
    var config = {
      method: "get",
      url: `http://api.marketstack.com/v1/tickers/${symbols}/eod?access_key=${this.ApiKey}`,
    };
    axios(config)
      .then((response) => {
        console.log("Success");
        const data = response.data.data;
        const name = data.name;
        const symbol = data.symbol;
        const stock_exchange = data.stock_exchange;
        const eod = [];
        data.eod.forEach((element) => {
          eod.push({
            open: element.open,
            high: element.high,
            low: element.low,
            close: element.close,
            volume: element.volume,
            exchange: element.exchange,
            date: element.date,
          });
        });
        res.send({ name, symbol, stock_exchange, eod });
      })
      .catch((error) => {
        console.log("Error");
        res.send(error);
      });
  };
}

module.exports = MarketApi;
