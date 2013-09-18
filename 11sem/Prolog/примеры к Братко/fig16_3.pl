% Figure 16.3  A knowledge base for identifying faults in an electric
% network such as the one in Figure 16.2.


% A small knowledge base for locating faults in an electric network

%  If a device is on and not working and its fuse is intact
%  then the device is broken.

broken_rule ::
		if
			on(Device)  and
			device( Device)  and
			(not working(Device))  and
			connected( Device, Fuse)  and
	                proved( intact( Fuse))
		then
                        proved( broken( Device)).

%  If a unit is working
%  then its fuse is OK.

fuse_ok_rule ::
		if
			connected( Device, Fuse)  and
			working( Device)
		then
                        proved( intact( Fuse)).


%  If two different devices are connected to a fuse and
%  are both on and not working then the fuse has failed.
%  NOTE: This assumes that at most one device is broken!

fused_rule ::
		if
			connected( Device1, Fuse)  and
			on( Device1)  and
			(not working( Device1))  and
			samefuse( Device2, Device1)  and
			on( Device2)  and
			(not working( Device2))
		then
                        proved( failed( Fuse)).


same_fuse_rule ::
		if
			connected( Device1, Fuse)  and
			connected( Device2, Fuse)  and
			different( Device1, Device2)
 		then
			samefuse( Device1, Device2).

device_on_rule ::
        if
              working( Device)
        then
              on( Device).


fact :: different( X, Y)   :-   not (X = Y).

fact :: device( heater).
fact :: device( light1).
fact :: device( light2).
fact :: device( light3).
fact :: device( light4).

fact :: connected( light1, fuse1).
fact :: connected( light2, fuse1).
fact :: connected( heater, fuse1).
fact :: connected( light3, fuse2).
fact :: connected( light4, fuse2).


askable( on(D), on('Device')).

askable( working(D), working('Device')).
