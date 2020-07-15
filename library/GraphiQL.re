open Tyxml;

let html =
  <html>
    <head>
      <title> "Simple GraphiQL Example" </title>
      <link
        href="https://unpkg.com/graphiql/graphiql.min.css"
        rel="stylesheet"
      />
    </head>
    <body style="margin: 0;">
      <div id="graphiql" style="height: 100vh;" />
      <script src="https://unpkg.com/react/umd/react.production.min.js" />
      <script
        src="https://unpkg.com/react-dom/umd/react-dom.production.min.js"
      />
      <script src="https://unpkg.com/graphiql/graphiql.min.js" />
      <script src="/public/graphiql.js" />
    </body>
  </html>;
