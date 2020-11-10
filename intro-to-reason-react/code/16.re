switch (thing.nullableProperty) {
    | Some(text) => text
    | None => "fallback text"
}