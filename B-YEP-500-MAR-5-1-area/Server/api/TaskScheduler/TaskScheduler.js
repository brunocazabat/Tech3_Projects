const request = require("request");
var schedule = require("node-schedule");
var axios = require("axios");

class TaskScheduler {
  constructor() {}
  schedulers = [];
  convertTZ = (date, tzString) => {
    return date.toLocaleString("fr-FR", { timeZone: tzString });
  };


  scheduler = (req, res) => {
    var date = new Date(
      req.body.date.year,
      req.body.date.month,
      req.body.date.day,
      req.body.date.hour,
      req.body.date.mins,
      req.body.date.sec
    );
    var today = new Date();
    if (date <= today) {
      res.send({
        error: "La date doit etre supérieure à celle ou nous sommes",
        success: false,
      });
    } else {
      const job = schedule.scheduleJob(
        // `00 00 ${req.body.date.hour} * * 0-6`,
        date,
        function () {
          switch (this.acAsync) {
            case "MAIL":
              var config = {
                method: "post",
                url: "http://localhost:8080/mailer/send",
                header: {
                  "Content-Type": "application/json",
                },
                data: {
                  to: this.acparamAsync,
                  subject: "[AREA] DRRIIING DRRIIING IL EST L'HEURE",
                  text: "Voici votre rappel de: " + date,
                },
              };
              axios(config)
                .then(function (response) {
                  console.log({
                    return: "Mail envoyé avec succès.",
                    success: true,
                  });
                })
                .catch(function (error) {
                  console.log({ error: error, success: false });
                });
              break;
            case "NEWS":
              var news = {
                method: "get",
                url: "http://localhost:8080/news/getrandomnews",
                header: {
                  "Content-Type": "application/json",
                },
              };
              axios(news)
                .then((response) => {
                  console.log(response.data);
                  var text = "Voici votre news du jour:\n\n"
                  text += "De: " + response.data.source.name + ". Publié le: " + response.data.publishedAt + "\n";
                  text += "Url: " + response.data.url + "\n\n";
                  text += "Titre: " + response.data.title + "\n";
                  text += response.data.content.substr(0, response.data.content.indexOf("["));
                  var mail = {
                    method: "post",
                    url: "http://localhost:8080/mailer/send",
                    header: {
                      "Content-Type": "application/json",
                    },
                    data: {
                      to: this.acparamAsync,
                      subject: "[AREA] Your daily news",
                      text: text,
                    },
                  };
                  axios(mail)
                    .then((response) => {
                      console.log({
                        return: "Mail envoyé avec succès.",
                        success: true,
                      });
                    })
                    .catch((error) => {
                      console.log({ error: error, success: false });
                    });
                })
                .catch((error) => {
                  console.log({ error: error, success: false });
                });
              break;
            case "MARKET":
              console.log("Market")
              var market = {
                method: "get",
                url: "http://localhost:8080/market/tickers/" + req.body.symbol + "/eod",
                header: {
                  "Content-Type": "application/json",
                },
              };
              axios(market)
                .then((response) => {
                  var text = "Les actions de " + response.data.name + " le " + response.data.eod[0].date + "\n";
                  text = text + "Se sont ouvertes à " + response.data.eod[0].open + "$USD\n";
                  text = text + "Et se sont fermées à " + response.data.eod[0].close + "$USD\n";
                  var mail = {
                    method: "post",
                    url: "http://localhost:8080/mailer/send",
                    header: {
                      "Content-Type": "application/json",
                    },
                    data: {
                      to: this.acparamAsync,
                      subject: "[AREA] Your daily market's news",
                      text: text,
                    },
                  };
                  axios(mail)
                    .then((response) => {
                      console.log({
                        return: "Mail envoyé avec succès.",
                        success: true,
                      });
                    })
                    .catch((error) => {
                      console.log({ error: error, success: false });
                    });
                })
                .catch((error) => {
                  console.log({ error: error, success: false });
                });
              break;
            case "METEO":
              var meteo = {
                method: "get",
                url: "http://localhost:8080/meteo/getCurrentMeteo?query=" + req.body.city,
                header: {
                  "Content-Type": "application/json",
                },
              };
              axios(meteo)
                .then((response) => {
                  console.log(response.data);
                  var mail = {
                    method: "post",
                    url: "http://localhost:8080/mailer/send",
                    header: {
                      "Content-Type": "application/json",
                    },
                    data: {
                      to: this.acparamAsync,
                      subject: `[AREA] Meteo notifications.`,
                      text: `The temperature in ${response.data.location.name} is ${response.data.current.temperature}°C.\nAnd there is ${response.data.current.weather_descriptions}`,
                    },
                  };
                  axios(mail)
                    .then((response) => {
                      console.log({
                        return: "Mail envoyé avec succès.",
                        success: true,
                      });
                    })
                    .catch((error) => {
                      console.log({ error: error, success: false });
                    });
                })
                .catch((error) => {
                  console.log({ error: error, success: false });
                });
              break;
            default:
              console.log({ success: false });
          }
          job.cancel();
        }.bind({
          acAsync: req.body.actions,
          acparamAsync: req.body.actionParameter,
        })
      );
      res.send({
        return: "L'action " + req.body.actions + " sera effectuée le " + date,
        success: true,
      });
    }
  };
}

module.exports = TaskScheduler;
