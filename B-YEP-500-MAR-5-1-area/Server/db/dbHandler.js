
const mongoose = require("mongoose");
const EpitechAPI = require("../api/Epitech/EpitechAPI");
const {User} = require('./schema/User');

const URI = 'mongodb+srv://test:test@cluster0.sq7rq.mongodb.net/area?retryWrites=true&w=majority'

getHash = function (password) {
    return bcrypt.hashSync(password, bcrypt.genSaltSync(12));
};

class dbHandler {

    constructor() { }

    connectDB = async () => {
        await mongoose.connect(URI, { useNewUrlParser: true, useUnifiedTopology: true, },);
        console.log('db connected..!');
    }

    createUser = async (req) => {
        console.log(req.body.email)
        const {firstname, name, email, password} = req.body;
        let user = {};
        user.firstname = firstname;
        user.name = name;
        user.email = email;
        user.password = password;
        user.date = Date.now();
        let userModel = new User(user);
        await userModel.save(function(error) {
            if (error)
                return console.log(error)
        });
    }

    registerUser = (req, res, callback) => {
        User.find({email: req.body.email}, function(err, user) {
            if (err) {
                console.log(err);
                res.send({return: "Error while creating user.", success: false});
            } else if (user.length > 0){
                console.log("User already exist.");
                console.log({success: false});
                res.send({return: "User already exist.", success: false});
            } else {
                console.log("User not found.")
                console.log({success: true});
                callback(req);
                res.send({return: "User successfully created.", success: true});
            }
        })
    }

    deleteUser = async (req, res) => {
        var paramEmail = req.body.email
        res.setHeader('Content-Type', 'application/json');
        User.deleteOne({email: paramEmail}, function(err, user) {
            if (err) {
                console.log(err)
                res.send({return: "Error while deleting user.", success: false});
            }
            if (!user) {
                res.send({return: "User not deleted.", success: false});
            } else
                res.send({return: "User successfully deleted.", success: true});
        })
    }

    loginUser = async (req, res) => {
        if (typeof(req.body.email) == "undefined" || typeof(req.body.password) == "undefined") {
            res.send({return: "Undefined email or password in body.", success : false});
            return;
        }

        var paramEmail = req.body.email
        var password = req.body.password
        res.setHeader('Content-Type', 'application/json');

        User.findOne({email: paramEmail}, function(err, user) {
            if (err) {
                console.log(err)
                res.json({return: "Error while finding user.", success: false})
            }
            if (!user)
                res.json({return: "User not found, please created an account.", success: false})
            else
                if (!password.localeCompare(user.password))
                    res.json({return: "User connected!", success: true})
        })
    }

    getUser = async (req, res) => {
        var paramEmail = req.query.search
        // if (typeof(req.query.search == "undefined")) {
        //     res.send({return: "Undefined email.", success : false}); return;
        // }
        User.findOne({email: paramEmail}, function(err, user) {
            if (err) {
                console.log(err)
                res.send({return: "Error while finding user.", success: false}); return;
            } else if (!user) {
                res.send({return: "No user found.", success: false}); return;
            } else {
                const value = {
                    firstname: user.firstname,
                    name: user.name,
                    email: user.email,
                    date_of_creation: user.date,
                    success: true
                }
                res.send(value); return;
            }
        })
    }

    updateUser = async (req, res) => {
        var paramEmail = req.query.search;

        if (req.body.firstname === null || req.body.firstname === undefined) {
            res.send({success: false}); return;
        }
        if (req.body.name === null || req.body.name === undefined) {
            res.send({success: false}); return;
        }
        if (req.body.email === null || req.body.email === undefined) {
            res.send({success: false}); return;
        }

        User.findOne({email: paramEmail}, function (err, doc) {
            doc.firstname = req.body.firstname;
            doc.name = req.body.name;
            doc.email = req.body.email;
            doc.save();
        });
        res.send({success: true});
    }

    updateYoutubeToken = async (req, res) => {
        var paramEmail = req.query.search;
        // if (req.body.token === null || req.body.token === undefined) {
        //     res.send({success: false}); return;
        // }
        var access_token = req.body.access_token;
        var refresh_token = req.body.refresh_token;
        var scope = req.body.scope;
        var token_type = req.body.token_type;
        var expiry_date = req.body.expiry_date;
        User.findOne({email: paramEmail}, function (err, doc) {
            doc.youtubeSchema.access_token = access_token;
            doc.youtubeSchema.refresh_token = refresh_token;
            doc.youtubeSchema.scope = scope;
            doc.youtubeSchema.token_type = token_type;
            doc.youtubeSchema.expiry_date = expiry_date;
            doc.save();
        });
        res.send({body: req.body, success: true});
    }

    getYoutubeCredentials = (req, res) => {
        if (req.query.search === null || req.query.search === null)
          res.json({return: "search is not there", success: false})
        const paramEmail = req.query.search;

        User.findOne({email: paramEmail}, function (err, user) {
            if (err) {
                console.log(err)
                res.send({return: "Error while finding user.", success: false}); return;
            } else if (!user) {
                res.send({return: "No user found.", success: false}); return;
            } else {
                const value = {
                    youtubeCredentials: user.youtubeSchema,
                    success: true
                }
                res.send(value); return;
            }
        });
        
      }
}

module.exports = dbHandler
