import React, { Component } from "react";
import axios from "axios";
import "bootstrap/dist/css/bootstrap.min.css";
import Table from "react-bootstrap/Table";

class MakeApiCall extends Component {
  constructor(props) {
    super(props);
    this.state = { posts: [], loading: false };
  }
  componentDidMount() {
    const config = {
      headers: { "Access-Control-Allow-Origin": "*" },
    };
    const url = "http://localhost:8080/weatherforecast";
    axios
      .get(url, config)
      .then((response) => {
        this.setState({ posts: response.data, loading: true });
      })
      .catch((error) => {
        console.log(error);
      });
  }
  static renderTable(myData) {
    return (
      <>
        <h1>Continuous Integration - API Data</h1>
        <br></br>
        <Table striped bordered hover>
          <thead>
            <tr>
              <th>Date</th>
              <th>Temperature in C</th>
              <th>Temperature in F</th>
              <th>Summary</th>
            </tr>
          </thead>
          <tbody>
            {myData.map((forecasts) => (
              <tr key={forecasts.date}>
                <td>{forecasts.date}</td>
                <td>{forecasts.temperatureC}°C</td>
                <td>{forecasts.temperatureF}°F</td>
                <td>{forecasts.summary}</td>
              </tr>
            ))}
          </tbody>
        </Table>
      </>
    );
  }
  render() {
    return this.state.loading ? (
      MakeApiCall.renderTable(this.state.posts)
    ) : (
      <p>Loading...</p>
    );
  }
}

export default MakeApiCall;
