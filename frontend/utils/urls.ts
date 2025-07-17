/// <reference types="vite/client" />
const API_PORT =
  import.meta.env.DEV || window.location.port === "5173" ? ":4131" : "";

export const API_BASE_HOST =
  window.location.protocol + "//" + window.location.hostname + API_PORT;

export const API_NETWORK_URL = `${API_BASE_HOST}/network`;
