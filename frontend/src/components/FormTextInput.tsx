import type {
  FieldValues,
  Path,
  RegisterOptions,
  UseFormRegister
} from "react-hook-form";
import styles from "./FormTextInput.module.css";

type Props<T extends FieldValues> = {
  label: string;
  name: Path<T>;
  type?: string;
  register: UseFormRegister<T>;
  error?: string;
  rules?: RegisterOptions<T, Path<T>>;
  onBlur?: () => void;
};

export function FormTextInput<T extends FieldValues>({
  label,
  name,
  type = "text",
  register,
  error,
  rules,
  onBlur = () => {}
}: Props<T>) {
  const registered = register(name, rules);

  return (
    <div
      style={{
        display: "flex",
        flexDirection: "column",
        gap: "0.25rem",
        maxWidth: "20rem"
      }}
    >
      <label htmlFor={name}>{label}</label>
      <input
        id={name}
        type={type}
        {...register(name, rules)}
        className={`${styles.input} ${error ? styles.error : ""}`}
        onBlur={(e) => {
          registered.onBlur(e);
          if (onBlur) onBlur();
        }}
      />
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
