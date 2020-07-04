Fmt_tty.setup_std_outputs();
Logs.set_level(Some(Logs.Info));
Logs.set_reporter(Logs_fmt.reporter());

let graphql_handler = Morph_graphql_server.make(Library.Schema.schema);

let handler: Morph.Server.handler = (req: Morph.Request.t) => {
  let path_parts =
    req.request.target
    |> Uri.of_string
    |> Uri.path
    |> String.split_on_char('/')
    |> List.filter(s => s != "");

  switch (req.request.meth, path_parts) {
  | (_, []) => Morph.Response.text("Hello world!") |> Lwt.return
  | (_, ["greet", name]) =>
    Morph.Response.text("Hello " ++ name ++ "!") |> Lwt.return
  | (`GET, ["graphql"]) =>
    Morph.Response.html(Library.GraphiQL.html) |> Lwt.return
  | (_, ["graphql"]) => graphql_handler(req)
  | (_, _) => Morph.Response.not_found() |> Lwt.return
  };
};

let http_server = Morph.Server.make();

Morph.start(
  ~servers=[http_server],
  ~middlewares=[],
  handler,
)
|> Lwt_main.run;
