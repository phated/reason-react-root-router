open Webapi.Dom;

type msg = Route(ReasonReact.Router.url);
type state = {
  prevLocation: ReasonReact.Router.url,
  nextLocation: ReasonReact.Router.url
};

let emptyLoc = (): ReasonReact.Router.url => { path: [], hash: "", search: "" };

let component = ReasonReact.reducerComponent("Router");

let make = (_children) => {
  ...component,
  initialState: () => { prevLocation: emptyLoc(), nextLocation: emptyLoc() },
  didMount: (_) => switch [%external window] {
    | None => ReasonReact.NoUpdate
    | Some(window) => {
        let appLoad = Event.make("popstate");
        let _ = Window.dispatchEvent(appLoad, window);
        ReasonReact.NoUpdate
    }
  },
  reducer: (msg, state) => switch msg {
  | Route(url) => ReasonReact.Update({ prevLocation: state.nextLocation, nextLocation: url })
  },
  render: (self) => _children((self.state.prevLocation, self.state.nextLocation)),
  subscriptions: ({ send }) => [
    Sub(
      () => ReasonReact.Router.watchUrl(url => send(Route(url))),
      ReasonReact.Router.unwatchUrl
    )
  ]
};
