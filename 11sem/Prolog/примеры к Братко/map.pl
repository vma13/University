%  A road-map path-finding problem

%  The interesting probem is path from s to t

s( X, Y, C)  :-  c( X, Y, C); c( Y, X, C).

c( s, a, 2).  c( a, b, 2).  c( b, c, 2).  c( c, d, 3).

c( d, t, 3).  c( t, g, 2).  c( g, f, 2).  c( f, e, 5).

c( e, s, 2).

goal(t).

% heuristic estimates are the direct distances to t

h( s, 7).   h( a, 5).  h( b, 4).  h( c, 4).  h( d, 3).

h( e, 7).   h( f, 4).  h( g, 2).  h( t, 0).
