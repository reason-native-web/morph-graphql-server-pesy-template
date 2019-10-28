open Graphql_lwt;

type user = {
  id: int,
  name: string,
  email: string,
};

let users =
  ref([
    {id: 1, name: "Ulrik Strid", email: "ulrik@strid.com"},
    {id: 2, name: "Cem Turan", email: "cem2ran@gmail.com"},
  ]);

let user =
  Schema.(
    obj("user", ~doc="A user in the system", ~fields=_ =>
      [
        field("id", ~typ=non_null(int), ~args=Arg.[], ~resolve=(info, p) =>
          p.id
        ),
        field(
          "name", ~typ=non_null(string), ~args=Arg.[], ~resolve=(info, p) =>
          p.name
        ),
        field(
          "email", ~typ=non_null(string), ~args=Arg.[], ~resolve=(info, p) =>
          p.email
        ),
      ]
    )
  );

let schema: Schema.schema(Hmap.t) =
  Schema.(
    schema(
      ~mutations=[
        field(
          "addUser",
          ~typ=non_null(user),
          ~args=
            Arg.[
              arg("name", non_null(string)),
              arg("email", non_null(string)),
            ],
          ~resolve=(_info, (), name, email) => {
            let new_user = {id: List.length(users^) + 1, name, email};
            users := [new_user, ...users^];
            new_user;
          },
        ),
      ],
      [
        field(
          "users",
          ~typ=non_null(list(non_null(user))),
          ~args=Arg.[],
          ~resolve=(_info, ()) =>
          users^
        ),
        field(
          "userById",
          ~typ=user,
          ~args=Arg.[arg("id", non_null(int))],
          ~resolve=(_info, (), id) =>
          List.find_opt(u => u.id == id, users^)
        ),
      ],
    )
  );