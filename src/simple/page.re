type action = Increase | AddTodo | UpdateTodo string;
type state = {counter: int, todo: list string};

let component = ReasonReact.reducerComponent "Greeting";

let make ::name _children => {
  {
    ...component,
    initialState: fun () => {counter: 0, todo: []},
    reducer: fun action state =>
      switch action {
      | Increase => ReasonReact.Update {...state, counter: state.counter + 1}
      | AddTodo => ReasonReact.Update {...state, todo: ["do something", ...state.todo]}
      },
    render: fun self => {
      let count = self.state.counter;
      let todo = self.state.todo;
      let todoLs = Array.of_list (List.map (fun msg => <li>(ReasonReact.stringToElement msg)</li>) todo);

      let greeting = {j|Hello $name, You've clicked the button $count times(s)!|j};
      <div>
        <h1> (ReasonReact.stringToElement "What up!") </h1>
        <button onClick=(self.reduce (fun _event => Increase))> (ReasonReact.stringToElement greeting) </button>
        <button onClick=(self.reduce (fun _event => AddTodo))> (ReasonReact.stringToElement "Add Todo") </button>
        <input onChange=(self.reduce (fun event => UpdateTodo "hello world")) placeholder=("Write a todo") />
        <ul>(ReasonReact.arrayToElement todoLs)</ul>
      </div>
    }
  }
};
