# What I want to tlak about

## Type System

- Variants

  - Allowing a finite amount of states in your application
  - pattern matching; dealing with each of these now finite amount of states. Because you know of all of your possbile application states, you know that you have properly dealt with them and the compiler will tell you if you've missed one.
  - making invalid states impossible
  - https://guide.elm-lang.org/appendix/types_as_sets.html

  - (how are they different to enums) a tag with possibly some data:

    imagine you want to model fetching some data from an api. In javascript you may start to model it like this:

    ```javascript
    let data = null;

    fetch("http://gimme-the-goods.com/api")
      .then(res => res.json())
      .then(json => {
        data = json;
      });
    ```

    This might look okay initially but let's say we actually build it into our application:

    ```javascript
    /*
      type Props = {
        data: { text: string } | null
        getData: () => void
      }
    */

    class MyComponent extends Component {
      componentDidMount() {
        this.props.getData();
      }

      render() {
        if (this.props.data) {
          return <p>checkout my data: {this.props.data.text}</p>;
        } else {
          return <p>loading...</p>;
        }
      }
    }
    ```

    what happens if we forget about the component did mount code (it will say that it's loading when it's not)
    what if it was a button click that triggered getting the data, how could we say that it hasn't started loading yet (until taht button has been pressed)
    what if there was an error fetchin the data, the user will just wait on the page thinking it was still loading

    you might change it to something like this:

    ```javascript
    /*
      type Props = {
        data: { text: string } | null,
        error: string | null,
        didError: boolean,
        isLoadingData: boolean,
        wasSuccessful: boolean,
    
        getData: () => void
      }
    */

    function MyComponent(props) {
      if (props.isLoadingData) {
        return <p>Loading...</p>;
      } else if (props.didError) {
        return <p>Something went wrong: {props.error}</p>;
      } else if (props.wasSuccessful) {
        return <p>Checkout my data: {props.data.text}</p>;
      } else {
        return (
          <button onClick={props.getData}>
            No data yet, Click me to load the data
          </button>
        );
      }
    }
    ```

    This code is however pretty error prone for a few reasons:

    - it's easy to forget to update the isLoadingData/didError/wasSuccessful fields in your state
    - you can just ignore didError/isLoadingData/wasSuccessful (what if you access props.data, read the value as null. How do you know whether the api returned null or whether the data)
    - There are so many impossible states that your application can be in. What if both didError and wasSuccessful are `true` or the data attribute and the error attribute are set. What if the application says it is loading but data is also set.

    With Flow you can make this a bit better:

    ```javascript
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
    ```

    The code above is a lot better but it still has some problems:

    - We can still set RemoteData.status to be something other than the four values specified if we are setting it using a variable that the type system sets to `any`
    - Since the data we are getting comes from an API, there is no guarantee that it will actually be a string when it arrives. So we aren't handling the case where the API changes underneath us. This will lead to those dreaded `Unable to get property 'value' of undefined` errors that leave your page broken and your customers wondering why they are seeing a blank page.

    So how would we handle this in a ReasonML application?

    ```reasonml
    // MyComponent.re

    type data = {text: string};

    type remoteData =
      | NotRequested
      | Loading
      | Success(data)
      | Error(string);

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

    ```

    - The above code while looking almost identical, actually adresses all of the issues that were identified earlier. We can only ever set data to one of the four values (and the type system guarantees that),
    - We can only look at the Success data or Error data if we have first checked that the request was successful or had errored
    - We get told when not all cases are covered (Like if we only cover the case of Success and Error, but not the loading case)
    - We are also forced to verify that the data that came from the api is actually in the format that the type system expects (This )

    ## lets talk about switch expressions

    in Reasonml switch is an expression (it actually returns a value) rather than a statement like in javascript. 
    Since Reason programs are 100% type covered and the switch expression always returns something, the type system will make sure that you are returning something for each case and that each case returns the same type of thing.
    We can't just return a number in the third case because the type checker has seen that react elements had been returned previously.

    So in javascript we can write this where we have forgotten to return something.

    ```javascript
    function MyComponent(props: Props) {
      switch (props.result.data.status) {
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
          return <p>Something went wrong: {props.error}</p>;
        default:
          // This can never happen (or can it...)
          return <p>Something went TERRIBLY wrong</p>;
      }
    }
    ```

    In reasonml, the last value in each case is always the return value and will be type checked.

    ## Pattern Matching

    You may have noticed that in the previous example, ReasonML's switch statement was doing a bit more than the javascript equivilant

    ```reasonml
    switch (data) {
    | NotRequested =>
      <button onClick={getData}>
        ReasonReact.string("No data yet, Click me to load the data")
      </button>;

    | Loading =>
      <p>ReasonReact.string("Loading...")</p>;

    | Success(data) =>
      <p>ReasonReact.string("Checkout my data: " ++ data)</p>

    | Error(error) =>
      <p>ReasonReact.string("Something went wrong: " ++ error)</p>
    }
    ```

    In the first two cases we were jusst matching against the tags (like we would match against strings in the javascript example). In the third case though, we match against Success and pull out the data that it holds. 
    Matching against the tag is actually the only way to get the data out and you can only use the data in the case where you have matched against Success

    ```reasonml
    switch (data) {
    ...

    | Success(data) =>
      // I can access the data here

    | Error(_) =>
      // I can't access the data here

    }
    // I can't access the data here
    ```

    What we are seeing here is called pattern matching and you can do some pretty neet things with it. Let's say our endpoint can either return some data if it exists, or null if it doesn't.

    ```reasonml
    type data = { text: string };

    type remoteData =
      | NotRequested
      | Loading
      | Success(option(data))
      | Error(string);

    switch (data) {
    | NotRequested =>
      ...

    | Loading =>
      ...

    | Error(error) =>
      ...

    | Success(res) =>
      switch (res) {
      | None => <p> {ReasonReact.string("No Data")} </p>

      | Some(data) =>
        <p> {ReasonReact.string("Checkout my data: " ++ data.text)} </p>
      }

    }
    ```

    You can do this with two switch expressions or you can flatten out the switch:

    ```reasonml
    type data = { text: string };

    type remoteData =
      | NotRequested
      | Loading
      | Success(option(data))
      | Error(string);

    switch (data) {
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
    ```

    Pattern matching also doesn't just work on variants. You can use it to match on all kinds of things. Let's imagine that we are using some bad external API and when no data exists it sometimes gives you back null, and other times it gives you back an object with an empty text field. You can handle this case really nicely with pattern matching:

    ```reasonml
    switch (data) {
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
    ```

    let's just havve a look at this example in javascript:

    ```javascript
    switch (result.status) {
      case "Not Requested":
        return ...
      case "Loading":
        return ...
      case "Success":
        if (result.data === null || result.data.text === ""){
          return <p>No Data</p>
        } else {
          return <p>Checkout my data: {data.text}</p>
        }
        return
      case "Error":
        return ...
      default:
        // This can never happen (or can it...)
        return <p>Something went TERRIBLY wrong</p>;
    }
    ```

    I've come across the situation a fair bit where what is shown on the ui depends on multiple bits of state. If this is complicated behaviour you end up drawing up a table of conditions and what should be shown for them.

    Let's take the example of a router where you want to show a different set of pages if the user is logged in than when he isn't:

    you might draw out a table like this:

    | route    | isLoggedIn | isAdmin | RESULT                    |
    | Home     | _          | _       | show home page            |
    | Login    | false      | _       | show login page           |
    | Login    | true       | _       | redirect to news feed     |
    | NewsFeed | false      | false   | redirect to home page     |
    | NewsFeed | true       | false   | show news feed page       |
    | NewsFeed | true       | true    | show admin news feed page |

    In javacript you would now need to turn that into a heap of nested ifs. In ReasonML you can just pattern match on the 3 values and essentially copy out that table. :

    ```reasonml
    switch ((route, isLoggedIn, isAdmin)) {
    | (Home, _, _) => <HomePage />
    | (Login, false, _) => <LoginPage />
    | (Login, true, _) => 
      changeRoute(NewsFeed);
      <NewsFeedPage />;
    | (NewsFeed, false, false) => 
      changeRoute(Home);
      <HomePage />;
    | (NewsFeed, true, false) => <NewsFeedPage />
    | (NewsFeed, true, true) => <AdminNewsFeedPage />
    }
    ```

    This also makes it really easy to change later and reason about when you have a bug.

    # Null in ReasonML

    So the guy who came up with `null` has called it his Billion Dollar mistake saying that "it has probably caused a billion dollars of pain and damage in the last forty years". How many times have you seen `TypeError: Cannot read property of undefined | null` or just a `NaN` where some total was supposed to be?

    ReasonML doesn't have nulls. It still has the concept of things that may or may not exist but it doesn't use nulls for this. In ReasonML there is variant called option. It looks like this:

    ```reasonml
    type option('a) = 
      | Some('a)
      | None 
    ```

    Remember how I said earlier on that with variants you can't look at their parameters until you have checked which branch of the variant you are on? This enforces that if some value is optional, we can't look at the contents of it until we have first pattern matched on it. 

    so where in javascript you can just do this and have your program crash when you don't :

    ```javascript
    <p>{thing.nullableProperty.text}</p>
    ```

    in reason you would have to write but because of this, you are always conscious of what your app will do:
    ```reasonml
    switch (thing.nullableProperty) {
      | Some(text) => text
      | None => "fallback text"
    }
    ```


    Other Cool stuff

    ppx
    interop is a little weird since things don't necessarily map to js 1 to 1
    errors are sometimes not great (react, syntax errors)


    

