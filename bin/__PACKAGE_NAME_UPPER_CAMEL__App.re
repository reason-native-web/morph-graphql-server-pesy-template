Fmt_tty.setup_std_outputs();
Logs.set_level(Some(Logs.Info));
Logs.set_reporter(Logs_fmt.reporter());

let handler = (request: Morph_core.Request.t) => {
  open Morph_core;

  let path_parts =
    request.target
    |> Uri.of_string
    |> Uri.path
    |> String.split_on_char('/')
    |> List.filter(s => s != "");

  switch (request.meth, path_parts) {
  | (_, []) => Morph_core.Response.text("Hello world!", Response.empty)
  | (_, ["greet", name]) =>
    Morph_core.Response.text("Hello " ++ name ++ "!", Response.empty)
  | (`GET, ["static", ...file_path]) =>
    Morph_core.Response.static(
      file_path |> String.concat("/"),
      Response.empty,
    )
  | (_, _) => Response.not_found(Response.empty)
  };
};

Morph.start_server(~middlewares=[Library.Middleware.logger], handler)
|> Lwt_main.run;
