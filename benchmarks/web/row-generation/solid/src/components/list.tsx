import { For, createEffect, createSignal } from "solid-js";

const range = (start: number, end: number) =>
  Array.from({ length: end }, (_, i) => i + start);

export const List = () => {
  const [list, setList] = createSignal<Array<number>>([]);
  const [count, setCount] = createSignal<number>(0);
  const [timestamp, setTimestamp] = createSignal<number | undefined>(undefined);
  const [time, setTime] = createSignal<number>(0);
  const set = () => {
    setTimestamp(Date.now());
    setList(range(0, count()).reverse());
  };
  const increment = () => {
    setTimestamp(Date.now());
    setCount(count() + 1);
  };
  createEffect(() => {
    set();
  }, count());

  let mounted: HTMLDivElement;
  createEffect(() => {
    let stamp = timestamp();
    if (stamp) {
      setTime(Date.now() - stamp);
      setTimestamp(undefined);
    }
  }, mounted!);
  return (
    <>
      <div>
        <button onClick={increment}>+</button>
      </div>
      <div>{time()} ms</div>
      <div>
        <input
          type="number"
          min={0}
          value={count()}
          onInput={(e) => setCount(Number(e.target.value.replace(/\D/g, "")))}
        />
      </div>

      <For ref={mounted!} each={list()}>
        {(i) => <div>{i}</div>}
      </For>
    </>
  );
};
