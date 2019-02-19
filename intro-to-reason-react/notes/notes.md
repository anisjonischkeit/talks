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
    import { getData } from "/redux/actions";

    class MyComponent extends Component {
      componentDidMount() {
        this.props.getData();
      }

      render() {
        if (this.props.data) {
          return <p>checkout my data: {this.props.data}</p>;
        } else {
          return <p>loading...</p>;
        }
      }
    }

    const mapStateToProps = state => ({ data: state.data });
    const mapDispatchToProps = dispatch => ({ getData: dispatch(getData) });

    connect(
      mapStateToProps,
      mapDispatchToProps
    )(MyComponent);
    ```

    what happens if we forget about the component did mount code (it will say that it's loading when it's not)
    what if it was a button click that triggered getting the data, how could we say that it hasn't started loading yet (until taht button has been pressed)
    what if there was an error fetchin the data, the user will just wait on the page thinking it was still loading
