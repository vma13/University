%  Figure 23.5  A simple interpreter for object-oriented programs.


%  An interpreter for object-oriented programs

%  send( Message, Object)  if
%    find Object's methods and 
%    execute the method that corresponds to Message

send( Object, Message)  :-
  get_methods( Object, Methods),             % Find Object's methods
  process( Message, Methods).                % Execute corresponding method

get_methods( Object, Methods)  :-
  object( Object, Methods).                          % Private methods

get_methods( Object, Methods)  :-
  isa( Object, SuperObject),          
  get_methods( SuperObject, Methods).                % Inherited methods

process( Message, [Message | _]).                    % Use a fact

process( Message, [ (Message  :-  Body) | _])  :-    % Use a rule
  call( Body).

process( Message, [_ | Methods])  :-
  process( Message, Methods).
