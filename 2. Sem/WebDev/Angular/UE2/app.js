var express = require("express");
var cors = require("cors");
var app = express();
app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.post("/login", (req, res, next) => {
  const loginData = JSON.stringify(req.body);
  console.log(loginData);

  res.status(200).json({ message: "Hello Login from express.js" });
});

module.exports = app;
