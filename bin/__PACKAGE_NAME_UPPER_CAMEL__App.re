Fmt_tty.setup_std_outputs();
Logs.set_level(Some(Logs.Info));
Logs.set_reporter(Logs_fmt.reporter());

let graphql_handler = Morph_graphql_server.make(Library.Schema.schema);

let graphiql_handler = _ =>
  Library.TyxmlRender.respond_html(Library.GraphiQL.html) |> Lwt.return;

let get_routes =
  Routes.[
    empty @--> (_ => Morph.Response.text("Hello world!") |> Lwt.return),
    s("graphql") /? nil @--> graphiql_handler,
  ];

let post_routes = Routes.[s("graphql") /? nil @--> graphql_handler];

let port =
  switch (Sys.getenv_opt("PORT")) {
  | Some(p) => int_of_string(p)
  | None => 5050
  };

let http_server =
  Morph.Server.make(~port, ~address=Unix.inet_addr_loopback, ());

Morph.start(
  ~servers=[http_server],
  ~middlewares=[
    Morph.Middlewares.Static.make(~path="public", ~public_path="./public"),
  ],
  Morph.Router.make(~get=get_routes, ~post=post_routes, ()),
)
|> Lwt_main.run;
