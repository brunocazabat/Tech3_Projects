const request = require("request");
const NewsAPI = require("newsapi");
const { default: axios } = require("axios");
const newsapi = new NewsAPI("d1c3f30f84854e1fb7c1c03f5101778f");

class NewsServices {
  listCategory = [
    "business",
    "entertainment",
    "general",
    "health",
    "science",
    "sports",
    "technology",
  ];

  constructor() {}

  getRandomInt = (max) => {
    return Math.floor(Math.random() * Math.floor(max));
  };

  getLastNews = (req, res) => {
    newsapi.v2
      .topHeadlines({
        language: "fr",
      })
      .then((response) => {
        if (response.status === "ok") {
          res.send(response);
        } else {
          res.send({ success: false });
        }
      });
  };

  getNewsFromSubject = (req, res) => {
    newsapi.v2
      .everything({
        q: req.params.keyword,
        language: "fr",
      })
      .then((response) => {
        if (response.status === "ok") {
          res.send(response);
        } else {
          res.send({ success: false });
        }
      });
  };

  sendMailFromNewsSubject = (req, res) => {
    var recipient = req.body.email;

    newsapi.v2
     .everything({
        q: req.params.keyword,
        language: "fr",
      })
      .then((response) => {
        if (response.status === "ok") {
          var text = "De: " + response.articles[0].source.name + ". Publié le: " + response.articles[0].publishedAt + "\n";
          text += "Url: " + response.articles[0].url + "\n\n";
          text += "Titre: " + response.articles[0].title + "\n";
          text += "Contenu: " + response.articles[0].content + "\n";
          var config = {
            method: "post",
            url: "http://localhost:8080/mailer/send",
            header: {
              "Content-Type": "application/json",
            },
            data: {
              to: recipient,
              subject: `[AREA] Your Daily News by Subject.`,
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
            res.send({ success: true });
        } else {
          res.send({ success: false });
        }
      });
  };

  getNewsFromCategory = (req, res) => {
    newsapi.v2
      .topHeadlines({
        category: req.params.category,
        language: "fr",
      })
      .then((response) => {
        if (response.status === "ok") {
          res.send(response.articles[0]);
        } else {
          res.send({ success: false });
        }
      });
  };

  sendMailFromNewsCategory = (req, res) => {
    var recipient = req.body.email;

    newsapi.v2
      .topHeadlines({
        category: req.params.category,
        language: "fr",
      })
      .then((response) => {
        if (response.status === "ok") {
          var text = "De: " + response.articles[0].source.name + ". Publié le: " + response.articles[0].publishedAt + "\n";
          text += "Url: " + response.articles[0].url + "\n\n";
          text += "Titre: " + response.articles[0].title + "\n";
          text += "Contenu: " + response.articles[0].content + "\n";
          var config = {
            method: "post",
            url: "http://localhost:8080/mailer/send",
            header: {
              "Content-Type": "application/json",
            },
            data: {
              to: recipient,
              subject: `[AREA] Your Daily News by Category.`,
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
            res.send({ success: true });
        } else {
          res.send({ success: false });
        }
      });
  };

  getRandomNews = (req, res) => {
    var categ = this.getRandomInt(7);
    newsapi.v2
      .topHeadlines({
        category: this.listCategory[categ],
        language: "fr",
      })
      .then((response) => {
        if (response.status === "ok") {
          res.send(
            response.articles[this.getRandomInt(response.articles.length)]
          );
        } else {
          res.send({ success: false });
        }
      });
  };

  sendRandomNewsToImgur = (req, res) => {
    var categ = this.getRandomInt(7);
    newsapi.v2
      .topHeadlines({
        category: this.listCategory[categ],
        language: "fr",
      })
      .then((response) => {
        if (response.status === "ok") {
          var img =
            "https://sv-verneuil.footeo.com/uploads/sv-verneuil/news/breaking-news-generic-1.jpg";
          if (response.articles.urlToImage !== null)
            var article =
              response.articles[this.getRandomInt(response.articles.length)];
          img = article.urlToImage;
          console.log(img);
          var config = {
            method: "post",
            url: "http://localhost:8080/imgur/uploadImage",
            header: {
              "Content-Type": "application/json",
            },
            data: {
              image: img,
              title: article.title,
              description: article.content,
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
          res.send({ success: true });
        } else {
          res.send({ success: false });
        }
      });
  };
}

module.exports = NewsServices;
