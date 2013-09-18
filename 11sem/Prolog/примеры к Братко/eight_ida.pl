% State space definition to be used with IDA*
% Predicates needed are: s/2, f/2, goal/1
% To compute f, a node has also to include its search depth 

%  Problem-specific procedures for the 8-puzzle */

/* Current situation is represented as a list of positions
   of the tiles, with first item in the list corresponding
   to the empty square.

   Example:

   1   1 2 3          is represented by:
   2   8   4          [2/2, 1/3, 2/3, 3/3, 3/2, 3/1, 2/1, 1/1]
   3   7 6 5

       1 2 3

   'Empty' can move to any of its neighbours which means that
   'empty' and its neighbour interchange their positions.
*/

% Specification for A*

s( [Empty|L], [T|L1], 1)  :-       % All arc-costs are 1
   swap( Empty, T, L, L1).         % Swap Empty and T in L giving L1

s( State0, State)  :-             % Ignore cost
   s( State0, State, Cost).

swap( E, T, [T|L], [E|L])  :-
   d( E, T, 1).                   % Manhattan dist. between E and T is 1

swap( E, T, [T1|L], [T1|L1])  :-
   swap( E, T, L, L1).

d( X/Y, X1/Y1, D)  :-
   dif( X, X1, Dx),
   dif( Y, Y1, Dy),
   D is Dx + Dy.

dif( A, B, D)  :-
   D is A-B, D >= 0, !;
   D is B-A.

% Heuristic estimate h is the sum of distances of each tile
% from its 'home' square plus 3 times 'sequencing' score

h( [Empty|L], H)  :-
   goal([Empty1|G]),
   totdist( L, G, D),
   seq( L, S),
   H is D + 3*S.

totdist( [], [], 0).

totdist( [T|L], [T1|L1], D)  :-
   d( T, T1, D1),
   totdist( L, L1, D2),
   D is D1 + D2.

seq( [First|L], S)  :-
   seq( [First|L], First, S).

seq( [T1,T2|L], First, S)  :-
   score( T1, T2, S1),
   seq( [T2|L], First, S2),
   S is S1 + S2.

seq( [Last], First, S)  :-
   score( Last, First, S).

score( 2/2, _, 1)  :-  !.      % Tile in centre scores 1

score( 1/3, 2/3, 0)  :-  !.
score( 2/3, 3/3, 0)  :-  !.
score( 3/3, 3/2, 0)  :-  !.
score( 3/2, 3/1, 0)  :-  !.
score( 3/1, 2/1, 0)  :-  !.
score( 2/1, 1/1, 0)  :-  !.
score( 1/1, 1/2, 0)  :-  !.
score( 1/2, 1/3, 0)  :-  !.

score( _, _, 2).               % Tiles out of sequence

goal( [2/2,1/3,2/3,3/3,3/2,3/1,2/1,1/1,1/2]).

% Starting positions for some puzzles

start1( [2/2,1/3,3/2,2/3,3/3,3/1,2/1,1/1,1/2]).  % Requires 4 steps

start2( [2/1,1/2,1/3,3/3,3/2,3/1,2/2,1/1,2/3]).  % 5 steps

start3( [3/3,1/3,2/2,2/3,3/2,3/1,2/1,1/1,1/2]).  % 2 steps

start4( [2/2,2/3,1/3,3/1,1/2,2/1,3/3,1/1,3/2]).  % 18 steps

start5( [1/2,3/3,3/1,1/3,3/2,1/1,2/3,2/1,2/2]).  % 24 steps
      % H = totdist + 3*seq finds solution 38 steps long

% Display a solution path as a list of board positions

showsol([]).

showsol([P|L])  :-
   showsol(L),
   nl, write('---'),
   showpos(P).

%  Display a board position

showpos( [S0,S1,S2,S3,S4,S5,S6,S7,S8])  :-
   member( Y, [3,2,1]),        % Order of Y-coordinates
   nl, member( X, [1,2,3]),    % Order of X-coordinates
   member( Tile-X/Y, [' '-S0,1-S1,2-S2,3-S3,4-S4,5-S5,6-S6,7-S7,8-S8]),
   write(Tile),
   fail.          % Backtrack to next square

showpos([_|_]).

tile(S, [S0, S1, S2, S3, S4, S5, S6, S7, S8], Tile)  :-
   member( Tile/S,
      [' '/S0, 1/S1, 2/S2, 3/S3, 4/S4, 5/S5, 6/S6, 7/S7, 8/S8]).


% Specification of eight puzzle for IDA*

s( Depth:State, NewDepth:NewState)  :-
  s( State, NewState, _),
  NewDepth is Depth + 1.

f( Depth:[Empty|Tiles], F)  :-
  goal( [Empty0|Tiles0]),
  totdist( Tiles, Tiles0, Dist),    
  F is Depth + Dist.       % Use total dist. as heuristic function

goal( _:[2/2,1/3,2/3,3/3,3/2,3/1,2/1,1/1,1/2]).

% Initial states for IDA* are of the form 0:State, where State
% is a start state for A*

showpos( Depth:State)  :-
  showpos( State).

  

