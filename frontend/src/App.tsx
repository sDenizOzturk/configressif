import "./App.css";

function App() {
  return (
    <>
      <div
        style={{
          display: "flex",
          flexDirection: "column",
          alignItems: "center",
          gap: "1rem",
          marginTop: "4rem",
        }}
      >
        <button onClick={() => alert("Device Settings Clicked")}>
          Device Settings
        </button>
        <button onClick={() => alert("Network Settings Clicked")}>
          Network Settings
        </button>
      </div>
    </>
  );
}

export default App;
