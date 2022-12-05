var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var logger = require('morgan');
var mongoose = require('mongoose');
var indexRouter = require('./routes/index');
var passport = require('passport');
var LocalStrategy    = require('passport-local').Strategy;
var app = express();

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'twig');
app.use(logger('dev'));
app.use(express.static(path.join(__dirname, 'public')));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(cookieParser());
app.use(require('express-session')({
    secret: 'keyboard cat',
    resave: false,
    saveUninitialized: false
}));

app.use(passport.initialize());
app.use(passport.session());


app.use('/', indexRouter);
app.use(function(req, res, next) {
  next(createError(404));
});
app.use(function(err, req, res, next) {
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};
  res.status(err.status || 500);
  res.render('error');
});

mongoose.connect("mongodb://db:27017/dashboard", function(err) {
    if (err) {
        console.log('MongoDB connection error: ' + err);
        process.exit(1);
    }
});

var Account = require('./routes/models/account');
passport.use(new LocalStrategy(Account.authenticate()));
passport.serializeUser(Account.serializeUser());
passport.deserializeUser(Account.deserializeUser());


const port = 8080;
app.listen(port, () => {
    console.log("You are live on " + port)
});

module.exports = app;