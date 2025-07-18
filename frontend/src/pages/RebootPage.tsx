import { useEffect, useMemo, useState } from "react";
import { useLocation, useNavigate } from "react-router-dom";

interface RebootOptions {
  countdown: number;
  redirectAfter: number;
}

export const RebootPage = () => {
  useEffect(() => {
    window.history.replaceState(null, document.title);
  }, []);

  const navigate = useNavigate();
  const location = useLocation();

  const rebootOptions = useMemo(() => {
    const state = location.state as RebootOptions | null;
    if (
      !state ||
      typeof state.countdown !== "number" ||
      typeof state.redirectAfter !== "number"
    ) {
      return null;
    }
    return state;
  }, [location.state]);

  useEffect(() => {
    if (!rebootOptions) {
      navigate("/", { replace: true });
    }
  }, [rebootOptions, navigate]);

  const [phase, setPhase] = useState<"countdown" | "rebooting">("countdown");
  const [secondsLeft, setSecondsLeft] = useState(
    () => rebootOptions?.countdown ?? 0
  );

  useEffect(() => {
    if (!rebootOptions) return;

    const interval = setInterval(() => {
      setSecondsLeft((prev) => {
        if (prev <= 1) {
          clearInterval(interval);
          setPhase("rebooting");
          return rebootOptions.redirectAfter;
        }
        return prev - 1;
      });
    }, 1000);

    return () => clearInterval(interval);
  }, [rebootOptions]);

  useEffect(() => {
    if (phase !== "rebooting") return;

    const interval = setInterval(() => {
      setSecondsLeft((prev) => {
        if (prev <= 1) {
          clearInterval(interval);
          return 0;
        }
        return prev - 1;
      });
    }, 1000);

    return () => clearInterval(interval);
  }, [phase]);

  useEffect(() => {
    if (!rebootOptions) return;

    const timeout = setTimeout(() => {
      navigate("/", { replace: true });
    }, rebootOptions.redirectAfter * 1000);

    return () => clearTimeout(timeout);
  }, [rebootOptions, navigate]);

  if (!rebootOptions) return null;

  return (
    <div style={{ textAlign: "center", marginTop: "3rem" }}>
      {phase === "countdown" ? (
        <h2>Device will restart in: {secondsLeft} seconds</h2>
      ) : (
        <>
          <h2>Device is rebooting...</h2>
          <p>Redirecting in {secondsLeft} seconds…</p>
          <p style={{ marginTop: "1rem" }}>
            After the reboot, make sure you're connected to the device or its
            network.
          </p>
        </>
      )}
    </div>
  );
};
