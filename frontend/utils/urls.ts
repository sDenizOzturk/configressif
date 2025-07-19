/// <reference types="vite/client" />

export const API_BASE_HOST =
  window.location.protocol +
  "//" +
  window.location.hostname +
  (import.meta.env.DEV || window.location.port === "5173" ? ":4131" : "/api");

export const API_NETWORK_URL = `${API_BASE_HOST}/network`;

export const API_NTP_URL = `${API_BASE_HOST}/ntp`;
