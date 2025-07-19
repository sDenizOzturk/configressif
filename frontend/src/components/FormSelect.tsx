import type { UseFormRegister, RegisterOptions, Path } from "react-hook-form";
import styles from "./FormTextInput.module.css"; // input stilleriyle aynı

type Option = {
  label: string;
  value: string | number;
};

type Props<T extends Record<string, unknown>> = {
  label: string;
  name: keyof T;
  register: UseFormRegister<T>;
  options: Option[];
  rules?: RegisterOptions<T, Path<T>>;
  error?: string;
};

export function FormSelect<T extends Record<string, unknown>>({
  label,
  name,
  register,
  options,
  rules,
  error
}: Props<T>) {
  return (
    <div
      style={{
        display: "flex",
        flexDirection: "column",
        gap: "0.25rem",
        maxWidth: "20rem"
      }}
    >
      <label htmlFor={name as string}>{label}</label>
      <select
        id={name as string}
        {...register(name as Path<T>, rules)}
        className={`${styles.input} ${error ? styles.error : ""}`}
      >
        {options.map((opt) => (
          <option key={opt.value} value={opt.value}>
            {opt.label}
          </option>
        ))}
      </select>
      {error && (
        <span
          style={{
            color: "red",
            fontSize: "0.8rem",
            whiteSpace: "normal",
            wordBreak: "break-word"
          }}
        >
          {error}
        </span>
      )}
    </div>
  );
}
