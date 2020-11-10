switch (result) {
| NotRequested =>
    ...

| Loading =>
    ...

| Error(error) =>
    ...

| Success(None) | Success(Some({ text: "" })) => 
    <p> {ReasonReact.string("No Data")} </p>

| Success(Some(data)) =>
    <p> {ReasonReact.string("Checkout my data: " ++ data.text)} </p>
}