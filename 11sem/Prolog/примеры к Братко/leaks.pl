% A toy knowledge base (Fig. 15.5 translated to Prolog)

if  kitchen_dry and hall_wet  then   leak_in_bathroom.

if  hall_wet and bathroom_dry  then  problem_in_kitchen.

if  window_closed or no_rain  then  no_water_from_outside.

if  problem_in_kitchen and no_water_from_outside  then  leak_in_kitchen.


% Declare fact/1 as a dynamic predicate to enable assert for this predicate

:- dynamic fact/1.

fact( window_closed).
fact( hall_wet).
fact( bathroom_dry).
