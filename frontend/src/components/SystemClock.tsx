import { useEffect, useState } from "react";

type Props = {
  initialTime?: number;
};

export const SystemClock = ({ initialTime }: Props) => {
  useEffect(() => {
    if (initialTime == undefined) return;

    const interval = setInterval(() => {
      setNow((prev) => (prev !== null ? prev + 1 : null));
    }, 1000);

    return () => clearInterval(interval);
  }, [initialTime]);

  const [now, setNow] = useState<number | null>(initialTime!);
  if (!now) return;

  return (
    <div
      style={{
        display: "flex",
        flexDirection: "column",
        textAlign: "center",
        fontSize: "0.8rem"
      }}
    >
      <span style={{ fontWeight: "bold" }}>Current Device Time</span>
      <span>
        {new Date(now * 1000).toLocaleString(undefined, {
          hour12: false,
          timeZone: "UTC"
        })}
      </span>
    </div>
  );
};
