const graphQLFetcher = (graphQLParams) =>
  fetch(window.location, {
    method: "post",
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
    body: JSON.stringify(graphQLParams),
  })
    .then((response) => response.json())
    .catch(() => response.text());

ReactDOM.render(
  React.createElement(GraphiQL, { fetcher: graphQLFetcher }),
  document.getElementById("graphiql")
);
