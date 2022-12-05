const request = require("request");
const axios = require("axios");
var schedule = require("node-schedule");

class AutomatedObject {
  constructor() {}

  scheduled = null;

  programmed = "*/5 * * * * *";
  action = null;
  target = null;
  running = true;
  query = null;
  bp = [];

  meteo = {
    type: "meteo",
    location: null,
    observation_time: null,
    temperature: null,
    feelslike: null,
    weather_descriptions: null,
  };

  credits = 0;
  notifLength = 0;

  nbSubs = 0;
  nbVideo = 0;
  nbView = 0;

  nbBinome = 0;

  create = (req, res) => {
    if (
      req.body.action == null ||
      req.body.update == null ||
      req.body.target == null
    ) {
      res.send({ success: false });
      return;
    }

    var update = req.body.update;

    this.action = req.body.action;
    this.target = req.body.target;
    this.query = req.body.query;

    if (update.includes("h")) {
      this.programmed = `*/${update.substr(0, update.length - 1)} * * *`;
      console.log("Programmed for every " + this.programmed + " hour(s)");
      res.send({ success: true });
    } else if (update.includes("min")) {
      this.programmed = `*/${update.substr(0, update.length - 3)} * * * *`;
      console.log("Programmed for every " + this.programmed + " minute(s)");
      res.send({ success: true });
    } else if (update.includes("s")) {
      this.programmed = `*/${update.substr(0, update.length - 1)} * * * * *`;
      console.log("Programmed for every " + this.programmed + " second(s)");
      res.send({ success: true });
    } else {
      res.send({ success: false });
      return;
    }

    this.run();
  };

  stop = (req, res) => {
    this.schedule.cancel();
  };

  backpack = (req, res) => {
    // this.bp = [this.meteo];
    // res.send(this.bp);
  };

  getItemBP = (req, res) => {
    if (this.bp.length === 0) {
      res.send({ item: null });
      return;
    }
    res.send({ item: this.bp[0] });
    this.bp.shift();
  };

  getMeteoTemp = (query, temp, recipient) => {
    request(
      "http://localhost:8080/meteo/getCurrentMeteo?query=" + query,
      (err, res, body) => {
        var parsedBody = JSON.parse(body);
        if (
          this.meteo.temperature !== parsedBody.current.temperature &&
          parsedBody.current.temperature > temp
        ) {
          //action
          var config = {
            method: "post",
            url: "http://localhost:8080/mailer/send",
            header: {
              "Content-Type": "application/json",
            },
            data: {
              to: recipient,
              subject: `[AREA] Meteo notifications.`,
              text: `The meteo in ${query} is above ${temp}°C.`,
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
        } else {
          console.log("dans else");
        }
        this.meteo = {
          type: "meteo",
          location: parsedBody.location.name,
          observation_time: parsedBody.current.observation_time,
          temperature: parsedBody.current.temperature,
          feelslike: parsedBody.current.feelslike,
          weather_descriptions: parsedBody.current.weather_descriptions[0],
        };
        this.bp.push(this.meteo);
        console.log(this.meteo);
      }
    );
  };

  getEpitechCredits = (recipient) => {
    request("http://localhost:8080/epitech/account", (err, res, body) => {
      var parsedBody = JSON.parse(body);
      var current_credits = parsedBody.parsedBody.credits;
      if (this.credits !== current_credits) {
        var config = {
          method: "post",
          url: "http://localhost:8080/mailer/send",
          header: {
            "Content-Type": "application/json",
          },
          data: {
            to: recipient,
            subject: `[AREA] Epitech credits modification.`,
            text: `Your actual credits are ${current_credits} and were ${this.credits}.`,
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
        this.credits = current_credits;
        this.bp.push(this.credits);
        console.log("credits:", this.credits);
      }
    });
  };

  getEpitechNotification = (recipient) => {
    request("http://localhost:8080/epitech/message", (err, res, body) => {
      var parsedBody = JSON.parse(body);
      if (this.notifLength < parsedBody.length) {
        this.notifLength = parsedBody.length;
        var config = {
          method: "post",
          url: "http://localhost:8080/mailer/send",
          header: {
            "Content-Type": "application/json",
          },
          data: {
            to: recipient,
            subject: `[AREA] Epitech New Notification.`,
            text: parsedBody[0].title,
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
      }
    });
  };

  getNewBinome = (recipient, login) => {
    request("http://localhost:8080/epitech/binomes/" + login, (err, res, body) => {
      var parsedBody = JSON.parse(body);
      console.log(parsedBody);
      if (parsedBody.success === false) {
        return;
      }
      var length = parsedBody.parsedBody.binomes.length;
      if (this.nbBinome < length) {
        this.nbBinome = length
        var config = {
          method: "post",
          url: "http://localhost:8080/mailer/send",
          header: {
            "Content-Type": "application/json",
          },
          data: {
            to: recipient,
            subject: `[AREA] Epitech New pair.`,
            text: "You are in pair with " + parsedBody.parsedBody.binomes[length -1].login,
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
      }
    });
  };

  getYoutubeSubs = (channel, recipient) => {
    request(
      "http://localhost:8080/youtube/getChannelStat?q=" + channel,
      (err, res, body) => {
        var parsedBody = JSON.parse(body);
        if (this.nbSubs !== parsedBody.statistics.subscriberCount) {
          var config = {
            method: "post",
            url: "http://localhost:8080/mailer/send",
            header: {
              "Content-Type": "application/json",
            },
            data: {
              to: recipient,
              subject: `[AREA] Youtube notifications.`,
              text: `The channel ${channel} has ${parsedBody.statistics.subscriberCount} subscribers.`,
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
          this.nbSubs = parsedBody.statistics.subscriberCount;
          this.bp.push(this.nbSubs);
        } else {
          console.log(this.nbSubs);
        }
      }
    );
  };

  getYoutubeVideos = (channel, recipient) => {
    request(
      "http://localhost:8080/youtube/getChannelStat?q=" + channel,
      (err, res, body) => {
        var parsedBody = JSON.parse(body);
        if (this.nbVideo !== parsedBody.statistics.videoCount) {
          var config = {
            method: "post",
            url: "http://localhost:8080/mailer/send",
            header: {
              "Content-Type": "application/json",
            },
            data: {
              to: recipient,
              subject: `[AREA] Youtube notifications.`,
              text: `The channel ${channel} has a new video.`,
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
          this.nbVideo = parsedBody.statistics.videoCount;
          this.bp.push(this.nbVideo);
        } else {
          console.log(this.nbVideo);
        }
      }
    );
  };

  getLastNew = (recipient) => {
    request("http://localhost:8080/news/getlastnews", (err, res, body) => {
      var parsedBody = JSON.parse(body);
      var text = "De: " + parsedBody.articles[0].source.name + ". Publié le: " + parsedBody.articles[0].publishedAt + "\n";
      text += "Url: " + parsedBody.articles[0].url + "\n\n";
      text += "Titre: " + parsedBody.articles[0].title + "\n";
      var config = {
        method: "post",
        url: "http://localhost:8080/mailer/send",
        header: {
          "Content-Type": "application/json",
        },
        data: {
          to: recipient,
          subject: `[AREA] Your Daily News.`,
          text: text,
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
    });
  };

  getYoutubeViews = (channel, xViews, recipient) => {
    request(
      "http://localhost:8080/youtube/getChannelStat?q=" + channel,
      (err, res, body) => {
        var parsedBody = JSON.parse(body);
        if (
          this.nbView !== Math.floor(parsedBody.statistics.viewCount / xViews)
        ) {
          var config = {
            method: "post",
            url: "http://localhost:8080/mailer/send",
            header: {
              "Content-Type": "application/json",
            },
            data: {
              to: recipient,
              subject: `[AREA] Youtube notifications.`,
              text: `The channel ${channel} has ${parsedBody.statistics.viewCount} views.`,
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
          this.nbView = Math.floor(parsedBody.statistics.viewCount / xViews);
          this.bp.push(this.nbView);
        } else {
          console.log(this.nbView);
        }
      }
    );
  };

  run = () => {
    this.scheduled = schedule.scheduleJob(
      this.programmed,
      function () {
        switch (this.acAsync) {
          case "MAIL_METEO": //si temparature > this.queryAsync
            this.gMeteo(
              this.queryAsync[0],
              this.queryAsync[1],
              this.targetAsync
            );
            break;
          case "MAIL_VIDEO_YOUTUBE": //si une video youtube est ajouté sur le compte
            this.gYtVideos(this.queryAsync[0], this.targetAsync);
            break;
          case "MAIL_LAST_NEW": //si une video youtube est ajouté sur le compte
            this.gNews(this.targetAsync);
            break;
          case "MAIL_NEW_NOTIFICATION": //si une video youtube est ajouté sur le compte
            this.gEpiNotif();
            break;
          case "MAIL_NEW_VIEWS": //si une video youtube est ajouté sur le compte
            this.gYtViews(
              this.queryAsync[0],
              this.queryAsync[1],
              this.targetAsync
            );
            break;
          case "MAIL_GPA_CHANGE": //si une video youtube est ajouté sur le compte
            this.gEpiCredits(this.targetAsync);
            break;
          case "MAIL_NEW_BINOME":
            this.gNewBinome(this.targetAsync,this.queryAsync[0])
            break;
          case "MAIL_SUB_CHANGE": //si une video youtube est ajouté sur le compte
            this.gYtSubs(this.queryAsync[0], this.targetAsync);
            break;
          default:
            console.log("Nothing");
            console.log({ return: "Nothing", success: false });
            break;
        }
      }.bind({
        acAsync: this.action,
        targetAsync: this.target,
        queryAsync: this.query,
        gMeteo: this.getMeteoTemp,
        gEpiCredits: this.getEpitechCredits,
        gYtSubs: this.getYoutubeSubs,
        gEpiNotif: this.getEpitechNotification,
        gYtVideos: this.getYoutubeVideos,
        gYtViews: this.getYoutubeViews,
        gNews: this.getLastNew,
        gNewBinome: this.getNewBinome
      })
    );
  };
}

module.exports = AutomatedObject;
