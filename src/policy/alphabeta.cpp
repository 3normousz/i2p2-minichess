#include <cstdlib>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

#include "../state/state.hpp"
#include "./alphabeta.hpp"

int alphabeta(State *state, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0)
    {
        return state->evaluate();
    }
    int value;
    if (maximizingPlayer)
    {
        value = INT_MIN;
        for (auto move : state->legal_actions)
        {
            value = max(value, alphabeta(state->next_state(move), depth - 1, alpha, beta, false));
            alpha = max(alpha, value);
            if (alpha >= beta)
            {
                break;
            }
        }
        return value;
    }
    else
    {
        value = INT_MAX;
        for (auto move : state->legal_actions)
        {
            value = min(value, alphabeta(state->next_state(move), depth - 1, alpha, beta, true));
            beta = min(beta, value);
            if (beta <= alpha)
            {
                break;
            }
        }
        return value;
    }
}

Move Alphabeta::get_move(State *state, int depth)
{
    Move best_move = state->legal_actions[0];
    int best_score = INT_MIN;

    for (size_t i = 1; i < state->legal_actions.size(); ++i)
    {
        Move move = state->legal_actions[i];
        State *next_state = state->next_state(move);
        int score = alphabeta(next_state, depth, INT_MIN, INT_MAX, false);
        if (score > best_score)
        {
            best_move = move;
            best_score = score;
        }
    }
    return best_move;
};