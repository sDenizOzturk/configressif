import React from "react";
import { useNavigate } from "react-router-dom";

const HomePage: React.FC = () => {
  const navigate = useNavigate();

  return (
    <div
      style={{
        display: "flex",
        flexDirection: "column",
        alignItems: "center",
        gap: "1rem"
      }}
    >
      <button onClick={() => navigate("/device")}>Device Settings</button>
      <button onClick={() => navigate("/network")}>Network Settings</button>
    </div>
  );
};

export default HomePage;
