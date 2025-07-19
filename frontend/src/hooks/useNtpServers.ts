import { useEffect, useState } from "react";

export interface Server {
  label: string;
  value: string;
}

interface LoadingController {
  startLoading: () => void;
  stopLoading: () => void;
}

export function useNtpServers(loading?: LoadingController) {
  const [servers, setServers] = useState<Server[]>([]);

  const { startLoading, stopLoading } = loading || {
    startLoading: () => {},
    stopLoading: () => {}
  };

  useEffect(() => {
    const load = async () => {
      startLoading();
      try {
        const res = await fetch("/configs/ntp-servers.json");
        const json: Server[] = await res.json();
        setServers(json);
      } catch (err) {
        console.error("Failed to load NTP servers:", err);
      } finally {
        stopLoading();
      }
    };

    load();
  }, [startLoading, stopLoading]);

  return servers;
}
