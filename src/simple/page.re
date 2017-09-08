open ReasonJs.Dom;

type action =
  | AddTodo string
  | UpdateValue string
  | RemoveTodo int;

type todo = {
  id: int,
  value: string
};

type state = {
  todo: list todo,
  value: string
};

let component = ReasonReact.reducerComponent "ReasonML Todos";

let getTargetValue el =>
  switch el {
  | Some e => HtmlElement.value e
  | None => ""
  };

let make ::name _children => {
  ...component,
  initialState: fun () => {todo: [], value: ""},
  reducer: fun action state =>
    switch action {
    | AddTodo msg =>
      ReasonReact.Update {
        ...state,
        value: "",
        todo: [{id: List.length state.todo, value: msg}, ...state.todo]
      }
    | UpdateValue msg => ReasonReact.Update {...state, value: msg}
    | RemoveTodo id =>
      ReasonReact.Update {
        ...state,
        todo: List.filter (fun el => el.id !== id) state.todo
      }
    },
  render: fun self => {
    let todo = self.state.todo;
    let todoLs =
      todo |>
      List.map (
        fun {id, value} =>
          <li key=value>
            <button onClick=(self.reduce (fun _event => RemoveTodo id))>
              (ReasonReact.stringToElement "remove")
            </button>
            (ReasonReact.stringToElement value)
          </li>
      ) |> Array.of_list;
    <div>
      <h1> (ReasonReact.stringToElement "What up!") </h1>
      <input
        value=self.state.value
        onChange=(
          self.reduce (
            fun event =>
              UpdateValue (
                event |> ReactEventRe.Form.target |> Element.asHtmlElement |> getTargetValue
              )
          )
        )
        placeholder="Write a todo"
      />
      <br />
      <br />
      <button onClick=(self.reduce (fun _event => AddTodo self.state.value))>
        (ReasonReact.stringToElement "Add Todo")
      </button>
      <ul> (ReasonReact.arrayToElement todoLs) </ul>
    </div>
  }
};
