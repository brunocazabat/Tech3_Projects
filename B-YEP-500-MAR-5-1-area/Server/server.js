const express = require("express");
const app = express();
const port = process.env.port || 8080;
const connectDB = require("./db/dbHandler.js");
const bodyParser = require("body-parser");
const passport = require("passport");
const cookieSession = require("cookie-session");
const axios = require("axios");
require("./passport-setup");

const db = new connectDB();

db.connectDB();

app.use(function (req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header(
    "Access-Control-Allow-Headers",
    "Origin, X-Requested-With, Content-Type, Accept"
  );
  res.header("Access-Control-Allow-Methods", "PUT, GET, POST, DELETE, OPTIONS");
  next();
});

app.get("/", function (req, res) {
  res.send("Server online!");
});

app.get("/redirect", function (req, res) {
  res.send("Redirected!");
});

app.use("/about.json", require("./misc/about"));

app.use(bodyParser.json());

app.use(
  cookieSession({
    name: "area-session",
    keys: ["key1, key2"],
  })
);

var email = "";

const isLoggedIn = (req, res, next) => {
  email = req.user;
  if (req.user) {
    next();
  } else {
    res.sendStatus(401);
  }
};

app.use(passport.initialize());
app.use(passport.session());

app.use("/db", require("./db/routes"));
app.use("/youtube", require("./api/youtube/routes"));
app.use("/imgur", require("./api/Imgur/routes"));
app.use("/meteo", require("./api/Meteo/routes"));
app.use("/epitech", require("./api/Epitech/routes"));
app.use("/mailer", require("./api/Mailer/routes"));
app.use("/scheduler", require("./api/TaskScheduler/routes"));
app.use("/automate", require("./api/automation/routes"));
app.use("/market", require("./api/Market/routes"));
app.use("/news", require("./api/NewsApi/routes"));

app.get("/google/callback", (req, res) => res.send("callback here:"));

app.get("/isLogged", (req, res) => {
  if (email === "") {
    res.send({ success: false });
  } else {
    const mail = email.emails[0].value;
    const name = email._json.given_name;
    var config = {
      method: "get",
      url: "http://localhost:8080/db/getUser?search=" + mail,
      headers: {},
    };
    axios(config)
      .then((response) => {
        if (response.data.success) {
          res.send(response.data);
        } else {
          var acc_data = JSON.stringify({
            firstname: name,
            name: "",
            email: mail,
            password: "google",
          });

          var acc_config = {
            method: "post",
            url: "http://localhost:8080/db/createUser",
            headers: {
              "Content-Type": "application/json",
            },
            data: acc_data,
          };

          axios(acc_config)
            .then(function (response) {
              if (response.data.success) {
                res.send({firstname: name, name: "", email: mail, success: true});
              } else {
                res.send({ success: false });
              }
            })
            .catch(function (error) {
              console.log(error);
            });
        }
      })
      .catch((error) => {
        console.log(error);
      });
  }
});

app.get("/failed", (req, res) => res.send("You Failed to Log in!"));
app.get("/good", isLoggedIn, (req, res) => res.send(`Welcome Mr nidule`));
app.get(
  "/google",
  passport.authenticate("google", { scope: ["profile", "email"] })
);
app.get(
  "/google/auth/callback",
  passport.authenticate("google", { failureRedirect: "/failed" }),
  function (req, res) {
    res.redirect("/good");
  }
);
app.get("/logout", (req, res) => {
  req.session = null;
  req.logout();
  res.redirect("/");
});

app.listen(port, function () {
  console.log("Example app listening on port 8080!");
});
