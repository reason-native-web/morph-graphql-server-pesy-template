Fmt_tty.setup_std_outputs();
Logs.set_level(Some(Logs.Info));
Logs.set_reporter(Logs_fmt.reporter());

let handler = (request: Morph_core.Request.t) => {
  let req_uri = request.target |> Uri.of_string;
  let req_path = Uri.path(req_uri);
  let path_parts =
    CCString.split(~by="/", req_path) |> CCList.filter(s => s != "");

  switch (request.meth, path*parts) {
  | (_, "") => Morph_core.Response.text("Hello world!")
  | (_, "greet", name) => Morph_core.Response.text("Hello " ++ greeting ++ "!")
  | (`GET, ["static", ...file_path]) => Morph_core.Response.static(file_path)
  | (_, _) => Routes.FourOhFour.make(~request, ())
  };
};

Morph.start_server(~middlewares=[Middleware.logger], handler) |> Lwt_main.run;
