% Figure 4.5  A flight route planner and an example flight timetable.


% A FLIGHT ROUTE PLANNER

:-  op( 50, xfy, :).

% route( Place1, Place2, Day, Route):
%    Route is a sequence of flights on Day, starting at Place1, ending at Place2

route( P1, P2, Day, [ P1 / P2 / Fnum / Deptime ] )  :-    % Direct flight   
  flight( P1, P2, Day, Fnum, Deptime, _).

route( P1, P2, Day, [ (P1 / P3 / Fnum1 / Dep1) | RestRoute] )  :-    % Indirect connection   
  route( P3, P2, Day, RestRoute),
  flight( P1, P3, Day, Fnum1, Dep1, Arr1),
  deptime( RestRoute, Dep2),                                        % Departure time of Route   
  transfer( Arr1, Dep2).                                        % Enough time for transfer 

flight( Place1, Place2, Day, Fnum, Deptime, Arrtime)  :-
   timetable( Place1, Place2, Flightlist),
   member( Deptime / Arrtime / Fnum / Daylist , Flightlist),
   flyday( Day, Daylist).

flyday( Day, Daylist)  :-
   member( Day, Daylist).

flyday( Day, alldays)  :-
   member( Day, [mo,tu,we,th,fr,sa,su] ).

deptime( [ P1 / P2 / Fnum / Dep | _], Dep).

transfer( Hours1:Mins1, Hours2:Mins2)  :-
   60 * (Hours2 - Hours1) + Mins2 - Mins1 >= 40.

member( X, [X | L] ).

member( X, [Y | L] )  :-
   member( X, L).


% A FLIGHT DATABASE

timetable( edinburgh, london,
           [  9:40 / 10:50 / ba4733 / alldays,
             13:40 / 14:50 / ba4773 / alldays,
             19:40 / 20:50 / ba4833 / [mo,tu,we,th,fr,su] ] ). 

timetable( london, edinburgh,
           [  9:40 / 10:50 / ba4732 / alldays,
             11:40 / 12:50 / ba4752 / alldays,
             18:40 / 19:50 / ba4822 / [mo,tu,we,th,fr] ] ). 

timetable( london, ljubljana,
           [ 13:20 / 16:20 / jp212 / [mo,tu,we,fr,su],
             16:30 / 19:30 / ba473 / [mo,we,th,sa] ] ). 

timetable( london, zurich,
           [  9:10 / 11:45 / ba614 / alldays,
             14:45 / 17:20 / sr805 / alldays ] ). 

timetable( london, milan,
           [  8:30 / 11:20 / ba510 / alldays,
             11:00 / 13:50 / az459 / alldays ] ). 

timetable( ljubljana, zurich,
           [ 11:30 / 12:40 / jp322 / [tu,th] ] ). 

timetable( ljubljana, london,
           [ 11:10 / 12:20 / jp211 / [mo,tu,we,fr,su],
             20:30 / 21:30 / ba472 / [mo,we,th,sa] ] ). 

timetable( milan, london,
           [  9:10 / 10:00 / az458 / alldays,
             12:20 / 13:10 / ba511 / alldays ] ). 

timetable( milan, zurich,
           [  9:25 / 10:15 / sr621 / alldays,
             12:45 / 13:35 / sr623 / alldays ] ). 

timetable( zurich, ljubljana,
           [ 13:30 / 14:40 / jp323 / [tu,th] ] ). 

timetable( zurich, london,
           [ 9:00 / 9:40 / ba613 / [mo,tu,we,th,fr,sa],
            16:10 / 16:55 / sr806 / [mo,tu,we,th,fr,su] ] ). 

timetable( zurich, milan,
           [ 7:55 / 8:45 / sr620 / alldays ] ).


query3(City1,City2,City3,FN1,FN2,FN3,FN4)  :-
  permutation( [milan,ljubljana,zurich],[City1,City2,City3]),
  flight( london, City1, tu, FN1, Dep1, Arr1),
  flight( City1, City2, we, FN2, Dep2, Arr2),
  flight( City2, City3, th, FN3, Dep3, Arr3),
  flight( City3, london, fr, FN4, Dep4, Arr4).

conc([], L, L).

conc([X|L1],L2, [X|L3]) :-
  conc(L1,L2,L3).

permutation( [], []).

permutation( L, [X | P])  :-
  del( X, L, L1),
  permutation( L1, P).

del( X, [X|L], L).

del( X, [Y|L], [Y|L1])  :-
  del( X, L, L1).



