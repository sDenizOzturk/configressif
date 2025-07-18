import React from "react";

type Props = {
  label: string;
  type?: "submit" | "button" | "reset";
  disabled?: boolean;
};

export const FormButton: React.FC<Props> = ({
  label,
  type = "submit",
  disabled = false
}) => {
  return (
    <button
      type={type}
      disabled={disabled}
      style={{
        padding: "0.6rem 1.2rem",
        borderRadius: "0.5rem",
        fontSize: "1rem",
        backgroundColor: "#007bff",
        color: "#fff",
        border: "none",
        cursor: disabled ? "not-allowed" : "pointer",
        opacity: disabled ? 0.5 : 1,
        transition: "background-color 0.2s ease"
      }}
    >
      {label}
    </button>
  );
};
