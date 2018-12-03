/* Useful Inbuilt Variants */

type option('a) =
  | Some('a)
  | None

let safeHead = arr =>
  if (Js.Array.length(arr) > 0) {
    Some(arr[0])
  } else {
    None
  };

switch(safeHead(arr)) {
  | Some(head) => 
    /* We only get access to the value after 
    ** we have checked it exists
    */
  | None => 
    /* We have to handle the case where the list is empty */
};


/* Belt.Result.t */
type result('a, 'b) = 
  | Ok('a) /* Belt.Result.Ok */
  | Error('b) /* Belt.Result.Error */



/* Useful Custom Variants */

type remoteData('data, 'error) =
  | NotRequested
  | Loading
  | Success('data)
  | Error('error)


type route = 
  | Home
  | Profile
  | Login



