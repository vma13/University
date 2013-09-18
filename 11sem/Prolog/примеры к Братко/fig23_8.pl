%  Figure 23.8  An object-oriented program about a robot world.


% A robot world: table, blocks and camera

object( camera,
  [ look( a, 1, 1),            % Find XY-coord. of a visible block
    look( d, 3, 2),
    xy_coord( 2, 2),            % xy-coordinates of camera
    z_coord( 20)]).            % z-coordinate of camera

object( block( Block),
  [ ( xy_coord( X, Y)  :-
        send( camera, look( Block, X, Y))),
    ( xy_coord( X, Y)  :-
        send( Block, under( Block1)),
        send( Block1, xy_coord( X, Y))),
    ( z_coord( 0)  :-
        send( Block, on( table))),
    ( z_coord( Z)  :-
        send( Block, on( Block1)),
        send( Block1, z_coord( Z1)),
        Z is Z1 + 1)]).

object( physical_object( Name),
  [ (coord( X, Y, Z)  :-
       send( Name, xy_coord( X, Y)),
       send( Name, z_coord( Z)))]).

object( a, [ on(b)]).
object( b, [ under(a), on(c)]).
object( c, [ under(b), on(table)]).
object( d, [ on(table)]).

isa( a, block( a)).
isa( b, block( b)).
isa( c, block( c)).
isa( d, block( d)).
isa( block( Name), physical_object( Name)).
isa( camera, physical_object( camera)).
