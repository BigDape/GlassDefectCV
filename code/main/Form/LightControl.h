#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H


#include <QHBoxLayout>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "hstool.h"


#define RECIPE_FULLPATH "Recipes"
#define SYSTEM_PATH "Recipes/system.ini"

QT_BEGIN_NAMESPACE
namespace Ui {
class LightControl;
}
QT_END_NAMESPACE

namespace SocketNameSpace {
    class HSSocketInterface;
}


class LightControl : public QWidget
{
    Q_OBJECT

public:
    explicit LightControl( QWidget* parent = nullptr);
    ~LightControl();
    // 读取json工单到表单中
    void readRecipeToTable(std::string filePath);

private:
    // 初始化connect函数
    void initConnect();
    // 初始化函数
    bool InitLightControl();
    // 将当前的m_root写入到json文件中
    void writeCurrentRooterToJson();
    // 初始化输入框输入类型
    void initLineEditInputType();

private slots:
    void slotAllSet();
    void slotAllGet();
    void slotAllSave();
    void slotCreateRecipe();
    void slotTestConnect();
    void slotTrigger();
    void slotChangeRecipe(int index);

private:
    QTimer* timer;
    std::shared_ptr<QTimer> timer1;
    SignalControl m_signalctrl;
    std::unique_ptr<SocketNameSpace::HSSocketInterface> SocketObjectPtr;

private:
    Ui::LightControl* ui;
};

#endif // LIGHTCONTROL_H
