var express = require("express");
var cors = require("cors");
var app = express();
app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
var Datastore = require("nedb"),
  users = new Datastore({ filename: "users.db" });
var Datastore = require("nedb"),
  highscore = new Datastore({ filename: "highscore.db" });
var currentToken = "";

function makeid() {
  var result = [];
  var characters =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  var charactersLength = characters.length;
  for (var i = 0; i < 10; i++) {
    result.push(
      characters.charAt(Math.floor(Math.random() * charactersLength))
    );
  }
  return result.join("");
}

users.loadDatabase(function (error) {
  if (error) {
    console.log(
      "FATAL: local database could not be loaded. Caused by: " + error
    );
    throw error;
  }
  console.log("INFO: local database loaded successfully.");
});

highscore.loadDatabase(function (error) {
  if (error) {
    console.log(
      "FATAL: local database could not be loaded. Caused by: " + error
    );
    throw error;
  }
  console.log("INFO: local database loaded successfully.");
});

app.post("/", function (req, res) {
  res.send("POST request to the homepage");
});

app.post("/login", function (req, res, next) {
  users.findOne(
    { email: req.body.email, password: req.body.password },
    function (err, doc) {
      if (doc == null) {
        res.status(400).json({
          message: "Wrong Input!",
        });
      } else {
        currentToken = makeid();
        res.status(200).json({
          message: "Logged In Successfully! Token is " + currentToken,
        });
      }
    }
  );
});

app.post("/signup", function (req, res, next) {
  users.findOne({ email: req.body.email }, function (err, doc) {
    if (doc == null) {
      currentToken = makeid();
      users.insert(req.body, function (error, newDoc) {
        res.status(200).json({
          message: "Successfully signed up! Token is " + currentToken,
        });
      });
    } else {
      res.status(400).json({
        message: "There is a user with this username!",
      });
    }
  });
});

app.get("/profile", function (req, res) {
  highscore.findOne({ email: req.query.email }, function (err, doc) {
    if (doc == null) {
      res.status(404).json({
        message: "There are no entries!",
      });
    } else {
      res.status(200).json(doc);
    }
  });
});

app.get("/highscore", function (req, res) {
  highscore.find({}, function (err, doc) {
    if (doc == null) {
      res.status(404).json({
        message: "There are no entries!",
      });
    } else {
      res.status(200).json(doc);
    }
  });
});
/*
app.post('/highscore', function (req, res) {
  highscore.insert(req.body, function (error, newDoc) {   
      res.status(200).json({
          message: 'Successfully posted!'
      }); 
  });
});
*/
app.post("/highscore", function (req, res) {
  highscore.update(
    { email: req.body.email },
    { $max: { highscore: req.body.highscore } },
    { upsert: true },
    function (error, newDoc) {
      res.status(200).json({
        message: "Successfully posted!",
      });
    }
  );
});

app.post("/logout", function (req, res) {
  currentToken = "";
  res.status(200).json({
    message: "Successfully logged out!",
  });
});

app.get("");

module.exports = app;
