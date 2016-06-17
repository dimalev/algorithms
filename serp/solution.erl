-module(solution).
-export([main/0]).

s(1, 1, 1, _MH) ->
    false;
s(X, Y, H, MH) when (X < H) and (H >= MH) ->
    (X < H + 1 - Y) or
      ((Y =< H div 2) and (H > MH) and s(X - H div 2, Y, H div 2, MH)) or
      ((Y > H div 2) and (H > MH) and s(X, Y - H div 2, H div 2, MH));
s(X, Y, H, MH) when (X >= H) and (H >= MH) ->
    (X > Y + H - 1) or
        ((Y =< H div 2) and (H > MH) and s(X - H div 2, Y, H div 2, MH)) or
        ((Y > H div 2) and (H > MH) and s(X - H, Y - H div 2, H div 2, MH)).

ps(L, P, H, MH) ->
    case s(P, L, H, MH) of
        true ->
            io:fwrite("_");
        false ->
            io:fwrite("1")
    end,
    case P < 2 * H - 1 of
        true ->
            ps(L, P + 1, H, MH);
        false ->
            case L < H of
                true ->
                    io:fwrite("~n"),
                    ps(L + 1, 1, H, MH);
                false ->
                    ok
            end
    end.


main() ->
%    {ok, [N]} = io:fread("", "~d"),
    N = 3,
    ps(1, 1, 32, 32 bsr N).
