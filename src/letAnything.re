/* Async Await */

let myAsyncFunction = () => {
  let%Promise result = Fetch.fetch("http://www.example.com")
  let%Promise jsonData =  Fetch.Response.json(result) 

  Js.log(jsonData)
}


/* Optional Chaining */

type address = {
  streetNo: int,
  streetName: string,
  /* ...other fields, */

  description: option(string)
}

type company = {
  name: string,
  address: option(address)
}

type user = {
  name: string,
  company: option(company)
}

let getAddressDescription: user => option(int) = (user) => {
  let%Opt company = user.company;
  let%Opt address = company.address;
  
  address.description;
}

/* Javascript Version
const getAddressDescription(user) {
  const company = user.company
  if (company != null) {
    const address = company.address 

    return address.description
  } 
}
*/


/* Result Chaining */

let myResultChain = () => {
  let%Result user = getUser()
  let%Result company = getCompany(user)

  company.description
}
