/* MyComponent.re */

/* types */

type data = { text: string };

type remoteData =
    | NotRequested
    | Loading
    | Success(data)
    | Error(string);


/* react component */

let component = ReasonReact.statelessComponent("MyComponent");

let make = (~result, ~getData, _children) => {
    ...component,
    render: _self =>
        switch (result) {
        | NotRequested =>
            <button onClick=getData>
                {ReasonReact.string("No data yet, Click me to load the data")}
            </button>

        | Loading => <p> {ReasonReact.string("Loading...")} </p>

        | Success(data) =>
            <p> {ReasonReact.string("Checkout my data: " ++ data.text)} </p>

        | Error(error) =>
            <p> {ReasonReact.string("Something went wrong: " ++ error)} </p>
        },
};