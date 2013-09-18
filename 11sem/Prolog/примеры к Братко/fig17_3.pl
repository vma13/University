%  Figure 17.3  A definition of the planning space for manipulating camera.


%  Planning space for getting camera ready
%  Opening the case
can( open_case, [camera_in_case]).
adds( open_case, [camera_outside_case]).
deletes( open_case, [camera_in_case]).

%  Closing the case

can( close_case, [camera_outside_case, slot_closed( film), slot_closed( battery)]).
adds( close_case, [camera_in_case]).
deletes( close_case, [camera_outside_case]).

%  Opening a slot

can( open_slot( X), [camera_outside_case, slot_closed( X)]).
adds( open_slot( X), [slot_open( X)]).
deletes( open_slot( X), [slot_closed( X)]).

%  Closing a slot

can( close_slot( X), [camera_outside_case, slot_open( X)]).
adds( close_slot( X), [slot_closed( X)]).
deletes( close_slot( X), [slot_open( X)]).

% Rewinding film

can( rewind, [camera_outside_case, in( film), film_at_end]).
adds( rewind, [film_at_start]).
deletes( rewind, [film_at_end]).

%  Removing battery or film

can( remove( battery), [slot_open( battery), in( battery)]).
can( remove( film), [slot_open( film), in( film), film_at_start]).
adds( remove( X), [slot_empty( X)]).
deletes( remove( X), [in( X)]).

%  Inserting new battery or film

can( insert_new( X), [slot_open( X), slot_empty( X)]).
adds( insert_new( battery), [in( battery), ok( battery)]).
adds( insert_new( film), [in( film), film_at_start, film_unused]).
deletes( insert_new( X), [slot_empty( X)]).

%  Taking pictures

can( take_pictures, [in( film), film_at_start, film_unused, 
  in( battery), ok( battery), slot_closed( film), slot_closed( battery)]).
adds( take_pictures, [film_at_end]).
deletes( take_pictures, [film_at_start, film_unused]).

%  A state with film used and battery weak (note: battery is
%  assumed weak because ok( battery) is not included in the state)

state1( [camera_in_case, slot_closed( film), slot_closed( battery),
  in( film), film_at_end, in( battery)]).

