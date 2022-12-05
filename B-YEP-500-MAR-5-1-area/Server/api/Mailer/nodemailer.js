const request = require("request");
var nodemailer = require("nodemailer");
var MailListener = require("mail-listener2");
const axios = require("axios");

var emailDate = new Date().getTime();
var mailListener = new MailListener({
  username: "gvfxstudio@gmail.com",
  password: "GmailPassword2211",
  host: "imap.gmail.com",
  port: 993, // imap port
  tls: true,
  //debug: console.log, // Or your custom function with only one incoming argument. Default: null
  tlsOptions: { rejectUnauthorized: false },
  mailbox: "INBOX", // mailbox to monitor
  searchFilter: ["UNSEEN", ["SINCE", emailDate]], // the search filter being used after an IDLE notification has been retrieved
  markSeen: true, // all fetched email willbe marked as seen and not fetched next time
  fetchUnreadOnStart: true, // use it only if you want to get all unread email on lib start. Default is `false`,
});

class NodeMailerServices {
  constructor() {}

  login = (req, res) => {};

  send = (req, res) => {
    var transporter = nodemailer.createTransport({
      service: "gmail",
      auth: {
        user: "areaautomail@gmail.com",
        pass: "area2021",
      },
    });
    var mailOptions = {
      from: "areaautomail@gmail.com",
      to: req.body.to,
      subject: req.body.subject,
      text: req.body.text,
    };

    transporter.sendMail(mailOptions, function (error, info) {
      if (error) {
        console.log(error);
        res.json({ success: false });
      } else {
        console.log("Email sent: " + info.response);
        res.json({ success: true });
      }
    });
  };

  connectListen = (req, res) => {
    mailListener.start();
    mailListener.on("server:connected", function (res) {
      console.log("imapConnected");
    });

    mailListener.on("server:disconnected", function () {
      console.log("imapDisconnected");
    });

    mailListener.on("error", function (err) {
      console.log(err);
    });

    mailListener.on("mail", (mail, seqno, attributes) => {
      var email = req.query.email;
      console.log("from: ", mail.from[0].address, mail.from[0].name);
      console.log("to: ", mail.to[0].address, mail.to[0].name);
      console.log("date: ", mail.receivedDate);
      var config = {
        method: "post",
        url: "http://localhost:8080/mailer/send",
        "Content-Type": "application/json",
        data: {
          to: email,
          subject: `[AREA] Mail redirection from Imap.`,
          text: `from ${mail.from[0].address} to ${mail.to[0].address}\n\nSubject: ${mail.subject}\nText: ${mail.text}`,
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

    mailListener.on("attachment", function (attachment) {
      console.log(attachment.path);
    });
    res.send({ return: "Connected to imap listener", success: true });
  };

  disconnectListen = (req, res) => {
    mailListener.stop();
    res.send({ return: "Disconnected to imap listener", success: true });
  };
}

module.exports = NodeMailerServices;
