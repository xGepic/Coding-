import React, { Component } from "react";
import "./App.css";
import MakeApiCall from "./Components/MakeApiCall";

class App extends Component {
  render() {
    return (
      <div className="App">
        <MakeApiCall />
      </div>
    );
  }
}

export default App;
