import { Routes, Route } from "react-router-dom";
import HomePage from "./pages/HomePage";
import NetworkSettingsPage from "./pages/NetworkSettingsPage";

function App() {
  return (
    <Routes>
      <Route path="/" element={<HomePage />} />
      <Route path="/network" element={<NetworkSettingsPage />} />
    </Routes>
  );
}
export default App;
