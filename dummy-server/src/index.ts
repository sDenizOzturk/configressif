import express from "express";
import cors from "cors";
import networkRoutes from "./routes/network";

const app = express();
const port = 4131;

app.use(cors());
app.use(express.json());
app.use("/network", networkRoutes);

app.listen(port, () => {
  console.log(`[dummy-server] running at http://localhost:${port}`);
});
