const mongoose = require("mongoose");

var epitechSchema = mongoose.Schema({
    login: String,
    password: String
})

var googleSchema = mongoose.Schema({
    access_token: String,
})

var youtubeSchema = mongoose.Schema({
    access_token: String,
    refresh_token: String,
    scope: String,
    token_type: String,
    expiry_date: Number
})

var microsoftSchema = mongoose.Schema({
    login: String,
    password: String
})

var UsersSchema = mongoose.Schema({
    firstname: String,
    name: String,
    email: String,
    password: String,
    date: {
        type: Date
    },
    epitechLogin: {
        type: epitechSchema,
        default: {login: null, password: null}
    },
    googleOAuth2: {
        type: googleSchema,
        default: {access_token: null}
    },
    youtubeSchema: {
        type: youtubeSchema,
        default: {
            access_token: null,
            refresh_token: null,
            scope: null,
            token_type: null,
            expiry_date: null
        }
    }
});

Epitech = mongoose.model('epitech', epitechSchema);
Google = mongoose.model('google', googleSchema);
Youtube = mongoose.model('youtube', youtubeSchema);
User = mongoose.model('user', UsersSchema);

module.exports = {
    User,
    Google,
    Epitech
}