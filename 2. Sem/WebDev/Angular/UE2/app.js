var express = require("express");
var cors = require("cors");
var app = express();

var Datastore = require('nedb');
const database = new Datastore("database.db");
database.loadDatabase();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.post("/login", (req, res, next) => {
  const loginData = req.body;

  res.status(200).json({ message: "Hello Login from express.js" });
});

var rand = function(){
  return Math.random().toString(36).substring(2);
}
var token = function(){
  return rand() + rand();
}

app.post("/signup", (req, res, next) => {

  const signupEmail = req.body.email;
  const signupPassword = req.body.passwordOne;
  const signupToken = token();


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

module.exports = app;
