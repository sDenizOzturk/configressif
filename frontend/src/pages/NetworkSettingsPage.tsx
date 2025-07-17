import { useForm } from "react-hook-form";
import { FormTextInput } from "../components/FormTextInput";
import type { WifiConfigForm } from "../models/wifi-config";
import { FormCheckbox } from "../components/FormCheckbox";
import { FormButton } from "../components/FormButton";
import { useEffect } from "react";
import { API_NETWORK_URL } from "../../utils/urls";

const IP_ADDRESS_RULES = {
  required: "An IP address is required",
  validate: (ip: unknown) => {
    const parts = (typeof ip === "string" ? ip : "").split(".").map(Number);
    if (parts.length !== 4) {
      return "IP address must have 4 octets";
    }
    const valid = parts.length === 4 && parts.every((p) => p >= 0 && p <= 255);
    return valid || "Each octet must be between 0 and 255";
  }
};

const NetworkSettingsPage = () => {
  const {
    register,
    handleSubmit,
    watch,
    getValues,
    setValue,
    reset,
    formState: { errors }
  } = useForm<WifiConfigForm>({
    mode: "onTouched",
    reValidateMode: "onChange"
  });

  const wifiEnabled = watch("wifiEnabled");
  const dhcpEnabled = watch("dhcpEnabled");

  const handleIpBlur = () => {
    const ip = getValues("ip");

    const parts = ip.split(".").map(Number);
    const valid = parts.length === 4 && parts.every((p) => p >= 0 && p <= 255);

    if (valid) {
      if (getValues("gateway") === "") {
        const gateway = `${parts[0]}.${parts[1]}.${parts[2]}.1`;
        setValue("gateway", gateway, {
          shouldValidate: true,
          shouldDirty: true
        });
      }
      if (getValues("subnet") === "") {
        setValue("subnet", "255.255.255.0", {
          shouldValidate: true,
          shouldDirty: true
        });
      }
    }
  };

  useEffect(() => {
    const fetchConfig = async () => {
      try {
        const response = await fetch(API_NETWORK_URL);
        const data: WifiConfigForm = await response.json();
        reset(data);
      } catch (error) {
        console.error("Failed to fetch network config:", error);
      }
    };

    fetchConfig();
  }, [reset]);

  const onSubmit = async (data: WifiConfigForm) => {
    try {
      const response = await fetch(API_NETWORK_URL, {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify(data)
      });

      if (!response.ok) {
        throw new Error(`Server responded with ${response.status}`);
      }

      console.log("Saved successfully:", await response.json());
    } catch (error) {
      console.error("Failed to save config:", error);
    }
  };

  return (
    <div
      style={{
        display: "flex",
        justifyContent: "center",
        padding: "2rem",
        backgroundColor: "#f0f0f0bb",
        borderRadius: "1rem"
      }}
    >
      <div
        style={{
          display: "flex",
          flexDirection: "column",
          gap: "1rem",

          width: "16rem"
        }}
      >
        <h2>Network Settings</h2>
        <form
          onSubmit={handleSubmit(onSubmit)}
          style={{ display: "flex", flexDirection: "column", gap: "1rem" }}
        >
          <FormCheckbox<WifiConfigForm>
            label="Use WIFI"
            name="wifiEnabled"
            register={register}
          />

          {wifiEnabled && (
            <>
              <FormTextInput<WifiConfigForm>
                label="SSID"
                name="ssid"
                register={register}
                rules={{
                  required: "SSID is required",
                  maxLength: {
                    value: 32,
                    message: "SSID must be at most 32 characters"
                  }
                }}
                error={errors.ssid?.message}
              />

              <FormTextInput<WifiConfigForm>
                label="Password"
                name="password"
                type="password"
                register={register}
                error={errors.password?.message}
                rules={{
                  validate: (value) => {
                    const password = value as string;
                    if (password.length !== 0 && password.length < 8)
                      return "Password must be at least 8 characters, leave empty for open network";
                    if (password.length > 63)
                      return "Password must be at most 63 characters";
                    return true;
                  }
                }}
              />

              <FormCheckbox<WifiConfigForm>
                label="Use DHCP"
                name="dhcpEnabled"
                register={register}
              />
              {!dhcpEnabled && (
                <>
                  <FormTextInput<WifiConfigForm>
                    label="Static IP Address"
                    name="ip"
                    register={register}
                    error={errors.ip?.message}
                    rules={IP_ADDRESS_RULES}
                    onBlur={handleIpBlur}
                  />

                  <FormTextInput<WifiConfigForm>
                    label="Gateway"
                    name="gateway"
                    register={register}
                    error={errors.gateway?.message}
                    rules={IP_ADDRESS_RULES}
                  />

                  <FormTextInput<WifiConfigForm>
                    label="Subnet Mask"
                    name="subnet"
                    register={register}
                    error={errors.subnet?.message}
                    rules={IP_ADDRESS_RULES}
                  />
                </>
              )}
            </>
          )}

          <FormButton label="Save" />
        </form>
      </div>
    </div>
  );
};

export default NetworkSettingsPage;
