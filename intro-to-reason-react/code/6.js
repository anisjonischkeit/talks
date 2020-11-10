function MyComponent(props: Props) {
    switch (props.result.status) {
        case "Not Requested":
            return (
              <button onClick={props.getData}>
                No data yet, Click me to load the data
              </button>
            );
        case "Loading":
            return <p>Loading...</p>;
        case "Success":
            // forgot to return
            <p>Checkout my data: {props.result.data.text}</p>;
        case "Error":
            return <p>Something went wrong: {props.result.error}</p>;
        default:
            // This can never happen (or can it...)
            return <p>Something went TERRIBLY wrong</p>;
    }
}