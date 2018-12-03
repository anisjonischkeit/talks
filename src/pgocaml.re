/* PGOCaml */

let insertEmployee = [%sqlf
  {|
    INSERT INTO employees (name, salary, email)
    VALUES ($name, $salary, $?email)
    RETURNING name, salary
  |}
];

execute_query(insertEmployee(~name="name", ~salary=10000, ~email=None));