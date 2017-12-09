

#ifndef REVERSI_HUMANPLAYER_H
#define REVERSI_HUMANPLAYER_H


#include "Player.h"

class HumanPlayer: public Player {
public:
    /************************************************************************
   * Name: HumanPlayer (Constructor)
   * Input: t- The player's token
   * Output: -
   * Operation: Matches a player with a token
   *************************************************************************/
    HumanPlayer(const Value t);
    /************************************************************************
    * Name: ~HumanPlayer (Destructor)
    * Input: -
    * Output: -
    * Operation: Not in use right now
    *************************************************************************/
    ~HumanPlayer();
    /************************************************************************
    * Name: MakeTurn
    * Input: -
    * Output: -
    * Operation: Gets a row and a col from the human player and makes a move
    *************************************************************************/
    virtual Coordinate makeTurn(Logic* l, Board* b, Printer* printer, set<Coordinate> availableMoves) const;
    virtual void startTurn(Printer* printer) const;
    virtual void cantMove(Printer* printer) const;
};


#endif //REVERSI_HUMANPLAYER_H
