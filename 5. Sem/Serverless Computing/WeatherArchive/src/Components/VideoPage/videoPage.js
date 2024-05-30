import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import "./videoStyles.css";

const VideoPage = () => {
  const [videoSearchTerm, setVideoSearchTerm] = useState("");
  const navigate = useNavigate();

  const goBackButton = () => {
    navigate("/");
  };

  const toVideoResultsComponent = () => {
    if (videoSearchTerm.trim().length === 0) {
      alert("Please enter a Search Term!");
      return;
    }
    navigate("/videoResults", { state: videoSearchTerm });
  };

  function RenderPage() {
    return (
      <div>
        <div id="videoTitleDiv">
          <h1 id="videoTitle">Video Page</h1>
        </div>
        <div id="wrapper">
          <div id="searchBarDiv">
            <input
              type="text"
              id="search-bar"
              placeholder="Search Video"
              value={videoSearchTerm}
              onChange={(e) => setVideoSearchTerm(e.target.value)}
            />
            <div id="buttonDiv">
              <button id="searchButton" onClick={toVideoResultsComponent}>
                Search
              </button>
            </div>
          </div>
          <div>
            <button id="GoBackButton" onClick={goBackButton}>
              Go Back
            </button>
          </div>
        </div>
      </div>
    );
  }
  return RenderPage();
};

export default VideoPage;
