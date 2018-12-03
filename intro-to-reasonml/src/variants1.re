type animal =
  | Cat
  | Dog
  | Mouse;

/* Variants can have arguments */
type getAgeResult =
  | Ok(int)
  | Error(string);

let canDrinkAlcohol = userId => {
  let ageResult = getUserAge(userId);

  switch (ageResult) {
  | Ok(age) when age >= 18 =>
    Js.log("YES! The person's age is " ++ Js.Int.toString(age))

  | Ok(17) => Js.log("Almost! The person's age is 17")

  | Ok(age) => Js.log("NO! The person's age is " ++ Js.Int.toString(age))

  | Error(err) => Js.log("Something went wrong: " ++ err)
  };
};

/* Pattern matching on records */
type person = {
  name: string,
  age: int,
};

let isUsersNameAnis = user =>
  switch (user) {
  | {name: "Anis" | "anis"} => true
  | _ => false
  };