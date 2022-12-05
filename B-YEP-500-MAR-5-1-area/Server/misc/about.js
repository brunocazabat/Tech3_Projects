const express = require("express");
const address = require("address");
const router = express.Router();

const getDate = () => {
  return Date.now();
};

router.get("/", (req, res) => {
  var client = {
    host: address.ip(),
  };
  var server = {
    current_time: getDate(),
    services: [
      {
        name: "Youtube",
        actions: [
          {
            name: "get_channel_stat",
            description: "get the statistics of a youtube channel",
          },
          {
            name: "get_search_result",
            description: "get the results of a research in youtube",
          },
        ],
        reactions: [
          {
            name: "send_mail_for_new_video",
            description:
              "Send a mail every time there is a new video uploaded.",
          },
          {
            name: "send_mail_for_x_views_in_channel",
            description:
              "Send a mail every time a step of X views is acheived.",
          },
        ],
      },
      {
        name: "Epitech",
        actions: [
          {
            name: "get_binomes",
            description: "Get all your epitech binomes",
          },
          {
            name: "get_messages",
            description: "Get your epitech message",
          },
          {
            name: "get_credits",
            description: "Get your epitech credits",
          },
        ],
        reactions: [],
      },
      {
        name: "TaskScheduler",
        actions: [
          {
            name: "event_scheduler",
            description: "Scheduler an event at a given time",
          },
        ],
        reactions: [
          {
            name: "send_mail_reminder",
            description: "Send a reminder to a given mail",
          },
          {
            name: "send_mail_random_info",
            description: "Send a random news",
          },
          {
            name: "send_mail_market_info",
            description: "Send the last market info of a symbol",
          },
          {
            name: "send_mail_meteo_info",
            description: "Send meteo info of a city",
          },
        ],
      },
      {
        name: "Meteo",
        actions: [
          {
            name: "get_current_meteo",
            description: "get the current weather from any places",
          },
        ],
        reactions: [
          {
            name: "send_mail_when_temp_is_over_query",
            description:
              "Send a mail when the temperature is over a given temperature",
          },
        ],
      },
      {
        name: "Imgur",
        actions: [
          {
            name: "upload_meteo_from_place",
            description: "Upload the current meteo of a given place on imgur",
          },
          {
            name: "upload_a_news",
            description: "Upload a news on imgur",
          },
        ],
        reactions: [],
      },
      {
        name: "Mailer",
        actions: [
          {
            name: "mail_listener",
            description: "Listen for a new mail",
          },
          {
            name: "send_mail",
            description: "Send a mail to a given mail address",
          },
        ],
        reactions: [],
      },
      {
        name: "Market",
        actions: [
          {
            name: "get_ticker_symbols",
            description: "Send market information about a symbol",
          },
        ],
        reactions: [],
      },
      {
        name: "News",
        actions: [
          {
            name: "get_last_news",
            description: "Get the last news",
          },
          {
            name: "get_news_from_subject",
            description: "Get news from a given subject",
          },
          {
            name: "get_news_from_category",
            description: "Get news from a given category",
          },
          {
            name: "get_random_news",
            description: "Get random news from a random category",
          },
        ],
        reactions: [],
      },
    ],
  };
  console.log({ client });
  res.send({ client, server });
});

module.exports = router;
