let render = ((prev: ReasonReact.Router.url, next: ReasonReact.Router.url)) => {
    switch(next.path) {
    | [] => <Page message="Main Page" />
    | _ => <Page message="Not Found" />
    }
};

ReactDOMRe.renderToElementWithId(<RootRouter> ...(render) </RootRouter>, "index");
