#pragma once

#ifdef PRAC_TESTS
#include "../tests/model.h"
#include "../tests/view.h"
#else
#include "model.h"
#include "view.h"
#endif

class Controller {
public:

    // Напишите контроллер.
    Controller() {
        view_.SetNewgameCallback([this](size_t x , size_t y) {
            model_.Reset(x , y);
            view_.SetupField(x , y);
            UpdateStatus();
        });
        view_.SetMoveCallback([this](size_t x , size_t y) {
            auto symbol = model_.DoMove(x , y);
            if (symbol!= Symbol::kEmpty) {
                view_.UpdateCell(x , y , ::ToQString(symbol));
            }
            UpdateStatus();
        });
        model_.Reset(3 , 3);
        view_.SetupField(3 , 3);
        UpdateStatus();
        view_.show();
    }

    void UpdateStatus() {
        auto winner = model_.GetWinner();
        if (winner.has_value() && winner==Symbol::kEmpty) {
            view_.SetStatus("Ничья");
            view_.SetStatusStyle("red" , true);
        }
        else if(winner.has_value()) {
            auto winner = (model_.GetWinner() ==Symbol::kCross) ? 'x' : 'o';
            view_.SetStatus(QString("Выиграл %1").arg(winner));
            view_.SetStatusStyle("green" , true);
            auto vec_win = model_.GetWinnerPath();
            for (auto i : vec_win ) {
                view_.SetCellStyle(i.first , i.second , "green" , true);
            }
        }
        else {
            view_.SetStatus(QString("Ход игрока %1").arg(::ToQString(model_.GetNextPlayer())));
            view_.SetStatusStyle("black" , false);


        }
    }


private:
    Model model_;
    View view_;
};
