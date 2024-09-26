#include "log.h"
#include <QDebug>
#include "log4qt/basicconfigurator.h"
#include "log4qt/logger.h"
#include "log4qt/consoleappender.h"
#include "log4qt/patternlayout.h"
#include "log4qt/propertyconfigurator.h"
#include "log4qt/loggerrepository.h"
#include "log4qt/logmanager.h"
#include "log4qt/dailyfileappender.h"
#include <QFile>

/*********
 *   \li c{section_count} : logger name with optional parameter section_count. Section count from end of logger name, sections delimiter is "::";
        \li d{format_string} : date with optional parameters in "{}"-brackets which used by QDateTime::toString();
        \li m : message
        \li p : level name
        \li r : relative date/time to start application
        \li t : thread name
        \li x : ndc name
        \li X : mdc name
        \li F : file name
        \li M : method name
        \li L : line number
****/



/**
 * @brief Log::Log
 */
Log::Log()
{
     qDebug()<<"==> log";
}


void Log::test()
{

    try {
        //Logger：记录器，有一个根Logger，可以有多个其他Logger
           Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger(); //根Logger，name为root
           //Log4Qt::Logger *mylog1 = Log4Qt::Logger::logger("Mylog1");  //其他Logger，name为Mylog1的
           logger->setLevel(Log4Qt::Level::DEBUG_INT); //设置日志输出级别
           Log4Qt::LogManager::setHandleQtMessages(true); //处理qt调试输出信息，将qDebug之类的信息重定向，不开启这个qDebug()、qWri

           /****************PatternLayout配置日志的输出格式****************************/
           Log4Qt::PatternLayout *layout = new Log4Qt::PatternLayout();
           layout->setConversionPattern("[%d{yyyy-MM-dd hh:mm:ss.zzz}][%t][%p][%c](%F:%L in %M): %m %n");
           layout->activateOptions(); // 激活Layout

           /***************************配置日志的输出位置***********/
           //ConsoleAppender：输出到控制台
           Log4Qt::ConsoleAppender *appender = new Log4Qt::ConsoleAppender(layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
           appender->activateOptions();
           logger->addAppender(appender);

           //DailyFileAppender：每天新建一个文件，保存当天的日志，超过指定的天数，删除最开始的日志
           Log4Qt::DailyFileAppender *dailiAppender = new Log4Qt::DailyFileAppender;
           dailiAppender->setLayout(layout); //设置输出格式
           dailiAppender->setFile("logFile.log"); //日志文件名：固定前缀
           dailiAppender->setDatePattern("_yyyy_MM_dd"); //日志文件名：根据每天日志变化的后缀
           dailiAppender->setAppendFile(true); //true表示消息增加到指定文件中，false则将消息覆盖指定的文件内容，默认值是false
           dailiAppender->setKeepDays(30); //设置保留天数
           dailiAppender->activateOptions();
           logger->addAppender(dailiAppender);


           logger->error("12333");
    } catch (...) {
        qDebug()<<"456";
    }


}
