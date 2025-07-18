import { Routes, Route } from "react-router-dom";
import HomePage from "./pages/HomePage";
import NetworkSettingsPage from "./pages/NetworkSettingsPage";
import { RebootPage } from "./pages/RebootPage";

function App() {
  return (
    <Routes>
      <Route path="/" element={<HomePage />} />
      <Route path="/network" element={<NetworkSettingsPage />} />
      <Route path="/reboot" element={<RebootPage />} />
    </Routes>
  );
}
export default App;
