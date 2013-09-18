% Induction of decision trees (program sketched on pages 466-468)
% Below, the scetched program was completed by adding some missing parts 

% Note: This program does not pay any attention to efficiency!

     induce_tree( Tree)  :-
        findall( example( Class, Obj), example( Class, Obj), Examples),
        findall( Att, attribute( Att, _ ), Attributes),
        induce_tree( Attributes, Examples, Tree).

% The form of the tree depends on the following three cases:

% (1) Tree = null if the example set is empty.
% (2) Tree = leaf( Class) if all of the examples are of the same class Class.
% (3) Tree = tree( Attribute, [ Val1 : SubTree1, Val2 : Subtree2, ...]) if examples 
%     belong to more than one class, 
%     Attribute is the root of the tree, 
%     Val1, Val2, ... are Attribute's values, and 
%     SubTree1, SubTree2, ... are the corresponding decision subtrees.

% These three cases are handled by the following three clauses:

% induce_tree( Attributes, Examples, Tree)

   induce_tree( _, [], null)  :-  !.

   induce_tree( _, [example( Class,_ ) | Examples], leaf( Class))  :-
     not ( member( example( ClassX, _), Examples),           % No other example
           ClassX \== Class), !.                             % of different class
   
   induce_tree( Attributes, Examples, tree( Attribute, SubTrees))  :-
     choose_attribute( Attributes, Examples, Attribute), !,
     del( Attribute, Attributes, RestAtts),                  % Delete Attribute
     attribute( Attribute, Values),
     induce_trees( Attribute, Values, RestAtts, Examples, SubTrees).

   induce_tree( _, Examples, leaf( ExClasses))  :-     % No (useful) attribute, leaf with class distr.
     findall( Class, member( example( Class, _), Examples), ExClasses). 

% induce_trees( Att, Values, RestAtts, Examples, SubTrees):
%   induce decision SubTrees for subsets of Examples according to Values of Attribute

   induce_trees( _, [], _, _, [] ).     % No attributes, no subtrees

   induce_trees( Att, [Val1 | Vals], RestAtts, Exs, [Val1 : Tree1 | Trees])  :-
     attval_subset( Att = Val1, Exs, ExampleSubset),
     induce_tree( RestAtts, ExampleSubset, Tree1),
     induce_trees( Att, Vals, RestAtts, Exs, Trees).

% attval_subset( Attribute = Value, Examples, Subset):
%   Subset is the subset of examples in Examples that satisfy the condition Attribute = Value:

   attval_subset( AttributeValue, Examples, ExampleSubset)  :-
     findall( example( Class, Obj),
              ( member( example( Class, Obj), Examples),
                satisfy( Obj, [ AttributeValue])),
              ExampleSubset).

% satisfy( Object, Description):
%   defined as in Figure 18.11. 

satisfy( Object, Conj)  :-
   not ( member( Att = Val, Conj),
         member( Att = ValX, Object),
         ValX \== Val).

% choose_attribute selects the attribute that discriminates well among the classes. 
% This involves the impurity criterion. The following clause minimizes the chosen 
% impurity measure using setof. 
% setof will order the available attributes according to increasing impurity

   choose_attribute( Atts, Examples, BestAtt)  :-
     setof( Impurity/Att,
            ( member( Att, Atts), impurity1( Examples, Att, Impurity)),
            [ MinImpurity/BestAtt | _] ).

% impurity1( Examples, Attribute, Impurity):
%   implements a chosen impurity measure. 
%   Impurity is the combined impurity of the subsets of examples after 
%   dividing the list Examples according to the values of Attribute.
%   

impurity1( Exs, Att, Imp)  :-
  attribute( Att, AttVals),
  term_sum( Exs, Att, AttVals, 0, Imp).  % Weighted sum of impurities over att. values

% term_sum( Exs, Att, AttVals, PartialSum, Sum)

term_sum( _, _, [], Sum, Sum).

term_sum( Exs, Att, [Val | Vals], PartSum, Sum)  :-
  length( Exs, N),
  findall( C, (member( example(C,Desc), Exs), satisfy( Desc, [Att=Val])), ExClasses),
     % ExClasses = list of the classes (with repetitions) of all the examples with Att=Val
  length( ExClasses, NV), NV > 0, !,
  findall( P, 
           ( bagof( 1, member( Class, ExClasses), L), length( L, NVC), P is NVC/NV),
           ClassDistribution),
  gini( ClassDistribution, Gini),
  NewPartSum is PartSum + Gini*NV/N,
  term_sum( Exs, Att, Vals, NewPartSum, Sum)
  ;
  term_sum( Exs, Att, Vals, PartSum, Sum).      % Here no example satisfied Att = Val

% gini( ProbabilityList, GiniIndex)
%    GiniIndex = SUM Pi*Pj over all i, j such that i \= j
%    This is equivalent to:
%    GiniIndex = 1 - SUM Pi*Pi over all i

gini( Probs, Index)  :-
  square_sum( Probs, 0, SquareSum),
  Index is 1 - SquareSum.

square_sum( [], S, S).

square_sum( [P | Ps], PartS, S)  :-
  NewPartS is PartS + P*P,
  square_sum( Ps, NewPartS, S).


  


