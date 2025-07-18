import { useEffect } from "react";
import { useNavigate } from "react-router-dom";

export interface RebootOptions {
  countdown: number;
  redirectAfter: number;
}

export const useReboot = (options?: RebootOptions) => {
  const navigate = useNavigate();

  useEffect(() => {
    if (!options) return;
    navigate("/reboot", {
      state: {
        countdown: options.countdown ?? 10,
        redirectAfter: options.redirectAfter ?? 20
      }
    });
  }, [navigate, options]);
};
