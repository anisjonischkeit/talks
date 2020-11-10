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
    case "Error":
        return ...
    default:
        return ...
}