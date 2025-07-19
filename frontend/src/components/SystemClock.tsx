import { useEffect, useState } from "react";

type Props = {
  initialTime: number | null;
};

export function SystemClock({ initialTime }: Props) {
  const [now, setNow] = useState<number | null>(initialTime);

  useEffect(() => {
    if (initialTime === null) return;

    const interval = setInterval(() => {
      setNow((prev) => (prev !== null ? prev + 1000 : null));
    }, 1000);

    return () => clearInterval(interval);
  }, [initialTime]);

  if (now === null) return null;

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
        {new Date(now).toLocaleString(undefined, {
          hour12: false
        })}
      </span>
    </div>
  );
}
