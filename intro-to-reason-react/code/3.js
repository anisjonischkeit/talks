
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