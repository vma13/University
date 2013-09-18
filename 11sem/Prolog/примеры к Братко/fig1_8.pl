% Figure 1.8   The family program.


parent( pam, bob).       % Pam is a parent of Bob
parent( tom, bob).
parent( tom, liz).
parent( bob, ann).
parent( bob, pat).
parent( pat, jim).

female( pam).            % Pam is female
male( tom).              % Tom is male
male( bob).
female( liz).
female( ann).
female( pat).
male( jim).

offspring( Y, X)  :-     % Y is an offspring of X if
   parent( X, Y).        % X is a parent of Y

mother( X, Y)  :-        % X is the mother of Y if
   parent( X, Y),        % X is a parent of Y and
   female( X).           % X is female

grandparent( X, Z)  :-   % X is a grandparent of Z if
   parent( X, Y),        % X is a parent of Y and
   parent( Y, Z).        % Y is a parent of Z

sister( X, Y)  :-        % X is a sister of Y if
   parent( Z, X),
   parent( Z, Y),        % X and Y have the same parent and
   female( X),           % X is female and
   different( X, Y).     % X and Y are different

predecessor( X, Z)  :-   % Rule prl: X is a predecessor of Z
   parent( X, Z).

predecessor( X, Z)  :-   % Rule pr2: X is a predecessor of Z
   parent( X, Y),
   predecessor( Y, Z).

