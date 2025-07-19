import { Router } from "express";
import { getNtpConfig, setNtpConfig } from "../controller/ntp";

const router = Router();

router.get("/", getNtpConfig);
router.post("/", setNtpConfig);

export default router;
