let component = ReasonReact.statefulComponent "Greeting";

let list = [|1, 2, 3|];

let make ::name _children => {
  let click _event {ReasonReact.state} => ReasonReact.Update (state + 1);
  {
    ...component,
    initialState: fun () => 0,
    render: fun {state, update} => {
      let greeting = {j|Hello $name, You've clicked the button $state times(s)!|j};
      <div>
        <h1> (ReasonReact.stringToElement "What up!") </h1>
        <button onClick=(update click)> (ReasonReact.stringToElement greeting) </button>
        ((ReasonReact.createDomElement "ul" (Array.map (fun item => <li>(ReasonReact.stringToElement "hello")</li>) list)) {"foo": "bar"})
      </div>
    }
  }
};
