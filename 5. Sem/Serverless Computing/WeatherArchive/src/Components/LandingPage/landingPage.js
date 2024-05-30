import React, { useState, useEffect } from "react";
import { Link, useNavigate } from "react-router-dom";
import axios from "axios";
import "./style.css";

const LandingPage = () => {
  const [searchTerm, setSearchTerm] = useState("");
  const [dates, setDates] = useState([]);
  const navigate = useNavigate();

  const toImageComponent = () => {
    if (searchTerm.trim().length === 0) {
      alert("Please enter a Search Term!");
      return;
    }
    if (searchTerm.includes("-")) {
      const loc = prompt("Please Enter a Location ");
      if (loc.trim().length === 0) {
        return;
      }
      navigate("/image", { state: { dat: searchTerm, loc: loc } });
    } else {
      const dat = prompt("Please Enter a Date (Format: 2023-01-02)");
      if (dat.trim().length === 0) {
        return;
      }
      navigate("/image", { state: { dat: dat, loc: searchTerm } });
    }
  };

  function removeDuplicates(arr) {
    return arr.filter((item, index) => arr.indexOf(item) === index);
  }
  useEffect(() => {
    async function fetchData() {
      try {
        const response = await axios.get(
          "https://937sshyksk.execute-api.us-east-1.amazonaws.com/Deploy/getdates"
        );
        let resp = response.data.body.split(",");
        const newDates = resp
          .toString()
          .replace(/"/g, "")
          .replace("[", "")
          .replace("]", "");
        setDates(removeDuplicates(newDates.split(",")));
      } catch (error) {
        console.log(error);
      }
    }
    fetchData();
  });

  function RenderDates() {
    return (
      <div>
        <h2>Available Dates:</h2>
        <ul id="dateDiv">
          {dates.map((string, index) => (
            <li key={index}>{string}</li>
          ))}
        </ul>
      </div>
    );
  }

  function RenderPage() {
    return (
      <div>
        <div id="titeldiv">
          <h1 id="titel">Weather Archive</h1>
          <h4>Type in a Date or Location</h4>
        </div>
        <div id="wrapper">
          <div id="searchBarDiv">
            <input
              type="text"
              id="search-bar"
              placeholder="Search the Archive"
              value={searchTerm}
              onChange={(e) => setSearchTerm(e.target.value)}
            />
            <div id="buttonDiv">
              <button id="searchButton" onClick={toImageComponent}>
                Search
              </button>
            </div>
          </div>
          <div>{RenderDates()}</div>
          <div>
            <Link to="/video">
              <button id="videoPageButton">Video</button>
            </Link>
          </div>
        </div>
      </div>
    );
  }
  return RenderPage();
};

export default LandingPage;
