type data = { text: string };

type remoteData =
    | NotRequested
    | Loading
    | Success(option(data))
    | Error(string);

switch (result) {
| NotRequested =>
    ...

| Loading =>
    ...

| Error(error) =>
    ...

| Success(None) => <p> {ReasonReact.string("No Data")} </p>
| Success(Some(data)) =>
    <p> {ReasonReact.string("Checkout my data: " ++ data.text)} </p>
}