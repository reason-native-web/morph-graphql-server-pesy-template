Fmt_tty.setup_std_outputs();
Logs.set_level(Some(Logs.Info));
Logs.set_reporter(Logs_fmt.reporter());

let graphql_handler = Morph_graphql_server.make(Library.Schema.schema);

let handler = (request: Morph.Request.t) => {
  open Morph;

  let path_parts =
    request.target
    |> Uri.of_string
    |> Uri.path
    |> String.split_on_char('/')
    |> List.filter(s => s != "");

  switch (request.meth, path_parts) {
  | (_, []) => Morph.Response.text("Hello world!", Response.empty)
  | (_, ["greet", name]) =>
    Morph.Response.text("Hello " ++ name ++ "!", Response.empty)
  | (`GET, ["graphql"]) =>
    Morph.Response.text(Library.GraphiQL.html, Morph.Response.empty)
  | (_, ["graphql"]) => graphql_handler(request)
  | (_, _) => Response.not_found(Response.empty)
  };
};

let http_server = Morph_server_http.make();

Morph.start(
  ~servers=[http_server],
  ~middlewares=[Library.Middleware.logger],
  handler,
)
|> Lwt_main.run;