#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H


#include <QHBoxLayout>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>

#define RECIPE_FULLPATH "Recipes"
#define SYSTEM_PATH "Recipes/system.ini"

QT_BEGIN_NAMESPACE
namespace Ui {
class LightControl;
}
QT_END_NAMESPACE

class LightControl : public QWidget
{
    Q_OBJECT

public:
    explicit LightControl( QWidget* parent = nullptr);
    ~LightControl();
    // 创建新的空白工单文件
    QString createNewRecipeFile(QString recipeFileName);
    // 读取json工单到表单中
    void readRecipeToTable(std::string filePath);

    // 写入当前表单数据到工单文件中
    void writeTableToRecipe(QString filename);

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
    void slot_updateCode();
    //更新工单
    void slotUpdateRecipe(int index);
    //全部设置
    void slotAllSet();
    //全部保存
    void slotAllSave();
    //新建工单
    void slotCreateRecipe();
    //拷贝工单
    void slotCopyRecipe();
    //触发
    void slotTrigger();

private:
    QTimer* timer;
    std::shared_ptr<QTimer> timer1;
private:
    Ui::LightControl* ui;
};

#endif // LIGHTCONTROL_H
