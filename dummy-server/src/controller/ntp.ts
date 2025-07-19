import { Request, Response } from "express";
import { NtpConfigForm } from "../models/ntp-config";

let storedNtpConfig: NtpConfigForm = {
  enabled: false,
  server: "pool.ntp.org",
  timezoneOffset: 0,
};

export const getNtpConfig = (_req: Request, res: Response) => {
  res.json({
    ...storedNtpConfig,
    currentTime: getSimulatedCurrentTime(),
  });
};

export const setNtpConfig = (req: Request, res: Response) => {
  storedNtpConfig = req.body;
  console.log("[dummy-server] Received NTP config:", storedNtpConfig);

  res.json({
    status: "ok",
    currentTime: getSimulatedCurrentTime(),
  });
};

export const getSimulatedCurrentTime = (): number | null => {
  if (!storedNtpConfig.enabled) return null;

  const localNow = new Date();
  const timezoneOffsetMs = localNow.getTimezoneOffset() * 60 * 1000;
  const utcNow = Date.now() + timezoneOffsetMs;
  const offsetMs = storedNtpConfig.timezoneOffset * 60 * 60 * 1000;

  return utcNow + offsetMs;
};
