%  Figures 16.6, 16.7, 16.8, 16.9 combined, with small improvements


%  An expert system shell


:-  op( 900, xfx, ::).
:-  op( 800, xfx, was).
:-  op( 870, fx, if).
:-  op( 880, xfx, then).
:-  op( 550, xfy, or).
:-  op( 540, xfy, and).
:-  op( 300, fx, 'derived by').
:-  op( 600, xfx, from).
:-  op( 600, xfx, by).
:-  op( 900, fy, not).

% Program assumes built-in operator: op( 700, xfx, is)

% Top-level driving procedure

expert  :-
  getquestion( Question),       % Input user's question
  ( answeryes( Question);	% Try to find positive answer
    answerno( Question) ).	% If no positive answer then find negative

answeryes( Question)  :-		% Look for positive answers to Question
  markstatus( negative), 		% No positive answer yet
  explore( Question, [], Answer),       % Trace is empty
  positive( Answer),                    % Look for positive answers
  markstatus( positive),		% Positive answer found
  present( Answer), nl,
  write('More solutions? '), 
  getreply( Reply),	 		% Read user's reply
  Reply = no.            % Otherwise backtrack to 'explore'

answerno( Question)  :-			% Look for negative answer to question
  retract( no_positive_answer_yet), !,  % Has there been no positive answer?
  explore( Question, [], Answer),
  negative( Answer),
  present( Answer), nl,
  write('More negative solutions? '), 
  getreply( Reply),
  Reply = no.		% Otherwise backtrack to 'explore'

markstatus( negative)  :-
  assert( no_positive_answer_yet).

markstatus( positive)  :-
  retract( no_positive_answer_yet), !; true.

getquestion( Question)  :-
  nl, write( 'Question, please '),
  nl,
  read( Question).


% explore( Goal, Trace, Answer):
%   find Answer to a given Goal. Trace is a chain of ancestor
%   goals and rules. 
%   'explore' tends to find a positive answer to a question.
%   Answer is 'false' only when all the possibilities have been
%   investigated and they all resulted in 'false'


explore( Goal, Trace, _)  :-
  copy_term( Goal, Copy),	% Make copy of Goal with variables renamed
  member( Copy by Rule, Trace),	% Similar ancestor goal?
  instance_of( Copy, Goal),   	% Ancestor goal as general as Goal?
  !, fail.			% Abandon Goal because of cycle!

explore( Goal, Trace, Goal is true was 'found as a fact')  :-
  fact :: Goal.

explore( Goal, Trace,	               % Assume only one rule about each type of goal
    Goal is TruthValue was 'derived by' Rule from Answer)  :-
  Rule :: if Condition then Goal,      % Rule relevant to Goal
  explore( Condition, [Goal by Rule | Trace], Answer),
  truth( Answer, TruthValue).

explore( Goal1 and Goal2, Trace, Answer)  :-  !,
  explore( Goal1, Trace, Answer1),
  continue( Answer1, Goal1 and Goal2, Trace, Answer).

explore( Goal1 or Goal2, Trace, Answer)  :-
  exploreyes( Goal1, Trace, Answer)          % Positive answer to Goal1
  ;
  exploreyes( Goal2, Trace, Answer).         % Positive answer to Goal2

explore( Goal1 or Goal2, Trace, Answer1 and Answer2)  :-  !,
  not exploreyes( Goal1, Trace, _),
  not exploreyes( Goal2, Trace, _),          % No positive answer
  explore( Goal1, Trace, Answer1), 	     % Answer1 must be negative
  explore( Goal2, Trace, Answer2).           % Answer2 must be negative


explore( not Goal, Trace, Answer)  :-  !,    % Assuming no variables in Goal
  explore( Goal, Trace, Answer1),
  invert( Answer1, Answer).

explore( Goal, Trace, Goal is Answer was told)  :-
  useranswer( Goal, Trace, Answer).                 % User-supplied answer

exploreyes( Goal, Trace, Answer)  :-
  explore( Goal, Trace, Answer),
  positive( Answer).

continue( Answer1, Goal1 and Goal2, Trace, Answer)  :-
  positive( Answer1),
  explore( Goal2, Trace, Answer2),
  (  positive( Answer2), Answer = Answer1 and Answer2
     ;
     negative( Answer2), Answer = Answer2 ).

continue( Answer1, Goal1 and Goal2, _, Answer1)  :-
  negative( Answer1).

truth( Question is TruthValue was Found, TruthValue)  :-  !.

truth( Answer1 and Answer2, TruthValue)  :-
  truth( Answer1, true),
  truth( Answer2, true), !,
  TruthValue = true
  ;
  TruthValue = false.

positive( Answer)  :-
  truth( Answer, true).

negative( Answer)  :-
  truth( Answer, false).


invert( Quest is true was Found, (not Quest) is false was Found).

invert( Quest is false was Found, (not Quest) is true was Found).

instantiated( Term)  :-
  numbervars( Term, 0, 0).   	% No variables in Term


% useranswer( Goal, Trace, Answer):
%   Generate, through backtracking, user-supplied solutions to Goal.
%   Trace is a chain of ancestor goals and rules used for 'why' explanation

useranswer( Goal, Trace, Answer)  :-
  askable( Goal, _),                    % May be asked of the user
  freshcopy( Goal, Copy),               % Variables in Goal renamed
  useranswer( Goal, Copy, Trace, Answer, 1).

% Do not ask again about an instantiated goal

useranswer( Goal, _, _, _, N)  :-
  N > 1,		            % Repeated question?
  instantiated( Goal), !,
  fail.		                    % Do not ask again

% Is Goal implied true or false for all instantiations?

useranswer( Goal, Copy, _, Answer, _)  :-
  wastold( Copy, Answer, _),
  instance_of( Copy, Goal), !.	    % Answer to Goal implied


% Retrieve known solutions, indexed from N on, for Goal.

useranswer( Goal, _, _, true, N)  :-
  wastold( Goal, true, M),
  M >= N.

% Has everything already been said about Goal?

useranswer( Goal, Copy, _, Answer, N)  :-
  end_answers( Copy),
  instance_of( Copy, Goal), !,     % Everything was already said about Goal
  not wastold( Goal, _, _),        % There was no explicit answer
  Answer = false.                  % It follows Answer must be negative

% Ask the user for (more) solutions

useranswer( Goal, _, Trace, Answer, N)  :-
  askuser( Goal, Trace, Answer, N).

askuser( Goal, Trace, Answer, N)  :-
  askable( Goal, ExternFormat),
  format( Goal, ExternFormat, Question, [], Variables),    % Get question format
  ask( Goal, Question, Variables, Trace, Answer, N).

ask( Goal, Question, Variables, Trace, Answer, N)  :-
  nl,
  (  Variables = [], !, 	             % Introduce question
     write( 'Is it true: ')
     ;
     write( 'Any (more) solution to: ') 
  ),
  write( Question), write('? '), 
  getreply( Reply), !,                       % Reply = yes/no/why
  process( Reply, Goal, Question, Variables, Trace, Answer, N).


process( why, Goal, Question, Variables, Trace, Answer, N)  :-
  showtrace( Trace),
  ask( Goal, Question, Variables, Trace, Answer, N).

process( yes, Goal, _, Variables, Trace, true, N)  :-
  nextindex( Next),                          % Get new free index for 'wastold'
  Next1 is Next + 1,
  (  askvars( Variables),
     assertz( wastold( Goal, true, Next))              % Record solution
     ;
     copy_term( Goal, Copy),                           % Copy of Goal
     useranswer( Goal, Copy, Trace, Answer, Next1) ).  % More answers?

process( no, Goal, _, _, _, false, N)  :-
  freshcopy( Goal, Copy),
  wastold( Copy, true, _), !,               % 'no' means: no more solutions
  assertz( end_answers( Goal)),             % Mark end of answers
  fail
  ;
  nextindex( Next),                         % Next free index for 'wastold'
  assertz( wastold( Goal, false, Next)).    % 'no' means: no solution


format( Var, Name, Name, Vars, [Var/Name|Vars])  :-
  var( Var), !.

format( Atom, Name, Atom, Vars, Vars)  :-
  atomic( Atom),  !,
  atomic( Name).

format( Goal, Form, Question, Vars0, Vars)  :-
  Goal =.. [Functor|Args1],
  Form =.. [Functor|Forms],
  formatall( Args1, Forms, Args2, Vars0, Vars),
  Question =.. [Functor|Args2], !.

% If formatting failed due to structural difference format Goal after itself

format( Goal, _, Question, Vars0, Vars)  :-
  format( Goal, Goal, Question, Vars0, Vars).

formatall( [], [], [], Vars, Vars).

formatall( [X|XL], [F|FL], [Q|QL], Vars0, Vars)  :-
  formatall( XL, FL, QL, Vars0, Vars1),
  format( X, F, Q, Vars1, Vars).

askvars( []).

askvars( [Variable/Name|Variables])  :-
  nl, write( Name), write( ' = '), 
  read( Variable),
  askvars( Variables).

showtrace([])  :-
  nl, write('This was your question'), nl.

showtrace( [Goal by Rule | Trace])  :-
  nl, write( 'To investigate, by '),
  write( Rule), write( ', '),
  write( Goal),
  showtrace( Trace).

% instance-of( T1, T2) means: instance of T1 is T2; that is
% term T1 is more general than T2 or equally general as T2

instance_of( Term, Term1)  :-	% Instance of Term is Term1
  copy_term( Term1, Term2),	% Copy of Term1 with fresh set of variables
  numbervars( Term2, 0, _), !,
  Term = Term2.                 % This succeeds if Term1 is instance of Term

freshcopy( Term, FreshTerm)  :- % Make a copy of Term with variables renamed
  asserta( copy( Term)),
  retract( copy( FreshTerm)), !.


nextindex( Next)  :-            % Next free index for 'wastold'
  retract( lastindex( Last)), !,
  Next is Last + 1,
  assert( lastindex( Next)).

% Initialise dynamic procedures lastindex/1, wastold/3, end_answers/1

:- assert( lastindex( 0)),
   assert( wastold( dummy, false, 0)),
   assert( end_answers( dummy)).

% Displaying the conclusion of a consultation and 'how' explanation

present( Answer)  :-
  nl, showconclusion( Answer),
  nl, write( 'Would you like to see how?'),
  nl, 
  getreply( Reply),
  ( Reply = yes, !, show( Answer)
    ;
    true ).

showconclusion( Answer1 and Answer2)  :-  !,
  showconclusion( Answer1), write( ' and '),
  showconclusion( Answer2).

showconclusion( Conclusion was Found)  :-
  write( Conclusion).

% 'show' displays a complete soltuin tree

show( Solution)  :-
  nl, show( Solution, 0), !.            % Indent by 0

show( Answer1 and Answer2, H)  :-  !,   % Indent by H
  show( Answer1, H),
  tab( H), write(and), nl,
  show( Answer2, H).

show( Answer was Found, H)  :-          % Indent by H
  tab( H), writeans( Answer),           % Show conclusion
  nl, tab( H),
  write( '  was '),
  show1( Found, H).                     % Show evidence

show1( Derived from Answer, H)  :-  !,
  write( Derived), write(' from'),      % Show rule name
  nl, H1 is H + 4,
  show( Answer, H1).                    % Show antecedent

show1( Found, _)  :-                    % Found = 'told' or 'found as fact'
  write( Found), nl.

writeans( Goal is true)  :-  !,
  write( Goal).		                % Omit 'is true' on output

writeans( Answer)  :-                   % This is negative answer
  write( Answer).

means( why, why)  :-  !.
means( w,   why)  :-  !.

means( yes, yes)  :-  !.
means( y,   yes)  :-  !.

means( no,  no)   :-  !.
means( n,   no)   :-  !.

% Note: getreply should not be called with the argument instantiated

getreply( Meaning)  :-
  read( Reply),
  means( Reply, Meaning),  !;          % Reply means something?
  nl, write('Answer unknown, try again please!'),     % Handle bad reply
  nl, 
  getreply( Meaning).                  % Try again


member( X, [X|_]).

member( X, [_|L])  :-
  member( X, L).

numbervars( Term, N, Nplus1)  :-
  var( Term), !,                      % Variable?
  Term = var/N,
  Nplus1 is N + 1.

numbervars( Term, N, M)  :-
  Term =.. [Functor | Args],          % Structure or atomic
  numberargs( Args, N, M).

numberargs( [], N, N)  :-  !.

numberargs( [X | L], N, M)  :-
  numbervars( X, N, N1),
  numberargs( L, N1, M).

