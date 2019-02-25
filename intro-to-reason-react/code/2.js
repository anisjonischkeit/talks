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