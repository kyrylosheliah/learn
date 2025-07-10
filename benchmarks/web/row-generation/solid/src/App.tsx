import type { Component } from "solid-js";

import logo from "./logo.svg";
import styles from "./App.module.css";
import { List } from "./components/list";

const App: Component = () => {
  return (
    <div class={styles.App}>
      <List />
    </div>
  );
};

export default App;
