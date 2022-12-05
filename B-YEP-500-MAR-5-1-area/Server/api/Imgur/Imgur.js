const request = require("request");
const axios = require("axios");
var data = { error: "No token generated", success: false };
const client_id = "581ee108516390a";
const client_secret = "9595257a054ea63ab8fcadab057e8e75e43f6d19";

var access_token = "bf5fa01ad532c32b6750eaf9df001166bc31e4fc";

class ImgurServices {
  constructor() {}

  GenerateAccessTokenViaCode = (req, res) => {
    const code = req.query.code;
    if (code === undefined || code === null) {
      res.json({ return: "code is undefined or null.", success: false });
    } else {
      var config = {
        method: "post",
        url: "https://api.imgur.com/oauth2/token",
        header: {},
        data: {
          client_id: client_id,
          client_secret: client_secret,
          grant_type: "authorization_code",
          code: code,
        },
      };

      axios(config)
        .then(function (response) {
          data = {
            access_token: response.data.access_token,
            expires_in: response.data.expires_in,
            token_type: response.data.token_type,
            scope: response.data.scope,
            refresh_token: response.data.refresh_token,
            account_id: response.data.account_id,
            account_username: response.data.account_username,
          };
          access_token = response.data.access_token;
          console.log(data);
          res.json(data);
        })
        .catch(function (error) {
          res.json({ error: "Error with the query parameter", success: false });
        });
    }
  };

  uploadImage = (req, res) => {
    const title = req.body.title;
    const description = req.body.description;
    var image = req.body.image;

    var type = "url";
    const images = [
      "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",
    ];
    
    if (title === null || description === null) {
      res.json({ return: "Argument manquant dans body", success: false });
    }
    
    if (image === null || image == undefined) {
      type = "base64";
      image = images[0];
    }

    var options = {
      method: "POST",
      url: "https://api.imgur.com/3/image",
      headers: {
        Authorization: `Bearer ${access_token}`,
      },
      formData: {
        type: type,
        image: `${image}`,
        title: `${title}`,
        description: `${description}`,
      },
    };
    request(options, function (error) {
      if (error) {
        res.json({ return: "Image non envoyée", success: false });
      } else {
        res.json({ return: "Image bien envoyée", success: true });
      }
    });
  };

  getAccessToken = (req, res) => {
    if (access_token === null) {
      res.json({ return: "You are not authorized to imgur.", success: false });
    } else {
      res.json({ access_token: access_token, success: true });
    }
  };

  GenerateAccessTokenViaPin = (req, res) => {
    const pin = req.query.pin;

    if (pin === undefined || pin === null) {
      res.json({ return: "pin is undefined or null.", success: false });
    } else {
      var config = {
        method: "post",
        url: "https://api.imgur.com/oauth2/token",
        header: {},
        data: {
          client_id: client_id,
          client_secret: client_secret,
          grant_type: "pin",
          pin: pin,
        },
      };

      axios(config)
        .then(function (response) {
          data = {
            access_token: response.data.access_token,
            expires_in: response.data.expires_in,
            token_type: response.data.token_type,
            scope: response.data.scope,
            refresh_token: response.data.refresh_token,
            account_id: response.data.account_id,
            account_username: response.data.account_username,
          };
          access_token = response.data.access_token;
          console.log(data);
          res.json(data);
        })
        .catch(function (error) {
          res.json({ error: "Error with the query parameter", success: false });
        });
    }
  };

  getDataToken = (req, res) => {
    res.json(data);
  };
}

module.exports = ImgurServices;
