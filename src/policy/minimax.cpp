#include <cstdlib>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

#include "../state/state.hpp"
#include "./minimax.hpp"

int minimax(State *state, int depth, bool maximizingPlayer)
{
    if (depth == 0 || state->game_state != GameState::UNKNOWN)
    {
        return state->evaluate();
    }

    int value;
    if (maximizingPlayer)
    {
        value = INT_MIN;
        for (auto move : state->legal_actions)
        {
            value = max(value, minimax(state->next_state(move), depth - 1, false));
        }
        return value;
    }
    else
    {
        value = INT_MAX;
        for (auto move : state->legal_actions)
        {
            value = min(value, minimax(state->next_state(move), depth - 1, true));
        }
        return value;
    }
};

Move Minimax::get_move(State *state, int depth)
{
    Move best_move = state->legal_actions[0];
    int best_score = INT_MIN;

    for (size_t i = 1; i < state->legal_actions.size(); ++i)
    {
        Move move = state->legal_actions[i];
        State *next_state = state->next_state(move);
        int score = minimax(next_state, depth, true);
        if (score > best_score)
        {
            best_move = move;
            best_score = score;
        }
    }
    return best_move;
};