#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QQuickItem>
#include <QQuickWindow>

class FractalWindowRenderer;

class FractalWindow : public QQuickItem
{
    Q_OBJECT

    // Q_PROPERTY(QQuickWindow* windowElement READ windowElement WRITE setWindowElement NOTIFY windowElementChanged REQUIRED FINAL)

    Q_PROPERTY(int xCoord READ xCoord WRITE setXCoord NOTIFY xCoordChanged REQUIRED FINAL)
    Q_PROPERTY(int yCoord READ yCoord WRITE setYCoord NOTIFY yCoordChanged REQUIRED FINAL)
    Q_PROPERTY(int zCoord READ zCoord WRITE setZCoord NOTIFY zCoordChanged REQUIRED FINAL)



    QML_ELEMENT
public:
    FractalWindow();

    void paintMandelbrot();

    QQuickWindow *windowElement() const;
    void setWindowElement(QQuickWindow *newWindowElement);

    int xCoord() const;
    void setXCoord(int newXCoord);

    int yCoord() const;
    void setYCoord(int newYCoord);

    int zCoord() const;
    void setZCoord(int newZCoord);

public slots:
    void sync();
    void cleanup();

signals:
    void windowElementChanged();

    void xCoordChanged();

    void yCoordChanged();

    void zCoordChanged();

private slots:
    void handleWindowChanged(QQuickWindow* wnd);

private:
    void releaseResources() override;
    FractalWindowRenderer *m_renderer;
    QQuickWindow *m_windowElement = nullptr;
    int m_xCoord;
    int m_yCoord;
    int m_zCoord;
};

#endif // FRACTALWINDOW_H
