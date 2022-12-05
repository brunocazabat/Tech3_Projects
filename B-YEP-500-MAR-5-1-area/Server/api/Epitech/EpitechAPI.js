const request = require("request");
const axios = require("axios");
// const msal = require("@azure/msal-node");

// const config = {
//   auth: {
//     clientId: "a0e404c3-acf7-4987-8e99-77e24237b211",
//     authority: "https://login.microsoftonline.com/common",
//     clientSecret: "VcX931-o7k-e_rOt.hAECDF7jDCuNOPbZb",
//   },
//   system: {
//     loggerOptions: {
//       loggerCallback(loglevel, message, containsPii) {
//         console.log(message);
//       },
//       piiLoggingEnabled: false,
//       logLevel: msal.LogLevel.Verbose,
//     },
//   },
// };

// Create msal application object
// const pca = new msal.ConfidentialClientApplication(config);

class EpitechServices {
  constructor() {}

  autolog = null;

  login = (req, res) => {
    this.autolog = req.params.autolog;
    res.send({ autolog: this.autolog, success: true });
  };

  getBinomes = (req, res) => {
    const login = req.params.login;
    if (this.autolog === null) {
      res.send({ return: "Please login first.", success: false });
    } else {
      request(
        `https://intra.epitech.eu/${this.autolog}/user/${login}/binome?format=json`,
        function (error, response, body) {
          console.error("error:", error);
          console.log("statusCode:", response && response.statusCode);
          var parsedBody = JSON.parse(body);
          res.send({ parsedBody, success: true });
        }
      );
    }
  };

  sendMessageMail = (req, res) => {
    if (this.autolog === null) {
      res.send({ return: "Please login first.", success: false });
    } else {
      request(
        `https://intra.epitech.eu/${this.autolog}/user/notification/message?format=json`,
        function (error, response, body) {
          var parsedBody = JSON.parse(body);
          var title = `Vous have ${parsedBody.length} recent messages on the Epitech's intra.\n`;
          var content = `You have ${parsedBody.length} messages:\n`;
          parsedBody.forEach((element) => {
            content += `From: ${element.user.title} at ${element.date}\n`;
            content += `\tTitle: ${element.title.replace(/<.*>/, "")}\n`;
            content += `\tContent: ${element.content.replace(/<.*>/, "")}\n\n`;
          });
          console.log(this.acparamAsync);
          var config = {
            method: "post",
            url: "http://localhost:8080/mailer/send",
            header: {
              "Content-Type": "application/json",
            },
            data: {
              to: this.acparamAsync,
              subject: "[AREA] " + title,
              text: content,
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
          res.send({ parsedBody, success: true });
        }.bind({ acparamAsync: req.body.actionParameter })
      );
    }
  };

  message = (req, res) => {
    if (this.autolog === null) {
      res.send({ return: "Please login first.", success: false });
    } else {
      request(
        `https://intra.epitech.eu/${this.autolog}/user/notification/message?format=json`,
        function (error, response, body) {
          var parsedBody = JSON.parse(body);
          res.send({ parsedBody, success: true });
          // parsedBody.binomes.forEach(element => {
          //   console.log(element.login, element.weight);
          // });
        }
      );
    }
  };

  notifications = (req, res) => {
    if (this.autolog === null) {
      res.send({ return: "Please login first.", success: false });
    } else {
      request(
        `https://intra.epitech.eu/${this.autolog}/user/notification/absences?format=json`,
        function (error, response, body) {
          console.error("error:", error);
          console.log("statusCode:", response && response.statusCode);
          var parsedBody = JSON.parse(body);
          console.log(parsedBody);
          // parsedBody.binomes.forEach(element => {
          //   console.log(element.login, element.weight);
          // });
        }
      );
      res.send({ success: true });
    }
  };

  account = (req, res) => {
    if (this.autolog === null) {
      res.send({ return: "Please login first.", success: false });
    } else {
      request(
        `https://intra.epitech.eu/${this.autolog}/user/?format=json`,
        function (error, response, body) {
          var parsedBody = JSON.parse(body);
          res.send({ parsedBody, success: true });
        }
      );
    }
  };

  apointments = (req, res) => {};

  // login = (req, res) => {
  //   const authCodeUrlParameters = {
  //     scopes: ["user.read"],
  //     redirectUri: "http://localhost:8080/epitech/redirect",
  //   };

  //   // get url to sign user in and consent to scopes needed for application
  //   pca
  //     .getAuthCodeUrl(authCodeUrlParameters)
  //     .then((response) => {
  //       res.redirect(response);
  //     })
  //     .catch((error) => console.log(JSON.stringify(error)));
  // };

  // redirect = (req, res) => {
  //   const tokenRequest = {
  //     code: req.query.code,
  //     scopes: ["user.read"],
  //     redirectUri: "http://localhost:8080/epitech/redirect",
  //   };
  //   pca
  //     .acquireTokenByCode(tokenRequest)
  //     .then((response) => {
  //       console.log("\nResponse: \n:", response);
  //       res.sendStatus(200);
  //     })
  //     .catch((error) => {
  //       console.log(error);
  //       res.status(500).send(error);
  //     });
  // };

  // getMeetingsInformations = (req, res) => {};
}

module.exports = EpitechServices;
