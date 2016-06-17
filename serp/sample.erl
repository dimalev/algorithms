-module(sample).
-export([main/0]).

f(0) ->
    true;
f(X) ->
    io:fwrite("called with ~w~n", [X]),
    (X > 3) and (f(X - 1)).

main() ->
    f(4).
