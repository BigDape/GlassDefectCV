/*******************************************
    @ClassName   : TitleBar
    @Description : 标题栏
    @Creator     : Chengwenjie
    @Author      : Chengwenjie
    @Date        : 2023-08-08
********************************************/
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(QWidget* parent = nullptr);

public slots:
    // 更新工单名称
    void slotUpdateRecipe(QString name);
    // 更新系统名称
    void slotUpdateSystem(QString name);

private:
    std::shared_ptr<QLabel> m_pIconLabel;
    std::shared_ptr<QLabel> m_pTitleLabel;
    std::shared_ptr<QLabel> m_CurrentRecipeLabel;//工单标签

};

#endif // TITLEBAR_H
