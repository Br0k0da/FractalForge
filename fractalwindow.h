#ifndef FRACTALWINDOW_H
#define FRACTALWINDOW_H

#include <QQuickItem>
#include <QQuickWindow>

class FractalWindowRenderer;

class FractalWindow : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(float fScale READ fScale WRITE setFScale NOTIFY fScaleChanged FINAL)
    Q_PROPERTY(float xOffset READ xOffset WRITE setXOffset NOTIFY xOffsetChanged FINAL)
    Q_PROPERTY(float yOffset READ yOffset WRITE setYOffset NOTIFY yOffsetChanged FINAL)

    QML_ELEMENT
public:
    FractalWindow();

    void paintMandelbrot();

    QQuickWindow *windowElement() const;
    void setWindowElement(QQuickWindow *newWindowElement);

    // Геттер и Сеттер параметра scale
    float fScale() const;
    void setFScale(float newFScale);

    float yOffset() const;
    void setYOffset(float newYOffset);

    float xOffset() const;
    void setXOffset(float newXOffset);

public slots:
    void sync();
    void cleanup();

signals:
    void windowElementChanged();

    void fScaleChanged();

    void yOffsetChanged();

    void xOffsetChanged();

private slots:
    void handleWindowChanged(QQuickWindow* wnd);

private:
    void releaseResources() override;
    FractalWindowRenderer *m_renderer;
    QQuickWindow *m_windowElement = nullptr;

    // Приближение и отдаление фрактала
    float m_fScale = 1.0;
    float m_yOffset = 0.0;
    float m_xOffset = 0.0;
};

#endif // FRACTALWINDOW_H
