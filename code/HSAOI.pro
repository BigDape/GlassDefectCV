#---------------------------------------------------------------------------------------
# Function：    玻璃检测仪
# debugger：    MSVC2017 64
#
# @Author     zsg
# @Time       2022/03/27
#---------------------------------------------------------------------------------------
TEMPLATE = subdirs

SUBDIRS += log \
           DataBase \
           algorithm \
           camera \
           communication \
           hstool \
           jsoncpp \

SUBDIRS += main test


