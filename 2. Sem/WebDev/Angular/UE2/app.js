var express = require("express");
var cors = require("cors");
var crypto = require("crypto");
var app = express();

var mongoose = require('mongoose');
mongoose.connect("mongodb+srv://TestUser:<password>@cluster0.8rleo.mongodb.net/myFirstDatabase?retryWrites=true&w=majority");

var Datastore = require('nedb');
const database = new Datastore("database.db");
database.loadDatabase();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.post("/login", (req, res, next) => {
  
  const loginData = req.body;
  res.status(200).json({ message: "Hello Login from express.js" });


  const loginDataModel = new LoginData({
    userName: req.body.email,
    password: req.body.password
});

loginDataModel.save();

});

app.post("/signup/", (req, res, next) => {

  const signupEmail = req.body.email;
  const signupPassword = req.body.passwordOne;
  const signupToken = crypto.randomBytes(20).toString('hex');

  database.find({signupEmail: signupEmail}, function (err, docs){

    if(docs == ""){

      database.insert({signupEmail, signupPassword, signupToken});
      res.status(200).json({ message: "[SUCCESS] Signup Successful!" });
    }
    else{
      
      res.status(400).json();
    }
  })
});

app.get("/loginData", (req, res, next) => {

  LoginData.find({}, function(err, logins) {

        res.json(logins);
  });
});

module.exports = app;
