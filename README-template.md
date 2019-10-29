# <PACKAGE_NAME_FULL>

A project which demonstrates a Reason workflow with [Esy][].

[esy]: https://github.com/esy/esy

## Usage

You need Esy, you can install the beta using [npm](https://npmjs.com):

    % npm install -g esy@latest

> NOTE: Make sure `esy --version` returns at least `0.5.8` for this project to build.

Then run the `esy` command from this project root to install and build dependencies.

    % esy

You can start the server to try it out (runs `scripts.start` specified in
`package.json`):

    % esy start

This will start a simple graphql server that runs on port 8080 and has the following routes:

    GET / -> responds with "Hello world!"
    GET /greet/:name -> responds with "Hello ${name}!"
    GET /graphql -> responds GraphiQL user interface
    POST /graphql -> responds with GraphQL response

After you make some changes to source code, you can re-run project's build
again with the same simple `esy` command.

    % esy

And test compiled executable (runs `scripts.tests` specified in
`package.json`):

    % esy test

Documentation for the libraries in the project can be generated with:

    % esy doc
    % open-cli `esy echo '#{self.target_dir}/default/_doc/_html/index.html'`

This assumes you have a command like [open-cli](https://github.com/sindresorhus/open-cli) installed on your system.
