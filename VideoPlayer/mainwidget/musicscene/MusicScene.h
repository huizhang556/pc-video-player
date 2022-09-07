#ifndef MUSICSCENE_H
#define MUSICSCENE_H

#include <QWidget>

namespace Ui {
class MusicScene;
}

class MusicScene : public QWidget
{
    Q_OBJECT

public:
    explicit MusicScene(QWidget *parent = nullptr);
    ~MusicScene();
    void        initWorkUI();
    void        handleSignalsAndSlots();

private:
    Ui::MusicScene *ui;
};

#endif // MUSICSCENE_H
