import { useEffect, useRef, useState } from "react";

const range = (start: number, end: number) =>
  Array.from({ length: end }, (_, i) => i + start);

export const List = () => {
  const [list, setList] = useState<Array<number>>([]);
  const [count, setCount] = useState<number>(0);
  const [timestamp, setTimestamp] = useState<number | undefined>(undefined);
  const [time, setTime] = useState<number>(0);
  const set = () => {
    setTimestamp(Date.now());
    setList(range(0, count).reverse());
  };
  const increment = () => {
    setTimestamp(Date.now());
    setCount(count + 1);
  };
  useEffect(() => {
    set();
  }, [count]);

  const mounted = useRef();
  useEffect(() => {
    if (mounted.current) {
      // do componentDidUpdate logic
      if (timestamp) {
        setTime(Date.now() - timestamp);
        setTimestamp(undefined);
      }
    } else {
      // do componentDidMount logic
      (mounted.current as any) = true;
    }
  });
  return (
    <>
      <div>
        <button onClick={increment}>+</button>
      </div>
      <div>{time} ms</div>
      <div>
        <input
          type="number"
          min={0}
          value={count}
          onChange={(e) => setCount(Number(e.target.value.replace(/\D/g, "")))}
        />
      </div>

      {list.map((i, index) => (
        <div key={index}>{i}</div>
      ))}
    </>
  );
};
