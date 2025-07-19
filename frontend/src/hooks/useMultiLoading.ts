import { useCallback, useState } from "react";

export function useMultiLoading() {
  const [count, setCount] = useState(0);

  const increment = useCallback(() => {
    setCount((prev) => prev + 1);
  }, []);

  const decrement = useCallback(() => {
    setCount((prev) => Math.max(0, prev - 1));
  }, []);

  const reset = useCallback(() => {
    setCount(0);
  }, []);

  return {
    isLoading: count > 0,
    loadingCount: count,
    startLoading: increment,
    stopLoading: decrement,
    resetLoading: reset
  };
}
