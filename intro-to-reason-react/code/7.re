switch (result) {
| NotRequested =>
    <button onClick={getData}>
        ReasonReact.string("No data yet, Click me to load the data")
    </button>;

| Loading =>
    <p>ReasonReact.string("Loading...")</p>;

| Success(data) =>
    <p>ReasonReact.string("Checkout my data: " ++ data.text)</p>

| Error(error) =>
    <p>ReasonReact.string("Something went wrong: " ++ error)</p>
}