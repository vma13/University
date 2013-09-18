%  Figure 23.6  An object-oriented program about geometric figures.


/*                    polygon( [Side1, Side2, ...])
                         /              \
                       /                  \
       rectangle( Length, Width)      reg_polygon( Side, N)
                         \             /       \
                           \         /           \
                           square( Side)      pentagon( Side)
*/

object( polygon( Sides),
  [ ( perimeter( P)  :-
        sum( Sides, P) ) ] ).

object( reg_polygon( Side, N),
  [ ( perimeter( P)  :-
        P is Side * N),  
    ( describe  :-  write( 'Regular polygon') ) ] ).

object( square( Side),
  [ ( describe  :-
        write( 'Square with side '),
        write( Side) ) ] ).

object( rectangle( Length, Width),
  [ ( area( A)  :-  
        A is Length * Width),
    ( describe  :-
        write( 'Rectangle of size '),
        write( Length * Width) ) ] ).
     
object( pentagon( Side),
        [ ( describe  :- write( 'Pentagon') ) ] ).

isa( square( Side), rectangle( Side, Side)).

isa( square( Side), reg_polygon( Side, 4)).

isa( rectangle( Length, Width), polygon( [Length,Width,Length,Width])).

isa( pentagon( Side), reg_polygon( Side, 5)).

isa( reg_polygon( Side, N), polygon( L))  :-
  makelist( Side, N, L).

% makelist( Item, N, List)   if
%   List is the list in which Item appears N times 

makelist( _, 0, []).

makelist( Item, N, [Item | List])  :-
  N > 0, N1 is N - 1,
  makelist( Item, N1, List).

% sum( ListOfNumbers, Sum)  if
%   Sum is the sum of numbers in ListOfNumbers

sum( [], 0).

sum( [Number | Numbers], Sum)  :-
  sum( Numbers, Sum1),
  Sum is Sum1 + Number.
