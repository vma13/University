% Figure 2.16   Four versions of the predecessor program.


% Four versions of the predecessor program

% The original version

pred1( X, Z)  :-
   parent( X, Z).

pred1( X, Z)  :-
   parent( X, Y),
   pred1( Y, Z).

% Variation a: swap clauses of the original version

pred2( X, Z)  :-
   parent( X, Y),
   pred2( Y, Z).

pred2( X, Z)  :-
   parent( X, Z).

% Variation b: swap goals in second clause of the original version

pred3( X, Z)  :-
   parent( X, Z).

pred3( X, Z)  :-
   pred3( X, Y),
   parent( Y, Z).

% Variation c: swap goals and clauses of the original version

pred4( X, Z)  :-
   pred4( X, Y),
   parent( Y, Z).

pred4( X, Z)  :-
   parent( X, Z).



