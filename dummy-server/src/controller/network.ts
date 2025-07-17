import { Request, Response } from "express";

import type { WifiConfigForm } from "../models/wifi-config";

let storedNetworkConfig: WifiConfigForm = {
  wifiEnabled: false,
  ssid: "",
  password: "",
  dhcpEnabled: true,
  ip: "",
  gateway: "",
  subnet: "",
};

export const getNetworkConfig = (_req: Request, res: Response) => {
  res.json(storedNetworkConfig || {});
};

export const setNetworkConfig = (req: Request, res: Response) => {
  storedNetworkConfig = req.body;
  res.json({ success: true });
};
