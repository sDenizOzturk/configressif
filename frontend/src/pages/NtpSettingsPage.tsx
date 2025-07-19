import { useForm } from "react-hook-form";
import { FormCheckbox } from "../components/FormCheckbox";
import { FormButton } from "../components/FormButton";
import { useEffect, useState } from "react";
import { API_NTP_URL } from "../../utils/urls";
import { Spinner } from "../components/Spinner";
import { SystemClock } from "../components/SystemClock";
import { FormSelect } from "../components/FormSelect";
import type { NtpConfigForm } from "../models/ntp-config";
import { useTimezoneOffsets } from "../hooks/useTimezoneOffsets";
import { useNtpServers } from "../hooks/useNtpServers";

type NtpResponse = NtpConfigForm & {
  currentTime: number;
};

const NtpSettingsPage = () => {
  const {
    register,
    handleSubmit,
    watch,
    reset,
    formState: { errors }
  } = useForm<NtpConfigForm>({
    mode: "onTouched",
    reValidateMode: "onChange"
  });

  const enabled = watch("enabled");

  const [initialSystemTime, setInitialSystemTime] = useState<number | null>(
    null
  );
  const [isLoading, setIsLoading] = useState(true);

  const NTP_SERVERS = useNtpServers(setIsLoading);
  const TIMEZONE_OFFSETS = useTimezoneOffsets(setIsLoading);

  useEffect(() => {
    const fetchConfig = async () => {
      setIsLoading(true);
      try {
        const response = await fetch(API_NTP_URL);
        const data: NtpResponse = await response.json();
        reset(data);
        setInitialSystemTime(data.currentTime);
      } catch (error) {
        console.error("Failed to fetch NTP config:", error);
      }
      setIsLoading(false);
    };

    fetchConfig();
  }, [reset]);

  const onSubmit = async (data: NtpConfigForm) => {
    setIsLoading(true);
    try {
      const response = await fetch(API_NTP_URL, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(data)
      });

      if (!response.ok)
        throw new Error(`Server responded with ${response.status}`);

      const result: NtpResponse = await response.json();
      setInitialSystemTime(result.currentTime);
    } catch (error) {
      console.error("Failed to save NTP config:", error);
    }
    setIsLoading(false);
  };

  if (isLoading) return <Spinner />;

  return (
    <div style={{ display: "flex", justifyContent: "center", padding: "2rem" }}>
      <div
        style={{
          display: "flex",
          flexDirection: "column",
          gap: "1rem",
          width: "16rem"
        }}
      >
        <h2>NTP Settings</h2>

        <form
          onSubmit={handleSubmit(onSubmit)}
          style={{ display: "flex", flexDirection: "column", gap: "1rem" }}
        >
          <FormCheckbox<NtpConfigForm>
            label="Enable NTP"
            name="enabled"
            register={register}
          />

          {enabled && (
            <>
              <FormSelect<NtpConfigForm>
                label="NTP Server"
                name="server"
                register={register}
                rules={{ required: "NTP server is required" }}
                options={NTP_SERVERS}
                error={errors.server?.message}
              />
              <FormSelect<NtpConfigForm>
                label="Timezone Offset"
                name="timezoneOffset"
                register={register}
                rules={{
                  required: "Timezone offset is required",
                  valueAsNumber: true
                }}
                options={TIMEZONE_OFFSETS}
                error={errors.timezoneOffset?.message}
              />
            </>
          )}

          <FormButton label="Save" />
        </form>

        <SystemClock initialTime={initialSystemTime} />
      </div>
    </div>
  );
};

export default NtpSettingsPage;
