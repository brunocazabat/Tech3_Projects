const request = require("request");
const axios = require("axios");
var { google } = require("googleapis");
const YouTubeNotifier = require("youtube-notification");

var OAuth2 = google.auth.OAuth2;
var SCOPES = ["https://www.googleapis.com/auth/youtube.readonly"];
var TOKEN_PATH = "./youtube-credential.json";

class youtubeAPI {
  notifier = new YouTubeNotifier({
    hubCallback: "https://localhost",
    port: 8000,
    path: "/youtube",
  });

  constructor() {
    this.notifier.setup();
    this.notifier.on("notified", (data) => {
      console.log("New Video");
      console.log(
        `${data.channel.name} just uploaded a new video titled: ${data.video.title}`
      );
    });
  }

  // https://accounts.google.com/o/oauth2/v2/auth?access_type=offline&scope=https%3A%2F%2Fwww.googleapis.com%2Fauth%2Fyoutube.force-ssl&response_type=code&client_id=524667447554-g52kl8ts59u6o367c5nm73httevmbrn8.apps.googleusercontent.com&redirect_uri=http%3A%2F%2Flocalhost%3A8080%2Fgoogle%2Fcallback
  authorize = (req, res) => {
    const code = req.query.code;
    const search = req.query.search;

    request(
      "http://localhost:8080/db/getYoutubeCredentials?search=" + search,
      function (error, response, body) {
        var parsedBody = JSON.parse(body);
        var access_token = parsedBody.youtubeCredentials.access_token;
        if (access_token.length > 0) {
          res.json({
            return:
              "Already authorize. try: GET http://localhost:8080/db/getYoutubeCredentials?search=" +
              search,
            success: false,
          });
        } else {
          var clientSecret = "fRdllhgXfys6pXYepCBrIOWn";
          var clientId =
            "524667447554-g52kl8ts59u6o367c5nm73httevmbrn8.apps.googleusercontent.com";
          var redirectUrl = "http://localhost:8080/google/callback";
          var oauth2Client = new OAuth2(clientId, clientSecret, redirectUrl);

          oauth2Client.getToken(code, function (err, token) {
            if (err) {
              console.log("Error while trying to retrieve access token", err);
              return;
            }
            oauth2Client.credentials = token;
            var config = {
              method: "put",
              url:
                "http://localhost:8080/db/updateYoutubeUser?search=" + search,
              header: {},
              data: {
                access_token: token.access_token,
                refresh_token: token.refresh_token,
                scope: token.scope,
                token_type: token.token_type,
                expiry_date: token.expiry_date,
              },
            };

            axios(config).then(function (response) {
              console.log(token);
              res.json(response);
              return;
            });
          });
        }
      }
    );
  };

  getChannelStat = (req, res) => {
    var q = req.query.q;
    if (q === undefined || q === null) {
      res.json({ return: "search is undefined or null.", success: false });
    } else {
      request(
        `https://youtube.googleapis.com/youtube/v3/channels?part=statistics&forUsername=${q}&key=AIzaSyBbJSI0WcYlEnB8PM2xT1oh88CrNUpjsvY`,
        (error, response, body) => {
          if (!error && response.statusCode == 200) {
            var parsedBody = JSON.parse(body);
            var statistics = parsedBody.items[0].statistics;
            res.json({ statistics, success: true });
          } else {
            res.json({ success: false });
          }
        }
      );
    }
  };

  //getSearchList return des
  getSearchList = (req, res) => {
    var q = req.query.q;
    if (q === undefined || q === null) {
      res.json({ return: "search is undefined or null.", success: false });
    } else {
      request(
        "https://www.googleapis.com/youtube/v3/search?part=snippet&q=" +
          q +
          "&key=AIzaSyBbJSI0WcYlEnB8PM2xT1oh88CrNUpjsvY",
        (error, response, body) => {
          if (!error && response.statusCode == 200) {
            var parsedBody = JSON.parse(body);
            res.json({ parsedBody, success: true });
          } else {
            res.json({ success: false });
          }
        }
      );
    }
  };

  subscribe = (req, res) => {
    this.notifier.subscribe(req.body.channel);
  };

  unsubscribe = (req, res) => {
    this.notifier.unsubscribe(req.body.channel);
  };

  sendThumbnailToImgur = (req, res) => {
    var q = req.body.query;
    if (q === undefined || q === null) {
      res.json({ return: "search is undefined or null.", success: false });
    } else {
      request(
        "https://www.googleapis.com/youtube/v3/search?part=snippet&q=" +
          q +
          "&key=AIzaSyBbJSI0WcYlEnB8PM2xT1oh88CrNUpjsvY",
        (error, response, body) => {
          if (!error && response.statusCode == 200) {
            var parsedBody = JSON.parse(body);
            var config = {
              method: "post",
              url: "http://localhost:8080/imgur/uploadImage",
              header: {
                "Content-Type": "application/json",
              },
              data: {
                image: parsedBody.items[0].snippet.thumbnails.high.url,
                title: parsedBody.items[0].snippet.title,
                description: `${parsedBody.items[0].snippet.description} (www.youtube.com/watch?v=${parsedBody.items[0].id.videoId})`,
              },
            };
            axios(config)
              .then(function (response) {
                console.log({
                  return: "Image upload sur imgur.",
                  success: true,
                });
              })
              .catch(function (error) {
                console.log({ error: error, success: false });
              });
            res.json({ success: true });
            // res.json({ parsedBody, success: true });
          } else {
            res.json({ success: false });
          }
        }
      );
    }
  };
}

module.exports = youtubeAPI;
