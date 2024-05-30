import React, { useState, useEffect } from "react";
import { useLocation, useNavigate } from "react-router-dom";
import axios from "axios";
import "./imageStyle.css";

const ImagePage = () => {
  const [imgMetaData, setImgMetaData] = useState("");
  const [imageUrl, setImageUrl] = useState("");
  const [myError, setMyError] = useState();
  const location = useLocation();
  const navigate = useNavigate();

  const titel =
    location.state.loc.charAt(0).toUpperCase() +
    location.state.loc.substring(1);

  const startDate = location.state.dat + "%2000:00:00";
  const endDate = location.state.dat + " %2023:59:00";

  const goBackButton = () => {
    navigate("/");
  };

  useEffect(() => {
    const config = {
      headers: {},
    };
    async function fetchData() {
      try {
        const response = await axios.get(
          "https://937sshyksk.execute-api.us-east-1.amazonaws.com/Deploy/getimage?begin=" +
            startDate +
            "&end=" +
            endDate +
            "&loc=" +
            location.state.loc +
            "&Key=kHM0GgXPkb89BYpAkAwu69TX3wyhnQlK8EPww5Bp",
          config
        );
        Object.keys(response.data).length === 0
          ? setMyError(true)
          : setMyError(false);
        setImgMetaData(Object.keys(response.data));
        setImageUrl(
          `data:image/jpeg;base64,${response.data[Object.keys(response.data)]}`
        );
      } catch (error) {
        console.log(error);
      }
    }
    fetchData();
  });

  function HandleImage() {
    return myError ? (
      <h2>Invalid Lambda Call </h2>
    ) : (
      <div id="imgDiv">
        <img src={imageUrl} alt="Lambda Img" />
        <h3>
          Metadata:<br></br>
          {imgMetaData}
        </h3>
      </div>
    );
  }

  function RenderPage() {
    return (
      <div id="wrapper">
        <div id="titeldiv2">
          <h1 id="seachInput">{titel}</h1>
        </div>
        <div>
          <button id="GoBackButton" onClick={goBackButton}>
            Go Back
          </button>
        </div>
        {HandleImage()}
      </div>
    );
  }
  return RenderPage();
};

export default ImagePage;
