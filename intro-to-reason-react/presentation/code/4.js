// @flow

type Props = {
  data: RemoteData,
  getData: () => void
};

type RemoteData =
  | { status: "Not Requested" }
  | { status: "Loading" }
  | { status: "Success", data: { text: string } }
  | { status: "Error", error: string };

function MyComponent(props: Props) {
  switch (props.data.status) {
    case "Not Requested":
      return (
        <button onClick={props.getData}>
          No data yet, Click me to load the data
        </button>
      );
    case "Loading":
      return <p>Loading...</p>;
    case "Success":
      return <p>Checkout my data: {props.data.text}</p>;
    case "Error":
      return <p>Something went wrong: {props.error}</p>;
    default:
      // This can never happen (or can it...)
      return <p>Something went TERRIBLY wrong</p>;
  }
}