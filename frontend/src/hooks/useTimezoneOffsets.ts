import { useEffect, useState } from "react";

type Offset = { label: string; value: number };

interface LoadingController {
  startLoading: () => void;
  stopLoading: () => void;
}

export function useTimezoneOffsets(loading?: LoadingController) {
  const [offsets, setOffsets] = useState<Offset[]>([]);

  const { startLoading, stopLoading } = loading || {
    startLoading: () => {},
    stopLoading: () => {}
  };

  useEffect(() => {
    const fetchOffsets = async () => {
      startLoading();
      try {
        const res = await fetch("/configs/timezone-offsets.json");
        const data: Offset[] = await res.json();
        setOffsets(data);
      } catch (err) {
        console.error("Failed to load timezone offsets:", err);
      } finally {
        stopLoading();
      }
    };

    fetchOffsets();
  }, [startLoading, stopLoading]);

  return offsets;
}
