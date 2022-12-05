var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var MongoClient = require("mongodb").MongoClient


var Service = new Schema({
    name: {
        type: String,
        unique: true
    },
});

function insertService(req, data) {
    MongoClient.connect('mongodb://db:27017', function(err, db) {
        if (err)
            throw err;
        var dbo = db.db('dashboard');
        var query = {name: data.name};
        dbo.collection('services').find(query).toArray(function(err, result) {
            if (err)
                throw err;
            if (result.length === 0) {
                dbo.collection("services").insertOne(data, function (err, res) {
                    if (err)
                        throw err
                });
            }
        });
    });
}

module.exports = mongoose.model('Service', Service);
module.exports.insertService = insertService;