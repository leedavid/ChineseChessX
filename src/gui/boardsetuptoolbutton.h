/****************************************************************************
*   Copyright (C) 2012 by Jens Nissen jens-chessx@gmx.net                   *
****************************************************************************/

#ifndef BOARDSETUPTOOLBUTTON_H
#define BOARDSETUPTOOLBUTTON_H

#include "piece.h"

#include <QLabel>
#include <QPixmap>

class BoardSetupToolButton : public QLabel
{
    Q_OBJECT
public:
    explicit BoardSetupToolButton(QWidget *parent = 0);
    void setBasePixmap(const QPixmap &pm);

    Piece piece() const;
    void setPiece(const Piece &piece);
    QPixmap BasePixmap() const;

signals:
    void signalDragStarted(QWidget*, QMouseEvent*);
    void signalClicked(Piece p);

public slots:
    void slotClearBackground(Piece p);
    void slotSetSelected();

protected:
    QPixmap m_pixmap;
    Piece m_piece;

    virtual int heightForWidth(int) const;
    virtual bool hasHeightForWidth() const;

    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseReleaseEvent(QMouseEvent * e);
    virtual void resizeEvent(QResizeEvent * e);
};

#endif // BOARDSETUPTOOLBUTTON_H
