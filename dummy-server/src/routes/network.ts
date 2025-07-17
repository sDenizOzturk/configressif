import { Router } from "express";
import { getNetworkConfig, setNetworkConfig } from "../controller/network";

const router = Router();

router.get("/", getNetworkConfig);
router.post("/", setNetworkConfig);

export default router;
