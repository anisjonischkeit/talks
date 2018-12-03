open Js.String;

let yellUnPiped = value =>
  repeat(3, toUpperCase(value))

let yellPiped = value =>
  value
    |> toUpperCase
    |> repeat(3)

let yellFastPiped = value =>
  value
    ->toUpperCase
    ->repeat(3, _)



