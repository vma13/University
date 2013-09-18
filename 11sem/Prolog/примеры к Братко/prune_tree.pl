% Solution to Exercise 18.6

% prunetree( Tree, PrunedTree): PrunedTree is optimally pruned Tree
%    with respect to estimated classification error using Laplace estimate
%    Assume trees are binary:
%    Tree = leaf( Node, ClassFrequencyList), or
%    Tree = tree( Root, LeftSubtree, RightSubtree)

prunetree( Tree, PrunedTree)  :-
   prune( Tree, PrunedTree, Error, FrequencyList).

% prune( Tree, PrunedTree, Error, FrequencyList):
%    PrunedTree is optimally pruned Tree with classification Error,
%    FrequencyList is the list of frequencies of classes at root of Tree

prune( leaf( Node, FreqList), leaf( Node, FreqList), Error, FreqList)  :-
   static_error( FreqList, Error).

prune( tree( Root, Left, Right), PrunedT, Error, FreqList)  :-
   prune( Left, Left1, LeftError, LeftFreq),
   prune( Right, Right1, RightError, RightFreq),
   sumlists( LeftFreq, RightFreq, FreqList),   % Add corresponding elements
   static_error( FreqList, StaticErr),
   sum( LeftFreq, N1),
   sum( RightFreq, N2),
   BackedErr is ( N1*LeftError + N2*RightError) / ( N1 + N2),
   decide( StaticErr, BackedErr, Root, FreqList, Left1, Right1, Error, PrunedT).

% Decide to prune or not:

decide( StatErr, BackErr, Root, FreqL, _, _, StatErr, leaf( Root, FreqL))  :-
   StatErr =< BackErr, !.      % Static error smaller: prune subtrees 

% Otherwise do not prune:
decide( _, BackErr, Root, _, Left, Right, BackErr, tree( Root, Left, Right)).

% static_error( ClassFrequencyList, Error): estimated class. error

static_error( FreqList, Error)  :-       % Use Laplace estimate
   max( FreqList, Max),                  % Maximum number in FreqList
   sum( FreqList, All),                  % Sum of numbers in FreqList    
   number_of_classes( NumClasses),
   Error is ( All - Max + NumClasses - 1) / ( All + NumClasses).

sum( [], 0).

sum( [Number | Numbers], Sum)  :-
   sum( Numbers, Sum1),
   Sum is Sum1 + Number.

max( [X], X).

max( [X,Y | List], Max)  :-
   X > Y, !, max( [X | List], Max)
   ;
   max( [Y | List], Max).

sumlists( [], [], []).

sumlists( [X1 | L1], [X2 | L2], [X3 | L3])  :-
   X3 is X1 + X2,
   sumlists( L1, L2, L3).

% A tree

tree1( tree( a,                                           % Root
             tree( b, leaf( e, [3,2]), leaf( f, [1,0])),  % Left subtree    
             tree( c, tree( d, leaf( g, [1,1]), leaf( h,[0,1])), leaf(i,[1,0])))). 

number_of_classes( 2).

% Test query: ?-  tree1( Tree), prunetree( Tree, PrunedTree).
