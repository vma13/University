% File energy.pl: An oscillator model with energy constraint 
% (alternative to one in Fig. 20.14).

legalstate( [ X, V, A])  :-
     deriv( X, V),
     deriv( V, A),
     MinusA = a:_,
     sum( A, MinusA, a:zero/std),              % MinusA = -A
     mplus( X, MinusA),                        % Spring pulling block back
     energy( X, V).                            % Weak energy conserv. constraint

   energy( X, V)  :-  
      V = v:v0/_, !, X = x:zero/_              % If V=v0, X must be zero
      ;
      X = x:zero/_, !, V = v:minf..zero/_      % Here V must be -v0
      ;
      true.                                    % Otherwise X non-zero, no constraint on V
