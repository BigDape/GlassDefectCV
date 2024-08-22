#include "JsonRecipeWidget.h"
#include "Global.h"
#include "log_singleton.h"
#include "math.h"
#include "ui_JsonRecipeWidget.h"
#include<QDebug>
#include<QFormLayout>
#pragma execution_character_set("utf-8")

JsonRecipeWidget::JsonRecipeWidget(QWidget* parent, JsonParse2Map* RecipeParse,QString Ticketname)
    : QWidget(parent)
    , ui(new Ui::JsonRecipeWidget)
{
    ui->setupUi(this);
    CurrentRecipe = RecipeParse;
    ParamsListName<<"尺寸测量"<<"缺陷检测"<<"自定义参数";


    tickFileName="./Recipes/tickets/TicketCamera.json";


    tickName=Ticketname;
    InitTickData(tickName);

   // ParamsListName=name;
    InitWidgetLayout();
    this->setWindowTitle(Global::CurrentRecipe);
    InitRecipesInFiles();
    InitTreeWidget();
    connect(TreeWidget, &QTreeWidget::itemDoubleClicked, this,
        &JsonRecipeWidget::slot_ItemDoubleClicked);
    connect(TreeWidget, &QTreeWidget::itemClicked, this,
        &JsonRecipeWidget::slot_ItemSelected);
}

JsonRecipeWidget::~JsonRecipeWidget() { delete ui; }



void JsonRecipeWidget::InitTickData(QString TicketName)//初始化子项数目
{
    QFile file(tickFileName);
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()) {
        qDebug() << "Tick文件打开错误";
    }
    QString jsonString = QString(file.readAll());//json文件的全部内容(qstring)
    file.close();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    if (jsonDocument.isNull()) {
        qDebug() << "tickJson文件读取错误";
    }
    QJsonObject jsonObj;
    jsonObj=jsonDocument.object();
    QStringList jsonlist1=jsonObj.keys();
    QString a1=jsonObj[TicketName].toString();
    QStringList a2=a1.split(".",QString::SkipEmptyParts);
    if(TicketName=="相机"){
        int numPartToKeep=Global::camDefineNum;
        if(a2.size()>numPartToKeep){
            a2=a2.mid(0,numPartToKeep);
        }
    }
    ParamsListName=a2;
}

void JsonRecipeWidget::SaveTicketData()
{
    qDebug()<<"aaa";
    QString b1;
    for(const auto&it:ParamsListName){
        b1+=it+".";
    }
    qDebug()<<"b1"<<b1;

    QFile file(tickFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file.";
    }
    QByteArray jsonData = file.readAll();
    file.close();
    // 解析 JSON 数据
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull() || !jsonDoc.isObject())
        qDebug() << "Failed to parse JSON document.";
       // 获取 JSON 对象
    QJsonObject jsonObj = jsonDoc.object();
    jsonObj[tickName]=b1;
    jsonDoc=QJsonDocument(jsonObj);

    QString jsonstr = jsonDoc.toJson();

    // Write the updated JSON back to the file
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << jsonstr;
    file.close();
}


void JsonRecipeWidget::InitTreeWidget()
{
    if (TreeWidget->topLevelItemCount() > 0) {
        // 清除子项
        TreeWidget->clear();
    }
    QStringList HStrList;
    HStrList.push_back("参数");
    HStrList.push_back("数值");
    int HlableCnt = HStrList.count();

    TreeWidget->setColumnCount(HlableCnt);
    TreeWidget->setHeaderLabels(HStrList);
    TreeWidget->setColumnWidth(0, 200);
    for(int i=0;i<ParamsListName.size();i++){
        QTreeWidgetItem* rootItem=new QTreeWidgetItem(TreeWidget);
        rootItem->setText(0,ParamsListName[i]);
    }

    TreeWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ReadValue2Tree();
    TreeWidget->expandAll();
}

void JsonRecipeWidget::InitRecipesInFiles()
{
    cbx_RecipeSelect->clear();
    QString FoldPath = "Recipes";
    QDir Folder(FoldPath);
    QStringList Filters;
    Filters << "*.json";
    Folder.setNameFilters(Filters);

    QStringList FileNames;

    foreach (QString fileName, Folder.entryList(QDir::Files)) {
        QString baseName = QFileInfo(fileName).baseName();
        FileNames.append(baseName);
    }
    foreach (QString FileName, FileNames) {
        cbx_RecipeSelect->addItem(FileName);
    }
    qDebug()<<"Global::CurrentRecipe"<<Global::CurrentRecipe;
    int SelectIndex = cbx_RecipeSelect->findText(Global::CurrentRecipe);
    cbx_RecipeSelect->setCurrentIndex(SelectIndex);
}

void JsonRecipeWidget::InitWidgetLayout()
{
    cbx_RecipeSelect = new QComboBox(this);
    ui->Layout_head->setContentsMargins(10, 10, 10, 0);
    ui->Layout_head->addWidget(cbx_RecipeSelect);

    TreeWidget = new QTreeWidget(this);
    ui->Layout_table->setContentsMargins(10, 10, 10, 10);
    ui->Layout_table->addWidget(TreeWidget);

    btn_SelectRecipe = new QPushButton(this);
    btn_SelectRecipe->setText("选择");
    connect(btn_SelectRecipe, SIGNAL(clicked()), this, SLOT(SelectRecipe()));

    btn_NewRecipe = new QPushButton(this);
    btn_NewRecipe->setText("新建工单");
    connect(btn_NewRecipe, SIGNAL(clicked()), this, SLOT(CreateNewRecipe()));

    btn_DeleteRecipe = new QPushButton(this);
    btn_DeleteRecipe->setText("删除");
    connect(btn_DeleteRecipe, SIGNAL(clicked()), this, SLOT(DeleteRecipe()));

    btn_Read = new QPushButton(this);
    btn_Read->setText("读取");
    connect(btn_Read, SIGNAL(clicked()), this, SLOT(ReadValue2Tree()));

    btn_Save = new QPushButton(this);
    btn_Save->setText("保存");
    connect(btn_Save, SIGNAL(clicked()), this, SLOT(SaveValue2tree()));

    btn_NewParam = new QPushButton(this);
    btn_NewParam->setText("新建参数");
    connect(btn_NewParam, SIGNAL(clicked()), this, SLOT(GetNewParam()));

    btn_DeleteSingleParam = new QPushButton(this);
    btn_DeleteSingleParam->setText("删除元素");
    connect(btn_DeleteSingleParam, SIGNAL(clicked()), this,
        SLOT(DeleteSingleParam()));

    btn_CreateSon=new QPushButton(this);
    btn_CreateSon->setText("创建子项名称");
    connect(btn_CreateSon,&QPushButton::clicked,this,&JsonRecipeWidget::CreateNewSon);

    btn_DeleteTicket=new QPushButton(this);
    btn_DeleteTicket->setText("删除工单");
    connect(btn_DeleteTicket,&QPushButton::clicked,this,&JsonRecipeWidget::DeleteTick);

    ui->Layout_btns->setContentsMargins(10, 10, 10, 10);
    ui->Layout_btns->addWidget(btn_SelectRecipe);
    ui->Layout_btns->addWidget(btn_NewRecipe);
    ui->Layout_btns->addWidget(btn_DeleteRecipe);
    ui->Layout_btns->addWidget(btn_Read);
    ui->Layout_btns->addWidget(btn_Save);
    ui->Layout_btns->addWidget(btn_NewParam);
    ui->Layout_btns->addWidget(btn_DeleteSingleParam);
    ui->Layout_btns->addWidget(btn_CreateSon);
    ui->Layout_btns->addWidget(btn_DeleteTicket);
    ui->Layout_btns->setAlignment(Qt::AlignTop);
    lbl_OperationResult = new QLabel(this);
    ui->Layout_bottom->setContentsMargins(10, 0, 10, 0);
    ui->Layout_bottom->addWidget(lbl_OperationResult);
}



void JsonRecipeWidget::ReadParamsFromRecipe()
{
    CurrentRecipe->ReadParamsFromFile();
    CurrentRecipe->GetValueFromRecipes(ParamsListName,Params4ListAll);
}

void JsonRecipeWidget::SelectRecipe()
{
    if (cbx_RecipeSelect->currentText() == Global::CurrentRecipe) {
        lbl_OperationResult->setText("无需操作");
        return;
    }
    Global::CurrentRecipe=cbx_RecipeSelect->currentText();
    this->setWindowTitle(cbx_RecipeSelect->currentText());
    emit sig_DeliverName(cbx_RecipeSelect->currentText());
    HTuple CurrentRecipeHT=  Global::CurrentRecipe.toUtf8().constData();
    ReadDict("Recipes/"+ CurrentRecipeHT +".json", HTuple(), HTuple(), &Global::RecipeDict);
}

void JsonRecipeWidget::CreateNewRecipe()
{
    QDialog GetRecipeNameDialog;
    QLabel* Info = new QLabel("新建工单");
    QLineEdit* lineEdit = new QLineEdit(&GetRecipeNameDialog);
    QPushButton* Btn_Yes = new QPushButton("确定", &GetRecipeNameDialog);
    QString InputText = "";

    QObject::connect(Btn_Yes, &QPushButton::clicked, [&]() {
        GetRecipeNameDialog.setObjectName("新建工单");
        InputText = lineEdit->text();
        QString Inputlog = "用户输入: " + InputText;
        log_singleton::Write_Log(Inputlog, Log_Level::General);
        GetRecipeNameDialog.close();
    });

    QVBoxLayout* layout = new QVBoxLayout(&GetRecipeNameDialog);
    layout->addWidget(Info);
    layout->addWidget(lineEdit);
    layout->addWidget(Btn_Yes);

    // 显示对话框
    GetRecipeNameDialog.exec();

    //    qDebug() << InputText;

    if (InputText == "") {
        log_singleton::Write_Log("输入为空!", Log_Level::Error);
        return;
    }

    QString SourceFilePath = "Recipes/" + Global::CurrentRecipe + ".json";
    QString DestFilePath = "Recipes/" + InputText + ".json";

    log_singleton::Write_Log(SourceFilePath, Log_Level::General);
    if (QFile::copy(SourceFilePath, DestFilePath)) {
        log_singleton::Write_Log("文件复制成功", Log_Level::General);
        if (!QFile::exists(DestFilePath))
            log_singleton::Write_Log("文件不存在", Log_Level::Error);
    } else {
        log_singleton::Write_Log("文件复制失败", Log_Level::Error);
        return;
    }
    InitRecipesInFiles();
    int SelectIndex = cbx_RecipeSelect->findText(InputText);
    cbx_RecipeSelect->setCurrentIndex(SelectIndex);
    btn_SelectRecipe->click();
}

void JsonRecipeWidget::DeleteRecipe()
{
    if (Global::CurrentRecipe != cbx_RecipeSelect->currentText()) {

        QString filePath = "Recipes/" + cbx_RecipeSelect->currentText() + ".json"; // 文件路径
        QFile file(filePath);
        if (file.remove()) {
            lbl_OperationResult->setText("文件删除成功");
            log_singleton::Write_Log("文件删除成功", Log_Level::General);
        } else {
            lbl_OperationResult->setText("文件删除失败");
            log_singleton::Write_Log("文件删除失败", Log_Level::Error);
        }
        InitRecipesInFiles();
    } else {
        lbl_OperationResult->setText("不可删除当前工单!!!");
        log_singleton::Write_Log("不可删除当前工单!!!", Log_Level::Error);
    }
}

void JsonRecipeWidget::slot_RecipeChanged(JsonParse2Map* m_RecipeChanged)
{
    CurrentRecipe = m_RecipeChanged;
    CurrentRecipe->getParameter("相机0.帧次",Global::FramesPerTri);
    qDebug()<<"相机0.帧次"<<Global::FramesPerTri;
    Global::RecChangeSignal=true;
    //写入参数
    ReadValue2Tree();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    //到此为止切换配方完成
    emit sig_CameraParamsChangeRecipe();
    emit sig_LightControlChange();
    emit sig_RecipeChange();
}

void JsonRecipeWidget::ReadValue2Tree()
{
    //读取参数
    ReadParamsFromRecipe();
    //刷新前先清空
 //   int parentCount=TreeWidget->topLevelItemCount();
    int parentCount=ParamsListName.size();
    for(int i=0;i<parentCount;i++){
        QTreeWidgetItem* parentItem = TreeWidget->topLevelItem(i);
        // 清除所有子节点
       while (parentItem->childCount() > 0) {
           QTreeWidgetItem* child = parentItem->takeChild(0);
           delete child;
       }
       // 添加新子节点
       for (int j = 0; j < Params4ListAll[i].size(); j++) {
           QTreeWidgetItem* child = new QTreeWidgetItem(parentItem);
           child->setText(0, Params4ListAll[i][j].Name);
           child->setText(1, QString::number(Params4ListAll[i][j].Value));

           parentItem->addChild(child);
       }
    }
    TreeWidget->expandAll();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 工单: " + cbx_RecipeSelect->currentText() + " 参数已读取";
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();
}

void JsonRecipeWidget::SaveValue2tree()
{
    if(cbx_RecipeSelect->currentText()!=Global::CurrentRecipe){
        qDebug()<<"无法保存，因为当前工单不一致";
        lbl_OperationResult->setText("无法保存，因为当前工单不一致");
        return;
    }

    for(int i=0;i<ParamsListName.size();i++){
        QTreeWidgetItem*parent=TreeWidget->topLevelItem(i);
        for(int j=0;j<Params4ListAll[i].size();j++){
        //   Params4ListAll[i][j].Name=parent->child(j)->text(0);
           Params4ListAll[i][j].Value=parent->child(j)->text(1).toDouble();
          qDebug()<<ParamsListName[i]<<Params4ListAll[i][j].Name<<"Params4ListAll[i][j].Value"<<Params4ListAll[i][j].Value;
        }
    }
    CurrentRecipe->SetValue2Recipes(ParamsListName,Params4ListAll);
    CurrentRecipe->SaveParamsToFile();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 工单参数已保存";
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();

    HTuple CurrentRecipeHT=  Global::CurrentRecipe.toUtf8().constData();
    ReadDict("Recipes/"+ CurrentRecipeHT +".json", HTuple(), HTuple(), &Global::RecipeDict);

}

void JsonRecipeWidget::GetNewParam()
{
    QDialog dialog;
    dialog.setWindowTitle("新建工单参数");
    QLabel*label1=new QLabel("参数选择");
    QFormLayout*folayout=new QFormLayout(&dialog);
    QComboBox*combox=new QComboBox(&dialog);
    combox->addItems(ParamsListName);
    folayout->addRow(label1,combox);
    // 添加第二行，一个QLineEdit
    QLabel *label2 = new QLabel("输入名称");
    QLineEdit *lineEdit1 = new QLineEdit;
    folayout->addRow(label2, lineEdit1);

    QLabel *label3 = new QLabel("输入数据");
    QLineEdit *lineEdit2 = new QLineEdit;
    folayout->addRow(label3, lineEdit2);
    QPushButton*btn_yes=new QPushButton("确定",&dialog);
    folayout->addWidget(btn_yes);
    int index;
    QString InputName = "";
    QString InputValue = "";
    connect(btn_yes,&QPushButton::clicked,[&](){
        index=combox->currentIndex();
        qDebug()<<"index"<<index;
        InputName=lineEdit1->text();
        InputValue=lineEdit2->text();
        dialog.close();
        Key2Value newData;
        newData.Name=InputName;
        newData.Value=InputValue.toDouble();

        Params4ListAll[index].append(newData);

        QTreeWidgetItem*child=new QTreeWidgetItem(TreeWidget->topLevelItem(index));
        child->setText(0,InputName);
        child->setText(1,InputValue);
        TreeWidget->topLevelItem(index)->addChild(child);

        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 已新建参数，需要点击保存按钮后存入文件";
        log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

        lbl_OperationResult->setText(currentDateTimeString);
        lbl_OperationResult->adjustSize();

    });
    dialog.setLayout(folayout);
    dialog.exec();
}

void JsonRecipeWidget::DeleteSingleParam()
{
    if (SelectedisRootItem) {//点击工单时无效操作
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 无效操作";
        log_singleton::Write_Log(currentDateTimeString, Log_Level::General);
        lbl_OperationResult->setText(currentDateTimeString);
        lbl_OperationResult->adjustSize();
        return;
    }

    QString ElementDelete = SelectedParent + "." + SelectedName;
    CurrentRecipe->DeleteParameter(ElementDelete);
    CurrentRecipe->SaveParamsToFile();
    ReadValue2Tree();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 已删除元素";
    log_singleton::Write_Log(currentDateTimeString, Log_Level::General);

    lbl_OperationResult->setText(currentDateTimeString);
    lbl_OperationResult->adjustSize();
}

void JsonRecipeWidget::CreateNewSon()
{
    //比上面的qdialog要好用一些
    bool ok;
    QString str=QInputDialog::getText(this,"新建子项名称","子项名称:",QLineEdit::Normal,"",&ok);
    if(ok){
    ParamsListName<<str;
    int i=ParamsListName.size();
    QTreeWidgetItem* rootItem=new QTreeWidgetItem(TreeWidget);
    rootItem->setText(0,ParamsListName[i-1]);
    SaveTicketData();
    ReadValue2Tree();
    }
}

void JsonRecipeWidget::DeleteTick()
{
    if (SelectedisRootItem) {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString currentDateTimeString = currentDateTime.toString("hh:mm:ss") + " 删除子项";
        QMessageBox msgBox;
        msgBox.setText("是否删除当前子项");
        msgBox.setInformativeText("确定要执行这个操作吗?");
        msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret=msgBox.exec();
        if(ret==QMessageBox::Ok){
//            if(ParamsListName.contains(SelectedParent)){
//                QMessageBox::StandardButton ero;
//                ero=QMessageBox::critical(this,"错误","当前工单为系统工单，无法删除",QMessageBox::Ok);
//                return;
//            }
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this, "警告", "该操作无法撤回，确定要删除工单吗?", QMessageBox::Yes | QMessageBox::No);
            if(reply==QMessageBox::Yes){
                CurrentRecipe->DeleteParamTicket(SelectedParent);
                ParamsListName.removeAll(SelectedParent);
                SaveTicketData();
                InitTickData(tickName);
                CurrentRecipe->SaveParamsToFile();
                InitTreeWidget();

                log_singleton::Write_Log(currentDateTimeString, Log_Level::General);
                lbl_OperationResult->setText(currentDateTimeString);
                lbl_OperationResult->adjustSize();
            }
        }else if(ret==QMessageBox::Cancel){
            log_singleton::Write_Log("取消删除子项", Log_Level::General);
                        lbl_OperationResult->setText("取消删除子项");
                        lbl_OperationResult->adjustSize();
        }
        return;
    }
}


void JsonRecipeWidget::slot_ItemDoubleClicked(QTreeWidgetItem* item,
    int column)
{
    if (column == 1) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } else {
        item->setFlags(item->flags() & ~(Qt::ItemIsEditable));
    }


}

void JsonRecipeWidget::slot_ItemSelected(QTreeWidgetItem* item, int column)
{
    SelectedName = item->text(0);
    SelectedValue = item->text(1);
    if (item->parent() != nullptr) {
        SelectedParent = item->parent()->text(0);
        SelectedisRootItem = false;
    } else {
        SelectedParent =item->text(0);;
        SelectedisRootItem = true;
    }
    qDebug() << SelectedParent << "." << SelectedName << ". " << SelectedValue<<SelectedisRootItem;
}
