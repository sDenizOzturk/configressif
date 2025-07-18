import { useId } from "react";
import type {
  FieldValues,
  Path,
  RegisterOptions,
  UseFormRegister
} from "react-hook-form";

type Props<T extends FieldValues> = {
  label: string;
  name: Path<T>;
  register: UseFormRegister<T>;
  rules?: RegisterOptions<T, Path<T>>;
};

export function FormCheckbox<T extends FieldValues>({
  label,
  name,
  register,
  rules
}: Props<T>) {
  const id = useId();
  return (
    <div style={{ display: "flex", alignItems: "center", gap: "0.5rem" }}>
      <input type="checkbox" id={id} {...register(name, rules)} />
      <label htmlFor={id}>{label}</label>
    </div>
  );
}
