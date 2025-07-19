import { useEffect, useState } from "react";

type Offset = { label: string; value: number };

export function useTimezoneOffsets(setLoading?: (val: boolean) => void) {
  const [offsets, setOffsets] = useState<Offset[]>([]);

  useEffect(() => {
    const fetchOffsets = async () => {
      if (setLoading) setLoading(true);
      try {
        const res = await fetch("/configs/timezone-offsets.json");
        const data: Offset[] = await res.json();
        setOffsets(data);
      } catch (err) {
        console.error("Failed to load timezone offsets:", err);
      } finally {
        if (setLoading) setLoading(false);
      }
    };

    fetchOffsets();
  }, [setLoading]);

  return offsets;
}
