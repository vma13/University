% A toy knowledge base (Fig. 15.5 translated to Prolog)

if  kitchen_dry and hall_wet  then   leak_in_bathroom : 1.   % Certainty 1

if  hall_wet and bathroom_dry  then  problem_in_kitchen : 0.9.  % Certainty 0.9

if  window_closed or no_rain  then  no_water_from_outside : 1.

if  problem_in_kitchen and no_water_from_outside  then  leak_in_kitchen : 1.

given( window_closed, 0).
given( hall_wet, 1).
given( bathroom_dry, 1).
given( no_rain, 0.8).
given( kitchen_dry, 0).
