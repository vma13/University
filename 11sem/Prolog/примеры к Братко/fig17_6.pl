%   Figure 17.6  A means-ends planner with goal protection. 
%   Predicates satisfied, select, achieves and apply are as in Figure 17.5.

%   A means-ends planner with goal protection

plan( InitialState, Goals, Plan, FinalState)  :-
  plan( InitialState, Goals, [], Plan, FinalState).

%   plan( InitialState, Goals, ProtectedGoals, Plan, FinalState):
%     Goals true in FinalState, ProtectedGoals never destroyed by Plan

plan( State, Goals, _, [], State)  :-
  satisfied( State, Goals).                     % Goals true in State

plan( State, Goals, Protected, Plan, FinalState)  :-
  conc( PrePlan, [Action | PostPlan], Plan),    % Divide plan
  select( State, Goals, Goal),                  % Select an unsatisfied goal
  achieves( Action, Goal),
  can( Action, Condition),
  preserves( Action, Protected),                % Do not destroy protected goals
  plan( State, Condition, Protected, PrePlan, MidState1),
  apply( MidState1, Action, MidState2),
  plan( MidState2, Goals, [Goal | Protected], PostPlan, FinalState).

% preserves( Action, Goals): Action does not destroy any one of Goals

preserves( Action, Goals)  :-       % Action does not destroy Goals
  deletes( Action, Relations),
  not (member( Goal, Relations),
       member( Goal, Goals) ).


