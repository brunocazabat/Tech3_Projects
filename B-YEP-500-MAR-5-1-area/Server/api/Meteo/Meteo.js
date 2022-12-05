const axios = require("axios");
const access_key = "6e0d2db6b3dabfece1f9aa4e5e49683d";

class MeteoServices {
  constructor() {}

  getCurrentMeteo = (req, res) => {
    const query = req.query.query;
    const url = `http://api.weatherstack.com/current?access_key=${access_key}&query=${query}`;
    var config = {
      method: "get",
      url: url,
      header: {},
    };

    axios(config)
      .then(function (response) {
        res.json(response.data);
      })
      .catch(function (error) {
        res.json({ error: "Error with the query parameter", success: false });
      });
  };

  sendCurrentMeteoMail = async (req, res) => {
    const query = req.body.query;
    const actions = req.body.actions;
    const actionParameter = req.body.actionParameter;
    const url = `http://api.weatherstack.com/current?access_key=${access_key}&query=${query}`;
    var config = {
      method: "get",
      url: url,
      header: {},
    };

    axios(config)
      .then(
        function (response) {
          const w = response.data;
          var weather = `Here is the weather in ${w.request.query}:\n`;
          weather += `\tLocation:\n`;
          weather += `\t\t${w.request.type}: ${w.location.name}\n`;
          weather += `\t\tRegion: ${w.location.region}\n`;
          weather += `\t\tCountry: ${w.location.country}\n`;
          weather += `\tCurrent weather (${w.current.observation_time}):\n`;
          weather += `\t\tOverall: ${w.current.weather_descriptions[0]}\n`;
          weather += `\t\tTemperature: ${w.current.temperature} °C (feelslike ${w.current.feelslike} °C)\n`;
          weather += `\t\tWind Speed: ${w.current.wind_speed} km/h\n`;
          weather += `\t\tHumidity: ${w.current.humidity} %\n`;
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
                  subject: `[AREA] Here is the weather of ${response.data.request.query}.`,
                  text: weather,
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
            default:
              console.log({ success: false });
          }
          res.json({ return: "Meteo sent", success: true });
        }.bind({
          acAsync: actions,
          acparamAsync: actionParameter,
          queryAsync: query,
        })
      )
      .catch(function (error) {
        console.log(error);
        res.json({ error: "Error with the query parameter", success: false });
      });
  };

  sendMeteoToImgur = (req, res) => {
    const query = req.body.query;
    const url = `http://api.weatherstack.com/current?access_key=${access_key}&query=${query}`;
    var config = {
      method: "get",
      url: url,
      header: {},
    };

    axios(config)
      .then(function (response) {
        var data = response.data;
        console.log(data);
        var config = {
          method: "post",
          url: "http://localhost:8080/imgur/uploadImage",
          header: {
            "Content-Type": "application/json",
          },
          data: {
            image: data.current.weather_icons[0],
            title: `The Temperature in ${data.request.query} is ${data.current.temperature}°C at ${data.current.observation_time}`,
            description: `The Temperature in ${data.request.query} is ${data.current.temperature}°C at ${data.current.observation_time}.\nThe weather is ${data.current.weather_descriptions[0]} and the humidity is at ${data.current.humidity}%`,
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
          res.json({success: true });
      })
      .catch(function (error) {
        res.json({ error: "Error with the query parameter", success: false });
      });
  };
}

module.exports = MeteoServices;
