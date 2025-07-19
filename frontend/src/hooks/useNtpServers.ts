import { useEffect, useState } from "react";

type Server = { label: string; value: string };

export function useNtpServers(setLoading?: (val: boolean) => void) {
  const [servers, setServers] = useState<Server[]>([]);

  useEffect(() => {
    const load = async () => {
      if (setLoading) setLoading(true);
      try {
        const res = await fetch("/configs/ntp-servers.json");
        const json: Server[] = await res.json();
        setServers(json);
      } catch (err) {
        console.error("Failed to load NTP servers:", err);
      } finally {
        if (setLoading) setLoading(false);
      }
    };

    load();
  }, [setLoading]);

  return servers;
}
